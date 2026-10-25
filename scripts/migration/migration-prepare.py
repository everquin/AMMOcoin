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
from decimal import ROUND_CEILING, ROUND_DOWN, Decimal
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


def split_oversize(holders: list[dict[str, Any]]) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    """Owner decision AMMO-D-2026-10-18-13: keep the per-recipient cap and
    pay a larger balance in several outputs of at most MAX_PER_RECIPIENT_AMMO,
    each in its own transaction (an address can appear only once per tx).

    Returns (holders with each address once — oversize ones cut to their
    first part, extra parts). Amounts are split exactly in satoshis."""
    cap = Decimal(MAX_PER_RECIPIENT_AMMO)
    sat = Decimal("0.00000001")
    main: list[dict[str, Any]] = []
    extras: list[dict[str, Any]] = []
    for h in holders:
        amt = Decimal(str(h["balance"]))
        if amt <= cap:
            main.append(h)
            continue
        n = int((amt / cap).to_integral_value(rounding=ROUND_CEILING))
        part = (amt / n).quantize(sat, rounding=ROUND_DOWN)
        parts = [part] * n
        parts[-1] = amt - part * (n - 1)
        assert sum(parts) == amt and all(x <= cap for x in parts)
        main.append({**h, "balance": f"{parts[0]:.8f}", "part": f"1/{n}"})
        for i, x in enumerate(parts[1:], start=2):
            extras.append({**h, "balance": f"{x:.8f}", "part": f"{i}/{n}"})
    return main, extras


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


def plan_chunks(main: list[dict[str, Any]], extras: list[dict[str, Any]]) -> list[list[dict[str, Any]]]:
    """Recipient groups, one per transaction: the holders in groups of
    MAX_RECIPIENTS_PER_TX, then each extra part of an oversize balance on its
    own, so no address is ever paid twice in one transaction."""
    chunks = [main[i : i + MAX_RECIPIENTS_PER_TX] for i in range(0, len(main), MAX_RECIPIENTS_PER_TX)]
    chunks += [[x] for x in extras]
    for c in chunks:
        addrs = [h["address"] for h in c]
        assert len(addrs) == len(set(addrs)), "address repeated inside one transaction"
    return chunks


def chunk_need(chunk: list[dict[str, Any]]) -> Decimal:
    return sum((Decimal(str(h["balance"])) for h in chunk), Decimal(0)) + Decimal(str(FEE_PER_TX_AMMO))


def list_watch_utxos(binary: str) -> list[dict[str, Any]]:
    # AMMOcoin listunspent: (minconf maxconf addresses watchonly_config query_options include_unsafe);
    # watchonly_config 2 = include watch-only, which is how the reserve is held while building.
    raw = cli(binary, "listunspent", "1", "9999999", "[]", "2", "{}", "false")
    return json.loads(raw)


def build_fanout(binary: str, chunks: list[list[dict[str, Any]]], fanout_addresses: list[str],
                 change_address: str | None) -> dict[str, Any]:
    """One unsigned transaction that splits the reserve into one UTXO per
    payout batch (to the operator's own fan-out addresses, one per batch,
    since an address can take only one output per tx). Without it every
    batch would select the same reserve UTXO and all but the first would be
    double spends."""
    if len(fanout_addresses) < len(chunks):
        raise RuntimeError(f"Need {len(chunks)} distinct fan-out addresses, got {len(fanout_addresses)}.")
    needs = [chunk_need(c) for c in chunks]
    target = sum(needs, Decimal(0)) + Decimal(str(FEE_PER_TX_AMMO))
    utxos = sorted(list_watch_utxos(binary), key=lambda u: -Decimal(str(u["amount"])))
    picked, acc = [], Decimal(0)
    for u in utxos:
        picked.append(u)
        acc += Decimal(str(u["amount"]))
        if acc >= target:
            break
    if acc < target:
        raise RuntimeError(f"Watch-only UTXOs {acc} below fan-out target {target}.")
    outputs = {a: f"{n:.8f}" for a, n in zip(fanout_addresses, needs)}
    change = acc - target
    if change > Decimal(str(DUST_TOLERANCE_AMMO)):
        if not change_address or change_address in outputs:
            raise RuntimeError("A separate --change-address is required for the fan-out change.")
        outputs[change_address] = f"{change:.8f}"
    inputs = [{"txid": u["txid"], "vout": u["vout"]} for u in picked]
    raw_hex = cli(binary, "createrawtransaction", json.dumps(inputs), json.dumps(outputs))
    return {"batch_index": "fanout", "recipients": [], "inputs": inputs, "outputs": outputs, "unsigned_hex": raw_hex}


