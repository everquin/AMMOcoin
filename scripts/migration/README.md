# AMMOcoin v1.0 → v1.1.1 airdrop scripts

These scripts pay every v1.0 balance from the snapshot at v1.0 block 434,881 to the same address on v1.1.1. Payment comes from the block-1 reserve; the 61 signed contributor pledges are taken off first. The process, and what is published, is in [docs/compliance/AIRDROPS.md](../../docs/compliance/AIRDROPS.md). Where the money is held is in [RESERVES.md](../../docs/compliance/RESERVES.md).

## Payout, in order

| Step | Script | Where | What it does |
|---|---|---|---|
| 1 | `build-pledges.py` | anywhere | Rebuilds `docs/migration/data/quartermaster-pledges.csv` from the snapshot (refuses a snapshot with a different SHA-256). |
| 2 | `verify-pledges.py signatures.csv` | any node | Checks each pledge signature against its exact message (`verifymessage`). Exit 1 until all are SIGNED. |
| 3 | `build-payout-holders.py signatures.csv [--full-pay file]` | any node | Writes the payout list: snapshot minus signed pledges. Addresses in `--full-pay` (declined or unsigned at the Nov 1 deadline, AMMO-D-2026-10-25-01) are paid in full. Refuses unless the total is exact. |
| 4 | `migration-prepare.py --fan-out fanout.txt` | online, watch-only | Consolidation transactions (≤450 cold-stake inputs each) funding one address per batch. Rerun after any stale or rejected transaction; it funds only what is missing. |
| 5 | `migration-sign-offline.py --rpc-cookie …` | offline signer | Fan-outs: signs with the paper-wallet key, typed at a hidden prompt. Payout batches: signs from the signer's encrypted wallet. No chain copy needed; refuses if the node has a peer. Setup: [SIGNER.md](SIGNER.md). |
| 6 | `migration-broadcast.py` | online | Checks every input is unspent, then sends, with an audit log. Stops at a STALE transaction. |
| 7 | `migration-prepare.py --from-fan-out fanout.txt` | online, watch-only | The payout batches (≤50 recipients, ≤10M per output). Then repeat steps 5 and 6. |
| 8 | `verify-migration.py` | online | Reconciles every snapshot address against the chain, for publication. |

**Watch-only setup for steps 4 and 7.** Import the reserve's cold-stake script (one script for all reserve outputs), plus every fan-out and change address:

```
ammocoin-cli importaddress 76a97b63d11452da7b2840e451a37d750ece77eb4a0d94cdea3f67140aa6bab8b080064897a63eca2edbffb6aac514576888ac "" true false
ammocoin-cli importaddress <each fan-out / change address> "" false
```

The fan-out addresses come from the signer wallet (`signer-init.py` writes them to a text file). The change address is the paper-wallet address `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`. Neither may be in a wallet that stakes.

**Tests:** `python3 scripts/migration/test_migration_prepare.py`. No node is needed.

## Other scripts

- **Snapshot tools** (`v1.0-snapshot-tool.py`, `scan-all-balances.py`, `v1.0-blockchain-scanner.py`): how the published snapshot was made. They are not needed for the payout.
- **`verify-claim.py`:** the signed-message claim fallback (AIRDROPS.md §3). Its text still describes the withdrawn disposal model; fix it before any claim is processed (AIRDROPS.md §6).
- **`distribute-to-top-holders.py`, `verify-disposal-address.py`:** **superseded** (the earlier "Option 2.5" and disposal-address plans). Don't use them for the payout.
- **`v110-blocks-to-v111-bootstrap.py`:** bootstrap conversion for node operators. Not part of the payout.
