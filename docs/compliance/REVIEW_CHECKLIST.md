# Compliance review checklist (pre-merge)

Run this for **any** change that touches: issuance, block rewards, masternode payments, the treasury/budget, chain parameters, the block-1 / QuarterMaster / contributor reserves, the structured-release tiers, the payment gateway, the explorer, prices or currency display, exchanges, NUGGETS, privacy features or claims, release notes, white papers, READMEs, guides, FAQs, or any public or promotional copy.

Answer every question. A "yes" to a red-flag question blocks the merge until it is fixed, or until a new entry in [DECISIONS.md](DECISIONS.md) records an owner-approved exception (and, while counsel review is pending, the exception says so). Principle IDs refer to [PRINCIPLES.md](PRINCIPLES.md).

## A. Sale and pay-to-play (red flags)

- [ ] Does this create **any path from cash, card, other crypto or goods to AMMO** provided by the project, directly or through a third party? (P-01, P-02, P-14)
- [ ] Does it let anyone **buy** a tier position, masternode, "package", "bundle", "boost", "membership" or priority that leads to AMMO? (P-07, P-14)
- [ ] Does it let **purchased NUGGETS** (bought with cash or AMMO) reach AMMO or a tier position? (P-09)
- [ ] Does it sell, or prepare to sell, reserve AMMO, or buy AMMO back? (P-02)
- [ ] Does it ask anyone to send coins, keys, seed phrases or wallet files? (P-13)

## B. Price and value (red flags)

- [ ] Does it **publish, display, fetch or compute a price**, market cap, exchange rate or fiat equivalent for AMMO? (P-03)
- [ ] Is any **AMMO amount derived from a fiat amount** (USD/EUR to AMMO)? (P-03, P-09)
- [ ] Does copy **imply value or appreciation** (Bitcoin comparisons, scarcity, "early", "before it pumps", "moon", "worth")? (P-03)
- [ ] Does it quote a fixed NUGGETS-to-AMMO ratio? (P-09)

## C. Returns (red flags)

- [ ] Does code or copy use **ROI, APR, APY, yield, annual return, passive income, profit, compound growth, investment, guaranteed**, or a percentage return? (P-04)
- [ ] Are rewards described in anything other than **code terms** (AMMO per block, to whom, dependent on network participation and uptime)? (P-04)
- [ ] Are earnings shown in fiat? (P-03, P-04)

## D. Issuance and consensus

- [ ] Does this change `GetBlockValue`, `GetMasternodePayment`, `GetTotalBudget`, `nRewardZCV2Height`, `nRewardV55Height`, `nBudgetCycleBlocks`, `nMNCollateralAmt`, `nMNBlockReward`, `nNewMNBlockReward`, `nMaxMoneyOut` or the block-1 reserve? If yes: is it announced as a consensus change in the release notes, are the white paper, website and app updated to match, and is there a DECISIONS entry? (P-05)
- [ ] Do the tests (`source/src/test/budget_tests.cpp`, app `test/network_constants_test.dart`) still pass and match the documented schedule? (P-05)
- [ ] Does the airdrop-first order still hold for any reserve movement? (P-06)

## E. Exchanges and governance

- [ ] Does it add an exchange, swap-to-fiat, on-ramp, off-ramp, DEX, listing link, "where to buy" text or CoinMarketCap/CoinGecko integration? Only allowed after a recorded DAO Command (masternode) vote. (P-08)

## F. Privacy and legality

- [ ] Does copy say "anonymous", "untraceable" or "completely private", or omit the limits of shielding? (P-10)
- [ ] Is privacy promoted as a way around tax, reporting, sanctions or law enforcement? Is the tax footnote present where privacy is promoted at length? (P-11)
- [ ] Do programme pages carry "not an offer, not investment advice, no promise of return" and the jurisdiction note? (P-12, P-07)

## G. Substance over wording

- [ ] Could this change achieve something forbidden above by renaming it or routing it elsewhere? (P-14)
- [ ] Is a new economic decision being made? If so, is there a new [DECISIONS.md](DECISIONS.md) entry with enforcement file:line and owner approval? (P-15)
- [ ] Does it introduce code or copy that contradicts a principle without adding it to the *Known gaps* table? (P-15)

## H. Sign-off

- [ ] Reviewed by someone other than the author.
- [ ] If it changes issuance, the reserve, tiers, the gateway or any value-related copy: owner approval recorded (PR approval or `Approved-by:` line). Counsel review: pending / done (state which).
