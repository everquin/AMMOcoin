# AMMOcoin compliance decision log

ADR-style log of decisions that keep AMMOcoin from being pay-to-play, an ICO/token sale, or presented as having a value or a return. Newest last. Entries are never rewritten: to change a decision, add a new entry that says `Supersedes: <ID>`.

Not legal advice. Counsel review status: **pending**.

**Evidence rules.** SHAs without a prefix are in this repository (`everquin/AMMOcoin`, branch `v1.1.1-pos-fork`). `website` = `everquin/ammocoin_website` (branch `v1.1.1-site-accuracy`), `app` = `everquin/AMMOcoin_App` (branch `v1.1.1-app-fixes`). file:line refers to the tree at `a0a0918d9`. **UNVERIFIED** = could not be confirmed from the repositories.

**Owner approval.** All commits cited were made under the owner's git identity (`everquin`). Decisions marked *"Owner decision 2026-10-17"* were stated by the owner in the 2026-10-17 working session and relayed to the agent that wrote this log; there is no separately signed approval in the repository. Add a signed-off line (`Approved-by:`) to an entry when the owner confirms it in a commit or PR.

---

## AMMO-D-2026-10-16-01 v1.0 balances are airdropped to the same addresses; the disposal-address process is withdrawn

- **Date:** 2026-10-16
- **Principles:** AMMO-P-06, AMMO-P-13
- **Decision:** v1.0 balances from the snapshot at v1.0 block 434,881 are airdropped from the block-1 reserve to the same addresses. Holders send nothing. The earlier disposal-address / email / 90-day-deadline process is withdrawn. A signed message (`signmessage`) is the only fallback for a missed address. No deadline.
- **Context:** The v1.1.0 migration guides asked holders to send coins to a disposal address and register by email within 90 days. That pattern is indistinguishable from a scam and pressures holders.
- **Rationale:** Returning what holders already held, without asking them to send anything, is not a sale and not a solicitation.
- **Alternatives rejected:** disposal address + email registration (scam-shaped, custodial); deadline (pressure).
- **Enforcement / evidence:**
  - `a5858d1ce` adds `docs/migration/V1.0_BALANCE_AIRDROP.md` and marks `DISPOSAL_ADDRESS.md`, `DISTRIBUTION_PROCESS_GUIDE.md`, `MANUAL_MIGRATION_PLAN_v1.0_to_v1.1.0.md`, `USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md` superseded.
  - Snapshot data: `docs/migration/data/v1.0-complete-balance-snapshot.json`.
  - White paper 2nd Edition: `docs/whitepapers/AMMOcoin_Whitepaper_2ndEdition_v1.1.1.md:147-155`.
  - `website 1a4bb53` rewrites `migration.html` around the snapshot and airdrop and removes the 90-day banners.
  - The block-1 reserve itself is consensus: `source/src/validation.cpp:847-851` (`GetBlockValue(1) = 250,000,000 AMMO`).
- **Not enforced in code:** the order "airdrop first, then QuarterMaster reserve" is an off-chain commitment. **UNVERIFIED:** that the airdrop transactions have been sent, and a public, reconcilable record of them (see gap G-06).
- **Owner approval:** commit under owner identity.

## AMMO-D-2026-10-16-02 Correct the published premine address

- **Date:** 2026-10-16
- **Principles:** AMMO-P-05, AMMO-P-06
- **Decision:** The 250M premine is in block 1 at `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u`; `AGkC8...` is only the unspendable genesis output. Documents say so.
- **Rationale:** Anyone auditing the reserve needs the right address.
- **Enforcement / evidence:** `7b61ba5b5` (`V1.1.0_GENESIS_BLOCK_AUTHORITY.md`, v1.1.0 release notes, v1.1.0 white paper). `377c3362b` puts the premine address in the README.
- **Gap:** the code comment at `source/src/validation.cpp:849` still names `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` as the distribution address (G-01).
- **Owner approval:** commit under owner identity.

## AMMO-D-2026-10-16-03 The PoS fork must not change what blocks pay

- **Date:** 2026-10-16
- **Principles:** AMMO-P-05, AMMO-P-04
- **Decision:** The v1.1.1 fork activates every PIVX upgrade at block 2,776, but the reward schedule keeps its own heights (`nRewardZCV2Height` 1,153,160 and `nRewardV55Height` 3,715,200 on mainnet). Blocks keep paying 250 AMMO (3 to the masternode, 247 to the staker), and the budget stays 20% of block value x 43,200.
- **Context:** Keying rewards off the upgrade heights would have silently changed the economics at the fork (10 AMMO per block, 6 to masternodes, budget 100%).
- **Rationale:** A consensus change to issuance must be deliberate and announced, never a side effect.
- **Alternatives rejected:** accept the side effect; announce a new schedule.
- **Enforcement / evidence:**
  - `0f7d10faf`: `source/src/consensus/params.h:190-191` (fields), `source/src/chainparams.cpp:284-285` (mainnet values), `source/src/validation.cpp:816-852` (`GetBlockValue`), `source/src/budget/budgetmanager.cpp:858-871` (`GetTotalBudget`), `source/src/qt/transactionrecord.cpp:62`, tests `source/src/test/budget_tests.cpp:24-70`.
  - Masternode payment and collateral: `source/src/chainparams.cpp:214-216`.
  - Docs follow-up `c21bba0e7`; release notes `docs/release-notes/RELEASE_NOTES_v1.1.1_DRAFT.md:32`.
  - App mirrors the schedule: `app 88dc399`, `lib/utils/network_constants.dart:86-141`, `test/network_constants_test.dart`.
- **Owner approval:** commit under owner identity.

## AMMO-D-2026-10-16-04 Staking example uses realistic network weight; v1.1.0 white papers superseded

- **Date:** 2026-10-16
- **Principles:** AMMO-P-04, AMMO-P-05
- **Decision:** The staking guide's example no longer shows an ~87% "annual return"; the v1.1.0 white papers are marked superseded.
- **Evidence:** `5e2a9e2c8` (`docs/02-staking-guide.md`, `docs/whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md`, `docs/whitepapers/AMMOcoin_Whitepaper_v1.1.0.md`).
- **Gap:** the example still ends in a percentage return (`docs/02-staking-guide.md:294`, "Annual Return ... ~17%"), which AMMO-P-04 forbids (G-02).
- **Owner approval:** commit under owner identity.

