#!/usr/bin/env python3
"""
AMMOcoin v1.0 → v1.1 migration: step 3 of 3 — BROADCAST.

Reads a signed-distribution.json (produced by migration-sign-offline.py)
and broadcasts each signed tx via the local online daemon's
`sendrawtransaction` RPC.

Safety:
  * Validates every signed tx with `decoderawtransaction` before sending.
  * Cross-checks outputs against the batch's expected recipients.
  * Pauses BATCH_PAUSE_SEC between batches and waits for inclusion in
    the mempool before moving on.
  * Operator must type 'BROADCAST' to begin.
  * Resumable: a batch whose exact txid is already in the mempool or in a
    block is marked SENT in the audit log and skipped, so a part-sent file
    can simply be broadcast again. A batch whose input was spent by a
    DIFFERENT transaction is still STALE and stops the run.
    --no-skip-sent restores the old strict behavior (stop at any spent input).
  * Cold-stake (P2CS) outputs recorded by migration-prepare.py are checked
    script-for-script against the signed transaction.

Usage:
    python3 migration-broadcast.py \\
        --input signed-distribution.json \\
        --cli "ammocoin-cli -datadir=/path/to/builder" \\
        --pause 30
"""

import argparse
import json
import os
import shlex
import subprocess
import sys
import time
from datetime import datetime
from decimal import Decimal
from pathlib import Path


ALREADY_SENT_ERRORS = ("transaction already in block chain", "txn-already-in-mempool", "txn-already-known")


def cli_argv(binary: str) -> list[str]:
    """Split like the other migration scripts (shlex), so "ammocoin-cli -datadir=/x"
    works; a path that exists as given (even with spaces) is one program, as before."""
    if os.path.exists(binary):
        return [binary]
    argv = shlex.split(binary)
    if not argv:
        raise ValueError("empty node CLI command")
    return argv


def cli(binary: str, *args: str) -> str:
    proc = subprocess.run([*cli_argv(binary), *args], capture_output=True, text=True, timeout=60)
    if proc.returncode != 0:
        raise RuntimeError(f"ammocoin-cli {' '.join(args)} failed: {proc.stderr.strip()}")
    return proc.stdout.strip()


def verify_signed_batch(binary: str, batch: dict) -> None:
    decoded = json.loads(cli(binary, "decoderawtransaction", batch["signed_hex"]))
    if decoded["txid"] != batch.get("signed_txid"):
        raise RuntimeError(
            f"Batch {batch['batch_index']}: txid mismatch "
            f"(signed_txid={batch['signed_txid']}, decoded={decoded['txid']}). "
            "The signed file may have been tampered with."
        )
    # Cross-check expected outputs vs what's in the signed tx.
    expected = {a: float(v) for a, v in batch["outputs"].items()}
    seen: dict[str, float] = {}
    for v in decoded.get("vout", []):
        spk = v.get("scriptPubKey", {})
        for addr in spk.get("addresses", []) or ([spk["address"]] if "address" in spk else []):
            seen[addr] = seen.get(addr, 0.0) + float(v["value"])
    for addr, amt in expected.items():
        if abs(seen.get(addr, 0.0) - amt) > 0.00000001:
            raise RuntimeError(
                f"Batch {batch['batch_index']}: signed tx output for {addr} "
                f"is {seen.get(addr, 0.0):.8f}, expected {amt:.8f}. ABORT."
            )
    # Cold-stake outputs: the exact P2CS script (owner + staker), not just the owner address.
    for owner, c in (batch.get("cold_stake") or {}).items():
        hits = [v for v in decoded.get("vout", [])
                if v.get("scriptPubKey", {}).get("hex") == c["script_hex"]
                and abs(float(v["value"]) - float(c["amount"])) <= 0.00000001]
        if len(hits) != 1:
            raise RuntimeError(
                f"Batch {batch['batch_index']}: cold-stake output for {owner} (staker {c['staker']}) "
                "is not in the signed tx as built. ABORT."
            )


