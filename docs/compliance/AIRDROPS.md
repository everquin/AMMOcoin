# AMMOcoin airdrops: how they work and what is published

This document is the compliance record for the **v1.0 -> v1.1 migration airdrop**: how it works, what the project publishes so anyone can audit it, and why it is not a sale. It applies AMMO-P-01, AMMO-P-02, AMMO-P-03, AMMO-P-06 and AMMO-P-13 ([PRINCIPLES.md](PRINCIPLES.md)) and is recorded as decision AMMO-D-2026-10-17-10 ([DECISIONS.md](DECISIONS.md)). User instructions: [docs/migration/V1.0_BALANCE_AIRDROP.md](../migration/V1.0_BALANCE_AIRDROP.md).

Not legal advice. Counsel review status: **pending**.

> Every value marked **TO BE PUBLISHED** below is a placeholder. It must be replaced with the real value, in a commit under the owner's identity, before the airdrop is described anywhere as complete. Nothing in this file may be filled in from memory or estimated.

---

## 1. What the airdrop is

The v1.1 chain is a new chain (new genesis, new network magic from v1.1.1). The AMMO people held on the old v1.0 chain does not exist on it automatically. The airdrop gives each v1.0 holder the same balance on v1.1, at the same address, paid out of the block-1 reserve.

