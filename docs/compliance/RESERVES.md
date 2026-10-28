# AMMOcoin reserves: where the block-1 AMMO is, and what each part is for

This is the public record of every project-held pool of AMMO (decision AMMO-D-2026-10-24-04). Anyone can check every address and transaction below with a node or with [explorer.ammocoin.org](https://explorer.ammocoin.org).

> **Draft.** Rows marked **TO BE CREATED** are pools that don't exist on chain yet. Each gets its address when the owner creates it. Nothing here is filled in from memory: on-chain rows were read from a v1.1.1 node (ammo-02) on 2026-10-24 at height ~3556. Pool 1's change and the 2026-10-27 top-up were read on 2026-10-27 (VM controller wallet `listunspent`; explorer.ammocoin.org, block 4755).

The project sells no AMMO, publishes no price and runs no buy-backs (AMMO-P-02, P-03). AMMOcoin is Proudly Worthless™. These pools exist to carry out the airdrop and the published distribution programme, nothing else.

## 1. Rules

1. **One labelled pool per purpose.** Each pool has a small, fixed set of addresses, all listed here. There are no unlabelled project wallets, and no splitting into addresses meant to look like independent holders.
2. **Many coins inside a pool are fine.** A pool may hold its AMMO as many outputs (UTXOs) for staking and payout batches (D-2026-10-18-13), all at its listed addresses.
3. **Airdrop first (P-06).** No AMMO leaves the block-1 reserve for another pool until the v1.0 airdrop payouts are broadcast, apart from the exceptions recorded in section 4. There is one so far: the masternode collateral (pool 6), 50,000 taken from pool 1's change on 2026-10-24 (D-2026-10-24-03, -05). It came out of the 250,000,000, so pool 1 then held less than pools 2–5 need; see the arithmetic below section 2 (D-2026-10-27-01). The gap was closed on 2026-10-27 with 50,000 from pool 8, which is outside the 250,000,000 (D-2026-10-27-04; txid in section 4). That top-up moved coins into pool 1, not out of it.
4. **Every movement between pools is logged** in section 4, with its txid, within 7 days, and before it's described anywhere as done.
5. **Cold by default.** Large pools are owned by offline keys and stake through cold-staking delegation to project staking nodes. A staking node can stake the coins but can't spend them. Only the GLiBz payout float is a hot wallet, and it is capped.
6. **Keys never leave their wallet.** No private key, passphrase or wallet file appears in this repository, a chat or a ticket.

## 2. Pools

| # | Pool | Purpose | Amount | Address(es) | Custody | Status |
|---|---|---|---|---|---|---|
| 1 | **Block-1 reserve** | Pays the v1.0 airdrop first, then funds pools 3–5 | 250,000,000 at block 1; 249,950,244.99994463 after 2026-10-24; **250,000,491.99994463 on 2026-10-27** after the 50,000 top-up from pool 8: 249,850,000 in cold staking (249,800,000 + 50,000, tx `2ff7fd5f…` vout 1) + 150,491.99994463 change (sections 3–4, arithmetic below). Covers the 250,000,000 pools 2–5 need | Coin owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`, staker `SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY` (ammo-02) | Paper wallet ("AMMOcoin v1.1.0 Distribution Wallet"), cold-staked | On chain |
| 2 | **v1.0 airdrop** | v1.0 snapshot balances minus the signed pledges, to the same addresses ([AIRDROPS.md](AIRDROPS.md)) | 159,958,300 (232,397,748.45021523 − 72,439,448.45021523 pledged), if every pledge is signed. Each pledge paid in full instead (D-2026-10-25-01) adds its pledge here and takes it from pools 3–4 | Paid straight to the v1.0 holders' addresses; claim hold-back address **TO BE CREATED** | Paid from pool 1 | Not paid yet |
| 3 | **QuarterMaster tiers** | FOUNDING-50, SPARTAN-300, PATRIOT-2000 positions, earned or awarded, never sold (P-07) | 40,000,000 | **TO BE CREATED** | Offline key, cold-staked | After the airdrop |
| 4 | **Contributor reserve** | AMMOgeek / AMMOfreak awards (P-07) | 50,000,000 | **TO BE CREATED** | Offline key, cold-staked | After the airdrop |
| 5 | **Unattributed v1.0 set-aside** | v1.0 coins the snapshot couldn't assign to an address (not zerocoin; see AIRDROPS.md section 6) (D-2026-10-18-12) | 41,700 | **TO BE CREATED** | Offline key | After the airdrop |
| 6 | **Masternode collateral** | Project masternodes mn1–mn5 (D-2026-10-24-03, -05) | 5 × 10,000 | mn1 `ARqYH63neJkpgJKGDhKExAHqkNRXnpLwLR`, mn2 `AJ31JCS5LQe3YtKcxk5Ja4NK14RcbhE1JD`, mn3 `AXWeeRBjg5n539ZsytqaHoiCT1F2RMVmgQ` (tx `838a4b0e92050cf3…` vouts 1–3); mn4 `AUtumrzgLphzJPyVHPcGQ52L8HvUVsimai`, mn5 `AHMa6JPXUNYWk3EVqoSF2fip2mbrRwSZ6a` (tx `c27deb8bfe76dd02…` vouts 0–1) | VM controller wallet | Funded 2026-10-24 from pool 1 change, before the airdrop: the one exception to rule 3. Masternode payments to these addresses are project rewards (pool 8), not collateral |
| 7 | **GLiBz payout float** | Pays earned-NUGGETS swaps from the GLiBz pouch (D-2026-10-17-03) | Capped; top-ups logged | **TO BE CREATED** | Hot wallet on the payout gateway | Funding source: owner decision pending |
| 8 | **Project mining and staking rewards** | Block rewards paid to the project's own wallet: PoW blocks before the v1.1.1 fork and PoS blocks after it. Not part of the 250,000,000 | 790,399.99704080 on 2026-10-24: the VM controller wallet held 990,644.99698543, of which 50,000 is pool 6 collateral and 150,244.99994463 is pool 1 change (arithmetic below). Most of it is in pieces under 1,000. On 2026-10-27, 50,000 of it moved to pool 1 and it paid the 0.0014574 network fee (D-2026-10-27-04, section 4): 740,399.99558340 against the 2026-10-24 reading, plus block rewards received since (not re-read) | Several hundred reward addresses; list **TO BE PUBLISHED** | VM controller wallet | On chain; itemised list to follow |

### Arithmetic

All figures are exact chain or file values; sources in brackets.

**What the 250,000,000 is for (pools 2–5).**

| | AMMO |
|---|---|
| v1.0 snapshot total, 10,080 addresses (snapshot file `snapshot_info.total_supply`) | 232,397,748.45021523 |
| − pledged by the 61 contributors (`quartermaster-pledges.csv`, sum of `pledge`) | 72,439,448.45021523 |
| = pool 2, v1.0 airdrop | 159,958,300.00000000 |
| + pool 3, QuarterMaster tiers | 40,000,000.00000000 |
| + pool 4, contributor reserve | 50,000,000.00000000 |
| + pool 5, unattributed set-aside (snapshot `expected_supply` − `total_supply`, rounded; AIRDROPS.md section 6) | 41,700.00000000 |
| **= block 1** (`GetBlockValue(1)`) | **250,000,000.00000000** |

The claim hold-back is part of pool 2. A pledge paid in full moves its amount from pools 3–4 to pool 2; the total stays 250,000,000.

**What pool 1 actually held after 2026-10-24 (sections 3 and 4).**

| | AMMO |
|---|---|
| Block 1 | 250,000,000.00000000 |
| + its own stake on 2026-10-22: 48 × 5,208,338.54166666 = 250,000,249.99999968 | 249.99999968 |
| − fees of the five cold-staking transactions (250,000,249.99999968 − 249,800,000 − 200,245.00000003) | 4.99999965 |
| = 249,800,000 cold-staked + 200,245.00000003 change | 250,000,245.00000003 |
| − to pool 6 (`838a4b0e…` 30,000 + `c27deb8b…` 20,000) | 50,000.00000000 |
| − fees of those two transactions (0.00002940 + 0.00002600) | 0.00005540 |
| **= 249,800,000 cold-staked + 150,244.99994463 change** | **249,950,244.99994463** |

**The gap (closed 2026-10-27).** Pools 2–5 need 250,000,000.00000000; after 2026-10-24 pool 1 held 249,950,244.99994463, which was **49,755.00005537 short** (the 50,000 collateral, plus 0.00005540 fees, less the 245.00000003 the stake added). D-2026-10-27-04, which closes the open point of D-2026-10-27-01, chose to move 50,000 from pool 8 (outside the 250,000,000, same wallet) into pool 1. The other options (counting pool 1's own stake rewards since 2026-10-22, releasing the collateral back to pool 1, making pool 3 or 4 smaller) were not chosen. The owner sent it on 2026-10-27: `2ff7fd5f1c73f55b3685bda0e813a0e92624d43050eb58068bdfc2b61f42694f`, block 4755 (section 4).

**After the top-up (2026-10-27).** The transfer was a `delegatestake` from the VM controller wallet, so the wallet paid the fee on top and pool 1 received the full 50,000 as one cold-staked output (vout 1: staker `SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY`, owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`).

