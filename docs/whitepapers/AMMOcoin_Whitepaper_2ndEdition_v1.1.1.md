---
title: "AMMOcoin White Paper"
subtitle: "2nd Edition (v1.1.1)"
author: "Founding50 Personae: quarterMASTER / flibbertigibbet / techMASTER / StinkelVoss / Covfefe"
date: "rev. 2026/10/23"
---

# AMMOcoin White Paper, 2nd Edition (v1.1.1)

*"Cryptocurrency for people, patriots & the planet"*

**Prepared by:** Founding50 Personae: quarterMASTER / flibbertigibbet / techMASTER / StinkelVoss / Covfefe

**2nd Edition (v1.1.1), rev. 2026/10/23.** This edition replaces the 1st Edition of 2022/01/15. Every technical figure in it is taken from the AMMOcoin v1.1.1 source code. Install v1.1.1 only from the official AMMOcoin GitHub release (github.com/everquin/AMMOcoin/releases), never from any other source. Where this paper and the code disagree, the code wins, and this paper will be corrected.

---

## Contents

1. Special Thanks: Bitcoin, DASH, PIVX, AMMO
2. Disclaimer
3. What Changed Since the 1st Edition
4. AMMO Specs
5. The Mission: People, Patriots, The Planet
6. The Road to v1.1.1
7. Global Payment System: Private, Fast, Cheap, Secure
8. Operators: nodes, stakenodes & masternodes
9. DAO Command
10. Supply
11. Initial Valuation: No ICO, No Exchanges, The Closed Loop
12. Structured Release: The Vanguard Deployment
13. Where to Check Our Work

---

## 1. Special Thanks

### BITCOIN
Thank you to Satoshi Nakamoto for creating Bitcoin and the technology on which all cryptocurrencies were developed or inspired from.

### DASH
Thank you to the DASH (www.dash.org) developers for their pioneering work in advancing the bitcoin functionality, above all the masternode network and on-chain governance that AMMO still runs on.

### PIVX
Thank you to the PIVX (www.pivx.org) development team, which forked DASH and has kept expanding the benefits and potential on which AMMO is built. AMMOcoin v1.1 is built on PIVX's modern codebase (the PIVX Core 5.x line, with network upgrades through v5.6). From PIVX AMMO inherits its Proof-of-Stake consensus, cold staking, the masternode payment and budget system, and Sapling shielded transactions, the zk-SNARK technology PIVX adopted from Zcash. Our thanks also go to the Zcash developers who created Sapling.

### AMMO
Thank you, now and in advance, to the individuals, teams and developers who helped bring AMMO (www.ammocoin.org) into existence and who will propel it into the future.

---

## 2. Disclaimer

AMMO reinvents no wheels. The 1st Edition was written for a fork of the PIVX v3.3 protocol. Version 1.1 of AMMOcoin is a new chain built on the far more capable PIVX Core 5.x codebase, and v1.1.1 moves that chain to Proof of Stake. We chose the best starting point we could find, and we hope that some of the deep pool of PIVX and outside crypto developers will help us grow the functionality of the network.

This paper describes software and a community. It is not an offer to sell anything, not investment advice and not a promise of any return, yield, profit or price. Staking and masternodes are described here technically: what the code does, not what anyone receives. How often any one wallet stakes or any one masternode takes its turn depends on how many others are staking and running masternodes, and on keeping its own node online.

---

## 3. What Changed Since the 1st Edition

| Topic | 1st Edition (2022/01/15) | 2nd Edition (v1.1.1) |
|---|---|---|
| Codebase | Fork of PIVX v3.3 | New chain on PIVX Core 5.x (Sapling, cold staking) |
| Consensus | "Proof-of-Stake after initial PoW" | v1.1.0 mined 2,775 PoW blocks and stalled; **v1.1.1 hard fork to Proof of Stake at block 2,776**. No mining after the fork. |
| v1.0 chain | Live | Halted. v1.0 balances are **airdropped** to the same addresses from the 250,000,000 AMMO block-1 reserve. |
| Block time | about 120 seconds | **3 minutes** (about 480 blocks a day) |
| Issuance | A fixed amount per block, split between masternodes and stakers | **A declining schedule set by `GetBlockValue()` in the code** (Section 10); each block pays the masternode selected by the payment queue, and the staker that makes the block receives the rest |
| Masternode collateral | 5,000 AMMO, 20 confirmations | **10,000 AMMO, 15 confirmations** |
| Treasury | A superblock treasury | Superblock every **43,200 blocks** (about 90 days); budget set by `GetTotalBudget()` in the code, paid only to proposals approved by masternode vote |
| RPC port | 37019 | **51473** (P2P stays 37020) |
| Fast payments | SwiftX | **SwiftX removed**; it is not in the v1.1 code |
| Privacy | "Anonymous" | **Transparent by default**, optional Sapling shielded addresses |
| Security | Quark hashing, "nine levels of encryption" | **Proof of Stake**; Quark only ever mattered for mining |
| Community hub | AMMO.chat | **GLiBz** (glibz.com), with NUGGETS and the Schwag'n Depot |
| Contributor reserve | Set aside for contributors | **AMMOgeek/AMMOfreak contributor reserve**, held by the QuarterMaster reserve |
| Structured release | Positions held in trust | **2,350 masternode positions** (FOUNDING-50, SPARTAN-300, PATRIOT-2000), held by the QuarterMaster reserve |
| Supply | "No limit", with a monthly estimate | Fixed issuance schedule in the code; supply totals in Section 10 |

