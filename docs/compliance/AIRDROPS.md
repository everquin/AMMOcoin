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
| Zerocoin set aside, unclaimable (section 4, supply difference) | 41,700.00000000 |
| **Left for the QuarterMaster and contributor reserves** | **90,000,000.00000000** |

- Each pledge is a `signmessage` signature from the pledging address over the exact text in `docs/migration/data/quartermaster-pledges.csv` (built by `scripts/migration/build-pledges.py`; `--check` proves the file matches a fresh build). Signatures are checked with `scripts/migration/verify-pledges.py` and published.
- The holder signs. Nobody signs for someone else, and no wallet or key is handed over: a pledge signed by anyone but the holder is not proof that the holder agreed.
- Pledges are voluntary and nothing is given in return — no tier position, reward or payment.
- No payout is built until every pledge is signed. A contributor who does not sign is paid their full snapshot balance like everyone else, and the pledge list is rebuilt and re-decided.
- Disclosure: these 61 early holders hold 94.1% of the v1.0 snapshot; after the pledges they receive 146,267,603.75 of the 159,958,300.00 AMMO paid out.

---

## 2. How the payout is made

1. **Snapshot.** The v1.0 UTXO set at block 434,881 is reduced to one balance per address (`scripts/migration/v1.0-snapshot-tool.py`). The result is the snapshot file above. Its SHA256 is published (section 4) so that the list cannot be changed afterwards without it being visible.
2. **Build.** Unsigned payout transactions are built on an online node with a **watch-only** wallet holding the reserve UTXOs (`scripts/migration/migration-prepare.py`). The script refuses to write its output unless the total paid equals the sum of the snapshot balances within dust tolerance, caps any one output, and limits recipients per transaction.
3. **Sign offline.** The batch is signed on an air-gapped machine (`scripts/migration/migration-sign-offline.py`). Reserve keys never touch an online machine.
4. **Broadcast.** Signed batches are verified and broadcast with a pause between batches, and an audit log of every txid is written (`scripts/migration/migration-broadcast.py`).
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
3. The project verifies the signature with `verifymessage` against the v1.0 address, checks the snapshot balance for that address, and checks that the address has not already been paid (no double payment).
4. The snapshot balance is paid to the named v1.1 address, from the block-1 reserve, and the txid is added to the published claim record (section 4).

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
| Contributor pledges | `docs/migration/data/quartermaster-pledges.csv` (61 addresses, 72,439,448.45021523 AMMO). **TO BE PUBLISHED:** the 61 signatures and the `verify-pledges.py` result |
| Signed-message claims | **TO BE PUBLISHED:** running list of v1.0 address, v1.1 address, amount, payout txid, date (signatures may be published too; they reveal nothing secret) |
| Block-1 reserve address | `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u` (block 1 output; `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` is only the unspendable genesis output) |
| Reserve change / holding addresses used by the payout | **TO BE PUBLISHED** |
| Amount held back for signed-message claims, and its address | **TO BE PUBLISHED** |
| QuarterMaster reserve address(es) | **TO BE PUBLISHED** (gap G-06) |
| Contributor (AMMOgeek/AMMOfreak) reserve address(es) | **TO BE PUBLISHED** |
| Disposal address (v1.1.0 process, withdrawn) | **TO BE PUBLISHED:** the address from `docs/migration/DISPOSAL_ADDRESS.md` and the balance it received, so that anyone who did send coins under the withdrawn process can be identified and made whole |
| Reconciliation statement | **TO BE PUBLISHED:** block-1 reserve 250,000,000 AMMO = airdrop paid + claims paid + claim hold-back + QuarterMaster reserve + contributor reserve + fees, with the addresses above |

When a value is published, replace its **TO BE PUBLISHED** marker in a commit, add the commit SHA to AMMO-D-2026-10-17-10, and update gap G-06.

---

## 5. Why this is not a sale

- **No payment.** Nobody pays anything, in any currency, coin or goods, to receive the airdrop or to make a claim. There is no fee.
- **No purchase.** Nothing is offered for sale. The airdrop restores balances people already held on the v1.0 chain, to the same addresses, in the same amounts. No one can get more by paying, and no one is offered AMMO who did not already hold it at the snapshot.
- **No solicitation.** Holders are not asked to send coins, register, sign up, or act by a deadline. The only action ever asked of anyone is a signature, and only when the automatic payout could not reach them.
- **No promise of value.** The project assigns AMMO no value and publishes no price, exchange rate, market cap or fiat equivalent for it (AMMO-P-03). Airdrop records state AMMO amounts only, never a fiat value. The airdrop is not described as a gift of value, a reward, an opportunity or an investment.
- **No raise.** The airdrop brings in no money and is not linked to any fundraising (AMMO-P-01). Reserve AMMO is never sold (AMMO-P-02).

Copy about the airdrop (site, app, social posts, release notes) must follow sections 1 and 5 and pass [REVIEW_CHECKLIST.md](REVIEW_CHECKLIST.md).

---

## 6. Known inconsistencies to fix before the payout

- `scripts/migration/verify-claim.py` still describes the withdrawn disposal-address model as current and calls the signed-message claim deprecated (it refuses to run without `--i-accept-the-risk`). That is the reverse of AMMO-D-2026-10-16-01. Update it before any claim is processed. `scripts/migration/README.md` still describes the tools as v1.0 -> v1.1.0 and lists `distribute-to-top-holders.py` (the earlier "Option 2.5" plan).
- `scripts/migration/migration-prepare.py` usage text refers to a `genesis-top-holders.json` holders file (from the earlier "Option 2.5" plan). The payout must be built from the published snapshot file (section 4), or from a file whose derivation from it is published.
- The snapshot file records `supply_match: false` (section 4). Most likely explanation (not yet proven): 41,700 AMMO of zerocoin mints, which count in the v1.0 supply total but have no address. Confirm with the zerocoin supply (`getinfo`) on a v1.0 node at block 434,881. Either way the 41,700 is set aside as unclaimable (AMMO-D-2026-10-18-12).
- `scripts/migration/migration-prepare.py` pays snapshot balances in full. It must take the signed pledge list and pay `airdrop_after_pledge` for the 61 pledging addresses before it is used.
- The user guide's example claim message (`docs/migration/V1.0_BALANCE_AIRDROP.md`) does not name a destination address; align it with section 3.