| | AMMO |
|---|---|
| Cold-staked before the top-up (section 3) | 249,800,000.00000000 |
| + cold-staked by the top-up (`2ff7fd5f…` vout 1) | 50,000.00000000 |
| + change at the five pool-1 change addresses (`listunspent`, 52 outputs, read 2026-10-27) | 150,491.99994463 |
| **= pool 1 on 2026-10-27** | **250,000,491.99994463** |
| − needed for pools 2–5 | 250,000,000.00000000 |
| **= to spare** | **491.99994463** |

Cross-check against the 2026-10-24 figures: 249,950,244.99994463 + 50,000 + 247.00000000 = 250,000,491.99994463. The 247.00000000 is what pool 1's change gained by staking between 2026-10-24 and 2026-10-27 (150,491.99994463 − 150,244.99994463): `ATvgq…`'s change staked and split into `a45f52be32478b04a4f77bed9c18a404b72dc9628072897b0e63683644539bce` vouts 1–48. Rewards to pool 1 stay in pool 1. So the spare is 244.99994463 from the top-up itself (50,000 − 49,755.00005537) plus those 247.00000000. The 249,800,000 cold-staked coins may also have staked since 2026-10-24; that is not read here, so any such rewards are not in the figure above.

| | AMMO |
|---|---|
| Pool 8 on 2026-10-24 | 790,399.99704080 |
| − to pool 1 | 50,000.00000000 |
| − network fee of the transfer (`2ff7fd5f…`, paid by pool 8) | 0.00145740 |
| **= pool 8 after the top-up, against the 2026-10-24 reading** | **740,399.99558340** |

