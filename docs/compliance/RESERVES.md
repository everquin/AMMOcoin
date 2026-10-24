# AMMOcoin reserves: where the block-1 AMMO is, and what each part is for

This is the public record of every project-held pool of AMMO (decision AMMO-D-2026-10-24-04). Anyone can check every address and transaction below with a node or with [explorer.ammocoin.org](https://explorer.ammocoin.org).

> **Draft.** Rows marked **TO BE CREATED** are pools that don't exist on chain yet. Each gets its address when the owner creates it. Nothing here is filled in from memory: on-chain rows were read from a v1.1.1 node (ammo-02) on 2026-10-24 at height ~3556.

The project sells no AMMO, publishes no price and runs no buy-backs (AMMO-P-02, P-03). AMMOcoin is Proudly Worthless™. These pools exist to carry out the airdrop and the published distribution programme, nothing else.

## 1. Rules

1. **One labelled pool per purpose.** Each pool has a small, fixed set of addresses, all listed here. There are no unlabelled project wallets, and no splitting into addresses meant to look like independent holders.
2. **Many coins inside a pool are fine.** A pool may hold its AMMO as many outputs (UTXOs) for staking and payout batches (D-2026-10-18-13), all at its listed addresses.
3. **Airdrop first (P-06).** No AMMO leaves the block-1 reserve for another pool until the v1.0 airdrop payouts are broadcast, apart from the exceptions recorded in section 4.
4. **Every movement between pools is logged** in section 4, with its txid, within 7 days, and before it's described anywhere as done.
5. **Cold by default.** Large pools are owned by offline keys and stake through cold-staking delegation to project staking nodes. A staking node can stake the coins but can't spend them. Only the GLiBz payout float is a hot wallet, and it is capped.
6. **Keys never leave their wallet.** No private key, passphrase or wallet file appears in this repository, a chat or a ticket.

## 2. Pools

| # | Pool | Purpose | Amount | Address(es) | Custody | Status |
|---|---|---|---|---|---|---|
| 1 | **Block-1 reserve** | Pays the v1.0 airdrop first, then funds pools 3–5 | 250,000,000 at block 1 (now 249,800,000 in cold staking + 200,245 change, section 3) | Coin owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`, staker `SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY` (ammo-02) | Paper wallet ("AMMOcoin v1.1.0 Distribution Wallet"), cold-staked | On chain |
| 2 | **v1.0 airdrop** | v1.0 snapshot balances minus the signed pledges, to the same addresses ([AIRDROPS.md](AIRDROPS.md)) | 159,958,300 (232,397,748.45021523 − 72,439,448.45021523 pledged) | Paid straight to the v1.0 holders' addresses; claim hold-back address **TO BE CREATED** | Paid from pool 1 | Not paid yet |
| 3 | **QuarterMaster tiers** | FOUNDING-50, SPARTAN-300, PATRIOT-2000 positions, earned or awarded, never sold (P-07) | 40,000,000 | **TO BE CREATED** | Offline key, cold-staked | After the airdrop |
| 4 | **Contributor reserve** | AMMOgeek / AMMOfreak awards (P-07) | 50,000,000 | **TO BE CREATED** | Offline key, cold-staked | After the airdrop |
| 5 | **Zerocoin set-aside** | v1.0 zerocoin that can't be claimed by address (D-2026-10-18-12) | 41,700 | **TO BE CREATED** | Offline key | After the airdrop |
| 6 | **Masternode collateral** | Project masternodes mn1–mn3 (D-2026-10-24-03) | 3 × 10,000 | mn1 `ARqYH63neJkpgJKGDhKExAHqkNRXnpLwLR`, mn2 `AJ31JCS5LQe3YtKcxk5Ja4NK14RcbhE1JD`, mn3 `AXWeeRBjg5n539ZsytqaHoiCT1F2RMVmgQ` (tx `838a4b0e92050cf3…` vouts 1–3) | VM controller wallet | Funded 2026-10-24 from pool 1 change |
| 7 | **GLiBz payout float** | Pays earned-NUGGETS swaps from the GLiBz pouch (D-2026-10-17-03) | Capped; top-ups logged | **TO BE CREATED** | Hot wallet on the payout gateway | Funding source: owner decision pending |

Arithmetic: block 1 paid 250,000,000 = pool 2 + pools 3–5 (159,958,300 + 40,000,000 + 50,000,000 + 41,700). The claim hold-back is part of pool 2. Pool 1 has since gained a 250 block reward from its own stake (section 3); that reward, less fees, is extra and stays in pool 1. It is reported in the reconciliation ([AIRDROPS.md](AIRDROPS.md) section 4).

## 3. Pool 1 on chain today (read 2026-10-24)

| Step | Transaction | What it did |
|---|---|---|
| Block 1 | `347406ef44341612ec77602de193fec6451706a706b1e155ae8860023d44595a` | 250,000,000 to `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u` |
| Stake, 2026-10-22 13:27Z | `3f723c58f41fa5fc4f0151fb089d54b88776f0810eadbb9b1aa361b6222f2796` | `AJSpv…` staked a block with the whole 250,000,000. The stake split it into 48 outputs of 5,208,338.54166666 (the 250,000,000 plus the 250 block reward), back to `AJSpv…`. All 48 are now spent. |
| Cold staking, 2026-10-22 21:35Z | `5bf32891876e0ba816c337aa104c92a2dcde52ad041b76699f680175467b2d5e` | 1,145 × 50,000 cold-staked; change 41,722.95833327 to `AMjFxfQRpw9UsGA7AcuzJYt4kq9dqeydgd` |
| Cold staking | `a9e73503caed0ed6f987d32845db87242df10bcddfc8b56b364c8e54c09be468` | 1,145 × 50,000 cold-staked; change 41,722.95833358 to `Adkh8D3TaHphLWTnQnf3WgdQpN4uvgVPLw` |
| Cold staking | `9518d51fb7819b9000f7fa150b691ad888f16190ce3c9b3a5288144cb661dc7f` | 1,145 × 50,000 cold-staked; change 41,722.95833327 to `ATvgqHV6GWJZF3xL5eSZQQTD9t5MQwkKBS` |
| Cold staking | `2a3fb4e92c0dc76f240ed417751c04d7df78b3169a936e31875c58bf0a2ecfa8` | 1,145 × 50,000 cold-staked; change 41,722.95833327 to `AYFSs5Vmx6NtNpJLRiWBWt58yHnhwETnbn` |
| Cold staking | `32bff5e2344e5fb4c53b107acb6876e0c180ec950d511b845db72b3784871db1` | 416 × 50,000 cold-staked; change 33,353.16666664 to `Ad9vGq9rdBHdFERwJG9bptNCoVb3BDkACY` |

Totals: 4,996 outputs × 50,000 = 249,800,000 cold-staked, coin owner `AGkC8…`, staker `SUr6…`. The change, 200,245.00000003 in total across the five addresses, was unspent at the time of reading. The five change addresses are part of pool 1, held in the project's VM controller wallet (confirmed 2026-10-24). 30,000 of it funded pool 6 (section 4).

`AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` was also the genesis output address. That output is unspendable; the address now also owns pool 1's cold-staked coins, as planned (wallets README, 2026-10-16).

## 4. Movements between pools

Every transfer between pools, or out of a pool, gets a row here. The owner's private working copy is `LEDGER.md` on the encrypted wallets volume.

| Date (UTC) | From pool | To pool / recipient | Amount | txid | Decision |
|---|---|---|---|---|---|
| 2026-10-22 13:27 | 1 (block-1 output) | 1 (its own stake, same address) | 250,000,000 + 250 block reward | `3f723c58…` | internal to pool 1 |
| 2026-10-22 21:35 | 1 | 1 (cold staking + change) | 249,800,000 + 200,245 | five txids in section 3 | internal to pool 1 |
| 2026-10-24 | 1 (change `AMjFxfQRpw9UsGA7AcuzJYt4kq9dqeydgd`, `5bf32891…` vout 1145) | 6 (mn1–mn3, vouts 1–3); change 11,722.95830387 back to `AMjFx…` (vout 0) | 30,000 | `838a4b0e92050cf3961f6d58547f35b71a31a860e2d72c4e4ced6ce395a2f6f8` | D-2026-10-24-03, -04 |
