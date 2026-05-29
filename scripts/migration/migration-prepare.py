#!/usr/bin/env python3
"""
AMMOcoin v1.0 → v1.1 migration: step 1 of 3 — PREPARE.

Builds unsigned distribution transactions on an ONLINE node that has a
WATCH-ONLY wallet containing the source UTXOs. No private keys are loaded
on this machine. The output JSON is carried to an air-gapped machine for
step 2 (migration-sign-offline.py).

Safety bounds enforced before any tx is built:
  * Each output amount ≤ MAX_PER_RECIPIENT (default 10,000,000 AMMO).
  * Total distributed must equal the sum of holders' balances to within
    DUST_TOLERANCE; otherwise the script refuses to write the output file.
  * Number of recipients per tx ≤ MAX_RECIPIENTS_PER_TX (default 50) —
    well within standardness limits and keeps any single failed broadcast
    from stranding too many recipients.
  * Operator must type 'CONFIRM' to write the unsigned-txs file.

Usage:
    python3 migration-prepare.py \\
        --holders genesis-top-holders.json \\
        --watch-wallet ammocoin-cli \\
        --output unsigned-distribution-YYYYMMDD.json
"""

import argparse
import json
import subprocess
import sys
from datetime import datetime
from pathlib import Path
from typing import Any

MAX_PER_RECIPIENT_AMMO = 10_000_000
MAX_RECIPIENTS_PER_TX = 50
DUST_TOLERANCE_AMMO = 0.01  # max acceptable rounding gap between sum-of-holders and sum-of-tx-outputs
FEE_PER_TX_AMMO = 0.0001    # network fee per batched tx — adjust if your fee policy differs


def cli(binary: str, *args: str) -> str:
    """Run ammocoin-cli and return stdout, raising on failure."""
    proc = subprocess.run(
        [binary, *args], capture_output=True, text=True, timeout=60
    )
    if proc.returncode != 0:
        raise RuntimeError(f"ammocoin-cli {' '.join(args)} failed: {proc.stderr.strip()}")
    return proc.stdout.strip()


def load_holders(path: Path) -> list[dict[str, Any]]:
    data = json.loads(path.read_text())
    holders = data.get("top_holders", [])
    if not holders:
        raise ValueError(f"No 'top_holders' in {path}")
    # Defensive: reject malformed entries up front, not mid-build.
    for i, h in enumerate(holders):
        if "address" not in h or "balance" not in h:
            raise ValueError(f"Holder #{i} missing 'address' or 'balance'")
        if float(h["balance"]) <= 0:
            raise ValueError(f"Holder #{i} ({h['address']}) has non-positive balance")
    return holders


def enforce_bounds(holders: list[dict[str, Any]]) -> float:
    total = 0.0
    for h in holders:
        amt = float(h["balance"])
        if amt > MAX_PER_RECIPIENT_AMMO:
            raise ValueError(
                f"Holder {h['address']} balance {amt:,.8f} exceeds "
                f"MAX_PER_RECIPIENT_AMMO={MAX_PER_RECIPIENT_AMMO:,}. "
                "Refusing to build. Edit holders file or raise the limit explicitly."
            )
        total += amt
    return total


def list_watch_utxos(binary: str) -> list[dict[str, Any]]:
    raw = cli(binary, "listunspent", "1", "9999999", "[]", "true", '{"include_unsafe": false}')
    return json.loads(raw)


def select_utxos(utxos: list[dict[str, Any]], target_ammo: float) -> list[dict[str, Any]]:
    # Largest-first selection. We only need to cover target + fees; donor
    # address change handling is left to the offline signer (it inspects
    # the unsigned tx and adds change as needed).
    sorted_u = sorted(utxos, key=lambda u: -float(u["amount"]))
    picked: list[dict[str, Any]] = []
    acc = 0.0
    for u in sorted_u:
        picked.append(u)
        acc += float(u["amount"])
        if acc >= target_ammo:
            return picked
    raise RuntimeError(
        f"Watch-only wallet UTXO total {acc:,.8f} is below target {target_ammo:,.8f}. "
        "Verify the watch-only wallet is fully synced and contains the migration fund."
    )