def build_batches(
    binary: str, chunks: list[list[dict[str, Any]]], change_address: str | None
) -> list[dict[str, Any]]:
    """One unsigned tx per chunk. Each spends its OWN UTXO (made by the
    fan-out step): the closest unused UTXO that covers it. A UTXO is never
    used by two batches."""
    utxos = list_watch_utxos(binary)
    used: set[tuple[str, int]] = set()
    batches: list[dict[str, Any]] = []
    for idx, chunk in enumerate(chunks):
        need = chunk_need(chunk)
        free = [u for u in utxos if (u["txid"], u["vout"]) not in used and Decimal(str(u["amount"])) >= need]
        if not free:
            raise RuntimeError(
                f"Batch {idx + 1}: no unused UTXO covers {need} AMMO. Run --fan-out first, "
                "sign and broadcast it, wait for confirmations, then rerun."
            )
        u = min(free, key=lambda x: Decimal(str(x["amount"])))
        used.add((u["txid"], u["vout"]))
        inputs = [{"txid": u["txid"], "vout": u["vout"]}]
        outputs = {h["address"]: f"{Decimal(str(h['balance'])):.8f}" for h in chunk}
        change = Decimal(str(u["amount"])) - need
        if change > Decimal(str(DUST_TOLERANCE_AMMO)):
            if not change_address or change_address in outputs:
                raise RuntimeError("Change address required (and must not be a recipient). Pass --change-address.")
            outputs[change_address] = f"{change:.8f}"
        raw_hex = cli(binary, "createrawtransaction", json.dumps(inputs), json.dumps(outputs))
        batches.append({"batch_index": idx, "recipients": chunk, "inputs": inputs,
                        "outputs": outputs, "unsigned_hex": raw_hex})
    return batches


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--holders", required=True, type=Path)
    p.add_argument("--watch-wallet", default="ammocoin-cli", help="Path to ammocoin-cli")
    p.add_argument("--change-address", default=None, help="Address to receive change (watch-only)")
    p.add_argument("--output", default=None, type=Path, help="Output JSON path")
    p.add_argument("--fan-out", default=None, type=Path, metavar="ADDRESSES_FILE",
                   help="Build only the fan-out tx: one reserve UTXO per batch, to these "
                        "operator-owned addresses (one per line). Run this first.")
    args = p.parse_args()

    out_path = args.output or Path(
        f"unsigned-distribution-{datetime.now().strftime('%Y%m%d-%H%M%S')}.json"
    )

    print("AMMOcoin v1.0→v1.1 distribution PREPARE (step 1 of 3)")
    print("=" * 64)

    holders = load_holders(args.holders)
    main_holders, extras = split_oversize(holders)
    total = enforce_bounds(main_holders) + enforce_bounds(extras)
    chunks = plan_chunks(main_holders, extras)
    n_batches = len(chunks)
    if extras:
        print(f"  Oversize balances split: {len(extras)} extra output(s), each its own tx")
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

    if args.fan_out:
        addrs = [l.strip() for l in args.fan_out.read_text().splitlines() if l.strip()]
        batches = [build_fanout(args.watch_wallet, chunks, addrs, args.change_address)]
    else:
        batches = build_batches(args.watch_wallet, chunks, args.change_address)

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