## AMMO-D-2026-10-16-05 Public site copy follows the code; untrue, ROI-like and anonymity claims removed

- **Date:** 2026-10-16
- **Principles:** AMMO-P-03, AMMO-P-04, AMMO-P-05, AMMO-P-08, AMMO-P-10
- **Decision:** ammocoin.org copy is rewritten from the v1.1.1 code. Removed: "Earn 60% Block Rewards", "200 AMMO stake reward", "Anonymity"/"AMMOcoin is Anonymous", "Limited Supply"/scarcity claims, "earmarked founder supply", "Trade at AMMOcapital - Cryptocurrency Exchange", AMMOmaster "packages" acquired with "earned/exchanged NUGGETS".
- **Evidence:** `website 1a4bb53`, `website e8c29b3`, `website 104eed5`. See the website repo's `docs/compliance/DECISIONS.md` for page-level detail.
- **Owner approval:** commits under owner identity.

## AMMO-D-2026-10-17-01 2nd Edition white paper: no ICO, no price, no exchanges, the closed loop, honest privacy, code wins

- **Date:** 2026-10-17
- **Principles:** AMMO-P-01 to AMMO-P-12
- **Decision:** Publish the 2nd Edition (v1.1.1) white paper, replacing the 1st Edition (2022/01/15), with: a disclaimer that it is not an offer, not advice and not a promise of return, yield, profit or price, and that rewards are described only in code terms (line 58); "ZERO. ZILCH. ZIP. NADA." and No ICO (346-357); No Exchanges without DAO Command approval (359-360); The Closed Loop (362-377); honest privacy (163-172) with the tax footnote (463); issuance exactly as in the code with the 1st Edition's supply estimates withdrawn (301-344); tier positions earned or awarded, never sold (405-420, 441); "where this paper and the code disagree, the code wins" (16).
- **Context:** The 1st Edition called AMMO anonymous, mis-stated supply and imagined AMMO.capital as an exchange.
- **Alternatives rejected:** keep the 1st Edition with errata; drop the white paper.
- **Enforcement / evidence:** `bbd8f61fc` (adds `docs/whitepapers/AMMOcoin_Whitepaper_2ndEdition_v1.1.1.md`; budget-cycle comment `source/src/chainparams.cpp:208` corrected to ~90 days), `ae2a1b3cb` (pending-release banner, GLiBz hub wording). Website copies: `website b4ae1db`, `website d293249` (`whitepaper.html`, PDF).
- **Gaps:** G-03 (Bitcoin-value comparison, line 357), G-04 (broken sentence at line 155).
- **Owner approval:** commits under owner identity.

## AMMO-D-2026-10-17-02 Structured-release tiers continue as earned/awarded positions held by the QuarterMaster reserve

- **Date:** 2026-10-17
- **Principles:** AMMO-P-02, AMMO-P-06, AMMO-P-07, AMMO-P-14
- **Decision:** FOUNDING-50 (50 x 200,000 AMMO, invitation only), SPARTAN-300 (300 x 33,333.333 AMMO) and PATRIOT-2000 (2,000 x 10,000 AMMO, opens after SPARTAN-300 is fully allocated) continue as an off-chain programme. The AMMO is held by the QuarterMaster reserve, funded from what remains of the block-1 reserve after the airdrop. Positions are earned with earned NUGGETS or awarded directly by the QuarterMaster; never sold; cash and purchased NUGGETS cannot be used. Rank and account-age requirements; jurisdiction note.
- **Context:** The tiers were removed from the site on 2026-10-16 while copy was corrected, then restored accurately. Earlier copy offered "AMMOmaster packages" for "earned/exchanged NUGGETS", which left room for a purchase path.
- **Rationale:** Distributing masternode collateral to many independent hands without any sale.
- **Alternatives rejected:** selling positions or packages; allowing purchased NUGGETS; dropping the programme.
- **Enforcement / evidence:** white paper `docs/whitepapers/AMMOcoin_Whitepaper_2ndEdition_v1.1.1.md:405-420`; `website afb24a5`, `website 28c00e7`. The earned-only rule is enforced on GLiBz (see the GLiBz compliance record); nothing in this repository enforces it, by design (the programme is not a consensus rule).
- **UNVERIFIED:** the QuarterMaster reserve wallet addresses are not published (G-06); positions allocated so far.
- **Owner approval:** Owner decision 2026-10-17 ("tiers continue as earned/awarded positions held by the QuarterMaster reserve").

## AMMO-D-2026-10-17-03 Closed loop with GLiBz approved

- **Date:** 2026-10-17
- **Principles:** AMMO-P-02, AMMO-P-03, AMMO-P-09
- **Decision:** Only earned NUGGETS swap to AMMO (tiered, capped per member per month, no fixed ratio quoted); purchased NUGGETS are spend-only; the dollar-priced store and the reward catalogue are kept apart; catalogue prices are not converted from dollars.
- **Evidence:** white paper lines 362-377; `website 28c00e7` (drops "100 NUGGETS = 1 AMMO" everywhere). GLiBz implementation is recorded in the GLiBz repository.
- **Related code here:** `payment-gateway/` sends AMMO for GLiBz swaps (`payment-gateway/src/app/api/payouts/route.ts`); it has no knowledge of earned vs purchased NUGGETS, so the gate must stay on GLiBz. Its wording calls the swap a "sale" (G-07).
- **Owner approval:** Owner decision 2026-10-17 ("closed loop approved").

## AMMO-D-2026-10-17-04 Exchange listings only through a masternode vote

- **Date:** 2026-10-17 (reaffirms a 1st Edition commitment)
- **Principles:** AMMO-P-08
- **Decision:** No exchange listing, including AMMO.capital, except through DAO Command approval. AMMO.capital is not live and offers no trading.
- **Evidence:** white paper lines 359-360, 392; `website e8c29b3` (AMMO.capital meta no longer advertises a live exchange); website `ammocapital.html:380`, `ammocoin-value.html` ("Exchanges only by vote").
- **Not enforced in code:** governance commitment only. The budget system (`source/src/budget/`) is the voting mechanism; no listing proposal exists.
- **Gaps:** G-05 (FAQ points to exchanges and CoinMarketCap), G-08 (explorer price/market-cap plumbing).
- **Owner approval:** commit under owner identity.

