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
| 6 | `migration-broadcast.py` | online | Checks every input is unspent, then sends, with an audit log. A batch whose own txid is already in the mempool or a block is logged `already_sent` and skipped, so a part-sent file can be broadcast again as is. Stops at a STALE transaction (an input spent by a different transaction) or a rejection. |
| 7 | `migration-prepare.py --from-fan-out fanout.txt` | online, watch-only | The payout batches (≤50 recipients, ≤10M per output). Then repeat steps 5 and 6. |
| 8 | `verify-migration.py --holders … --signed …` | online | Reconciles every payout address against the confirmed payout transactions (not current balances), and writes the CSV that is published. |

**Watch-only setup for steps 4 and 7.** Import the reserve's cold-stake script (one script for all reserve outputs), plus every fan-out and change address:

```
ammocoin-cli importaddress 76a97b63d11452da7b2840e451a37d750ece77eb4a0d94cdea3f67140aa6bab8b080064897a63eca2edbffb6aac514576888ac "" true false
ammocoin-cli importaddress <each fan-out / change address> "" false
```

The fan-out addresses come from the signer wallet (`signer-init.py` writes them to a text file). The change address is the paper-wallet address `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`. Neither may be in a wallet that stakes.

**Options for steps 4–7:**

- **Node CLI with arguments.** `--watch-wallet` (prepare) and `--cli` (broadcast) take a quoted command, split like the other scripts: `--cli "ammocoin-cli -datadir=/path/to/builder"`. A path that exists as given (spaces included) is still run as one program, so a wrapper script works too.
- **`--cli-timeout SEC`** (prepare), or the environment variable `AMMO_CLI_TIMEOUT`. Each node call may take this long. The default is 300 s, because `listunspent` over 100,000+ watched outputs is slow. The flag wins over the variable.
- **Resuming a broadcast.** If a broadcast stops part-way (Ctrl-C, network drop, a node restart), run the same command on the **same signed file** with a new `--log`. Batches already in the mempool or a block show `✓ SENT already` and are logged `already_sent`, with their confirmations. The rest are sent. This is the default (`--skip-sent`). `--no-skip-sent` turns it off: any spent input then stops the run, as before. A STALE batch still stops the run. With the default on, STALE means a different transaction spent the input: stop and investigate.
- **Cold-stake (P2CS) outputs** (pools 3–5, opt-in). Give a holder a `"staker"` field, or pass `--cold-stake-staker S…` to apply one staker to every holder. The holder's `address` is the owner (`A…`, the offline key that can spend). The staker (`S…`) can only stake. `--from-fan-out` then pays that output as `OP_DUP OP_HASH160 OP_ROT OP_IF OP_CHECKCOLDSTAKEVERIFY_LOF <staker> OP_ELSE <owner> OP_ENDIF OP_EQUALVERIFY OP_CHECKSIG` (`76a97b63d114<staker>6714<owner>6888ac`), the script the node's `delegatestake` builds on mainnet. The reserve script above is one of these. Prepare refuses unless the node decodes each such output as `coldstake` with `[staker, owner]`, and refuses outputs under 1 AMMO. The batch records the script under `"cold_stake"`, and broadcast checks it again. The signer needs no change. To check a script by hand, run `ammocoin-cli decodescript <hex>` (read-only).

  ```json
  {"top_holders": [
    {"address": "<POOL3_OWNER_A_ADDRESS>", "balance": "31052139.91421180", "staker": "<S_STAKER_ADDRESS>"}
  ]}
  ```

**Tests:** `python3 scripts/migration/test_migration_prepare.py` and `python3 scripts/migration/test_migration_broadcast.py`. No node is needed. Nothing is signed or sent.

## Other scripts

- **Snapshot tools** (`v1.0-snapshot-tool.py`, `scan-all-balances.py`, `v1.0-blockchain-scanner.py`): how the published snapshot was made. They are not needed for the payout.
- **`verify-claim.py`:** the signed-message claim fallback (AIRDROPS.md §3). It checks the signature over `AMMOcoin v1.1 airdrop claim: <v1.0> pay <v1.1>` and what is still owed (from the reconciliation), and records approved claims. It never sends coins; `--export` writes the approved claims as a holders file for steps 4–6.
- **`distribute-to-top-holders.py`, `verify-disposal-address.py`:** **superseded** (the earlier "Option 2.5" and disposal-address plans). Don't use them for the payout.
- **`v110-blocks-to-v111-bootstrap.py`:** bootstrap conversion for node operators. Not part of the payout.