| Item | Value |
|---|---|
| Source chain | AMMOcoin v1.0 |
| Snapshot height | **v1.0 block 434,881** |
| Snapshot block hash | `c23bdb63ff149251b4cdcf401d579118342cf3ca4af1df0e34f4ecbdce2067d9` (as recorded in the snapshot file's `snapshot_info`) |
| Snapshot file | `docs/migration/data/v1.0-complete-balance-snapshot.json` (10,080 addresses, 481,712 UTXOs, as recorded in its `snapshot_info`) |
| Paid from | the block-1 reserve, block 1 output `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u` (250,000,000 AMMO, `GetBlockValue(1)` in `source/src/validation.cpp`) |
| Paid to | the **same address** that held the balance at the snapshot |
| Amount | exactly the snapshot balance of that address; nothing is added, nothing is deducted |
| What the holder does | nothing (keep the v1.0 `wallet.dat`; its keys control the same address on v1.1) |
| Deadline | none |

### Order of use of the block-1 reserve (AMMO-P-06)

1. The airdrop is paid **first**.
2. Only what remains after the airdrop (including any amounts held back for signed-message claims, section 3, and the contributors' pledges below) funds the QuarterMaster reserve that holds the structured-release tier positions (AMMO-D-2026-10-17-02).

This order is an off-chain commitment. It becomes checkable only once the records in section 4 are published.

### Contributor pledges (AMMO-D-2026-10-18-12)

The QuarterMaster reserve (40,000,000 tiers + 50,000,000 contributor reserve) is larger than what a full airdrop leaves in the block-1 reserve (17,602,251.54978477). The 61 largest v1.0 holders are early contributors who agreed to make up the difference: each pledges **33.121679%** of their snapshot balance, and their airdrop is paid minus that pledge. The pledged AMMO never leaves the block-1 reserve.

| | AMMO |
|---|---|
| Block-1 reserve | 250,000,000.00000000 |
| Snapshot total (10,080 addresses) | 232,397,748.45021523 |
| Pledged by the 61 contributors (holding 218,707,052.19975480) | 72,439,448.45021523 |
| Airdrop actually paid (snapshot − pledges) | 159,958,300.00000000 |
| Set aside: unattributed v1.0 coins, unclaimable until the scan in section 6 (section 4, supply difference) | 41,700.00000000 |
| **Left for the QuarterMaster and contributor reserves** | **90,000,000.00000000** |

- Each pledge is a `signmessage` signature from the pledging address over the exact text in `docs/migration/data/quartermaster-pledges.csv` (built by `scripts/migration/build-pledges.py`; `--check` proves the file matches a fresh build). Signatures are checked with `scripts/migration/verify-pledges.py` and published.
- The holder signs, and no wallet or key is collected from anyone. Where the project holds the key for coins that belong to someone else, it signs only after that person agrees in writing; the consent is kept in the owner's private pledge tracker, and the airdrop record publishes how many pledges were signed this way and their total (AMMO-D-2026-10-25-01).
- Pledges are voluntary and nothing is given in return — no tier position, reward or payment.
- Replies close on **November 1, 2026** (AMMO-D-2026-10-25-01). A pledge address that has not signed by then, or declines, is paid its full snapshot balance (`build-payout-holders.py --full-pay`); unsigned holders are never paid less. The payout is built once every pledge is signed or listed as full-pay, and the resulting shortfall in the QuarterMaster reserve is published with the airdrop record.
- Disclosure: these 61 early holders hold 94.1% of the v1.0 snapshot; after the pledges they receive 146,267,603.75 of the 159,958,300.00 AMMO paid out.

---

## 2. How the payout is made

1. **Snapshot.** The v1.0 UTXO set at block 434,881 is reduced to one balance per address (`scripts/migration/v1.0-snapshot-tool.py`). The result is the snapshot file above. Its SHA256 is published (section 4) so that the list cannot be changed afterwards without it being visible.
2. **Build** on an online node with a **watch-only** wallet. The block-1 reserve is held as cold-stake outputs that all share one script (owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`, staker `SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY`; see [RESERVES.md](RESERVES.md)). The builder watches that script, not the owner address: `importaddress 76a97b63d11452da7b2840e451a37d750ece77eb4a0d94cdea3f67140aa6bab8b080064897a63eca2edbffb6aac514576888ac "" true false`. It also watches the funding (fan-out) and change addresses, which belong to the signing wallet and must not be in a staking wallet. Then `scripts/migration/migration-prepare.py` runs two passes:
   - **`--fan-out`:** consolidation transactions of at most 450 reserve inputs each (under the 100 kB standard size), funding one address per payout batch. The pass is idempotent: it funds only what each batch address still lacks (mempool included). After a rejected or stale transaction you simply run it again.
   - **`--from-fan-out`:** the payout batches, at most 50 recipients each, each spending its own funding address.

   Both passes refuse to write their output unless the total matches the payout file. Fees are sized to each transaction, at five times the node's relay fee.
3. **Sign offline** (`scripts/migration/migration-sign-offline.py`, set up as in [SIGNER.md](../../scripts/migration/SIGNER.md)). The signer is a local node with networking off, `connect=0` and no copy of the chain: each transaction carries the script and amount of every coin it spends, and the signer refuses to run while its node has a peer. Fan-out transactions spend the reserve, so the paper-wallet key is typed at a hidden prompt for each signing session and never stored. Payout batches spend the fan-out addresses, whose keys are in the signer's own encrypted wallet (backed up on the encrypted wallets volume). Fan-out change returns to the paper-wallet address. The signer refuses a transaction over 100 kB. Neither key ever touches an online machine.
4. **Broadcast** (`scripts/migration/migration-broadcast.py`). Before sending each transaction it checks every input is still unspent, on chain and in the mempool. ammo-02 keeps staking the reserve during the payout, so a fan-out input can be spent by a stake between build and broadcast. The tool then stops at that transaction ("STALE"), and the operator reruns the fan-out pass, which builds only what is missing. A stale **payout** input means something is wrong: stop and investigate. An audit log of every txid is written.
5. **Reconcile.** Every snapshot address is checked against the v1.1 chain (`scripts/migration/verify-migration.py`), and the results are published (section 4).

The holder is never contacted, never asked to register, and never asked to send anything.

---

## 3. Fallback: signed-message claim

Some balances cannot be paid automatically to the same address, for example:

- an address the payout batch could not pay (a script type the v1.1 payout cannot target, or an output the snapshot tool could not attribute to a single address);
- an address that was missed or paid wrongly (found in reconciliation or reported by a holder).

For these, and only these, the holder proves ownership of the v1.0 address with a signature. A signature proves control of the key **without revealing it**.

1. On any v1.0 wallet that holds the key (offline is fine):
   ```bash
   ammocoin-cli signmessage "V1.0_ADDRESS" "AMMOcoin v1.1 airdrop claim: V1.0_ADDRESS pay V1.1_ADDRESS"
   ```
   `V1.1_ADDRESS` is the same address where possible, otherwise a v1.1 address the holder controls. Naming the destination in the signed text stops a copied signature from being redirected.
2. The holder submits the v1.0 address, the exact message and the signature through the channel announced on the AMMOcoin GitHub repository.
3. The project checks the claim with `scripts/migration/verify-claim.py`:
   - the signature, with `verifymessage`, against the v1.0 address and that exact message;
   - that the address is in the snapshot;
   - what is still owed, from the reconciliation: expected minus paid, minus any claim already approved. No double payment.

   The script never sends coins. It records the approved claim.
4. The amount still owed is paid to the named v1.1 address from the block-1 reserve, the same way as the airdrop: watch-only build, offline signing, logged broadcast (`verify-claim.py --export` writes the payout list). The txid is added to the published claim record (section 4).

What a claim never involves: sending coins, paying a fee, sharing a private key, seed phrase or wallet file, or a deadline. Anyone who asks for any of these is not the project.

---

## 4. What is published

All of the following are published in this repository (and linked from ammocoin.org), so anyone can check the airdrop against the chain with a block explorer or their own node.

| Record | Status / value |
|---|---|
| Snapshot height and block hash | v1.0 block 434,881, `c23bdb63ff149251b4cdcf401d579118342cf3ca4af1df0e34f4ecbdce2067d9` (from the file; owner to confirm against a v1.0 node) |
| SHA256 of the snapshot file | `9da3c0d1c4b703d713a4f00c543e3e0db8f53c0c846b49499e218e9d8acf751c` = SHA256 of `docs/migration/data/v1.0-complete-balance-snapshot.json` as committed in `d25c53d39`. **TO BE CONFIRMED** by the owner as the canonical snapshot used for the payout; if a different file is used, publish that file and its hash instead |
| Snapshot totals | 10,080 addresses, 232,397,748.45021523 AMMO (file `snapshot_info.total_supply`). The file records `expected_supply` 232,439,448.45021522 and `supply_match: false` (difference 41,700 AMMO). **TO BE PUBLISHED:** explanation of the difference before payout |
| Airdrop payout transactions | **TO BE PUBLISHED:** list of txids (one row per batch: txid, block height, number of outputs, total AMMO), plus the broadcast audit log |
| Per-address reconciliation | **TO BE PUBLISHED:** CSV of snapshot address, snapshot balance, payout txid, v1.1 amount received, status (paid / claim pending / claim paid) |
| Contributor pledges | `docs/migration/data/quartermaster-pledges.csv` (61 addresses, 72,439,448.45021523 AMMO). **TO BE PUBLISHED:** the signatures and the `verify-pledges.py` result; the number and total signed by the project as custodian with written consent; the addresses paid in full after the November 1, 2026 deadline and the resulting reserve shortfall (D-2026-10-25-01) |
| Signed-message claims | **TO BE PUBLISHED:** running list of v1.0 address, v1.1 address, amount, payout txid, date (signatures may be published too; they reveal nothing secret) |
| Block-1 reserve address | `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u` (block 1 output; `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` is only the unspendable genesis output) |
| Reserve change / holding addresses used by the payout | **TO BE PUBLISHED** |
| Amount held back for signed-message claims, and its address | **TO BE PUBLISHED** |
| QuarterMaster reserve address(es) | **TO BE PUBLISHED** (gap G-06) |
| Contributor (AMMOgeek/AMMOfreak) reserve address(es) | **TO BE PUBLISHED** |
| Disposal address (v1.1.0 process, withdrawn) | **None was ever published.** `verify-disposal-address.py` still holds the placeholder `PENDING-AMMO-CORE-PUBLICATION`, no publication tag exists, and no repository, website page or document names one (checked 2026-10-25). Anyone who sent v1.0 coins somewhere under the withdrawn instructions should come forward; coins moved before the snapshot are counted at the address that received them. |
| Reconciliation statement | **TO BE PUBLISHED:** block-1 reserve 250,000,000 AMMO = airdrop paid + claims paid + claim hold-back + QuarterMaster reserve + contributor reserve + fees, with the addresses above |

When a value is published, replace its **TO BE PUBLISHED** marker in a commit, add the commit SHA to AMMO-D-2026-10-17-10, and update gap G-06.

---

## 5. Why this is not a sale

- **No payment.** Nobody pays anything, in any currency, coin or goods, to receive the airdrop or to make a claim. There is no fee.
- **No purchase.** Nothing is offered for sale. The airdrop restores balances people already held on the v1.0 chain, to the same addresses, in the same amounts. No one can get more by paying, and no one is offered AMMO who did not already hold it at the snapshot.
- **No solicitation.** Holders are not asked to send coins, register, sign up, or act by a deadline. The only action ever asked of anyone is a signature, and only when the automatic payout could not reach them. The 61 founding contributors are asked to reply to their pledge request by November 1, 2026 (AMMO-D-2026-10-25-01); that date can only stop a pledge being taken, never reduce what anyone is paid: no reply means the full snapshot balance.
- **No promise of value.** The project assigns AMMO no value and publishes no price, exchange rate, market cap or fiat equivalent for it (AMMO-P-03). Airdrop records state AMMO amounts only, never a fiat value. The airdrop is not described as a gift of value, a reward, an opportunity or an investment.
- **No raise.** The airdrop brings in no money and is not linked to any fundraising (AMMO-P-01). Reserve AMMO is never sold (AMMO-P-02).

Copy about the airdrop (site, app, social posts, release notes) must follow sections 1 and 5 and pass [REVIEW_CHECKLIST.md](REVIEW_CHECKLIST.md).

---

## 6. Known inconsistencies to fix before the payout

- The snapshot file records `supply_match: false`: its address balances total 232,397,748.45021523, against an `expected_supply` of 232,439,448.45021522, which is 41,699.99999999 less. **The zerocoin explanation is wrong** (checked 2026-10-25 on the v1.0 node ammo-13):
  - The zerocoin supply has been frozen at 568,897 since at least block 300,000. That doesn't match 41,700.
  - At block 409,459, the total of all unspent outputs (`gettxoutsetinfo`, 219,728,448.45021523) is the money supply minus 50. The same holds at block 434,881: `expected_supply` is the full unspent-output total.
  - So the 41,700 is held by unspent outputs that the snapshot did not attribute to any address. That would be non-standard scripts, such as pay-to-pubkey or multisig. The snapshot counts 481,712 outputs, while the v1.0 coin set already held 1,254,670 at block 409,459.
  - To settle it, scan the coin set at block 434,881 by script type. Only ammo-11 holds the v1.0 chain that far (tip 435,172; its daemon has been stopped since 2026-04-09). Until that scan is done, the 41,700 is set aside as unclaimable (AMMO-D-2026-10-18-12). If the scan finds pay-to-pubkey outputs, they belong to an address and should be added to the payout.
- `scripts/migration/migration-prepare.py` takes its `--holders` file from `scripts/migration/build-payout-holders.py`, which pays `airdrop_after_pledge` to the pledging addresses that signed and the full snapshot balance to any listed with `--full-pay` (AMMO-D-2026-10-25-01), and refuses to write anything unless every pledge is either a verified signature or full-pay (total 159,958,300.00000000 AMMO to 10,080 addresses, plus any pledges paid in full). Decided (AMMO-D-2026-10-18-13): the 10,000,000 per-recipient cap stays; `ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL` (24,713,345.21078793 after its pledge) is paid in three outputs of at most 10M, each in its own transaction.
- Fixed 2026-10-25 (PR "Airdrop readiness 2/2"):
  - `migration-prepare.py` assumed the reserve was a few large plain outputs and built a single fan-out transaction. The reserve is now 4,996 cold-stake outputs of 50,000, so the fan-out became size-limited consolidation transactions (above).
  - Its `listunspent` call was rejected by a real node.
  - Its flat 0.0001 fee was below the relay fee for a 50-output batch.
  - The broadcast and signing scripts crashed on the fan-out label.
  - Covered by `scripts/migration/test_migration_prepare.py`, and by a regtest run of the full flow with the v1.1.1 release binary: owner-signed cold-stake spends, a stake spending a fan-out input mid-run (caught as STALE, rerun built only the missing part), and 25 of 25 recipients paid exactly, including a balance split under the per-recipient cap.
- Fixed 2026-10-25 (PR "Airdrop readiness 3"):
  - `verify-claim.py` described the withdrawn disposal model and sent coins from a hot wallet. It now only verifies a section 3 claim and records it; payment goes through the offline-signed pipeline.
  - `verify-migration.py` compared current balances with the raw snapshot, on PIVX's RPC port, with placeholder credentials. That would have flagged every pledging address and every holder who had moved their coins. It now reconciles from the signed payout transactions that confirmed, against the payout list.
  - The user guide's example claim message now names the destination (section 3).
  - All three were checked on regtest after the payout run: 25 of 25 reconciled; an address left out of the payout shows as UNPAID; its claim is approved; a repeat claim, a claim by a paid address and a signature over the old message are refused.
  - Also fixed earlier: the migration README and the `migration-prepare.py` usage text now describe the current plan (PR "Airdrop readiness 2/2").
