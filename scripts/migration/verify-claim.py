#!/usr/bin/env python3
"""
AMMOcoin v1.0 -> v1.1.1 airdrop: check a signed-message claim (AIRDROPS.md section 3).

The fallback for a snapshot address the payout missed or paid short. The
holder signs, with the key of the v1.0 address, exactly:

    AMMOcoin v1.1 airdrop claim: <V1.0_ADDRESS> pay <V1.1_ADDRESS>

Naming the destination in the signed text stops a copied signature from
being redirected. This script checks:

  1. the snapshot file is the published one (SHA-256);
  2. the v1.0 address is in the reconciliation (verify-migration.py output)
     and is still owed something: expected - paid - claims already approved;
  3. the signature verifies against that exact message (`verifymessage`);
  4. the v1.1 address is valid.

It never sends coins. An approved claim is appended to the claims CSV; the
claims are then paid from the reserve like the airdrop itself (watch-only
build, offline signing, logged broadcast) using `--export` as the holders
file for migration-prepare.py. After broadcast, fill in `paid_txid` for each
row; --export skips rows that have one.

Usage:
    python3 scripts/migration/verify-claim.py --v10 A... --v11 A... --signature "H...=" \\
        --reconciliation reconciliation.csv --claims claims.csv --cli "ammocoin-cli -datadir=..."
    python3 scripts/migration/verify-claim.py --claims claims.csv --export claims-payout.json
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import shlex
import subprocess
import sys
from datetime import datetime, timezone
from decimal import Decimal
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SNAPSHOT = ROOT / "docs/migration/data/v1.0-complete-balance-snapshot.json"
SNAPSHOT_SHA256 = "9da3c0d1c4b703d713a4f00c543e3e0db8f53c0c846b49499e218e9d8acf751c"
FIELDS = ["v10_address", "v11_address", "amount", "message", "signature", "approved_at", "paid_txid"]


def message_for(v10: str, v11: str) -> str:
    return f"AMMOcoin v1.1 airdrop claim: {v10} pay {v11}"


def run(cli: list[str], *args: str) -> tuple[bool, str]:
    r = subprocess.run(cli + list(args), capture_output=True, text=True, timeout=30)
    return r.returncode == 0, (r.stdout if r.returncode == 0 else r.stderr).strip()


def load_claims(path: Path) -> list[dict]:
    return list(csv.DictReader(path.open())) if path.exists() else []


def export(claims_path: Path, out: Path) -> int:
    unpaid = [c for c in load_claims(claims_path) if not c.get("paid_txid")]
    out.write_text(json.dumps({"top_holders": [{"address": c["v11_address"], "balance": c["amount"]} for c in unpaid]}, indent=2))
    total = sum((Decimal(c["amount"]) for c in unpaid), Decimal(0))
    print(f"wrote {out}: {len(unpaid)} approved, unpaid claim(s), {total:,.8f} AMMO")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--v10", help="the v1.0 snapshot address")
    ap.add_argument("--v11", help="the v1.1 address to pay (the same address where possible)")
    ap.add_argument("--signature")
    ap.add_argument("--reconciliation", type=Path, help="verify-migration.py output CSV")
    ap.add_argument("--claims", required=True, type=Path, help="approved-claims CSV (created if missing)")
    ap.add_argument("--cli", default="ammocoin-cli", help="ammocoin-cli command (quoted, with any -datadir)")
    ap.add_argument("--export", type=Path, help="write the unpaid approved claims as a migration-prepare.py holders file")
    a = ap.parse_args()
    if a.export:
        return export(a.claims, a.export)
    if not (a.v10 and a.v11 and a.signature and a.reconciliation):
        ap.error("--v10, --v11, --signature and --reconciliation are required")
    cli = shlex.split(a.cli)
    v10, v11, sig = a.v10.strip(), a.v11.strip(), a.signature.strip()

    if hashlib.sha256(SNAPSHOT.read_bytes()).hexdigest() != SNAPSHOT_SHA256:
        sys.exit("snapshot file is not the published one; refusing")
    if v10 not in json.loads(SNAPSHOT.read_bytes())["balances"]:
        print(f"REFUSED: {v10} is not in the v1.0 snapshot at block 434,881.")
        return 1

    rec = {r["address"]: r for r in csv.DictReader(a.reconciliation.open())}
    if v10 not in rec:
        print(f"REFUSED: {v10} is not in the reconciliation. Run verify-migration.py over the full payout list first.")
        return 1
    claims = load_claims(a.claims)
    approved = sum((Decimal(c["amount"]) for c in claims if c["v10_address"] == v10), Decimal(0))
    owed = Decimal(rec[v10]["expected"]) - Decimal(rec[v10]["paid"]) - approved
    if owed <= 0:
        print(f"REFUSED: nothing is owed to {v10} (expected {rec[v10]['expected']}, paid {rec[v10]['paid']}, "
              f"claims already approved {approved:.8f}).")
        return 1

    msg = message_for(v10, v11)
    ok, out = run(cli, "verifymessage", v10, sig, msg)
    if not ok and "Malformed base64" not in out:
        sys.exit(f"verifymessage failed: {out}")
    if out != "true":
        print("REFUSED: the signature does not match. It must be made with the v1.0 address's key, over exactly:")
        print(f"  {msg}")
        return 1
    ok, out = run(cli, "validateaddress", v11)
    if not ok or not json.loads(out).get("isvalid"):
        print(f"REFUSED: {v11} is not a valid AMMOcoin address.")
        return 1

    new = not a.claims.exists()
    with a.claims.open("a", newline="") as fh:
        w = csv.DictWriter(fh, fieldnames=FIELDS)
        if new:
            w.writeheader()
        w.writerow({"v10_address": v10, "v11_address": v11, "amount": f"{owed:.8f}", "message": msg,
                    "signature": sig, "approved_at": datetime.now(timezone.utc).isoformat(timespec="seconds"),
                    "paid_txid": ""})
    print(f"APPROVED: {owed:,.8f} AMMO owed to {v10}, to be paid to {v11}. Recorded in {a.claims}.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
