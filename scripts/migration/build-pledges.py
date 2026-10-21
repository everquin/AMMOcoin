#!/usr/bin/env python3
"""
Build the QuarterMaster pledge list from the v1.0 snapshot (AMMO-D-2026-10-18-12).

The 61 largest v1.0 holders are early contributors who agreed to fund the
QuarterMaster reserve. Each pledges the same share of their snapshot balance;
the pledged amount is deducted from their airdrop and simply stays in the
block-1 reserve. Nobody sends anything.

    needed = 40,000,000 (tiers) + 50,000,000 (contributor reserve)
           - (250,000,000 - snapshot total)      # reserve left after a full airdrop
           + 41,700                               # zerocoin set aside, unclaimable

Pledges are rounded down to the satoshi; the leftover satoshis go to the
largest holders one each, so the pledges add up to `needed` exactly.

Output: docs/migration/data/quartermaster-pledges.csv, with the exact message
each contributor signs (signmessage, from the pledging address).

Usage:  python3 scripts/migration/build-pledges.py [--check]
        --check  rebuild in memory and fail if the committed CSV differs.
"""
from __future__ import annotations

import csv
import hashlib
import io
import json
import sys
from decimal import ROUND_DOWN, Decimal
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SNAPSHOT = ROOT / "docs/migration/data/v1.0-complete-balance-snapshot.json"
OUT = ROOT / "docs/migration/data/quartermaster-pledges.csv"

SNAPSHOT_SHA256 = "9da3c0d1c4b703d713a4f00c543e3e0db8f53c0c846b49499e218e9d8acf751c"
SNAPSHOT_HEIGHT = 434881
BLOCK1_RESERVE = Decimal("250000000")
TIERS = Decimal("40000000")
CONTRIBUTOR_RESERVE = Decimal("50000000")
ZEROCOIN_SET_ASIDE = Decimal("41700")
CONTRIBUTORS = 61  # the 61 largest snapshot addresses (owner, 2026-10-18)
SAT = Decimal("0.00000001")

MESSAGE = (
    "AMMOcoin v1.1 QuarterMaster pledge. Address {address}. "
    "Snapshot v1.0 block {height}, file sha256 {sha}. "
    "I contribute {pledge} AMMO of my airdrop to the QuarterMaster reserve; "
    "my airdrop is reduced by that amount. Voluntary; nothing is given in return."
)


def build() -> tuple[str, dict]:
    raw = SNAPSHOT.read_bytes()
    sha = hashlib.sha256(raw).hexdigest()
    if sha != SNAPSHOT_SHA256:
        sys.exit(f"snapshot sha256 {sha} != {SNAPSHOT_SHA256}; refusing to build")
    snap = json.loads(raw, parse_float=Decimal)
    balances = {a: Decimal(str(v)) for a, v in snap["balances"].items()}
    total = sum(balances.values())

    needed = TIERS + CONTRIBUTOR_RESERVE - (BLOCK1_RESERVE - total) + ZEROCOIN_SET_ASIDE
    top = sorted(balances.items(), key=lambda kv: (-kv[1], kv[0]))[:CONTRIBUTORS]
    base = sum(v for _, v in top)
    share = needed / base

    pledges = [(a, v, (v * share).quantize(SAT, rounding=ROUND_DOWN)) for a, v in top]
    short = int((needed - sum(p for _, _, p in pledges)) / SAT)
    for i in range(short):  # leftover satoshis to the largest holders, one each
        a, v, p = pledges[i]
        pledges[i] = (a, v, p + SAT)
    assert sum(p for _, _, p in pledges) == needed

    buf = io.StringIO()
    w = csv.writer(buf, lineterminator="\n")
    w.writerow(["rank", "address", "snapshot_balance", "pledge", "airdrop_after_pledge", "message"])
    for i, (a, v, p) in enumerate(pledges, 1):
        msg = MESSAGE.format(address=a, height=SNAPSHOT_HEIGHT, sha=SNAPSHOT_SHA256[:16], pledge=f"{p:.8f}")
        w.writerow([i, a, f"{v:.8f}", f"{p:.8f}", f"{v - p:.8f}", msg])

    summary = {
        "snapshot_total": total, "contributors": len(pledges), "contributors_balance": base,
        "needed": needed, "share_percent": (share * 100).quantize(Decimal("0.000001")),
        "reserve_after_airdrop": BLOCK1_RESERVE - total + needed,
        "quartermaster_and_contributor": TIERS + CONTRIBUTOR_RESERVE,
        "zerocoin_set_aside": ZEROCOIN_SET_ASIDE,
    }
    return buf.getvalue(), summary


def main() -> None:
    text, s = build()
    if "--check" in sys.argv:
        if not OUT.exists() or OUT.read_text() != text:
            sys.exit(f"{OUT.relative_to(ROOT)} differs from a fresh build")
        print("pledges: committed CSV matches a fresh build")
    else:
        OUT.write_text(text)
        print(f"wrote {OUT.relative_to(ROOT)}")
    for k, v in s.items():
        print(f"  {k}: {v:,}" if isinstance(v, Decimal) else f"  {k}: {v}")


if __name__ == "__main__":
    main()