def label(batch: dict) -> str:
    i = batch["batch_index"]
    return f"batch {i + 1}" if isinstance(i, int) else str(i)


def stale_inputs(binary: str, batch: dict) -> list[str]:
    """Inputs already spent (on chain or in the mempool). Fan-out inputs are
    cold-staked reserve outputs, so a stake can spend one between build and
    broadcast; rerun migration-prepare.py --fan-out, which funds only what is
    still missing."""
    decoded = json.loads(cli(binary, "decoderawtransaction", batch["signed_hex"]))
    gone = []
    for vin in decoded.get("vin", []):
        if not cli(binary, "gettxout", vin["txid"], str(vin["vout"]), "true"):
            gone.append(f"{vin['txid']}:{vin['vout']}")
    return gone


def already_sent(binary: str, txid: str) -> dict | None:
    """This exact transaction already in the mempool or in a block of the active
    chain? Returns {"where": "mempool"|"block", "confirmations": n} or None.
    Read-only: getrawtransaction (mempool, or chain with txindex=1), then the
    wallet's watch-only view (gettransaction) for confirmed txs."""
    try:
        info = json.loads(cli(binary, "getrawtransaction", txid, "1"))
        if info.get("txid") == txid:
            if "blockhash" not in info:
                return {"where": "mempool", "confirmations": 0}
            if int(info.get("confirmations", 0)) >= 1:  # 0 with a blockhash = block not in the active chain
                return {"where": "block", "confirmations": int(info["confirmations"])}
    except (RuntimeError, ValueError):
        pass
    try:
        info = json.loads(cli(binary, "gettransaction", txid, "true"))
        if info.get("txid") == txid and int(info.get("confirmations", 0)) >= 1:
            return {"where": "block", "confirmations": int(info["confirmations"])}
    except (RuntimeError, ValueError):
        pass
    return None