---

## 4. AMMO Specs

| Item | Setting (mainnet, v1.1.1) |
|---|---|
| Coin name | AMMOcoin |
| Coin abbreviation | AMMO |
| Codebase | PIVX Core 5.x (network upgrades through v5.6) |
| Consensus | Proof of Stake from block 2,776 (blocks 1 to 2,775 were mined with Proof of Work under v1.1.0) |
| Genesis block | `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2` (its coinbase is unspendable by design) |
| Target block time | 3 minutes (about 480 blocks a day) |
| Issuance | A declining schedule set by `GetBlockValue()` in the code (Section 10) |
| Masternode payment | Each block pays the masternode selected by the payment queue (`GetMasternodePayment()`) |
| Staker | The wallet that makes a block receives the rest of that block's issuance |
| Stake maturity | A coin must have 600 confirmations (about 30 hours) before it can stake |
| Coinbase maturity | Newly created coins can be spent after 100 confirmations |
| Cold staking | Yes: delegate to a staking server; owner keys stay offline |
| Masternode collateral | 10,000 AMMO in one output, 15 confirmations |
| Masternode network | Public, routable IPv4 address, P2P port 37020 |
| Treasury superblock | Every 43,200 blocks (about 90 days) |
| Treasury budget | Set by `GetTotalBudget()` in the code; paid only to proposals approved by masternode vote |
| Proposal fee | 50 AMMO, burned |
| Minimum transaction fee | 0.0001 AMMO per kB (transparent); shielded transactions use 100x that rate |
| Transaction fees in PoS blocks | Not paid to the staker; removed from circulation |
| Maximum block size | 2 MB |
| Address prefixes | Transparent `A...`; cold-staking `S...`; Sapling shielded `as1...` |
| Testnet addresses | `x...` or `y...` (P2P 37022, RPC 51475) |
| P2P port | 37020 |
| RPC port | 51473 (keep it private) |
| Network magic | `c7 9a e3 b5` (v1.1.1 does not talk to v1.0 or v1.1.0 nodes) |
| Block-1 reserve | 250,000,000 AMMO, set aside to airdrop v1.0 balances |
| Seed nodes | seed1.ammocoin.org, seed2.ammocoin.org |
| Amount ceiling | 9,999,999,999 AMMO: a sanity limit on any amount, not a supply target |

---

## 5. The Mission

*"Cryptocurrency for people, patriots & the planet"*

### PEOPLE
We the People matter. Every day individuals. Those who have the least are the ones who can benefit the most from the power of decentralized currencies, yet those are the ones who often know and understand the least about it. AMMO relies on a vanguard deployment and a steady series of promotional campaigns to educate and win the support of the masses: a wide and diverse pool of individuals around the world operating wallets, stakenodes and masternodes to form the backbone of the AMMO protocol.

### PATRIOTS
AMMO is American-born and global-bound. Patriots yearn for freedom lost in the world of modern centralized banking. Recent global events have shown that overzealous governments, "big brother" corporations and other nefarious actors all exploit today's technologies in order to spy, control and outright steal from individuals who lack the knowledge or resources to prevent it. AMMO runs on a robust, open-source protocol, keeps your coins under your own keys, and gives you real privacy tools when you choose to use them. AMMO is a Patriot's choice as the world delves ever deeper into the wild frontier of blockchain currencies.

### THE PLANET
This is our world. We aim for the stars but care for our home. Digital crypto should liberate us from needless paper waste, not expend precious electricity in its execution. From block 2,776 AMMO is secured by Proof of Stake: no mining rigs, no hashing race. A staking wallet runs on a laptop, a small Linux server or a 64-bit Raspberry Pi 4 or 5, drawing a tiny fraction of the electricity that proof-of-work coins like Bitcoin need. Conservation-minded individuals around the world can embrace AMMO as an eco-friendly choice.