Pool 8 has kept receiving block rewards since 2026-10-24, so its actual balance is higher; it was not re-read. The caveat below about when the 2026-10-24 reading was taken still applies.

**What the top-up spent.** 97 inputs totalling 50,003.00000000, all pool 8 (project block rewards). Three of them were masternode payments that had landed on the mn1, mn3 and mn4 addresses (`ARqYH…`, `AXWee…`, `AUtum…`); those payments are pool 8, not collateral (pool 6 row). Change of 2.99854260 went back to pool 8 at `AYEiLCRgdkqNu1AAKdDHoXo9TSEj4EdGvV` (vout 0, VM controller wallet). 50,003.00000000 − 50,000 − 2.99854260 = 0.00145740 fee. No input came from the collateral outputs (`838a4b0e…` vouts 1–3, `c27deb8b…` vouts 0–1) or from pool 1's change: before sending, the owner locked both sets with `lockunspent` (57 outputs: the 5 collateral outputs and pool 1's 52 change outputs) so the wallet could not pick them.

**Pool 8.** The VM controller wallet held 990,644.99698543 on 2026-10-24, and it also holds pool 6 and pool 1's change: 990,644.99698543 − 50,000 − 150,244.99994463 = 790,399.99704080 of project block rewards. This assumes the wallet was read after both collateral transactions, as the old pool 8 row said ("includes pool 6 collateral"); if it was read before them, pool 1 change was 200,245.00000003 and pool 8 was 790,399.99698540. Re-read the wallet to confirm.