def now() -> str:
    return datetime.utcnow().isoformat() + "Z"


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--input", required=True, type=Path)
    p.add_argument("--cli", default="ammocoin-cli",
                   help="ammocoin-cli command, quoted, with any -datadir/-conf (split like the other scripts)")
    p.add_argument("--skip-sent", dest="skip_sent", action="store_true", default=True,
                   help="(default) mark a batch whose exact txid is already in the mempool or a block as SENT and skip it")
    p.add_argument("--no-skip-sent", dest="skip_sent", action="store_false",
                   help="strict: treat any spent input as STALE, even when the spender is this same tx")
    p.add_argument("--pause", type=int, default=30, help="Seconds between batches")
    p.add_argument("--log", type=Path, default=None, help="Audit log JSON output path")
    args = p.parse_args()

    log_path = args.log or Path(
        f"broadcast-log-{datetime.now().strftime('%Y%m%d-%H%M%S')}.json"
    )

    artifact = json.loads(args.input.read_text())
    if artifact.get("schema_version") != "1":
        raise RuntimeError(f"Unknown schema_version {artifact.get('schema_version')!r}")

    print("AMMOcoin v1.0→v1.1 distribution BROADCAST (step 3 of 3)")
    print("=" * 64)
    print(f"  Batches to broadcast: {len(artifact['batches'])}")
    print(f"  Total to distribute:  {Decimal(str(artifact['sum_of_balances_ammo'])):,.8f} AMMO")
    print(f"  Pause between txs:    {args.pause}s")
    print(f"  Already-sent batches: {'skipped (logged as sent)' if args.skip_sent else 'NOT skipped (--no-skip-sent)'}")
    print(f"  Audit log:            {log_path}")
    print()

    # Sanity-decode every batch BEFORE broadcasting any of them. We'd rather
    # fail the whole run than partially distribute.
    print("Verifying all signed batches before sending...")
    for batch in artifact["batches"]:
        verify_signed_batch(args.cli, batch)
        print(f"  ✓ {label(batch)} verified ({batch['signed_txid']})")
    print()

    print("All batches verified. Type 'BROADCAST' to begin sending.")
    print("This action sends real transactions and cannot be undone.")
    if input("> ").strip() != "BROADCAST":
        print("Aborted.")
        return 1

    audit: list[dict] = []
    n_skipped = 0
    for batch in artifact["batches"]:
        idx = batch["batch_index"]
        print(f"\nBroadcasting {label(batch)} of {len(artifact['batches'])} ({batch['signed_txid']})...")
        if args.skip_sent:
            sent = already_sent(args.cli, batch["signed_txid"])
            if sent:
                where = "in the mempool" if sent["where"] == "mempool" else f"in a block, {sent['confirmations']} conf."
                print(f"  ✓ SENT already ({where}). Skipped, not rebroadcast.")
                audit.append({"batch_index": idx, "txid": batch["signed_txid"], "status": "already_sent",
                              "where": sent["where"], "confirmations": sent["confirmations"],
                              "checked_at": now()})
                log_path.write_text(json.dumps(audit, indent=2))
                n_skipped += 1
                continue
        gone = stale_inputs(args.cli, batch)
        if gone:
            print(f"  ✗ STALE: {len(gone)} input(s) already spent (e.g. {gone[0]}). Not sent.")
            if args.skip_sent:
                print("    This transaction is not in the mempool or the chain, so a DIFFERENT transaction spent them.")
            audit.append({"batch_index": idx, "expected_txid": batch["signed_txid"], "status": "stale",
                          "spent_inputs": gone, "broadcast_at": datetime.utcnow().isoformat() + "Z"})
            log_path.write_text(json.dumps(audit, indent=2))
            print(f"\nAudit log written to {log_path}.")
            if not isinstance(idx, int):
                print("A stake spent a reserve output. Rerun migration-prepare.py --fan-out: it builds only what is still missing.")
            else:
                print("A payout input is gone. Stop and investigate before anything else is sent.")
            return 1
        try:
            txid = cli(args.cli, "sendrawtransaction", batch["signed_hex"])
            print(f"  ✓ Accepted: {txid}")
            if txid != batch["signed_txid"]:
                print(f"  ! The node returned {txid}, not the signed txid {batch['signed_txid']}. Stop and investigate.")
                audit.append({"batch_index": idx, "txid": txid, "expected_txid": batch["signed_txid"],
                              "status": "txid_mismatch", "broadcast_at": now()})
                log_path.write_text(json.dumps(audit, indent=2))
                return 1
            audit.append(
                {
                    "batch_index": idx,
                    "txid": txid,
                    "status": "accepted",
                    "broadcast_at": datetime.utcnow().isoformat() + "Z",
                }
            )
        except RuntimeError as e:
            sent = already_sent(args.cli, batch["signed_txid"]) if args.skip_sent else None
            if sent and any(m in str(e) for m in ALREADY_SENT_ERRORS):
                print(f"  ✓ SENT already (the node says: {e}). Skipped.")
                audit.append({"batch_index": idx, "txid": batch["signed_txid"], "status": "already_sent",
                              "where": sent["where"], "confirmations": sent["confirmations"],
                              "checked_at": now()})
                log_path.write_text(json.dumps(audit, indent=2))
                n_skipped += 1
                continue
            print(f"  ✗ REJECTED: {e}")
            audit.append(
                {
                    "batch_index": idx,
                    "expected_txid": batch["signed_txid"],
                    "status": "rejected",
                    "error": str(e),
                    "broadcast_at": datetime.utcnow().isoformat() + "Z",
                }
            )
            # Save partial log and stop — do not continue after a rejection.
            log_path.write_text(json.dumps(audit, indent=2))
            print(f"\nAudit log written to {log_path}.")
            print("Investigate the rejection and decide whether to resume manually.")
            return 1

        if batch is not artifact["batches"][-1]:
            print(f"  Pausing {args.pause}s before next batch...")
            time.sleep(args.pause)

    log_path.write_text(json.dumps(audit, indent=2))
    print()
    print(f"✓ All {len(audit)} batches broadcast successfully"
          + (f" ({n_skipped} of them already sent before this run, skipped)." if n_skipped else "."))
    print(f"  Audit log: {log_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