## AMMO-D-2026-10-17-05 Front-facing code public; no deploy without review

- **Date:** 2026-10-17
- **Principles:** AMMO-P-15
- **Decision:** The wallet app and website front-facing code are public so anyone can check them. Nothing ships without review against this checklist.
- **Evidence:** `app 61d5674` (MIT licence), `app a5d52e1` (internal notes moved to `docs/internal` and credentials redacted). This folder, the PR template and CODEOWNERS (added with this log).
- **Not enforced:** **UNVERIFIED** whether GitHub branch protection / required reviews are on for any of the three repositories. The rule is procedural until they are.
- **Owner approval:** Owner decision 2026-10-17 ("app and website front-facing code public; no deploy without review").

## AMMO-D-2026-10-17-06 Establish this compliance record

- **Date:** 2026-10-17
- **Decision:** Add `docs/compliance/` (README, PRINCIPLES, DECISIONS, REVIEW_CHECKLIST), a PR template with a compliance section, and CODEOWNERS for economic paths in all three AMMOcoin repositories.
- **Owner approval:** requested by the owner 2026-10-17 ("for auditing and tracking make sure any and all decisions ... is documented well in each respective repo").

## AMMO-D-2026-10-17-08 Docs, white papers and gateway wording follow the principles (fixes G-01 to G-05, G-07 wording, G-09, G-10, G-11)

- **Date:** 2026-10-17
- **Principles:** AMMO-P-02, P-03, P-04, P-05, P-06, P-08, P-09, P-10, P-11, P-12
- **Shared ID:** the same ID is used for the matching fixes in the website log (`website 59883d1`) and the app log (`app 49c0801`).
- **Decision / change (`be2c0aad6`, branch `v1.1.1-pos-fork`):**
  - G-02 `docs/02-staking-guide.md`: "passive income", "while you sleep", "Compound Growth", "Annual Percentage Yield", "Portfolio Allocation" and the "Annual Return ~17%" example removed. Reward estimation is now: expected share of blocks = your weight / network weight; expected stakes per day = share x 480 blocks/day; each staked block pays `GetBlockValue()` minus `GetMasternodePayment()` at that height. No percentage return, no annualised figure. Tax section keeps record-keeping and adds the `[^tax]` footnote; "USD value at receipt" dropped (the project publishes no price).
  - G-02b `docs/03-masternode-setup.md`: "Economics & ROI Analysis" / "Investment Breakdown" / "ROI Optimization" / "Price Volatility" replaced by "How Masternode Payments Work" (collateral locked in your own wallet, 3 AMMO per paid block, about one payment every N blocks with N = enabled masternodes, the project publishes no price). "Premium rewards / higher returns than staking" (also untrue: 3 vs 247 AMMO) replaced with the code's payment.
  - G-02c `README.md`, `source/README.md`: "Passive income" -> stakers who create a block receive the staker share set by `GetBlockValue()`.
  - G-02d, G-05 `docs/10-faq.md`: "Where can I buy" now says the project does not sell AMMO, held no ICO and lists it nowhere; AMMO is received via staking, masternodes, contributions and *earned* GLiBz NUGGETS; listings only via a masternode vote. "Investment Questions" -> "Value Questions": AMMO is not an investment; the project makes no value claims and publishes no price. Added a tax question with the footnote. "your return depends on" / "Compounding" reworded.
  - G-09 `docs/01-wallet-setup.md`: "Currency Display - USD, EUR, BTC" replaced by the real display units (AMMO/mAMMO/uAMMO, `qt/bitcoinunits.cpp`); the wallet has no price feed.
  - G-10 `README.md`, `source/README.md`: "completely private" -> optional Sapling shielding, transparent by default, shield/unshield side visible, peers see your IP.
  - G-11 v1.1.0 white papers: banner now points to the 2nd Edition and withdraws every yield/return/investment/anonymous/DEX claim; "Annual Yield 8-12%", "Investment and Savings", "Anonymous Trading", "Yield Farming", "Staking yield stability" struck through inline with a withdrawal note; "Premine: 0% (completely fair launch)" corrected to the 250,000,000 AMMO block-1 reserve; "Fully private" Sapling claim corrected.
  - G-03 2nd Edition white paper: the Bitcoin "value of zero on its release" comparison (line 357) replaced by "AMMO has no assigned value, and the project makes no claim about what it is or will ever be worth"; line 305 no longer frames supply by what a bitcoin can "fetch"; line 423 "something worthwhile" -> "means something".
  - G-04 2nd Edition line 155: "Only what remains of the block-1 reserve after the airdrop funds the QuarterMaster reserve described in Section 12."
  - G-01 `source/src/validation.cpp` (comment only, no consensus change): block-1 output is `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u`; `AGkC8...` is only the unspendable genesis output.
  - G-07 (wording) `payment-gateway/PAYOUTS.md`, `src/app/api/payouts/route.ts`, `src/types/payout.ts`: the GLiBz flow is described as a swap of earned NUGGETS, not a "sale"; example key `glibz_swap:42`, memo "GLiBz earned Nuggets swap".
- **Not changed:** the GLiBz caller (`ammo_exchange.php` in the GLiBz repository) still uses the function name `_ammoExchangeSellNuggets`, the idempotency prefix `glibz_sell:` and the memo "GLiBz Nuggets sale". The prefix must not change for existing payout rows, or replays could double-send; the memo and function name should be renamed in the GLiBz repository (out of scope here). The gateway still cannot tell earned from purchased NUGGETS (by design; the gate stays on GLiBz). G-08 (explorer price/market-cap types and CoinMarketCap key) was not in this change and stays open.
- **Owner approval:** commit under owner identity; changes made at the owner's request in the 2026-10-17 session (relayed). No separate signed approval.

## AMMO-D-2026-10-17-09 Explorer carries no price, market-cap or market-data plumbing (fixes G-08)