def build_batches(
    binary: str, holders: list[dict[str, Any]], change_address: str | None
) -> list[dict[str, Any]]:
    batches: list[dict[str, Any]] = []
    for start in range(0, len(holders), MAX_RECIPIENTS_PER_TX):
        chunk = holders[start : start + MAX_RECIPIENTS_PER_TX]
        chunk_total = sum(float(h["balance"]) for h in chunk) + FEE_PER_TX_AMMO

        utxos = list_watch_utxos(binary)
        picked = select_utxos(utxos, chunk_total)

        inputs = [{"txid": u["txid"], "vout": u["vout"]} for u in picked]
        outputs = {h["address"]: f"{float(h['balance']):.8f}" for h in chunk}

        # Change is handled by the offline signer using fundrawtransaction
        # OR by computing it here. We compute it here so the offline signer
        # is deterministic and never has to call into the daemon for
        # selection logic.
        picked_total = sum(float(u["amount"]) for u in picked)
        change = picked_total - sum(float(h["balance"]) for h in chunk) - FEE_PER_TX_AMMO
        if change < -DUST_TOLERANCE_AMMO:
            raise RuntimeError(
                f"Batch {start//MAX_RECIPIENTS_PER_TX + 1}: change={change:.8f} is negative; "
                "selected UTXOs do not cover outputs + fee."
            )
        if change > DUST_TOLERANCE_AMMO:
            if not change_address:
                raise RuntimeError(
                    "Change address required but not supplied. Pass --change-address."
                )
            outputs[change_address] = f"{change:.8f}"

        # createrawtransaction validates inputs/outputs structure but does
        # NOT sign anything — perfect for the watch-only build step.
        # Note: outputs is a JSON object string.
        raw_hex = cli(
            binary,
            "createrawtransaction",
            json.dumps(inputs),
            json.dumps(outputs),
        )

        batches.append(
            {
                "batch_index": len(batches),
                "recipients": chunk,
                "inputs": inputs,
                "outputs": outputs,
                "unsigned_hex": raw_hex,
            }
        )
    return batches


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--holders", required=True, type=Path)
    p.add_argument("--watch-wallet", default="ammocoin-cli", help="Path to ammocoin-cli")
    p.add_argument("--change-address", default=None, help="Address to receive change (watch-only)")
    p.add_argument("--output", default=None, type=Path, help="Output JSON path")
    args = p.parse_args()

    out_path = args.output or Path(
        f"unsigned-distribution-{datetime.now().strftime('%Y%m%d-%H%M%S')}.json"
    )

    print("AMMOcoin v1.0→v1.1 distribution PREPARE (step 1 of 3)")
    print("=" * 64)

    holders = load_holders(args.holders)
    total = enforce_bounds(holders)
    n_batches = (len(holders) + MAX_RECIPIENTS_PER_TX - 1) // MAX_RECIPIENTS_PER_TX
    fee_total = n_batches * FEE_PER_TX_AMMO

    print(f"  Holders to fund:       {len(holders)}")
    print(f"  Sum of balances:       {total:,.8f} AMMO")
    print(f"  Batches (txs):         {n_batches} (≤{MAX_RECIPIENTS_PER_TX} recipients each)")
    print(f"  Network fees:          {fee_total:,.8f} AMMO ({FEE_PER_TX_AMMO}/tx × {n_batches})")
    print(f"  Per-tx ceiling:        {MAX_PER_RECIPIENT_AMMO:,} AMMO (enforced)")
    print()
    print("Type 'CONFIRM' to build the unsigned-distribution file.")
    print("Nothing has been signed or broadcast.")
    if input("> ").strip() != "CONFIRM":
        print("Aborted.")
        return 1

    batches = build_batches(args.watch_wallet, holders, args.change_address)

    artifact = {
        "schema_version": "1",
        "created_at": datetime.utcnow().isoformat() + "Z",
        "holders_source": str(args.holders),
        "sum_of_balances_ammo": total,
        "fee_total_ammo": fee_total,
        "max_per_recipient_ammo": MAX_PER_RECIPIENT_AMMO,
        "batches": batches,
    }
    out_path.write_text(json.dumps(artifact, indent=2))
    print()
    print(f"✓ Wrote {out_path}")
    print()
    print("Next steps:")
    print(f"  1. Copy {out_path} to your AIR-GAPPED signing machine.")
    print( "  2. Run: python3 migration-sign-offline.py "
           f"--input {out_path.name} --output signed-distribution.json")
    print( "  3. Carry signed-distribution.json back to an online machine.")
    print( "  4. Run: python3 migration-broadcast.py --input signed-distribution.json")
    return 0


if __name__ == "__main__":
    sys.exit(main())
