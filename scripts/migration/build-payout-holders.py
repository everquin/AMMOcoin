#!/usr/bin/env python3
"""
Build the airdrop payout list for migration-prepare.py (AMMO-D-2026-10-18-12).

Every snapshot address is paid its snapshot balance, except the 61 pledging
contributors, who are paid `airdrop_after_pledge` from
docs/migration/data/quartermaster-pledges.csv. Refuses to write anything
unless every pledge signature verifies (same check as verify-pledges.py), so
a pledge can never reduce someone's airdrop without their signature.

Output (the `--holders` file migration-prepare.py reads):
    {"top_holders": [{"address": ..., "balance": "<8-dp string>"}, ...], "summary": {...}}

Pledge addresses listed in --full-pay (one per line) are paid their FULL
snapshot balance instead: holders who declined, or did not sign by the
deadline (AMMO-D-2026-10-25-01). The expected total rises by their pledges.

Usage:
    python3 scripts/migration/build-payout-holders.py signatures.csv \
        --cli "/opt/ammocoin-v1.1.1/bin/ammocoin-cli -datadir=..." \
        [--full-pay full-pay.txt] --output payout-holders.json
"""
from __future__ import annotations

import argparse
import csv
import importlib.util
import json
import shlex
import sys
from decimal import Decimal
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
SNAPSHOT = ROOT / "docs/migration/data/v1.0-complete-balance-snapshot.json"
PLEDGES = ROOT / "docs/migration/data/quartermaster-pledges.csv"
EXPECTED_PAYOUT = Decimal("159958300.00000000")
MAX_PER_RECIPIENT = Decimal("10000000")  # migration-prepare.py's MAX_PER_RECIPIENT_AMMO


def _load(name: str):
    spec = importlib.util.spec_from_file_location(name.replace("-", "_"), HERE / f"{name}.py")
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("signatures", help="CSV with columns address,signature")
    ap.add_argument("--cli", default="ammocoin-cli")
    ap.add_argument("--output", required=True, type=Path)
    ap.add_argument("--full-pay", type=Path, default=None,
                    help="pledge addresses (one per line) paid in full: declined or unsigned at the deadline")
    a = ap.parse_args()

    # The pledge list must still be exactly what the builder produces.
    text, _ = _load("build-pledges").build()
    if PLEDGES.read_text() != text:
        sys.exit("quartermaster-pledges.csv differs from a fresh build; refusing")

    verify = _load("verify-pledges").verify
    cli = shlex.split(a.cli)
    pledges = {r["address"]: r for r in csv.DictReader(PLEDGES.open())}
    sigs = {r["address"].strip(): r["signature"].strip() for r in csv.DictReader(open(a.signatures))}
    full_pay: set[str] = set()
    if a.full_pay:
        full_pay = {l.strip() for l in a.full_pay.read_text().splitlines() if l.strip() and not l.startswith("#")}
        unknown = sorted(full_pay - set(pledges))
        if unknown:
            sys.exit(f"--full-pay lists {len(unknown)} address(es) that are not pledge addresses (e.g. {unknown[0]}); refusing")
    signed_too = sorted(x for x in full_pay if sigs.get(x))
    if signed_too:
        sys.exit(f"{len(signed_too)} --full-pay address(es) also have a signature (e.g. {signed_too[0]}); "
                 "a signed pledge is honored, so remove it from one list. Nothing written.")
    bad = [addr for addr, p in pledges.items()
           if addr not in full_pay and (not sigs.get(addr) or not verify(cli, addr, sigs[addr], p["message"]))]
    if bad:
        sys.exit(f"{len(bad)} pledge(s) missing or not verified (e.g. {bad[0]}); run verify-pledges.py, "
                 "or list them in --full-pay after the deadline. Nothing written.")
    pledged = {addr: p for addr, p in pledges.items() if addr not in full_pay}
    expected = EXPECTED_PAYOUT + sum((Decimal(pledges[x]["pledge"]) for x in full_pay), Decimal(0))

    snap = json.loads(SNAPSHOT.read_bytes(), parse_float=Decimal)
    holders = []
    for addr, bal in sorted(snap["balances"].items(), key=lambda kv: (-Decimal(str(kv[1])), kv[0])):
        pay = Decimal(pledged[addr]["airdrop_after_pledge"]) if addr in pledged else Decimal(str(bal))
        if pay > 0:
            holders.append({"address": addr, "balance": f"{pay:.8f}"})
    total = sum(Decimal(h["balance"]) for h in holders)
    if total != expected:
        sys.exit(f"payout total {total} != {expected}; refusing")

    over = [h for h in holders if Decimal(h["balance"]) > MAX_PER_RECIPIENT]
    a.output.write_text(json.dumps({
        "top_holders": holders,
        "summary": {"addresses": len(holders), "total": f"{total:.8f}",
                    "pledged_addresses": len(pledged), "full_pay_addresses": len(full_pay),
                    "reserve_shortfall_vs_plan": f"{expected - EXPECTED_PAYOUT:.8f}",
                    "over_per_recipient_cap": len(over)},
    }, indent=1))
    print(f"wrote {a.output}: {len(holders)} addresses, {total:,.8f} AMMO")
    if full_pay:
        print(f"{len(full_pay)} pledge address(es) paid in full; the QuarterMaster reserve is {expected - EXPECTED_PAYOUT:,.8f} AMMO "
              "short of plan. Publish this (AMMO-D-2026-10-25-01).")
    if over:
        print(f"NOTE: {len(over)} address(es) exceed the {MAX_PER_RECIPIENT:,} cap; migration-prepare.py splits them into ≤cap outputs in separate transactions "
              f"(largest {max(Decimal(h['balance']) for h in over):,.8f}).")


if __name__ == "__main__":
    main()
