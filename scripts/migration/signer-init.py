#!/usr/bin/env python3
"""
AMMOcoin airdrop: prepare the offline signer's own wallet (see SIGNER.md).

The payout batches spend from fan-out addresses, one per batch. Their keys
live in the signer node's wallet, which this script encrypts (passphrase typed
at a hidden prompt, over RPC, so it never appears in a command line or shell
history). It then makes the fan-out addresses, writes them to a text file
(addresses only, safe to copy to the online builder) and backs the wallet up.
The reserve's paper-wallet key is NOT stored here; migration-sign-offline.py
asks for it each time it signs a fan-out.

Rerunnable: it keeps the "fanout" addresses it already made and adds only
what is missing up to --count.

Usage:
    python3 signer-init.py --rpc-cookie /Volumes/AMMOcoin_Wallets/signer/data/.cookie \\
        --count 260 --out /Volumes/AMMOcoin_Wallets/signer/fanout-addresses.txt \\
        --backup /Volumes/AMMOcoin_Wallets/signer/backup-signer-wallet.dat
"""

import argparse
import getpass
import importlib.util
import sys
from pathlib import Path

spec = importlib.util.spec_from_file_location("signoff", Path(__file__).with_name("migration-sign-offline.py"))
signoff = importlib.util.module_from_spec(spec)
spec.loader.exec_module(signoff)

LABEL = "fanout"


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--rpc-cookie", required=True, type=Path)
    p.add_argument("--rpc-port", type=int, default=37029)
    p.add_argument("--count", type=int, default=260, help="fan-out addresses to have (one per payout batch, plus spare)")
    p.add_argument("--out", required=True, type=Path)
    p.add_argument("--backup", required=True, type=Path, action="append", help="wallet backup path (repeat for a second copy)")
    args = p.parse_args()

    rpc = signoff.Rpc(args.rpc_port, args.rpc_cookie)
    if rpc("getconnectioncount"):
        print("The signer node has peers. It must run with connect=0. ABORT.")
        return 1
    info = rpc("getwalletinfo")
    if "unlocked_until" not in info:
        print("The signer wallet is not encrypted yet. Choose its passphrase now.")
        print("Write it down and keep it with the paper wallet. Without it the fan-out funds can't be paid out.")
        pw = getpass.getpass("New signer wallet passphrase: ")
        if len(pw) < 12 or pw != getpass.getpass("Repeat it: "):
            print("Passphrases differ or are shorter than 12 characters. Nothing changed.")
            return 1
        print(rpc("encryptwallet", pw))
    else:
        pw = getpass.getpass("Signer wallet passphrase (hidden): ")
    rpc("walletpassphrase", pw, 600)
    pw = None
    try:
        have = list(rpc("getaddressesbylabel", LABEL).keys()) if LABEL in rpc("listlabels") else []
        rpc("keypoolrefill", max(100, args.count - len(have) + 10))
        made = [rpc("getnewaddress", LABEL) for _ in range(max(0, args.count - len(have)))]
        addrs = sorted(have) + made
        for b in args.backup:
            rpc("backupwallet", str(b))
            print(f"Backup: {b}")
    finally:
        rpc("walletlock")
    args.out.write_text("\n".join(addrs) + "\n")
    print(f"{len(addrs)} fan-out addresses ({len(made)} new) -> {args.out}")
    print("Copy that file (addresses only) to the online builder; it watches them with importaddress.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