Who says Patriots can't or aren't mindful of waste or needless draining of our planet's resources? After all, patriots are the ones usually mindful of conservation of the lands, its wildlife and its resources.

You can extend your patriotic vision into the crypto realm and feel good about it.

---

## 6. The Road to v1.1.1

Every frontier town has a story of a hard winter. Here is ours, told straight.

- **v1.0 (2021).** The first AMMO chain, a PIVX v3.3 fork. It stalled: most v1.0 nodes stopped at block 409,459 on March 29, 2025, and a fork branch ran on to block 435,172 until February 24, 2026. The v1.0 chain is halted and nobody can send v1.0 transactions.
- **v1.1.0.** A new chain on the modern PIVX codebase, with a new genesis block. Block 1 holds a one-time **250,000,000 AMMO reserve** to repay v1.0 holders. The chain mined 2,775 Proof-of-Work blocks and then stopped.
- **v1.1.1 (this edition).** A mandatory hard fork. From **block 2,776** blocks are made by staking, not mining. v1.1.1 uses new network magic bytes and a new data folder so it never mixes with v1.0 or v1.1.0. Every node, wallet, staker and masternode must upgrade. Install v1.1.1 only from the official AMMOcoin GitHub release.

### The v1.0 balance airdrop
v1.0 balances from the official snapshot at **v1.0 block 434,881** are airdropped to the **same addresses** on v1.1, paid from the block-1 reserve. The address format is the same, so the keys in your v1.0 `wallet.dat` control your airdropped balance.

- Keep your v1.0 `wallet.dat` and back it up offline.
- **Send nothing anywhere.** There is no disposal address and no email registration. Anyone who asks you to send coins, keys or wallet files "for migration" is trying to steal them.
- If an address is missed, a signed-message claim (`signmessage` with your v1.0 address) is the fallback. A signature proves ownership without revealing your key.
- There is no deadline. Earlier instructions with a deadline or a disposal address are withdrawn.

The airdrop is paid first. The QuarterMaster reserve described in Section 12 is funded from the block-1 reserve after the v1.0 airdrop, together with voluntary pledges from the early contributors who hold the largest v1.0 balances.

---

## 7. Global Payment System

AMMO aims to be a convenient, low-cost way for people to pay each other directly, anywhere in the world, with no bank in the middle. To get there, several things must be true.

### AMMO MUST BE PRIVATE
The reason individuals worldwide favor cash or precious gems and metals is the privacy they offer, a level far beyond what digital payment systems allow. Centralized and often compromised financial institutions offer convenience at the hefty cost of privacy. Sadly, much of crypto has bent to the whims of that same centralized banking model. Your privacy and your ability to use AMMO without forced, needless surveillance[^tax] should be comparable to the use of cash.

The 1st Edition called AMMO "anonymous". That overstated it, and here is the honest version:

- **Transparent by default.** Regular AMMO addresses work like Bitcoin's. The addresses and amounts of every transparent transaction are public on the blockchain.
- **Shielded when you choose.** AMMO v1.1 supports **Sapling** shielded addresses (`as1...`). When coins move between shielded addresses, the blockchain does not show the sender, the receiver or the amount. Commands include `getnewshieldaddress`, `shieldsendmany` and `getshieldbalance`.
- **Know the limits.** Shielding is optional. Moving coins from a transparent address into a shielded one, or back out, reveals the transparent side. Your IP address is visible to the peers your node connects to.

The mission of the AMMO founders is to teach users the methods, practices and habits that make privacy not only available but practiced: use shielded addresses for private payments, don't reuse transparent addresses, and encrypt and back up your wallet.

### AMMO MUST BE FAST
A transaction reaches the network within seconds of being sent. The network targets one block every **3 minutes**, so a payment typically gets its first confirmation within a few minutes; the receiver decides how many confirmations to wait for before treating a payment as final. The 1st Edition offered SwiftX for near-instant confirmations. **SwiftX is not part of AMMOcoin v1.1** and has been dropped from this edition.

### AMMO TRANSACTIONS MUST BE CHEAP
- **Minimum fee: 0.0001 AMMO per kB** for transparent transactions. A normal payment is well under 1 kB.
- **Shielded transactions** pay 100 times that rate (0.01 AMMO per kB), because they are larger and heavier to verify.
- **Custom fee:** the wallet can pay more than the minimum for faster inclusion when blocks are busy.
- **No zero-fee transactions.** Nodes do not relay a transaction below the minimum fee.
- In Proof-of-Stake blocks, fees are not paid to the staker; they are removed from circulation.
- Newly created coins can be spent after 100 confirmations. Ordinary received payments can be spent once they confirm.

