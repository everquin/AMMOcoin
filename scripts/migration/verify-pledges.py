#!/usr/bin/env python3
"""
Check QuarterMaster pledge signatures (AMMO-D-2026-10-18-12).

Input: a CSV of `address,signature` (one row per contributor, the base64
signature from `signmessage`). Each signature is checked against the exact
message for that address in docs/migration/data/quartermaster-pledges.csv,
with `ammocoin-cli verifymessage`. Any running v1.1.1 (or v1.0) node works:
verifymessage needs no wallet, no sync and no network.

Output: one line per pledge address (SIGNED / BAD SIGNATURE / MISSING), the
signed total and the shortfall against the full pledge total. Exit status 1
while anything is missing or bad.

Usage:
    python3 scripts/migration/verify-pledges.py signatures.csv \
        [--cli "/opt/ammocoin-v1.1.1/bin/ammocoin-cli -datadir=..."]
"""
from __future__ import annotations

import argparse
import csv
import shlex
import subprocess
import sys
from decimal import Decimal
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PLEDGES = ROOT / "docs/migration/data/quartermaster-pledges.csv"


def verify(cli: list[str], address: str, signature: str, message: str) -> bool:
    r = subprocess.run(cli + ["verifymessage", address, signature, message],
                       capture_output=True, text=True, timeout=30)
    if r.returncode != 0:
        err = r.stderr.strip()
        if "Malformed base64" in err or "Invalid address" in err:
            return False
        sys.exit(f"verifymessage failed for {address}: {err or r.stdout.strip()}")
    return r.stdout.strip() == "true"


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("signatures", help="CSV with columns address,signature")
    ap.add_argument("--cli", default="ammocoin-cli", help="ammocoin-cli command (quoted, with any -datadir)")
    a = ap.parse_args()
    cli = shlex.split(a.cli)

    pledges = {r["address"]: r for r in csv.DictReader(PLEDGES.open())}
    sigs: dict[str, str] = {}
    for r in csv.DictReader(open(a.signatures)):
        addr, sig = r.get("address", "").strip(), r.get("signature", "").strip()
        if addr not in pledges:
            print(f"  ignored: {addr or '(blank)'} is not a pledge address")
            continue
        sigs[addr] = sig

    total = signed = Decimal(0)
    problems = 0
    for addr, p in pledges.items():
        amount = Decimal(p["pledge"])
        total += amount
        if addr not in sigs or not sigs[addr]:
            print(f"  MISSING        {addr} {amount:>22,.8f}")
            problems += 1
        elif verify(cli, addr, sigs[addr], p["message"]):
            print(f"  SIGNED         {addr} {amount:>22,.8f}")
            signed += amount
        else:
            print(f"  BAD SIGNATURE  {addr} {amount:>22,.8f}  (signed a different message, or wrong key)")
            problems += 1

    print(f"\nsigned {signed:,.8f} of {total:,.8f} AMMO; short {total - signed:,.8f}")
    sys.exit(1 if problems else 0)


if __name__ == "__main__":
    main()
