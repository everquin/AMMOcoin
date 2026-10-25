#!/usr/bin/env python3
"""
AMMOcoin v1.0 -> v1.1.1 airdrop: step 8, RECONCILE (AIRDROPS.md section 4).

Checks that every address in the payout list received exactly its amount, in
confirmed payout transactions, and writes the reconciliation CSV that is
published.

It works from what was signed, not from current balances, so a holder who has
already moved their coins still reconciles, and a pledging address is checked
against its after-pledge amount (the payout list), not its snapshot balance.

  expected  the payout list (build-payout-holders.py output, the --holders
            file migration-prepare.py used)
  paid      the outputs of every payout transaction in the signed artifacts
            whose txid is confirmed on chain (at least --min-conf)

A transaction signed twice (a batch rebuilt after a stale input) counts once:
only the version that confirmed is counted, and two versions of one batch
spend the same inputs, so at most one can confirm.

Confirmation is read with `gettransaction` on the watch-only builder wallet
(it watches the funding addresses, so every payout is a wallet transaction),
falling back to `getrawtransaction txid 1` (needs -txindex).

Usage:
    python3 scripts/migration/verify-migration.py --holders payout-holders.json \\
        --signed payout-signed.json [--signed more-signed.json ...] \\
        --cli "ammocoin-cli -datadir=..." [--min-conf 6] --output reconciliation.csv

Exit status 0 only when every address is PAID and nothing else was paid.
"""
from __future__ import annotations

import argparse
import csv
import json
import shlex
import subprocess
import sys
from decimal import Decimal
from pathlib import Path


def run(cli: list[str], *args: str) -> str | None:
    r = subprocess.run(cli + list(args), capture_output=True, text=True, timeout=60)
    return r.stdout.strip() if r.returncode == 0 else None


def confirmations(cli: list[str], txid: str) -> int:
    for call in (("gettransaction", txid, "true"), ("getrawtransaction", txid, "1")):
        out = run(cli, *call)
        if out:
            return int(json.loads(out).get("confirmations", 0))
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--holders", required=True, type=Path)
    ap.add_argument("--signed", required=True, type=Path, action="append")
    ap.add_argument("--cli", default="ammocoin-cli", help="ammocoin-cli command (quoted, with any -datadir)")
    ap.add_argument("--min-conf", type=int, default=6)
    ap.add_argument("--output", required=True, type=Path)
    a = ap.parse_args()
    cli = shlex.split(a.cli)

    expected: dict[str, Decimal] = {}
    for h in json.loads(a.holders.read_text())["top_holders"]:
        expected[h["address"]] = expected.get(h["address"], Decimal(0)) + Decimal(h["balance"])

    txs: dict[str, dict] = {}  # txid -> batch, payout batches only
    for f in a.signed:
        for b in json.loads(f.read_text())["batches"]:
            if not str(b["batch_index"]).startswith("fanout"):
                txs.setdefault(b["signed_txid"], b)

    paid: dict[str, Decimal] = {}
    paid_in: dict[str, list[str]] = {}
    for txid, b in txs.items():
        if confirmations(cli, txid) < a.min_conf:
            continue
        decoded = json.loads(run(cli, "decoderawtransaction", b["signed_hex"]) or "{}")
        if decoded.get("txid") != txid:
            sys.exit(f"{txid}: signed_hex does not decode to this txid; refusing")
        recipients = {r["address"] for r in b["recipients"]}
        for v in decoded["vout"]:
            for addr in v.get("scriptPubKey", {}).get("addresses", []):
                if addr in recipients:  # skip the batch change output
                    paid[addr] = paid.get(addr, Decimal(0)) + Decimal(str(v["value"]))
                    paid_in.setdefault(addr, []).append(txid)

    counts = {"PAID": 0, "UNPAID": 0, "SHORT": 0, "OVER": 0, "NOT IN LIST": 0}
    rows = []
    for addr in sorted(set(expected) | set(paid)):
        e, p = expected.get(addr, Decimal(0)), paid.get(addr, Decimal(0))
        status = ("NOT IN LIST" if addr not in expected else "PAID" if p == e
                  else "UNPAID" if p == 0 else "SHORT" if p < e else "OVER")
        counts[status] += 1
        rows.append({"address": addr, "expected": f"{e:.8f}", "paid": f"{p:.8f}", "status": status,
                     "txids": " ".join(paid_in.get(addr, []))})
    with a.output.open("w", newline="") as fh:
        w = csv.DictWriter(fh, fieldnames=["address", "expected", "paid", "status", "txids"])
        w.writeheader()
        w.writerows(rows)

    te, tp = sum(expected.values(), Decimal(0)), sum(paid.values(), Decimal(0))
    confirmed = {t for l in paid_in.values() for t in l}
    print(f"payout txs in artifacts: {len(txs)}; confirmed (>= {a.min_conf}): {len(confirmed)}")
    print("  " + ", ".join(f"{k} {v}" for k, v in counts.items()))
    print(f"expected {te:,.8f}  paid {tp:,.8f}  difference {tp - te:,.8f} AMMO")
    print(f"wrote {a.output}")
    ok = counts["PAID"] == len(expected) == len(rows)
    print("RECONCILED: every address paid exactly." if ok else "NOT RECONCILED.")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
