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
  * Every transaction stays under MAX_STANDARD_TX_SIZE (100 kB): at most
    MAX_INPUTS_PER_TX inputs, and a fee sized to the transaction.
  * Operator must type 'CONFIRM' to write the unsigned-txs file.

The block-1 reserve is held as thousands of cold-staked 50,000 AMMO outputs
(RESERVES.md), so the payout runs in two passes:

  1. --fan-out FANOUT_ADDRESSES: consolidation transactions that spend reserve
     outputs (at most MAX_INPUTS_PER_TX each) into one funding address per
     payout batch. A batch may be funded across several of these
     transactions. The pass is idempotent: it funds only what each batch
     address still lacks (mempool included), so after a rejected or stale
     transaction you simply run it again. --max-txs N builds only the next N.
  2. --from-fan-out FANOUT_ADDRESSES: the payout batches, each spending every
     confirmed output at its own funding address.

The funding addresses (one per line, one per batch, in batch order) must
belong to the signing wallet and must NOT be in a staking wallet.

Usage:
    python3 migration-prepare.py --holders payout-holders.json \\
        --watch-wallet ammocoin-cli --change-address <reserve change addr> \\
        --fan-out fanout-addresses.txt [--max-txs 1] --output fanout.json
    python3 migration-prepare.py --holders payout-holders.json \\
        --watch-wallet ammocoin-cli --change-address <reserve change addr> \\
        --from-fan-out fanout-addresses.txt --output batches.json

