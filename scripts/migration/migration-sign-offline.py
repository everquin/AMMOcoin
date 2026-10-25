#!/usr/bin/env python3
"""
AMMOcoin v1.0 → v1.1 migration: step 2 of 3 — SIGN (OFFLINE).

Run this on an AIR-GAPPED machine that holds the migration-fund private
keys. It signs every unsigned tx in the input artifact and writes a
signed-distribution.json. It needs a local ammocoind and no network.

Two ways to sign:

  --rpc-cookie (recommended): a local ammocoind with no peers and no chain
  (see SIGNER.md). Each input's script and amount come from the artifact
  ("prevouts"), so the node needs no copy of the chain. The script talks to
  the node over JSON-RPC on 127.0.0.1, so secrets never appear in a command
  line or shell history, and it refuses to sign while the node has a peer.
  Fan-out txs spend the reserve: the paper-wallet key is typed at a hidden
  prompt and never stored. Payout batches spend the fan-out addresses, whose
  keys live in the signer's own encrypted wallet (signer-init.py).

  --cli (older): the keys are imported into the signing node's wallet and
  the node needs a synced chain.

Usage:
    python3 migration-sign-offline.py --input unsigned.json --output signed.json \\
        --rpc-cookie /Volumes/AMMOcoin_Wallets/signer/data/.cookie
    python3 migration-sign-offline.py --input unsigned.json --output signed.json --cli ammocoin-cli
"""

import argparse
import base64
import getpass
import json
import urllib.error
import urllib.request
import subprocess
import sys
from datetime import datetime
from pathlib import Path


def cli(binary: str, *args: str) -> str:
    proc = subprocess.run([binary, *args], capture_output=True, text=True, timeout=60)
    if proc.returncode != 0:
        raise RuntimeError(f"ammocoin-cli {' '.join(args)} failed: {proc.stderr.strip()}")
    return proc.stdout.strip()


class Rpc:
    """JSON-RPC to a local node, so the key travels in a request body, not argv."""
    def __init__(self, port: int, cookie: Path):
        self.url = f"http://127.0.0.1:{port}/"
        self.auth = base64.b64encode(cookie.read_text().strip().encode()).decode()

    def __call__(self, method: str, *params):
        req = urllib.request.Request(self.url, data=json.dumps({"id": 0, "method": method, "params": list(params)}).encode(),
                                     headers={"Authorization": "Basic " + self.auth, "Content-Type": "application/json"})
        try:
            body = json.loads(urllib.request.urlopen(req, timeout=120).read())
        except urllib.error.HTTPError as e:  # the node answers RPC errors with HTTP 500 + a JSON body
            body = json.loads(e.read())
        if body.get("error"):
            raise RuntimeError(f"{method} failed: {body['error'].get('message')}")
        return body["result"]


def is_fanout(batch: dict) -> bool:
    return str(batch["batch_index"]).startswith("fanout")


def sign_batch(signer, batch: dict, batch_idx, key: str | None = None) -> dict:
    """signer is a cli path (wallet keys, synced chain) or an Rpc (prevouts from
    the artifact; `key` for the reserve inputs, else the unlocked signer wallet)."""
    if not isinstance(signer, Rpc):
        parsed = json.loads(cli(signer, "signrawtransaction", batch["unsigned_hex"]))
        decode = lambda h: json.loads(cli(signer, "decoderawtransaction", h))
    else:
        prev = batch.get("prevouts")
        if not prev or [(p["txid"], p["vout"]) for p in prev] != [(i["txid"], i["vout"]) for i in batch["inputs"]]:
            raise RuntimeError(f"Batch {batch_idx}: no prevouts for its inputs. Rebuild it with the current migration-prepare.py. ABORT.")
        prevtxs = [{**p, "amount": float(p["amount"])} for p in prev]
        parsed = signer("signrawtransaction", batch["unsigned_hex"], prevtxs, *([[key]] if key else []))
        decode = lambda h: signer("decoderawtransaction", h)
    if not parsed.get("complete"):
        errs = parsed.get("errors", [])
        raise RuntimeError(
            f"Batch {batch_idx}: signing incomplete. "
            f"Missing keys or scripts? Errors: {errs}"
        )

    # Sanity: decode the signed tx and confirm outputs match what we expected.
    decoded = decode(parsed["hex"])
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

    size = len(parsed["hex"]) // 2
    if size > 100_000:  # MAX_STANDARD_TX_SIZE: a node would refuse to relay it
        raise RuntimeError(f"Batch {batch_idx}: signed tx is {size:,} bytes (> 100,000). Lower MAX_INPUTS_PER_TX. ABORT.")

    return {
        **batch,
        "signed_bytes": size,
        "signed_hex": parsed["hex"],
        "signed_txid": decoded["txid"],
    }


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--input", required=True, type=Path)
    p.add_argument("--output", required=True, type=Path)
    p.add_argument("--cli", default="ammocoin-cli")
    p.add_argument("--rpc-cookie", type=Path, help="sign on a local node over RPC (the signer node's .cookie)")
    p.add_argument("--rpc-port", type=int, default=37029)
    args = p.parse_args()
    signer = args.cli
    if args.rpc_cookie:
        signer = Rpc(args.rpc_port, args.rpc_cookie)
        peers = signer("getconnectioncount")
        if peers:
            print(f"The signing node has {peers} peer(s). It must run with connect=0, and networking must be off. ABORT.")
            return 1

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

    batches = artifact["batches"]
    key, unlocked = None, False
    if isinstance(signer, Rpc):
        if any(is_fanout(x) for x in batches):
            key = getpass.getpass("Reserve owner key, from the paper wallet (hidden; never stored): ").strip()
            if not key:
                print("No key. Aborted.")
                return 1
        if not all(is_fanout(x) for x in batches):
            signer("walletpassphrase", getpass.getpass("Signer wallet passphrase (hidden): "), 1800)
            unlocked = True
    print(f"  Batches to sign: {len(artifact['batches'])}")
    print(f"  Total to sign:   {artifact['sum_of_balances_ammo']:,.8f} AMMO")
    print()

    signed_batches = []
    try:
        for batch in batches:
            idx = batch["batch_index"]
            name = f"batch {idx + 1}" if isinstance(idx, int) else str(idx)
            print(f"Signing {name} of {len(batches)} "
                  f"({len(batch['recipients'])} recipients, {len(batch['inputs'])} inputs)...")
            signed_batches.append(sign_batch(signer, batch, idx, key if is_fanout(batch) else None))
    finally:
        key = None
        if unlocked:
            signer("walletlock")

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
