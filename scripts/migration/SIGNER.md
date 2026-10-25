# Offline airdrop signer

The signer signs the airdrop's fan-out and payout transactions. It is an `ammocoind` that never connects to anyone and holds no copy of the chain. Each transaction carries the script and amount of every coin it spends (`prevouts`), so the signer doesn't need the chain to sign.

## What holds which key

| Key | Spends | Where it is |
|---|---|---|
| Paper wallet, owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` | The reserve's cold-stake outputs (fan-out transactions) | On paper only. It is typed at a hidden prompt for each signing session and is never stored. |
| Signer wallet (encrypted) | The fan-out addresses (payout batches) | `signer/data/wallet.dat` on the encrypted wallets volume, plus a backup copy on the same volume. Its passphrase is kept with the paper wallet. |

Fan-out change returns to the paper-wallet address.

## Layout (the owner's Mac)

Everything lives on the encrypted disk image `/Volumes/AMMOcoin_Wallets`, in `signer/`:

- `bin/`: `ammocoind` and `ammocoin-cli` from the v1.1.1 macOS ARM64 release. The tarball's SHA-256 is `ec980a57…ee17` and matches `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt`.
- `scripts/`: `migration-sign-offline.py` and `signer-init.py`.
- `data/ammocoin.conf`: `connect=0`, `listen=0`, `dnsseed=0`, `staking=0`, with RPC on `127.0.0.1:37029` only. RPC uses the node's `.cookie`, so no password sits in the config.

Start and stop the signer node:

```
S=/Volumes/AMMOcoin_Wallets/signer
$S/bin/ammocoind -datadir=$S/data -daemon
$S/bin/ammocoin-cli -datadir=$S/data stop
```

## One-time setup

The node starts with an empty wallet. Then run:

```
python3 $S/scripts/signer-init.py --rpc-cookie $S/data/.cookie \
  --count 260 --out $S/fanout-addresses.txt --backup $S/backup-signer-wallet.dat
```

This does four things:

1. It asks twice for a new passphrase (at least 12 characters) and encrypts the wallet.
2. It makes 260 fan-out addresses. The payout needs one per batch, about 205, so the rest are spare.
3. It writes the addresses to `fanout-addresses.txt`. That file holds no secrets: it goes to the online builder, which watches the addresses.
4. It backs up the wallet.

You can run it again: it keeps the existing addresses and only adds what's missing.

## Each signing session

1. Turn Wi-Fi off and unplug Ethernet. The script also refuses to sign if the node has a peer.
2. Start the signer node.
3. Run:
   ```
   python3 $S/scripts/migration-sign-offline.py --input unsigned.json --output signed.json --rpc-cookie $S/data/.cookie
   ```
   - Fan-outs ask for the paper-wallet key.
   - Payout batches ask for the signer wallet passphrase. The wallet is locked again at the end.
4. Stop the signer node. Then turn networking back on and broadcast `signed.json` from the online side.

Typing the key wrong gives "signing incomplete", and nothing is written.

## Tested

The full payout ran on regtest with the v1.1.1 release binary on 2026-10-24:

- The signer node had 0 peers and was at height 0.
- Fan-outs were signed with the typed owner key.
- Payouts were signed from the encrypted signer wallet, which was locked again afterwards.
- A stale input was caught and rebuilt.
- 25 of 25 recipients were paid exactly.