- **Date:** 2026-10-17
- **Principles:** AMMO-P-03, AMMO-P-04, AMMO-P-08
- **Decision:** The block explorer shows on-chain data only. It has no price, market-cap, exchange-rate, fiat-value or return fields, no market-data API key, and no to-do to add one. Adding any of these is a P-03 red flag (REVIEW_CHECKLIST B) and needs a new decision entry.
- **Audit (2026-10-17):** searched for `price`, `market cap`, `USD`, `coingecko`, `coinmarketcap`, `ticker`, `APR`, `ROI` (and APY, exchange rate, fiat) across every branch of `everquin/ammocoin_website` and the tracked tree of this repository outside `source/` (explorer, payment gateway, paper wallet, scripts).
  - **Website, all branches** (`compliance-docs`, `v1.1.1-site-accuracy`, `main`, `cross-promo-build`, `mobirise-backup`): no code that fetches, computes or displays an AMMO price, market cap, fiat value, ticker or ROI/APR. The only `fetch()` calls load `proposals/index.json` and the tier counters (`assets/js/tier-counts.js`). Matches are disclaimers ("publishes no price") and the GLiBz store pricing goods in dollars. Recorded in the website log as the same ID.
  - **Explorer (this repo):** `blockchain-explorer/src/types/blockchain.ts` had `NetworkStats.marketCap?` / `price?` and an unused `PriceData` interface (price, change24h, change7d, volume24h, marketCap); `.env.example`, `README.md` and `DEPLOYMENT_GUIDE.md` set `NEXT_PUBLIC_COINMARKETCAP_API_KEY`; `SECURITY_AUDIT_v1.1.0.md` listed "Add price data integration (CoinMarketCap API)" as a to-do. No component, API route or hook read any of it (nothing was displayed).
  - **Payment gateway, paper wallet, scripts:** no price code.
- **Change (this commit, branch `compliance-docs`):** removed the two `NetworkStats` fields and `PriceData` (replaced by a comment pointing here); removed the CoinMarketCap key from `.env.example`, `README.md`, `DEPLOYMENT_GUIDE.md`; withdrew the audit to-do and the `PriceData` mention in `SECURITY_AUDIT_v1.1.0.md`; README feature list states "No price data".
- **Not changed:** the `type?: 'exchange' | 'whale' | ...` address-label type (labels addresses, shows no price or listing). Release builds still come from `v1.1.1-pos-fork`: this change must be merged or cherry-picked there before the explorer is deployed.
- **Found outside the repository:** an uncommitted `woocommerce-plugin/` folder in a local working copy of this repository (not on any branch) has an "AMMO/USD Rate" setting ("How many USD one AMMO is worth") and converts order totals from USD to AMMO (`includes/class-wc-ammocoin-gateway.php`, `ammo_usd_rate`). That is a fiat-to-AMMO conversion and a stated AMMO price, forbidden by AMMO-P-03 and REVIEW_CHECKLIST B. It was not modified (not tracked). Recorded as G-14; it must not be committed, published or deployed in that form.
- **Owner approval:** change made at the owner's request in the 2026-10-17 session (relayed); commit under owner identity. No separate signed approval.

## AMMO-D-2026-10-17-10 Airdrop record: how the migration airdrop works, what is published, why it is not a sale

- **Date:** 2026-10-17
- **Principles:** AMMO-P-01, AMMO-P-02, AMMO-P-03, AMMO-P-06, AMMO-P-13
- **Decision:** [AIRDROPS.md](AIRDROPS.md) is the compliance record for the v1.0 -> v1.1 airdrop. It fixes: snapshot at v1.0 block 434,881; payout of exactly the snapshot balance to the same address from the block-1 reserve, airdrop first; watch-only build, offline signing, logged broadcast, per-address reconciliation; a `signmessage` claim (message names the destination) only for addresses the payout cannot reach or that were missed; and the list of records that must be published (snapshot file hash, payout txids, reconciliation CSV, claims list, reserve / hold-back / QuarterMaster / contributor addresses, the withdrawn disposal address and what it received, and a reserve reconciliation statement). It states why the airdrop is not a sale: no payment, no purchase, no solicitation, no promise of value, no raise.
- **Context:** D-2026-10-16-01 set the airdrop model but no document said what would be published, so "airdrop first" (P-06) could not be audited (G-06).
- **Enforcement / evidence:** `docs/compliance/AIRDROPS.md` (this commit). Snapshot file `docs/migration/data/v1.0-complete-balance-snapshot.json` (committed `d25c53d39`), SHA256 `9da3c0d1c4b703d713a4f00c543e3e0db8f53c0c846b49499e218e9d8acf751c` (to be confirmed as canonical). Tooling `scripts/migration/migration-prepare.py`, `migration-sign-offline.py`, `migration-broadcast.py`, `verify-migration.py`.
- **Not enforced in code:** the whole programme is off-chain. Every record in AIRDROPS.md section 4 marked **TO BE PUBLISHED** is still missing.
- **Inconsistencies found (to fix before payout):** the snapshot file records `supply_match: false` (232,397,748.45021523 vs expected 232,439,448.45021522 AMMO, 41,700 AMMO apart); `scripts/migration/verify-claim.py` still calls the signed-message claim deprecated and the disposal model current (reverse of D-2026-10-16-01); `migration-prepare.py` usage refers to a `genesis-top-holders.json` from the earlier "Option 2.5" plan; the user guide's claim message names no destination. Tracked as G-15.
- **Owner approval:** written at the owner's request in the 2026-10-17 session (relayed); commit under owner identity. The published values need the owner's own commit.

## AMMO-D-2026-10-18-11 No AMMO/USD rate anywhere; the WooCommerce gateway is retired (fixes G-14)