payout-holders.json comes from build-payout-holders.py (published snapshot
minus signed pledges, AMMO-D-2026-10-18-12 / -10-25-01).
"""

import argparse
import json
import math
from decimal import ROUND_CEILING, ROUND_DOWN, Decimal
import subprocess
import sys
from datetime import datetime
from pathlib import Path
from typing import Any

MAX_PER_RECIPIENT_AMMO = 10_000_000
MAX_RECIPIENTS_PER_TX = 50
DUST_TOLERANCE_AMMO = 0.01  # max acceptable rounding gap between sum-of-holders and sum-of-tx-outputs
FEE_RATE_PER_KB = Decimal("0.0005")  # 5x the node relay fee (getnetworkinfo relayfee 0.0001/kB)
FEE_PER_TX_AMMO = 0.002     # payout batch tx: covers ~4 kB at FEE_RATE_PER_KB (50 outputs + a few inputs)
MAX_INPUTS_PER_TX = 450     # fan-out tx: 450 cold-stake inputs stays well under MAX_STANDARD_TX_SIZE (100,000 bytes)
INPUT_BYTES = 180           # signed size estimate per input (cold-stake owner spend is the largest kind)
OUTPUT_BYTES = 34
MIN_PIECE_AMMO = Decimal("1")  # never create a fan-out piece smaller than this unless it completes a batch


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


def prevout(u: dict[str, Any]) -> dict[str, Any]:
    """What the offline signer needs to sign this input without a copy of the chain."""
    return {"txid": u["txid"], "vout": u["vout"], "scriptPubKey": u["scriptPubKey"], "amount": f"{Decimal(str(u['amount'])):.8f}"}


def tx_fee(n_in: int, n_out: int) -> Decimal:
    size = 10 + n_in * INPUT_BYTES + n_out * OUTPUT_BYTES
    return Decimal(math.ceil(size / 1000)) * FEE_RATE_PER_KB


def list_utxos_at(binary: str, minconf: int) -> list[dict[str, Any]]:
    raw = cli(binary, "listunspent", str(minconf), "9999999", "[]", "2", "{}", "false")
    return json.loads(raw)


def build_fanout(binary: str, chunks: list[list[dict[str, Any]]], fanout_addresses: list[str],
                 change_address: str | None, max_txs: int | None = None) -> list[dict[str, Any]]:
    """Consolidation transactions that fund one address per payout batch from
    the reserve outputs, at most MAX_INPUTS_PER_TX inputs each. Funds only what
    each batch address still lacks (mempool included), so it can be rerun after
    a rejection. Without it every batch would select the same reserve UTXO."""
    if len(fanout_addresses) < len(chunks):
        raise RuntimeError(f"Need {len(chunks)} distinct fan-out addresses, got {len(fanout_addresses)}.")
    fan = fanout_addresses[: len(chunks)]
    if len(set(fan)) != len(fan):
        raise RuntimeError("Fan-out addresses must be distinct.")
    if not change_address or change_address in fan:
        raise RuntimeError("A separate --change-address is required for the fan-out change.")
    funded: dict[str, Decimal] = {a: Decimal(0) for a in fan}
    for u in list_utxos_at(binary, 0):
        if u.get("address") in funded:
            funded[u["address"]] += Decimal(str(u["amount"]))
    remaining = [max(Decimal(0), chunk_need(c) - funded[a]) for c, a in zip(chunks, fan)]
    reserve = sorted((u for u in list_utxos_at(binary, 1) if u.get("address") not in funded),
                     key=lambda u: (-Decimal(str(u["amount"])), u["txid"], u["vout"]))
    txs: list[dict[str, Any]] = []
    k, pos = 0, 0
    while k < len(chunks) and (max_txs is None or len(txs) < max_txs):
        while k < len(chunks) and remaining[k] == 0:
            k += 1
        if k == len(chunks):
            break
        inputs: list[dict[str, Any]] = []
        prevouts: list[dict[str, Any]] = []
        outputs: dict[str, Decimal] = {}
        acc = Decimal(0)
        while k < len(chunks):
            avail = acc - sum(outputs.values(), Decimal(0)) - tx_fee(len(inputs), len(outputs) + 2)
            take = min(remaining[k], max(avail, Decimal(0)))
            if take > 0 and (take >= MIN_PIECE_AMMO or take == remaining[k]):
                outputs[fan[k]] = outputs.get(fan[k], Decimal(0)) + take
                remaining[k] -= take
                if remaining[k] == 0:
                    k += 1
                    while k < len(chunks) and remaining[k] == 0:
                        k += 1
                continue
            if len(inputs) >= MAX_INPUTS_PER_TX:
                break
            if pos >= len(reserve):
                raise RuntimeError(f"Reserve UTXOs exhausted with {sum(remaining, Decimal(0))} AMMO still to fund.")
            u = reserve[pos]; pos += 1
            inputs.append({"txid": u["txid"], "vout": u["vout"]})
            prevouts.append(prevout(u))
            acc += Decimal(str(u["amount"]))
        if not outputs:
            break
        fee = tx_fee(len(inputs), len(outputs) + 1)
        change = acc - sum(outputs.values(), Decimal(0)) - fee
        if change < 0:
            raise RuntimeError("internal: fan-out change negative")
        out = {a: f"{v:.8f}" for a, v in outputs.items()}
        if change > Decimal(str(DUST_TOLERANCE_AMMO)):
            out[change_address] = f"{change:.8f}"
        raw_hex = cli(binary, "createrawtransaction", json.dumps(inputs), json.dumps(out))
        txs.append({"batch_index": f"fanout-{len(txs)}", "recipients": [], "inputs": inputs,
                    "prevouts": prevouts, "outputs": out, "fee": f"{fee:.8f}", "unsigned_hex": raw_hex})
    return txs


def build_batches(
    binary: str, chunks: list[list[dict[str, Any]]], change_address: str | None,
    fanout_addresses: list[str] | None = None,
) -> list[dict[str, Any]]:
    """One unsigned tx per chunk. With fanout_addresses, batch k spends every
    confirmed output at its own funding address (it may have been funded by
    several fan-out txs). Without, each batch spends the closest unused UTXO
    that covers it. A UTXO is never used by two batches."""
    if fanout_addresses is not None:
        return build_batches_from_fanout(binary, chunks, change_address, fanout_addresses)
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
        prevouts = [prevout(u)]
        outputs = {h["address"]: f"{Decimal(str(h['balance'])):.8f}" for h in chunk}
        change = Decimal(str(u["amount"])) - need
        if change > Decimal(str(DUST_TOLERANCE_AMMO)):
            if not change_address or change_address in outputs:
                raise RuntimeError("Change address required (and must not be a recipient). Pass --change-address.")
            outputs[change_address] = f"{change:.8f}"
        raw_hex = cli(binary, "createrawtransaction", json.dumps(inputs), json.dumps(outputs))
        batches.append({"batch_index": idx, "recipients": chunk, "inputs": inputs,
                        "prevouts": prevouts, "outputs": outputs, "unsigned_hex": raw_hex})
    return batches


def build_batches_from_fanout(binary: str, chunks: list[list[dict[str, Any]]], change_address: str | None,
                              fanout_addresses: list[str]) -> list[dict[str, Any]]:
    fan = fanout_addresses[: len(chunks)]
    if len(fan) < len(chunks):
        raise RuntimeError(f"Need {len(chunks)} fan-out addresses, got {len(fan)}.")
    by_addr: dict[str, list[dict[str, Any]]] = {a: [] for a in fan}
    for u in list_utxos_at(binary, 1):
        if u.get("address") in by_addr:
            by_addr[u["address"]].append(u)
    batches: list[dict[str, Any]] = []
    for idx, (chunk, a) in enumerate(zip(chunks, fan)):
        us = by_addr[a]
        have = sum((Decimal(str(u["amount"])) for u in us), Decimal(0))
        need = chunk_need(chunk)
        if have < need:
            raise RuntimeError(f"Batch {idx}: funding address {a} has {have} confirmed, needs {need}. "
                               "Run --fan-out again (it funds only what is missing), wait for a confirmation, rerun.")
        inputs = [{"txid": u["txid"], "vout": u["vout"]} for u in us]
        prevouts = [prevout(u) for u in us]
        outputs = {h["address"]: f"{Decimal(str(h['balance'])):.8f}" for h in chunk}
        if a in outputs or (change_address and change_address in outputs):
            raise RuntimeError(f"Batch {idx}: a recipient is a funding or change address; refusing.")
        if tx_fee(len(inputs), len(outputs) + 1) > Decimal(str(FEE_PER_TX_AMMO)):
            raise RuntimeError(f"Batch {idx}: {len(inputs)} inputs need a fee above FEE_PER_TX_AMMO; refusing.")
        change = have - need  # the fee paid is FEE_PER_TX_AMMO, already inside `need`
        if change > Decimal(str(DUST_TOLERANCE_AMMO)):
            if not change_address:
                raise RuntimeError("Change address required. Pass --change-address.")
            outputs[change_address] = f"{change:.8f}"
        raw_hex = cli(binary, "createrawtransaction", json.dumps(inputs), json.dumps(outputs))
        batches.append({"batch_index": idx, "recipients": chunk, "inputs": inputs,
                        "prevouts": prevouts, "outputs": outputs, "unsigned_hex": raw_hex})
    return batches


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--holders", required=True, type=Path)
    p.add_argument("--watch-wallet", default="ammocoin-cli", help="Path to ammocoin-cli")
    p.add_argument("--change-address", default=None, help="Address to receive change (watch-only)")
    p.add_argument("--output", default=None, type=Path, help="Output JSON path")
    p.add_argument("--fan-out", default=None, type=Path, metavar="ADDRESSES_FILE",
                   help="Build the fan-out txs: fund one address per batch (one per line, batch order) "
                        "from the reserve. Run this first; rerun after any rejection.")
    p.add_argument("--max-txs", type=int, default=None, help="With --fan-out: build at most N transactions")
    p.add_argument("--from-fan-out", default=None, type=Path, metavar="ADDRESSES_FILE",
                   help="Build the payout batches, each spending its own funding address")
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

    def read_addrs(path: Path) -> list[str]:
        return [l.strip() for l in path.read_text().splitlines() if l.strip() and not l.startswith("#")]

    if args.fan_out and args.from_fan_out:
        raise SystemExit("--fan-out and --from-fan-out are separate passes")
    if args.fan_out:
        batches = build_fanout(args.watch_wallet, chunks, read_addrs(args.fan_out), args.change_address, args.max_txs)
        if not batches:
            print("Every batch address is already funded (mempool included). Nothing to build.")
            return 0
        print(f"  Fan-out txs built:     {len(batches)} "
              f"({sum(len(b['inputs']) for b in batches)} reserve inputs)")
    elif args.from_fan_out:
        batches = build_batches(args.watch_wallet, chunks, args.change_address, read_addrs(args.from_fan_out))
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
