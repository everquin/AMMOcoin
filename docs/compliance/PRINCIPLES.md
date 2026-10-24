# AMMOcoin binding principles (canonical)

These principles apply to all AMMOcoin code, releases, documentation, the website, the wallet app and any promotion made by or for the AMMOcoin project. The IDs are stable and shared by the three AMMOcoin repositories (`everquin/AMMOcoin`, `everquin/ammocoin_website`, `everquin/AMMOcoin_App`). Do not renumber; retire an ID by superseding it in [DECISIONS.md](DECISIONS.md).

Not legal advice. Counsel review status: **pending** (see [README.md](README.md)).

The public statement of most of these principles is Section 11 ("Initial Valuation: No ICO, No Exchanges, The Closed Loop") of the 2nd Edition white paper, `docs/whitepapers/AMMOcoin_Whitepaper_2ndEdition_v1.1.1.md`.

---

## AMMO-P-01 No ICO, no pre-sale, no token sale

There has never been and will never be an Initial Coin Offering, pre-sale, private sale, SAFT, "whitelist" or any other sale of AMMO by the project. AMMO is not offered to raise money, and no one is asked to send money, coins or anything of value to the project to receive AMMO.

## AMMO-P-02 The project never sells AMMO for money and never buys it back

No reserve AMMO (block-1 reserve, QuarterMaster reserve, contributor reserve) is ever sold for cash, card, bank transfer, other cryptocurrency, gift cards or goods. The project does not buy AMMO back, run buy-backs, burns-for-price or market-making, or promise liquidity.

## AMMO-P-03 No price, no valuation: "ZERO. ZILCH. ZIP. NADA."

The project assigns AMMO no value and publishes no price, target, floor, exchange rate to any money, "market cap" or valuation. No AMMO amount is ever derived from a fiat amount by the project (no USD-to-AMMO conversion in code, copy or tools). Copy must not suggest that AMMO will or may gain value, including by comparison with Bitcoin or other assets.

## AMMO-P-04 No ROI, yield or profit promises; rewards in code terms only

Rewards are described only in the terms the code uses: how many AMMO a block pays and to whom (`GetBlockValue()`, `GetMasternodePayment()`, `GetTotalBudget()`), plus the plain fact that what one person receives depends on how many others stake or run masternodes and on keeping a node online. No "ROI", "APR", "APY", "annual return", "yield", "passive income", "profit", "earn while you sleep", "compound growth", "guaranteed" or "get in early" language, no percentage-return figures, and no fiat-denominated earnings estimates.

## AMMO-P-05 Issuance is set by the code, and the documents follow the code

The block reward schedule, masternode payment, treasury budget and block-1 reserve are consensus rules in `source/src/validation.cpp` and `source/src/chainparams.cpp`. Any change to them is a consensus change, must be announced as such, and must not be hidden inside another change. Where any document disagrees with the code, the code wins and the document is corrected.

## AMMO-P-06 Block-1 reserve: v1.0 airdrop first

The 250,000,000 AMMO block-1 reserve exists to airdrop v1.0 balances (snapshot at v1.0 block 434,881) to the same addresses. The airdrop is paid first. The QuarterMaster reserve is funded from the block-1 reserve after the v1.0 airdrop, together with voluntary pledges from the early contributors who hold the largest v1.0 balances. v1.0 holders are never asked to send coins, keys, wallet files or email registrations to receive the airdrop.

## AMMO-P-07 Structured-release tier positions are earned or awarded, never sold

FOUNDING-50, SPARTAN-300 and PATRIOT-2000 positions (40,000,000 AMMO, 2,350 positions, held by the QuarterMaster reserve) and the 50,000,000 AMMO AMMOgeek/AMMOfreak contributor reserve are an **off-chain distribution programme**, not a consensus rule. Positions are earned (with *earned* GLiBz NUGGETS) or awarded directly; they are never sold. Cash, card, AMMO purchases and *purchased* NUGGETS can never be used toward a position. Rank and account-age requirements apply; availability may be limited by jurisdiction; full terms are published on GLiBz. Masternodes are not sold as packages.

## AMMO-P-08 Exchange listings only through a masternode governance vote

The project does not list or seek to list AMMO on any exchange, and does not operate one, except through explicit approval in DAO Command (masternode vote). The project runs no exchange and seeks no listing. No wallet, site or tool made by the project integrates an exchange, swap-to-fiat, on-ramp or off-ramp.

## AMMO-P-09 The closed loop with GLiBz

- NUGGETS are the GLiBz platform currency, not a cryptocurrency, and have no cash value.
- Only NUGGETS **earned** through activity can be swapped for AMMO, at the GLiBz swap rate, tiered and capped per member each month. NUGGETS bought with cash or with AMMO are spend-only and can never reach AMMO or a tier position.
- No fixed NUGGETS-to-AMMO ratio is quoted in copy.
- Fiat goods (shop.glibz.com, priced in dollars) and the reward catalogue (redemption prices in NUGGETS or AMMO, set independently and not converted from dollars) are kept apart. Neither sets a price for AMMO.
- Member-to-member trades are the members' own business; the project sets no price and is not a party.

The GLiBz repository is canonical for how GLiBz enforces this; this principle records what AMMOcoin's documents may say about it.

## AMMO-P-10 Honest privacy claims

AMMO is transparent by default. Sapling shielded addresses are optional, and their limits are stated (transparent side of shield/unshield is visible; peers see your IP). Do not call AMMO "anonymous", "untraceable" or "completely private".

## AMMO-P-11 No evasion; the tax-obligation footnote

Privacy is never marketed as a way to avoid tax, financial reporting, sanctions or law enforcement. Wherever privacy is promoted at length, carry the footnote (white paper `[^tax]`): *"AMMO is not a proponent of its network being used to circumvent or bypass an individual's local, state or federal tax or financial reporting obligations. It only strives to offer the same level of individual responsibility and freedom as the hard currencies and stores of value it seeks to optimize. Every individual is responsible for their own actions."*

## AMMO-P-12 Not an offer; no advice

Every white paper, programme page and promotion states, where space allows, that it is not an offer to sell anything, not investment advice and not a promise of any return, yield, profit or price.

## AMMO-P-13 Safety in migrations and distributions

The project never asks anyone to send coins, private keys, seed phrases or wallet files. Ownership claims use signed messages. There is no deadline that pressures holders.

## AMMO-P-14 No skirting: substance over wording

A change that achieves something these principles forbid by another route (renaming a sale as a "donation", "membership", "package", "bundle", "boost" or "gift"; pricing in NUGGETS that can be bought with cash; routing cash through a third party) violates the principle it routes around. When in doubt, record the question in DECISIONS.md and get owner and, when available, counsel sign-off before shipping.

## AMMO-P-15 Review before release or deploy

No release, deploy or public copy change that touches these principles ships without review against [REVIEW_CHECKLIST.md](REVIEW_CHECKLIST.md). The app and website front-facing code are public so that anyone can check them.
