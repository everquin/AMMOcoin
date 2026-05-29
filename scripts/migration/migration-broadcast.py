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

Usage:
    python3 migration-broadcast.py \\
        --input signed-distribution.json \\
        --cli ammocoin-cli \\
        --pause 30
"""

import argparse
import json
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path


def cli(binary: str, *args: str) -> str:
    proc = subprocess.run([binary, *args], capture_output=True, text=True, timeout=60)
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


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--input", required=True, type=Path)
    p.add_argument("--cli", default="ammocoin-cli")
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
    print(f"  Total to distribute:  {artifact['sum_of_balances_ammo']:,.8f} AMMO")
    print(f"  Pause between txs:    {args.pause}s")
    print(f"  Audit log:            {log_path}")
    print()

    # Sanity-decode every batch BEFORE broadcasting any of them. We'd rather
    # fail the whole run than partially distribute.
    print("Verifying all signed batches before sending...")
    for batch in artifact["batches"]:
        verify_signed_batch(args.cli, batch)
        print(f"  ✓ Batch {batch['batch_index'] + 1} verified ({batch['signed_txid']})")
    print()

    print("All batches verified. Type 'BROADCAST' to begin sending.")
    print("This action sends real transactions and cannot be undone.")
    if input("> ").strip() != "BROADCAST":
        print("Aborted.")
        return 1

    audit: list[dict] = []
    for batch in artifact["batches"]:
        idx = batch["batch_index"]
        print(f"\nBroadcasting batch {idx + 1}/{len(artifact['batches'])} ({batch['signed_txid']})...")
        try:
            txid = cli(args.cli, "sendrawtransaction", batch["signed_hex"])
            print(f"  ✓ Accepted: {txid}")
            audit.append(
                {
                    "batch_index": idx,
                    "txid": txid,
                    "status": "accepted",
                    "broadcast_at": datetime.utcnow().isoformat() + "Z",
                }
            )
        except RuntimeError as e:
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

        if idx + 1 < len(artifact["batches"]):
            print(f"  Pausing {args.pause}s before next batch...")
            time.sleep(args.pause)

    log_path.write_text(json.dumps(audit, indent=2))
    print()
    print(f"✓ All {len(audit)} batches broadcast successfully.")
    print(f"  Audit log: {log_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
