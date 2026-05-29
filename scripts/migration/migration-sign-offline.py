#!/usr/bin/env python3
"""
AMMOcoin v1.0 → v1.1 migration: step 2 of 3 — SIGN (OFFLINE).

Run this on an AIR-GAPPED machine that holds the migration-fund private
keys. It signs every unsigned tx in the input artifact and writes a
signed-distribution.json. No daemon, no network, no RPC.

The machine MUST have a running ammocoind locally (or another isolated
signing tool that understands `signrawtransaction`). The daemon should
be started with `-disablewallet=0`, the migration-fund private keys
imported via `importprivkey`, and the host's network interface disabled
or air-gapped.

Usage:
    python3 migration-sign-offline.py \\
        --input unsigned-distribution-YYYYMMDD.json \\
        --output signed-distribution.json \\
        --cli ammocoin-cli
"""

import argparse
import json
import subprocess
import sys
from datetime import datetime
from pathlib import Path


def cli(binary: str, *args: str) -> str:
    proc = subprocess.run([binary, *args], capture_output=True, text=True, timeout=60)
    if proc.returncode != 0:
        raise RuntimeError(f"ammocoin-cli {' '.join(args)} failed: {proc.stderr.strip()}")
    return proc.stdout.strip()


def sign_batch(binary: str, batch: dict, batch_idx: int) -> dict:
    raw = cli(binary, "signrawtransaction", batch["unsigned_hex"])
    parsed = json.loads(raw)
    if not parsed.get("complete"):
        errs = parsed.get("errors", [])
        raise RuntimeError(
            f"Batch {batch_idx}: signing incomplete. "
            f"Missing keys or scripts? Errors: {errs}"
        )

    # Sanity: decode the signed tx and confirm outputs match what we expected.
    decoded = json.loads(cli(binary, "decoderawtransaction", parsed["hex"]))
    expected_outputs = {a: float(v) for a, v in batch["outputs"].items()}
    seen_outputs: dict[str, float] = {}
    for v in decoded.get("vout", []):
        spk = v.get("scriptPubKey", {})
        for addr in spk.get("addresses", []) or ([spk["address"]] if "address" in spk else []):
            seen_outputs[addr] = seen_outputs.get(addr, 0.0) + float(v["value"])
    for addr, amt in expected_outputs.items():
        seen = seen_outputs.get(addr, 0.0)
        if abs(seen - amt) > 0.00000001:
            raise RuntimeError(
                f"Batch {batch_idx}: output mismatch for {addr}: "
                f"expected {amt:.8f}, signed tx sends {seen:.8f}. ABORT."
            )

    return {
        **batch,
        "signed_hex": parsed["hex"],
        "signed_txid": decoded["txid"],
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--input", required=True, type=Path)
    p.add_argument("--output", required=True, type=Path)
    p.add_argument("--cli", default="ammocoin-cli")
    args = p.parse_args()

    print("AMMOcoin v1.0→v1.1 distribution SIGN (step 2 of 3) — OFFLINE")
    print("=" * 64)
    print("Confirm this machine is AIR-GAPPED. Disconnect Ethernet / Wi-Fi NOW.")
    print("If the machine is not air-gapped, abort with Ctrl+C.")
    if input("Type 'OFFLINE' to confirm: ").strip() != "OFFLINE":
        print("Aborted.")
        return 1

    artifact = json.loads(args.input.read_text())
    if artifact.get("schema_version") != "1":
        raise RuntimeError(
            f"Unknown schema_version {artifact.get('schema_version')!r}; expected '1'."
        )

    print(f"  Batches to sign: {len(artifact['batches'])}")
    print(f"  Total to sign:   {artifact['sum_of_balances_ammo']:,.8f} AMMO")
    print()

    signed_batches = []
    for batch in artifact["batches"]:
        idx = batch["batch_index"]
        print(f"Signing batch {idx + 1}/{len(artifact['batches'])} "
              f"({len(batch['recipients'])} recipients)...")
        signed_batches.append(sign_batch(args.cli, batch, idx))

    signed_artifact = {
        **artifact,
        "signed_at": datetime.utcnow().isoformat() + "Z",
        "batches": signed_batches,
    }
    args.output.write_text(json.dumps(signed_artifact, indent=2))
    print()
    print(f"✓ Wrote {args.output}")
    print()
    print("Next steps:")
    print( "  1. Carry the output file to an ONLINE machine via removable media.")
    print(f"  2. Run: python3 migration-broadcast.py --input {args.output.name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