## 3. Pool 1 on chain (read 2026-10-24; change and top-up read 2026-10-27)

| Step | Transaction | What it did |
|---|---|---|
| Block 1 | `347406ef44341612ec77602de193fec6451706a706b1e155ae8860023d44595a` | 250,000,000 to `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u` |
| Stake, 2026-10-22 13:27Z | `3f723c58f41fa5fc4f0151fb089d54b88776f0810eadbb9b1aa361b6222f2796` | `AJSpv…` staked a block with the whole 250,000,000. The stake split it into 48 outputs of 5,208,338.54166666 (the 250,000,000 plus the 250 block reward), back to `AJSpv…`. All 48 are now spent. |
| Cold staking, 2026-10-22 21:35Z | `5bf32891876e0ba816c337aa104c92a2dcde52ad041b76699f680175467b2d5e` | 1,145 × 50,000 cold-staked; change 41,722.95833327 to `AMjFxfQRpw9UsGA7AcuzJYt4kq9dqeydgd` |
| Cold staking | `a9e73503caed0ed6f987d32845db87242df10bcddfc8b56b364c8e54c09be468` | 1,145 × 50,000 cold-staked; change 41,722.95833358 to `Adkh8D3TaHphLWTnQnf3WgdQpN4uvgVPLw` |
| Cold staking | `9518d51fb7819b9000f7fa150b691ad888f16190ce3c9b3a5288144cb661dc7f` | 1,145 × 50,000 cold-staked; change 41,722.95833327 to `ATvgqHV6GWJZF3xL5eSZQQTD9t5MQwkKBS` |
| Cold staking | `2a3fb4e92c0dc76f240ed417751c04d7df78b3169a936e31875c58bf0a2ecfa8` | 1,145 × 50,000 cold-staked; change 41,722.95833327 to `AYFSs5Vmx6NtNpJLRiWBWt58yHnhwETnbn` |
| Cold staking | `32bff5e2344e5fb4c53b107acb6876e0c180ec950d511b845db72b3784871db1` | 416 × 50,000 cold-staked; change 33,353.16666664 to `Ad9vGq9rdBHdFERwJG9bptNCoVb3BDkACY` |
| Change stake, 2026-10-24 to 10-27 | `a45f52be32478b04a4f77bed9c18a404b72dc9628072897b0e63683644539bce` | `ATvgq…`'s change staked; the stake split it into vouts 1–48, still at pool 1's change addresses. Pool 1 change rose by 247.00000000 to 150,491.99994463 (52 outputs, read 2026-10-27) |
| Top-up from pool 8, 2026-10-27 13:11Z, block 4755 | `2ff7fd5f1c73f55b3685bda0e813a0e92624d43050eb58068bdfc2b61f42694f` | 1 × 50,000 cold-staked (vout 1), owner `AGkC8…`, staker `SUr6…`; all inputs from pool 8 (section 4) |

Totals: 4,996 outputs × 50,000 = 249,800,000 cold-staked, coin owner `AGkC8…`, staker `SUr6…`. The change, 200,245.00000003 in total across the five addresses, was unspent at the time of reading. The five change addresses are part of pool 1, held in the project's VM controller wallet (confirmed 2026-10-24). 50,000 of it funded pool 6 (section 4). On 2026-10-27: 4,997 cold-staked outputs (4,996 × 50,000 + the 50,000 top-up) = 249,850,000, and 150,491.99994463 change in 52 outputs at the same five addresses; whether the cold-staked outputs have staked since 2026-10-24 was not read.

`AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` was also the genesis output address. That output is unspendable; the address now also owns pool 1's cold-staked coins, as planned (wallets README, 2026-10-16).

## 4. Movements between pools

Every transfer between pools, or out of a pool, gets a row here. The owner's private working copy is `LEDGER.md` on the encrypted wallets volume.

