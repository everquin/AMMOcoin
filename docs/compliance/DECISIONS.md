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

---

## Known gaps (code or copy that contradicts a principle, or a decision without enforcement)

Open until fixed; record the fixing commit in the Status column.

| ID | Where | Problem | Principle | Status |
|---|---|---|---|---|
| G-01 | `source/src/validation.cpp:849` | Comment says the premine goes to `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`; the real block-1 address is `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u` (7b61ba5b5). | P-05 | Open |
| G-02 | `docs/02-staking-guide.md:3,15,18,21,227,294,335-345,366` | "Earn passive income", "Passive Income - Earn rewards while you sleep", "Compound Growth - Reinvest", "Annual Percentage Yield", "Annual Return ~17%", "Portfolio Allocation", "earning passive income". | P-04 | Open |
| G-02b | `docs/03-masternode-setup.md:485-505` | "Economics & ROI Analysis", "Investment Breakdown", "Initial Investment", "ROI Optimization", "Compound rewards by reinvesting", "Price Volatility - AMMO value fluctuation". | P-03, P-04 | Open |
| G-02c | `README.md:63`, `source/README.md:39` | "Staking Rewards: Passive income for network participants". | P-04 | Open |
| G-02d | `docs/10-faq.md:84,354-366` | "Investment Questions", "Is AMMOcoin a good investment?" answered with reasons to buy; "What factors affect AMMOcoin's price? Adoption: More users = higher demand". | P-03, P-04 | Open |
| G-03 | White paper 2nd Ed. line 357 (and website `whitepaper.html:1012`) | "AMMO has no intrinsic value as of right now. But, then again, Bitcoin had a value of zero on its release." implies expected appreciation. Line 305 frames supply in terms of what a bitcoin can "fetch". | P-03 | Open |
| G-04 | White paper 2nd Ed. line 155 | Sentence fragment: "Only what remains of the block-1 reserve after it funds the QuarterMaster reserve described in Section 12." The airdrop-first rule should read unambiguously. | P-06 | Open |
| G-05 | `docs/10-faq.md:20-24` | "Where can I buy AMMOcoin? Exchanges: Check CoinMarketCap for current listings; DEX Trading; OTC Trading" contradicts "not on any exchange". | P-02, P-08 | Open |
| G-06 | (missing) | No published QuarterMaster reserve addresses or airdrop distribution record (txids reconciled against the snapshot), so "airdrop first" and tier allocations cannot be audited on-chain. | P-06, P-07 | Open |
| G-07 | `payment-gateway/PAYOUTS.md:4,18,19,63`, `payment-gateway/src/app/api/payouts/route.ts:4`, `payment-gateway/src/types/payout.ts:5` | Describes the GLiBz swap as "sell Nuggets for AMMO", memo "GLiBz Nuggets sale", key `glibz_sell:`. Wording frames AMMO as being sold. The gateway cannot tell earned from purchased NUGGETS; the earned-only gate lives on GLiBz only. | P-02, P-09 | Open (wording); by design (gate) |
| G-08 | `blockchain-explorer/src/types/blockchain.ts:100-101,160-166`; `blockchain-explorer/README.md:182`, `DEPLOYMENT_GUIDE.md:161`, `SECURITY_AUDIT_v1.1.0.md:390` | `price`, `marketCap`, `PriceData` types and a CoinMarketCap API key / "Add price data integration" to-do. No UI use found, but the plumbing for a price display exists. | P-03, P-08 | Open |
| G-09 | `docs/01-wallet-setup.md:180` | "Currency Display - USD, EUR, BTC equivalent" setting described. | P-03 | Open |
| G-10 | `README.md:51` | "Zero-knowledge proofs for completely private transactions" overstates privacy (shielding is optional; transparent by default). | P-10 | Open |
| G-11 | `docs/whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md:345,616,644-653` | "Annual Yield 8-12%", "Investment and Savings", "Anonymous Trading", "Yield Farming". Marked superseded (5e2a9e2c8) but still in the tree. | P-04, P-10 | Mitigated (superseded banner); consider moving to an archive folder |
| G-12 | (process) | "No deploy without review" (D-2026-10-17-05) has no technical enforcement verified (branch protection, required reviewers). | P-15 | Open, UNVERIFIED |
| G-13 | `docs/migration/MANUAL_MIGRATION_PLAN_v1.0_to_v1.1.0.md:306` | Still describes a 90-day migration period closing 2026-04-03 (superseded banner present). | P-13 | Mitigated (superseded) |