- **Date:** 2026-10-18
- **Principles:** AMMO-P-02, AMMO-P-03, AMMO-P-09, AMMO-P-14
- **Decision:** nothing in the ecosystem states, stores or uses an AMMO/USD rate. Shop items are priced in USD only. AMMO stays an earned reward, never a currency with a quoted value. The local `woocommerce-plugin/` draft (a gateway that converts USD order totals to AMMO at a configured "AMMO/USD Rate") is retired: it must not be committed, published or installed, and it is not redesigned.
- **Context:** shop.glibz.com runs on Shopify; the WooCommerce gateway was never deployed. On GLiBz the same idea existed as `glibz_ammo_usd_rate` (AMMO shop prices derived from USD); the closed-loop release (glibz `release-plus-closed-loop`) already retires it, stops reading it in `shop_sync.php` and resets USD-derived AMMO prices to 0.
- **Enforcement / evidence:** `woocommerce-plugin/RETIRED.md` marks the local folder (it was never in git). GLiBz: `shop_sync.php` and `activate_closed_loop.php` on `release-plus-closed-loop` (f58240c93); live once the closed loop is deployed and activated.
- **Not enforced until then:** live glibz.com `shop_sync.php` still reads `glibz_ammo_usd_rate` if an admin sets it.
- **Owner approval:** owner chose "Remove the rate" in the 2026-10-18 session. **Prepared by:** Claude.

## AMMO-D-2026-10-18-12 Early contributors fund the QuarterMaster reserve by signed pledges; zerocoin 41,700 set aside

- **Date:** 2026-10-18
- **Principles:** AMMO-P-02, AMMO-P-06, AMMO-P-07, AMMO-P-13, AMMO-P-14
- **Decision:** the 61 largest v1.0 snapshot addresses belong to individuals who helped start AMMOcoin and ran nodes and masternodes; by their consensus they fund the QuarterMaster reserve. Each pledges the same share (33.121679%) of their snapshot balance; their airdrop is paid minus the pledge, and the pledged AMMO stays in the block-1 reserve (no donations sent after the fact). Total pledged 72,439,448.45021523 AMMO, so the reserve keeps exactly 90,000,000 for the 40M tiers + 50M contributor reserve, plus 41,700 set aside for unclaimable zerocoin. The v1.0 network is not needed: v1.0 and v1.1.1 share address, key and message-signing formats, and the snapshot is fixed.
- **Why:** the published "funded from what remains of the block-1 reserve after the airdrop" was arithmetically impossible (17.6M left vs 90M). Pledges make it true and checkable. A smaller airdrop instead of after-the-fact donations means no follow-through risk.
- **Safeguards:** each holder signs their own pledge (`signmessage`); no wallet or key is collected or used on anyone's behalf (a third-party signature would not prove consent and would put most of the supply under one person's control). Pledges are voluntary with nothing in return. No payout until all 61 are signed; anyone who does not sign is paid in full and the list is rebuilt. The 94.1% concentration among these holders is disclosed in AIRDROPS.md.
- **Enforcement / evidence:** `scripts/migration/build-pledges.py` (deterministic, refuses a snapshot with a different SHA256), `docs/migration/data/quartermaster-pledges.csv`, `scripts/migration/verify-pledges.py`, `docs/migration/PLEDGE_GUIDE.md`, AIRDROPS.md section 1.
- **Not enforced yet:** `migration-prepare.py` still pays full snapshot balances; signatures not collected; reserve addresses not published (G-06). Public copy saying "funded from what remains after the airdrop" must add "and the early contributors' pledges" before launch.
- **Owner approval:** owner, 2026-10-18 session ("all wallets on list are OURS … willing and agreed to donate percentages"; pro-rata; include the zerocoin set-aside). **Prepared by:** Claude.

## AMMO-D-2026-10-18-13 Payout cap kept; oversize balance split; one reserve UTXO per batch

- **Date:** 2026-10-18
- **Principles:** AMMO-P-13 (safety in migrations and distributions)
- **Decision:** the 10,000,000 AMMO per-recipient safety cap in `migration-prepare.py` stays. A balance above it (only `ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL`, 24,713,345.21078793 after its pledge) is paid in outputs of at most 10M, each in its own transaction, exact to the satoshi.
- **Also fixed:** every payout batch used to select the same reserve UTXO, so only the first transaction could confirm. The payout now starts with a fan-out transaction (one UTXO per batch, operator-owned addresses) and each batch spends a distinct UTXO.
- **Enforcement / evidence:** `scripts/migration/migration-prepare.py` (`split_oversize`, `plan_chunks`, `build_fanout`, `build_batches`), `scripts/migration/test_migration_prepare.py`.
- **Owner approval:** owner chose "Split into ≤10M outputs" in the 2026-10-18 session. **Prepared by:** Claude.

## AMMO-D-2026-10-24-02 Launch wording on `main`: no reward amounts, no earn/buy wording, Proudly Worthless™ in the user docs