### AMMO MUST BE SECURE
Security is one of the most important aspects of any cryptocurrency. The 1st Edition spent pages on the Quark hashing algorithm and claimed "nine levels of encryption". That is withdrawn. Quark chains six SHA-3 competition hash functions (BLAKE, Blue Midnight Wish, Grøstl, JH, Keccak and Skein) over nine rounds. It is hashing, not encryption, and it only ever mattered for mining. Under Proof of Stake, mining hashes no longer secure AMMO.

What actually protects the network and your coins in v1.1.1:

1. **Proof of Stake.** From block 2,776 blocks are made by staking wallets. To rewrite history an attacker would need to control most of the coins that are staking, not just rent hardware. Coins must have 600 confirmations before they can stake.
2. **Masternodes.** Each locks 10,000 AMMO, runs 24/7 on a public IP address, relays and checks blocks and transactions, and votes on the treasury budget.
3. **Cold staking.** Coins can stake on a server that holds only a staking key. It can stake them but can never spend them; the spending key stays in the owner's wallet, which can be offline.
4. **Encrypted wallets.** Encrypt your wallet and unlock it for staking only, so a running node can stake but cannot send.
5. **Open source, verified releases.** The code is public on GitHub. Every release ships a SHA-256 checksums file; check your download against it before running it.

---

## 8. Operators
### nodes, stakenodes & masternodes

### Operator: node
A node is an active AMMO core wallet. No specialized hardware is needed. An average laptop or desktop, a small Linux server or a 64-bit Raspberry Pi 4 or 5 has the computing power to join the network (Linux release binaries need Ubuntu 22.04 or newer, or Debian 12 or newer). When the wallet is running and connected it is considered hot; a wallet that is not running and connected is cold. Anyone with an AMMO core wallet can send and receive AMMO. The important fact for patriots is that you hold the keys and control all AMMO in your possession. That differs from the crypto exchanges many people know, where the exchange controls its clients' coins.

### Operator: stakenode
Nothing special is needed to become a stakenode. An AMMO core wallet that is running, synced, unlocked for staking and holding coins with at least **600 confirmations** is a stakenode. Each block, one staker wins the right to make it; that is how Proof of Stake secures the network. The chance of making any given block is proportional to the coins staking, so a small holder stakes less often than a large one. There is no minimum balance in the code.

```
ammocoin-cli walletpassphrase "YourPassphrase" 0 true
ammocoin-cli getstakingstatus
```

**Cold staking** lets a server that is online 24/7 stake your coins while the keys that can spend them stay in your own wallet, which can be offline:

1. On the staking server: `getnewstakingaddress` (returns an `S...` address), and `delegatoradd "<owner_address>"` to accept your delegation.
2. In your owner wallet: `delegatestake "<S_staking_address>" <amount> "<owner_address>"`.
3. Check with `getcoldstakingbalance` and `listcoldutxos` on the server, `getdelegatedbalance` in the owner wallet.

Delegated coins also need 600 confirmations before they stake. The server can never send them; to stop, spend them from the owner wallet back to a normal address.

### Operator: masternode
AMMOcoin wants as many "everyday" folks as possible to become an integral part of the network. We want quantity AND quality. A masternode requires an AMMO core wallet in the same manner as the stakenode. It also requires:

- **10,000 AMMO** collateral in one output, with at least 15 confirmations[^collateral]
- A **public, routable IPv4 address** with **P2P port 37020** open (any other port is rejected; keep RPC port 51473 private)
- A server online 24 hours a day: a VPS or dedicated Linux server (you're gonna love this)[^lean]

Setup uses a controller wallet that holds the collateral and the masternode server, which needs no coins: `createmasternodekey` and `getmasternodeoutputs` in the controller, one line in `masternode.conf`, `masternode=1` and `masternodeprivkey` on the server, then `startmasternode alias false <alias>` from the controller. The full steps are on ammocoin.org (Become an AMMOmaster) and in `docs/03-masternode-setup.md`; the `install-node.sh` script does most of the server work.

A masternode operator has proven a commitment to the success, security and diversity of the AMMO network: dedicated nodes running 24/7 relay and validate blocks and transactions, which bolsters consistency and reliability.

**How masternodes take part, in code terms:** enabled masternodes take turns in a payment queue. Each block pays the one masternode whose turn it is, out of that block's issuance (`GetMasternodePayment()`); the more masternodes, the longer each one waits for its turn. Masternodes also serve the network and hold the votes in DAO Command.

### First Operators
The wild west was tamed by brave settlers, prospectors and daring souls. Operators on the v1.1.1 network secure it and vote in DAO Command. The code treats every staker and masternode the same, whenever they join, and there is no edge in arriving first. The FOUNDING-50, SPARTAN-300 and PATRIOT-2000 positions in Section 12 are how the project puts masternodes into as many independent hands as possible.

---

## 9. DAO Command

*"I believe that banking institutions are more dangerous to our liberties than standing armies."* Thomas Jefferson

It is never wise to go out into the wild west alone. You ain't John Wayne and neither am I. We don't need corporations or elites. We need a posse of brave men and women to join our ranks. Diversity will be our greatest strength. Unique experiences, ideas and visions from the many shall make AMMO excel. Our command is that of the DAO, a Decentralized Autonomous Organization with no corporate hierarchy or structure.

### "One masternode. One vote"

Each enabled masternode has one vote. On-chain spending is decided only by proposals that masternodes vote for, and it is paid by the protocol itself from the treasury budget. Votes are signed by each masternode's key and are visible to the network; they carry no personal name.

**The treasury, in code terms.** Every **43,200 blocks** (about 90 days at 3-minute blocks) the network reaches a superblock. The budget for that cycle is set by `GetTotalBudget()` in the code. Only approved proposals are paid; unallocated budget is never created.

**Rules the code enforces:**

- Anyone with a wallet can submit a proposal; only masternodes vote.
- Proposal name: 20 characters at most. URL: 64 characters at most.
- The proposal fee is **50 AMMO**, burned (sent to an unspendable output). No refund.
- A proposal can ask for at most **6 payments**, one per cycle, starting at a superblock height. (The RPC help says "monthly"; on AMMOcoin mainnet each cycle is about 90 days.)
- A proposal must be at least 24 hours old to enter a budget.
- To pass, YES minus NO must be more than **10%** of enabled masternodes. A proposal is dropped if NO minus YES exceeds 30%.
- Passing proposals are ranked by YES votes and funded in that order until the cycle's budget is used up.
- Masternodes then vote on a finalized budget (5 AMMO finalization fee), and the approved payments are made by the network starting at the superblock height.

Each and every masternode operator can, and is encouraged to, submit proposals. This is done from the console of your wallet (Tools > Debug console, or `ammocoin-cli`):

1. **Find the next superblock.**
   ```
   getnextsuperblock
   ```
   Example result: `43200`. Use it as `start`.

2. **Prepare the proposal and pay the fee.** `preparebudget` takes six arguments:
   1. `"name"`: proposal name (20 character limit). Keep it concise and simple.
   2. `"url"`: link to the proposal details (64 character limit). Post the details where the community can discuss them, such as the Proposals page on ammocoin.org and GLiBz.
   3. `npayments`: total number of payments (1 to 6, one per cycle)
   4. `start`: the starting superblock height from step 1
   5. `"address"`: the AMMOcoin address to receive payments
   6. `monthly_payment`: the amount per payment, in AMMO

   ```
   preparebudget "trail-guide" "https://ammocoin.org/proposals/trail-guide" 2 43200 "A_YOUR_ADDRESS" 5000
   ```
   It returns the **fee transaction id** (the 50 AMMO fee). Record it and wait for that transaction to get at least 6 confirmations.

3. **Submit the proposal.** `submitbudget` takes the same six arguments plus the fee transaction id:
   ```
   submitbudget "trail-guide" "https://ammocoin.org/proposals/trail-guide" 2 43200 "A_YOUR_ADDRESS" 5000 "FEE_TXID"
   ```
   It returns the **proposal hash**. Share it with the masternode operators.

4. **Check and vote.**
   - Status of a proposal: `getbudgetinfo "trail-guide"`
   - Votes cast so far: `getbudgetvotes "trail-guide"`
   - What would be paid if the budget closed now: `getbudgetprojection`
   - Vote YES with every masternode in this controller wallet: `mnbudgetvote "many" "PROPOSAL_HASH" "yes"`
   - Vote NO with every masternode in this wallet: `mnbudgetvote "many" "PROPOSAL_HASH" "no"`
   - Vote with one masternode by alias: `mnbudgetvote "alias" "PROPOSAL_HASH" "yes" "mn1"`
   - Vote from the masternode server itself: `mnbudgetvote "local" "PROPOSAL_HASH" "yes"`

Remember: each masternode gets one vote. One operator running 10 masternodes casts 10 votes. The `"many"` mode casts the same vote for every masternode listed in that controller wallet's `masternode.conf`. An operator with masternodes spread across several controller wallets must vote from each wallet to cover them all.

---

## 10. Supply

*"It is the quality rather than the quantity that matters."* Lucius Annaeus Seneca

In Bitcoin, issuance is fixed by the code, on a schedule that anyone can read.

The 1st Edition said AMMO "has no limit supply" and estimated its monthly issuance. That is withdrawn. AMMO's issuance is set by its code, not by anyone's whim, and anyone can read it in `GetBlockValue()` in `src/validation.cpp`.

### The issuance schedule (as in the code)

Issuance is a declining schedule set by `GetBlockValue()` in `src/validation.cpp`. Block 1 holds the one-time 250,000,000 AMMO reserve. After that the schedule steps down at blocks 86,400, 151,200 and 302,400, then every 43,200 blocks through block 648,000, and changes again at the mainnet parameters `nRewardZCV2Height = 1,153,160` and `nRewardV55Height = 3,715,200`. v1.1.1 activates every PIVX network upgrade at block 2,776, but keeps these schedule heights separate so the fork does not change what blocks pay. Each block pays the masternode selected by the payment queue, and the staker that makes the block receives the rest.

At 480 blocks a day, block 3,715,200 is about 21 years after the fork. Real block times vary, so dates are estimates; heights are exact.

### Supply totals
- **Block-1 reserve:** 250,000,000 AMMO (airdrop to v1.0 holders first; the QuarterMaster reserve, Section 12, is funded from the block-1 reserve after the airdrop, together with voluntary pledges from the early contributors who hold the largest v1.0 balances).
- **Total supply through block 3,715,200:** 316,620,770 AMMO, the reserve included.
- **Maximum possible supply through block 3,715,200:** about 329,170,370 AMMO, and only if every treasury cycle is fully allocated to approved proposals. Unallocated budget is never created.
- **After block 3,715,200:** AMMO has no hard cap. Like PIVX, it keeps a small, fixed tail issuance set by the same code.
- Fees in Proof-of-Stake blocks are removed from circulation, so actual supply can run slightly below these figures.

The code also contains a constant of **9,999,999,999 AMMO** (`nMaxMoneyOut`). It is a sanity ceiling the code uses to reject impossible amounts, not a supply target or a schedule. Actual issuance is the reserve plus the schedule above.

---

## 11. Initial Valuation

**ZERO. ZILCH. ZIP. NADA.**

### No ICO
AMMO has no initial valuation, as there has never been and will never be any Initial Coin Offering (ICO), and there is no pre-sale.

AMMO is not on any crypto exchange. Why? By design. AMMO is released in a structured way to form as strong and diverse a network as possible. Where other cryptocurrencies relied on inflated ICOs, AMMO's release is focused on bolstering its network through as many stakenodes and masternodes as possible, under the control and benefit of as many individuals as possible.

Those who join the AMMO network as stakers and masternode operators are a critical component: they secure it, as Section 8 describes. Folks who become AMMOfreaks and AMMOgeeks, building and promoting the network, can receive awards from the contributor reserve.

So, yeah: AMMO has no assigned value, and the project makes no claim about what it is or will ever be worth.

### No Exchanges
Collectively, AMMO will not be offered on exchanges without explicit approval through DAO Command. As a decentralized system, no one has authority over individual AMMO holders. However, Founding50 members have vowed to honor decisions made through DAO Command in this important regard.

### The Closed Loop
The AMMOcoin project runs a closed loop. These are its principles:

1. **The project assigns AMMO no value.** It publishes no price, no target and no exchange rate to any money.
2. **The project never sells AMMO for money,** and **never buys it back.** No reserve AMMO is ever sold for cash, and no tier position can be bought.
3. **AMMO comes from taking part, never from a sale.** The ways in are:
   - **Staking** (making blocks)
   - **Masternodes** (taking turns in the payment queue)
   - **Treasury proposals** approved by masternode vote
   - **Structured release positions** (FOUNDING-50, SPARTAN-300, PATRIOT-2000)
   - **AMMOgeek and AMMOfreak awards** from the contributor reserve
   - **GLiBz NUGGETS from activity** swapped for AMMO
   - The **v1.0 airdrop**, which restores v1.0 balances
4. **NUGGETS have no cash value.** NUGGETS are the GLiBz platform currency, not a cryptocurrency, and cannot be cashed out for money.
5. **Only NUGGETS from activity convert to AMMO.** NUGGETS that come from activity on GLiBz can be swapped for AMMO at the current GLiBz swap rate, which GLiBz sets and which is tiered and capped per member each month. NUGGETS paid for with cash or with AMMO are spend-only: they stay inside GLiBz and can never be swapped for AMMO or used toward a tier position.
6. **Dollar goods and the reward catalogue are kept apart.** The GLiBz store at shop.glibz.com prices its goods in dollars with an ordinary card checkout. The GLiBz reward catalogue in the Schwag'n Depot has its own redemption amounts in NUGGETS or AMMO, which are not converted from dollars. Neither sets a price for AMMO.

---

## 12. Structured Release

The AMMO founders had a goal: AMMO diversified and spread around the globe as thoroughly as possible. AMMO in the hands of everyone. To do it cost-effectively and without needing corporate or elitist involvement.

### The Vanguard Deployment
AMMO deployment is structured around several key vectors.

#### AMMOcoin.org
The informational home of the AMMO protocol. Visitors can find out all about AMMO, read and download this snazzy white paper, get the wallets, follow the migration and proposals, and learn about the sister sites. Software is published only through the official AMMOcoin GitHub releases, each with a SHA-256 checksums file.

#### GLiBz (glibz.com)
GLiBz replaces AMMO.chat. Old links to AMMO.chat now land on GLiBz. GLiBz (glibz.com), the community hub in the AMMOcoin ecosystem, is a western-themed social and community platform built on the open-source UNA community software.

Much like the issues with traditional financial sources, traditional social media outlets have grown into monstrosities of privacy abuses, neglect of user desires and hyper-partisan biases that diminish the core purpose that made them so popular in the first place. Traditional social media is like the ancient pyramids built for the benefit of the pharaohs off the blood, sweat and tears of the abused masses. Another irritating reality is that each monolithic outlet offers one limited service: video here, short messages there, family over yonder, photos somewhere else.

At GLiBz you can do all of these things in one place, with one login, while keeping your god-given right to privacy, choice and self-control: post Squawks to The Feed, share photos in Troves, form Cahoots, send a Wire to yer pardners, holler on the Soapbox, and post Flix and Movin' Pictures.

- **NUGGETS.** Members collect NUGGETS for taking part: logging in, posting, commenting, connecting, referring and more. NUGGETS rank you on the Good Nugget Wall, can be redeemed in the GLiBz reward catalogue, and (NUGGETS from activity only) can be swapped for AMMO or redeemed toward a tier position. NUGGETS have no cash value.
- **The Schwag'n Depot.** The GLiBz marketplace: the Depot on glibz.com, with its reward catalogue, and the GLiBz store at **shop.glibz.com**, which sells goods in dollars.
- **Coming to GLiBz** (built and being switched on): an Activity hub listing every way to take part, AMMO airdrops for ranking up and for referrals, and a bridge to the sister ecosystem everQUIN.

### The QuarterMaster reserve
The AMMO for the structured release and the contributor reserve is held and controlled by the **QuarterMaster reserve**: the project's reserve wallets, named after QuarterMaster, the GLiBz and AMMOcoin host. It is funded from the 250,000,000 AMMO block-1 reserve **after the v1.0 balance airdrop is paid**, together with voluntary pledges from the early contributors who hold the largest v1.0 balances: v1.0 holders come first. The 61 largest v1.0 holders, early contributors, have agreed to pledge the same fixed share of their snapshot balances by signed message (listed in `docs/migration/data/quartermaster-pledges.csv`); their airdrop will be reduced by that amount (AMMO-D-2026-10-18-12).

The tiers and the contributor reserve are an off-chain distribution programme run by the AMMOcoin project. They are not a consensus rule, and nothing in the code reserves them.

### Masternode tiers: 2,350 positions

| Tier | Positions | Each position | Who | How |
|---|---|---|---|---|
| **FOUNDING-50** | 50 | Collateral for up to 20 masternodes | Founders, developers and the core teams who build and run the network, its wallets, explorers and sister sites | By invitation only; not offered to the public. In progress |
| **SPARTAN-300** | 300 | Collateral for 3 masternodes | The first outside adopters: AMMOgeeks, AMMOfreaks and GLiBz members | Opens with the v1.1.1 launch. Redeemed on GLiBz with NUGGETS from activity, or by direct QuarterMaster award |
| **PATRIOT-2000** | 2,000 | Exactly one masternode's collateral | Anyone who wants to help secure the AMMO blockchain as an AMMOmaster: the widest, most diverse tier | Opens after SPARTAN-300 is fully allocated. NUGGETS from activity or direct QuarterMaster award |

Positions are redeemed or awarded, never sold. Cash and paid-for NUGGETS cannot be used. Rank and account-age requirements apply, and full terms are published on GLiBz. A position can include optional help setting up the masternode on your own Linux server or cloud VPS; you keep the keys and run the node. Masternodes are not sold as packages: anyone with 10,000 AMMO can run one.

**What a position does, in code terms:** a masternode with 10,000 AMMO collateral takes its turn in the payment queue, serves the network and casts one vote per masternode in DAO Command. AMMO you hold can also stake and help make new blocks. Nothing more is promised: how often a node takes part depends on how many masternodes and stakers are on the network and on keeping your node online.

### AMMOgeek & AMMOfreak contributor reserve
A further reserve, also held by the QuarterMaster reserve, is earmarked for the people who expand the network (AMMOgeeks) and the people who promote it in their own circles (AMMOfreaks). Awards are made for contributions such as code, nodes, tools, content and campaigns; there is no set amount per contribution. It's the one time a "participation trophy" really means something.

This reserve is separate from the on-chain treasury, which pays only the budget proposals that masternode operators vote for. Anyone, contributors included, can also submit a budget proposal as an additional route.

#### AMMOgeeks
An AMMOgeek is an individual who has technical skills to offer. The contributor reserve exists to encourage and recognize the crypto community's help improving everything from AMMO wallets to new features within the AMMO network.

AMMO is built on the PIVX Core codebase, so it shares much of its infrastructure with DASH and PIVX. Enthusiasts and developers on those projects will find an easy fit, and a chance to put their existing knowledge and skill to work helping AMMO grow and become even more amazing.

If this is something you have an interest in, swing by GLiBz. The QuarterMASTER is the one coordinating this element of AMMO's structured release and the one who discusses contributor awards. Of course you can also join us on GitHub (github.com/everquin/AMMOcoin) to fork our files and begin working right away.

#### AMMOfreaks
AMMO was created with the determination to get it into the hands of as many individuals as humanly possible, all without the benefit (and obvious detriment) of huge corporate backers. To offset this, the enthusiasm and desire of folks like you to spread the word is absolutely paramount.

The contributor reserve recognizes individuals who hit the social media streets to drive excitement and information to the masses: affectionately, AMMOfreaks. Awards can come for sharing content, creating cool memes and promos, bringing people in, or any of a variety of ways.

First step as always is to download your AMMO wallet. Then swing by GLiBz, where the QuarterMASTER posts ways to contribute, and start collecting NUGGETS by taking part.

Tier positions and awards may not be available in every jurisdiction.

---

## 13. Where to Check Our Work

Don't trust: verify. Every figure in this edition comes from the AMMOcoin v1.1.1 source code (github.com/everquin/AMMOcoin):

| What | Where in the code |
|---|---|
| Issuance schedule, block-1 reserve | `src/validation.cpp`: `GetBlockValue()` |
| Masternode payment | `src/validation.cpp`: `GetMasternodePayment()`; `src/chainparams.cpp`: `nMNBlockReward`, `nNewMNBlockReward` |
| Fork height 2,776, schedule heights, block time, stake depth, collateral, budget cycle | `src/chainparams.cpp` (mainnet section) |
| Treasury budget | `src/budget/budgetmanager.cpp`: `GetTotalBudget()` |
| Proposal rules and RPCs | `src/budget/budgetproposal.cpp`, `src/rpc/budget.cpp` |
| Fees | `src/validation.cpp` (`minRelayTxFee`), `src/wallet/wallet.h` |
| Ports 37020 / 51473 | `src/chainparams.cpp`, `src/chainparamsbase.cpp` |

Guides: `docs/02-staking-guide.md`, `docs/03-masternode-setup.md`, `docs/06-dao-participation.md`, the v1.1.1 release notes, and `docs/migration/V1.0_BALANCE_AIRDROP.md`.

Nobody from the AMMOcoin team will ever ask you to send coins, private keys or wallet files.

[^tax]: AMMO is not a proponent of its network being used to circumvent or bypass an individual's local, state or federal tax or financial reporting obligations. It only strives to offer the same level of individual responsibility and freedom as cash. Every individual is responsible for their own actions.

[^collateral]: This AMMO never leaves the owner's wallet. It is simply "locked" as collateral for as long as its owner wishes to have it linked to an active masternode. Spending or moving the collateral output stops the masternode.

[^lean]: Forget about costly mining hardware and electricity-scarfing systems. AMMO sips energy on lean Linux servers (Ubuntu 22.04 or newer); a small cloud VPS is plenty.