| Date (UTC) | From pool | To pool / recipient | Amount | txid | Decision |
|---|---|---|---|---|---|
| 2026-10-22 13:27 | 1 (block-1 output) | 1 (its own stake, same address) | 250,000,000 + 250 block reward | `3f723c58…` | internal to pool 1 |
| 2026-10-22 21:35 | 1 | 1 (cold staking + change) | 249,800,000 + 200,245 | five txids in section 3 | internal to pool 1 |
| 2026-10-24 | 1 (change `AMjFxfQRpw9UsGA7AcuzJYt4kq9dqeydgd`, `5bf32891…` vout 1145) | 6 (mn1–mn3, vouts 1–3); change 11,722.95830387 back to `AMjFx…` (vout 0) | 30,000 | `838a4b0e92050cf3961f6d58547f35b71a31a860e2d72c4e4ced6ce395a2f6f8` | D-2026-10-24-03, -04 |
| 2026-10-24 | 1 (change `Adkh8D3TaHphLWTnQnf3WgdQpN4uvgVPLw`, `a9e73503…` vout 1145) | 6 (mn4 vout 0, mn5 vout 1); change 21,722.95830758 back to `Adkh8…` (vout 2) | 20,000 | `c27deb8bfe76dd02935a503e02f0414e478b3136a88a5531a5788f413d004825` | D-2026-10-24-05 |
| 2026-10-27 13:11, block 4755 | 8 (VM controller wallet; 97 inputs, 50,003 in total, all pool 8; collateral and pool 1 change locked with `lockunspent` first, none spent); change 2.99854260 back to pool 8 at `AYEiLCRgdkqNu1AAKdDHoXo9TSEj4EdGvV` (vout 0) | 1 (cold-staked, vout 1: owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`, staker `SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY`) | 50,000 received in full; fee 0.0014574 paid by pool 8 | `2ff7fd5f1c73f55b3685bda0e813a0e92624d43050eb58068bdfc2b61f42694f` | D-2026-10-27-04 (logged the day it was sent) |

### Planned

Decided but not sent. A planned movement is never described as done anywhere until its txid is in the table above (rule 4). Open: the Launch Season funding sequence (D-2026-10-27-08), rows marked *after the airdrop*. The 2026-10-27 top-up row is kept as the record of how it was planned.

| Decided | From pool | To pool | Amount | How the docs say it is sent | Decision | Status |
|---|---|---|---|---|---|---|
| 2026-10-27 | 1 (block-1 reserve) | 3, 4, 5 (QuarterMaster tiers, contributor reserve, unattributed set-aside), each a new offline key, cold-staked | 40,000,000 / 50,000,000 / 41,700 | Built watch-only and signed offline, the same way as the airdrop payout (AIRDROPS.md section 2) | D-2026-10-27-08 | *After the airdrop* |
| 2026-10-27 | 4 (contributor reserve) | 7 (GLiBz payout float, gateway hot wallet) | 100,000 first; top up when below 25,000; never more than 250,000 held | Sent from pool 4 to the pool 7 address (`getnewaddress "glibz-payout-float"` on the gateway), signed offline | D-2026-10-27-08 | *After the airdrop, once the gateway is live* |
| 2026-10-27 | 8 (project block rewards, VM controller wallet) | 1 (block-1 reserve, cold-staked: owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`, staker `SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY` on ammo-02) | 50,000, plus the network fee from pool 8 | Pool 1 is held as cold-staked coins owned by the paper wallet (rule 5, pool 1 row). Coins are added to a cold-staked holding with `delegatestake "<S staking address>" <amount> "<owner address>" true` from the sending wallet, `true` because the owner address is not in that wallet (docs/02-staking-guide.md, Cold staking step 2). `sendtoaddress` refuses an `S…` staking address (`source/src/wallet/rpcwallet.cpp:1187`). ammo-02 already accepts delegations owned by `AGkC8…` (D-2026-10-24-05). Delegated coins stake after 600 confirmations | D-2026-10-27-04 | **Sent 2026-10-27** by the owner with `delegatestake SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY 50000 AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME true`; txid `2ff7fd5f…` logged in the table above the same day. The new output stakes after 600 confirmations (around block 5355) |