- **Date:** 2026-10-24 (branch `docs-compliance-main`, PR into `main`)
- **Principles:** AMMO-P-01, P-02, P-03, P-04, P-08, P-09, P-12
- **Shared ID / follows:** website AMMO-D-2026-10-23-01 (launch wording sweep) and AMMO-D-2026-10-23-02 (Proudly Worthless™ brand line); AMMO-D-2026-10-24-01 (AMMO.capital removed).
- **Context:** `main` is the default branch that visitors and the launch posts land on (a scheduled 2026-11-13 post links `blob/main/docs/02-staking-guide.md`). The launch-wording PRs #3 (release notes) and #4 (white paper) were merged into `v1.1.1-pos-fork` only, so `main` still showed per-block reward amounts (250/247/3/6 AMMO), daily and per-cycle AMMO totals, "earn" wording, "Where can I buy AMMOcoin?", "investments", "Buy more AMMO", "(upcoming)"/"not released yet" banners and stale unofficial channels.
- **Decision:** the user documentation on `main` follows the website launch wording. It states no reward or payment amounts, no daily/per-cycle AMMO totals and no hosting prices; it uses no affirmative "earn", "buy", "purchase", "invest", "income", "value" or "price" wording; it carries no "yet", "for now", "early" or "be there first" framing. Staking and masternodes are described as running the network with your crew: making blocks, the masternode payment queue, governance votes and the treasury, with the amounts left to the code (`GetBlockValue()`, `GetMasternodePayment()`, `nMNBlockReward`, `nNewMNBlockReward`, `GetTotalBudget()`). Protocol parameters stay as numbers (10,000 AMMO collateral, 600 confirmations, 43,200-block cycle, fork height 2,776, ports, proposal fee, vote thresholds). This is stricter than AMMO-P-04 ("rewards in code terms") for user docs; P-04 is not changed. P-08 drops its AMMO.capital sentence (per D-2026-10-24-01). Required negations stay ("no ICO", "sells nothing", "publishes no price", not-an-offer notes).
- **Changes:**
  - White paper 2nd Edition: brought to the `v1.1.1-pos-fork` text (PR #4, `a1544fe31`, plus `b77a081dc`): no reward table or amounts, rev. 2026/10/23. In addition "Early Birds" ("the only edge is being there first") becomes "First Operators" (no edge in arriving first), and the pledge share is referenced to `docs/migration/data/quartermaster-pledges.csv` instead of a percentage.
  - Release notes v1.1.1: subsidy, masternode-payment and treasury rows from PR #3 (`7b13f0a1a`) applied; relative doc links kept so they resolve to the cleaned `main` docs; macOS check uses `--ignore-missing` against the all-platforms checksums file.
  - `README.md`: technical spec names `GetBlockValue()` instead of amounts; "Staking Rewards" feature line rewritten; "Additional exchange listings" and "Decentralized exchange (DEX)" roadmap items removed and replaced by the masternode-vote rule; v1.1.1 shown as released (2026-10-21).
  - `docs/10-faq.md`: "Where can I buy AMMOcoin?" -> "Can I get AMMO?" (the project sells nothing; airdrop, staking, masternodes, contributions, NUGGETS from activity); "How much can I earn from staking?" -> "What does a staked block pay?" (code terms only); minimum-for-rewards amounts, "~120,000 AMMO/day", "~1,440 AMMO/day", "3 AMMO" and hosting prices removed; "Value Questions" -> "Proudly Worthless™"; Discord/Telegram/Reddit/forum and `@AMMOcoinOfficial` replaced by ammocoin.org, x.com/ammocoin and GitHub, with the note that AMMOcoin has no official Discord or Telegram.
  - `docs/02-staking-guide.md`: reward table, "Earn block rewards", "247 AMMO" removed; "Transaction fees also go to the staker" corrected to the code (PoS blocks destroy fees, `source/src/validation.cpp`); "Track fair market value" removed from the tax section.
  - `docs/03-masternode-setup.md`: "Masternode Rewards", "Reward Calculation", "14.4 AMMO/day", "Active and earning", "earning rewards", "Purchase ... to accumulate", VPS prices and the unofficial Discord/Telegram/forum removed; payment queue described in code terms.
  - `docs/01`, `04`, `05`, `06`, `08`, `09`: "earn rewards", "investments", "Buy more AMMO", "Exchange Listings" success story, the treasury "2,160,000 AMMO" figure and "Vote Early" reworded; `06` budget described by `GetTotalBudget()`.
  - `docs/protocols/AMMO-AUTH-v1.md`: the "Price feed integration: item valuation in AMMO" future extension withdrawn (P-03).
  - Release status: "(upcoming)" / "not released yet" banners updated in `README.md`, `SEED_NODE_DEPLOYMENT.md`, `docs/README.md`, `docs/01`-`09`, `docs/migration/V1.0_BALANCE_AIRDROP.md`, `docs/operations/*` and the superseded-banner lines of the v1.1.0 release notes.
- **Not changed (historical or required):** `docs/compliance/*` (negations and history); superseded v1.1.0 white papers and v1.1.0 release notes bodies (archived, banners already withdraw their claims); `V1.1.0_GENESIS_BLOCK_AUTHORITY.md` (genesis code record); `docs/migration/PLEDGE_GUIDE.md` (signers need the exact pledge share); `docs/migration/DISPOSAL_ADDRESS.md`, `MANUAL_MIGRATION_PLAN_v1.0_to_v1.1.0.md`, `SIDE_BY_SIDE_OPERATION_GUIDE.md` (superseded v1.0/v1.1.0 migration records); `payment-gateway/PAYOUTS.md` ("earned NUGGETS" is the gate the code relies on); `docs/RELEASE_CHECKLIST_1.1.1.md` (internal checklist); RPC names such as `getnewexchangeaddress`; the white paper heading "Initial Valuation: No ICO, No Exchanges, The Closed Loop" (named by PRINCIPLES.md) and its "Coming to GLiBz" line (flip at GLiBz activation). Source code was not touched; no consensus fact changed.
- **Owner approval:** requested by the owner in the 2026-10-24 launch-review session (relayed); approval is the merge of the PR into `main`. **Prepared by:** Claude.

## AMMO-D-2026-10-24-03 Project-run masternodes for network health; they abstain from listing votes

- **Date:** 2026-10-24
- **Principles:** AMMO-P-08 (listings only by masternode vote), AMMO-P-02 (never sold)
- **Context:** On 2026-10-23 and 2026-10-24 the nodes split by banning each other as "misbehaving". With no masternodes on the network, each node resets its masternode sync after every pass (`source/src/masternode-sync.cpp`, `mnodeman.CountEnabled(true) <= 1` -> `Reset()`), about every 2 minutes. Each restart repeats `mnget` (+20, `masternode-payments.cpp:424`) and `mnvs` (+10, `budget/budgetmanager.cpp`) to peers that already answered, so long-lived connections reach the ban score of 100. Blocks were never rejected.
- **Decision:** The project runs three legacy masternodes on its own Vultr nodes (ammo-03, ammo-05, ammo-08). The collateral comes from project-held AMMO already on chain. Nothing is sold or bought, and no outside party funds them. Until at least as many independent masternodes are enabled as project ones, the project masternodes **abstain from every exchange-listing vote**. A listing therefore needs independent operators, as P-08 intends. They may vote on other proposals. Each such vote is recorded here, with the proposal hash.
- **Also:** our nodes whitelist each other (`whitelist=` in `ammocoin.conf`; whitelisted peers are not banned, `net_processing.cpp:2243`). A code fix for the reset loop is tracked as a separate decision if a v1.1.2 is cut.
- **Wording:** public copy may say the project runs masternodes to keep the network healthy. It states no payment amounts (D-2026-10-24-02).
- **Enforcement / evidence:** governance commitment, not code. The masternode collateral outputs and IPs are to be listed here once they are confirmed.
- **Owner approval:** the owner asked for masternodes on the spare Vultr nodes on 2026-10-24 ("run a few masternodes … through those"). The abstention rule is **proposed by Claude, pending owner approval** (approval is the merge).

## AMMO-D-2026-10-24-04 Purpose wallets: one labelled, published pool per purpose; no random splitting

- **Date:** 2026-10-24
- **Principles:** AMMO-P-02, P-06, P-07, P-13
- **Context:** before funding the reserves and the masternode collateral, the owner asked whether to split the project's AMMO across about 100 randomly funded v1.1.1 wallets and draw on them as needed. A read of the chain on 2026-10-24 showed the block-1 reserve already cold-staked: 4,996 x 50,000 AMMO, coin owner `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` (paper wallet), staker ammo-02, plus 200,245 AMMO of change in five addresses.
- **Decision:** project AMMO is held in a small set of named pools, each with its addresses published in [RESERVES.md](RESERVES.md):
  1. block-1 reserve;
  2. v1.0 airdrop (paid to holders) plus its claim hold-back;
  3. QuarterMaster tiers, 40,000,000;
  4. contributor reserve, 50,000,000;
  5. zerocoin set-aside, 41,700;
  6. masternode collateral;
  7. a capped GLiBz payout float.

  A pool may hold many outputs for staking and batching (D-2026-10-18-13). Every movement between pools is logged in RESERVES.md section 4 within 7 days. Large pools stay cold (offline owner key, cold-staking delegation). Airdrop first (P-06) still applies.
- **Alternatives rejected:** about 100 randomly funded wallets. They would make one project holding look like many independent holders, which misleads anyone reading the chain. They would also leave the reserves unauditable (G-06), and they multiply the backups, passphrases and files that can be lost or leaked.
- **Open:** the funding source for pool 6 (masternode collateral) and pool 7 (GLiBz float). Taking either from pools 3–5 changes the published amounts, so it needs its own decision. Using the change addresses of pool 1 or the PoW mining rewards needs a recorded row in section 4.
- **Enforcement / evidence:** [RESERVES.md](RESERVES.md) (chain data read from ammo-02 at height ~3556); owner's private ledger `LEDGER.md` on the encrypted wallets volume (no secrets). Not enforced in code.
- **Owner approval:** owner asked for this draft on 2026-10-24 ("draft the purpose-wallet decision and reserve page"); approval is the merge. **Prepared by:** Claude.

## AMMO-D-2026-10-24-05 Five project masternodes and backup reserve stakers (extends D-2026-10-24-03); project rewards listed as pool 8

- **Date:** 2026-10-24
- **Principles:** AMMO-P-08, P-13
- **Context:** the owner asked that the three masternodes not be the only always-on project nodes ("they can't be the only ones always running"). They chose more always-on stakers, more project masternodes, and room for independent operators.
- **Decision:**
  - **Two more project masternodes,** mn4 on ammo-04 (45.76.240.109) and mn5 on ammo-07 (217.69.14.126). Both servers moved from the October lab node to the official v1.1.1 release (`install-node.sh`, tarball SHA-256 `de51b2c2…`). Collateral is tx `c27deb8b…` (vouts 0–1), from pool 1 change. The listing-vote abstention of D-2026-10-24-03 covers all five.
  - **Backup stakers:** ammo-09 (`SXezXcWrmkTNyQ6L7pL9XgxfX71HbmwkVT`) and ammo-12 (`Sgs5kVjmEbgV9wSbwmCyiJNQtG7taN4Qrs`) accept cold-stake delegations owned by the paper wallet `AGkC8…`, as ammo-02 does. Moving part of pool 1's delegation to them needs the paper-wallet key and is a separate owner step. Until then ammo-02 remains the only staker of pool 1.
  - **All eight project servers whitelist each other** (see D-2026-10-24-03).
  - **Pool 8:** the project's own block rewards in the VM controller wallet, about 990,645 AMMO on 2026-10-24, are listed in RESERVES.md as pool 8, so that all project AMMO is in a named pool (D-2026-10-24-04).
- **Enforcement / evidence:** RESERVES.md pools 6 and 8 and section 4; owner's LEDGER.md.
- **Owner approval:** owner choices in the 2026-10-24 session; approval is the merge. **Prepared by:** Claude.

## AMMO-D-2026-10-25-01 Pledges held in custody, and a reply deadline (refines D-2026-10-18-12)

- **Date:** 2026-10-25
- **Principles:** AMMO-P-06, P-13, P-14
- **Context:** The 61 pledge addresses fall into three groups: addresses the owner holds for himself, addresses whose keys he holds for other people, and addresses outside his control whose holders he can contact. D-2026-10-18-12 says each holder signs their own pledge, and no payout goes out until all 61 have signed. A signature proves who holds the key, not who agreed. And waiting for every outside holder could push the airdrop past the Nov 5 launch.
- **Decision:**
  1. **Own addresses:** the owner signs.
  2. **Keys held for someone else:** the person the coins belong to agrees in writing first (email or message). The consent is kept privately in the owner's pledge tracker, then the owner signs with the key he holds. The public record gives the number of pledges signed by the project as custodian with the holder's written consent, and their total.
  3. **Outside holders:** each is asked with the published signing request. Nobody is asked for keys, wallet files or coins.
  4. **Deadline:** replies close on **November 1, 2026**. Any pledge address not signed by then, or declined, is paid its **full** snapshot balance (`build-payout-holders.py --full-pay`). The resulting shortfall in the QuarterMaster reserve is published with the airdrop record. Unsigned holders are never paid less.
- **Alternatives rejected:**
  - the custodian signing without consent, which would not prove agreement;
  - handing every held key back first, which is slow and hands over wallet control;
  - waiting for every reply, which would make the airdrop date depend on the slowest holder.
- **Enforcement / evidence:** `scripts/migration/build-payout-holders.py` (`--full-pay`: refuses unknown addresses, refuses an address that is both signed and full-pay, and recomputes the expected total = 159,958,300 + the pledges paid in full); signing request text (owner's files); `verify-pledges.py`.
- **Owner approval:** owner chose "their consent, you sign" and "deadline, then full pay" in the 2026-10-25 session. **Prepared by:** Claude.

---

## Known gaps (code or copy that contradicts a principle, or a decision without enforcement)

Open until fixed; record the fixing commit in the Status column.

| ID | Where | Problem | Principle | Status |
|---|---|---|---|---|
| G-01 | `source/src/validation.cpp:849` | Comment says the premine goes to `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`; the real block-1 address is `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u` (7b61ba5b5). | P-05 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-02 | `docs/02-staking-guide.md:3,15,18,21,227,294,335-345,366` | "Earn passive income", "Passive Income - Earn rewards while you sleep", "Compound Growth - Reinvest", "Annual Percentage Yield", "Annual Return ~17%", "Portfolio Allocation", "earning passive income". | P-04 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-02b | `docs/03-masternode-setup.md:485-505` | "Economics & ROI Analysis", "Investment Breakdown", "Initial Investment", "ROI Optimization", "Compound rewards by reinvesting", "Price Volatility - AMMO value fluctuation". | P-03, P-04 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-02c | `README.md:63`, `source/README.md:39` | "Staking Rewards: Passive income for network participants". | P-04 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-02d | `docs/10-faq.md:84,354-366` | "Investment Questions", "Is AMMOcoin a good investment?" answered with reasons to buy; "What factors affect AMMOcoin's price? Adoption: More users = higher demand". | P-03, P-04 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-03 | White paper 2nd Ed. line 357 (and website `whitepaper.html:1012`) | "AMMO has no intrinsic value as of right now. But, then again, Bitcoin had a value of zero on its release." implies expected appreciation. Line 305 frames supply in terms of what a bitcoin can "fetch". | P-03 | Fixed in `be2c0aad6` (D-2026-10-17-08); website copy `website 59883d1` |
| G-04 | White paper 2nd Ed. line 155 | Sentence fragment: "Only what remains of the block-1 reserve after it funds the QuarterMaster reserve described in Section 12." The airdrop-first rule should read unambiguously. | P-06 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-05 | `docs/10-faq.md:20-24` | "Where can I buy AMMOcoin? Exchanges: Check CoinMarketCap for current listings; DEX Trading; OTC Trading" contradicts "not on any exchange". | P-02, P-08 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-06 | (missing) | No published QuarterMaster reserve addresses or airdrop distribution record (txids reconciled against the snapshot), so "airdrop first" and tier allocations cannot be audited on-chain. | P-06, P-07 | Open: what must be published is now defined in `AIRDROPS.md` (D-2026-10-17-10); values still TO BE PUBLISHED. Pool addresses and the block-1 reserve's current outputs are in `RESERVES.md` (D-2026-10-24-04); pools 2–7 still TO BE CREATED |
| G-07 | `payment-gateway/PAYOUTS.md:4,18,19,63`, `payment-gateway/src/app/api/payouts/route.ts:4`, `payment-gateway/src/types/payout.ts:5` | Describes the GLiBz swap as "sell Nuggets for AMMO", memo "GLiBz Nuggets sale", key `glibz_sell:`. Wording frames AMMO as being sold. The gateway cannot tell earned from purchased NUGGETS; the earned-only gate lives on GLiBz only. | P-02, P-09 | Wording fixed in `be2c0aad6` (D-2026-10-17-08); GLiBz-side memo/function name still say "sell"/"sale" (GLiBz repo); gate by design |
| G-08 | `blockchain-explorer/src/types/blockchain.ts:100-101,160-166`; `blockchain-explorer/README.md:182`, `DEPLOYMENT_GUIDE.md:161`, `SECURITY_AUDIT_v1.1.0.md:390` | `price`, `marketCap`, `PriceData` types and a CoinMarketCap API key / "Add price data integration" to-do. No UI use found, but the plumbing for a price display exists. | P-03, P-08 | Fixed on `compliance-docs` (AMMO-D-2026-10-17-09); merge to `v1.1.1-pos-fork` pending |
| G-09 | `docs/01-wallet-setup.md:180` | "Currency Display - USD, EUR, BTC equivalent" setting described. | P-03 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-10 | `README.md:51` | "Zero-knowledge proofs for completely private transactions" overstates privacy (shielding is optional; transparent by default). | P-10 | Fixed in `be2c0aad6` (D-2026-10-17-08) |
| G-11 | `docs/whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md:345,616,644-653` | "Annual Yield 8-12%", "Investment and Savings", "Anonymous Trading", "Yield Farming". Marked superseded (5e2a9e2c8) but still in the tree. | P-04, P-10 | Mitigated: superseded banner and inline strike-through (`be2c0aad6`, D-2026-10-17-08); consider moving to an archive folder |
| G-12 | (process) | "No deploy without review" (D-2026-10-17-05) has no technical enforcement verified (branch protection, required reviewers). | P-15 | Open, UNVERIFIED |
| G-13 | `docs/migration/MANUAL_MIGRATION_PLAN_v1.0_to_v1.1.0.md:306` | Still describes a 90-day migration period closing 2026-04-03 (superseded banner present). | P-13 | Mitigated (superseded) |
| G-14 | `woocommerce-plugin/includes/class-wc-ammocoin-gateway.php` (uncommitted local folder, not on any branch) | "AMMO/USD Rate" setting ("How many USD one AMMO is worth") converts USD order totals to AMMO: a stated AMMO price and fiat-to-AMMO conversion. | P-03, P-02 | Decided D-2026-10-18-11: plugin retired, never committed or installed; GLiBz rate retired by the closed-loop release |
| G-15 | `docs/migration/data/v1.0-complete-balance-snapshot.json` (`supply_match: false`), `scripts/migration/verify-claim.py:3-16`, `scripts/migration/migration-prepare.py:21-24`, `docs/migration/V1.0_BALANCE_AIRDROP.md` | Snapshot total does not match its expected supply (41,700 AMMO); claim tool and prepare script still follow withdrawn models; user-guide claim message names no destination. | P-06, P-13 | Open (see `AIRDROPS.md` section 6) |
