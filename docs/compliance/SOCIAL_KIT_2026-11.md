# AMMOcoin social kit (Oct 24 -> Nov 20, 2026): rules and content review

This document is the compliance record for the **scheduled social-media kit** that covers AMMOcoin's public launch on Nov 5, 2026: what the kit contains, the rules every post was written to, how the content was reviewed, and what is still open. It applies AMMO-P-01, AMMO-P-02, AMMO-P-03, AMMO-P-04, AMMO-P-08, AMMO-P-10, AMMO-P-12, AMMO-P-13, AMMO-P-14 and AMMO-P-15 ([PRINCIPLES.md](PRINCIPLES.md)) and was run through [REVIEW_CHECKLIST.md](REVIEW_CHECKLIST.md).

Not legal advice. Counsel review status: **pending**.

> The kit is built but **not uploaded, scheduled or posted**. Any change to a post after this review must be checked against section 2 again before it is scheduled.

---

## 1. What the kit is

| Item | Value |
|---|---|
| Location | `/Volumes/CRUCIAL_2TB/GOOGLE/_AMMOCOIN/promo/` (owner's local drive, not in any repository) |
| Source of every post | `content.py` (one entry per post: date, card text, captions, link, claims) |
| Generators | `cards.py` (PNG cards, contact sheet), `videos.py` (silent 9:16 MP4), `publer.py` (CSVs, `claims.md`, `README.md`) |
| Period | Oct 24 -> Nov 20, 2026, US Central time |
| Cadence | 1 post a day per network; 2 a day on X (a daily glossary card at 17:00); Nov 5: launch at 09:00 and 17:00, ecosystem cross-over at 13:00 |
| Series | *Under the Hood* (Oct 24 -> Nov 4, 12 posts), launch day (3 posts), *How-to* (Nov 6 -> Nov 20, 15 posts), *AMMO Glossary* (X only, 26 posts) |
| Networks | The five owner-confirmed accounts (2026-10-22), one Publer CSV each: X x.com/ammocoin, Facebook facebook.com/ammocoin, YouTube Shorts youtube.com/@ammocoin6637, Instagram instagram.com/ammocoin, TikTok tiktok.com/@ammocoin. Community page: glibz.com/ammocoin. AMMOcoin has **no Telegram and no Discord**. |
| Audio | None. Videos carry a silent audio track; no music from any catalogue is used. |
| Claims file | `claims.md` in the kit: every factual claim with its source |

## 2. Rules every post follows

1. **No price, no value (P-03).** No price, value, worth, market cap, exchange rate, fiat amount, Bitcoin comparison or scarcity framing.
2. **No returns (P-04).** No investment, returns, profit, APY, APR, yield, "earn", passive income, "moon", gains or guarantees. Staking is described only as how the network agrees on new blocks and stays secure ("stake to help secure the network"). No reward amounts, rates, masternode payments or treasury amounts appear in any post, even where the code would allow them to be stated.
3. **No sale, no exchanges (P-01, P-02, P-08).** No "buy", no exchanges, listings, on-ramps or "where to get AMMO". AMMO is never offered.
4. **No airdrop or payout promises (P-06, P-13).** (Launch Season posts: scoped exception for "draw", "winners", "bounty", see AMMO-D-2026-10-27-07.) The v1.0 balance airdrop and any payout are not mentioned.
5. **No pressure (P-13, P-14).** No "join early", no FOMO countdowns. The launch date is stated neutrally ("AMMOcoin's public launch is Nov 5, 2026"); the only date card is a single neutral "Nov 5" post on X on Nov 4.
6. **Links.** Announcements link only to the GitHub release (`https://github.com/everquin/AMMOcoin/releases/tag/v1.1.1`). Education posts link to the source, the docs on `main`, or `explorer.ammocoin.org`. The Nov 5 cross-over names ammocoin.org, everquin.com and glibz.com with no rewards, NUGGETS or programmes mentioned. The Nov 19 help post names GitHub issues, the docs and the community page glibz.com/ammocoin. Captions close with "More at glibz.com/ammocoin" (on X, in the first reply). Instagram captions say "link in bio"; Instagram and TikTok captions carry no URLs, since links are not clickable there.
7. **Honest privacy (P-10).** The only privacy statement says transactions are transparent by default, Sapling shielding is optional and the shield/unshield sides are visible.
8. **Safety (P-13).** Security posts say AMMOcoin will never ask anyone to send coins, keys or wallet files, and that anyone who does is attempting a scam (release notes wording).
9. **Not an offer (P-12).** Long captions (Facebook, Instagram, TikTok, YouTube) end with: *"AMMOcoin is open-source network software. This post is not an offer and not financial advice."* The wording avoids the words "investment" and "return" so the disclaimer itself cannot be quoted as a return claim.
10. **Verifiable.** Every claim is listed in the kit's `claims.md` with a source (release notes, source code, docs, explorer, DNS). A claim that could not be verified was changed or dropped (section 4).

## 3. Content review (2026-10-22)

| Check | Result |
|---|---|
| Banned-word scan of every caption (all 5 CSVs, including first comments and alt text) and every string drawn on a card (`cards/card-text.txt`), case-insensitive: `price`, `value`, `market cap`, `invest`, `return`, `profit`, `APY`, `APR`, `yield`, `earn` (word start), `passive income`, `moon`, `buy`, `exchange`, `listing`, `scarc`, `airdrop`, `payout`, `reward`, `worth`, `gain`, `pump`, `guarantee`, `income`, `early`, `fomo` | Clean (no matches) |
| REVIEW_CHECKLIST A (sale / pay-to-play) | No path to AMMO, no purchase, no request for coins or keys |
| REVIEW_CHECKLIST B (price and value) | No price, fiat amount, value implication or NUGGETS ratio |
| REVIEW_CHECKLIST C (returns) | No return language; no reward descriptions at all |
| REVIEW_CHECKLIST E (exchanges) | No exchange, listing or "where to buy" text |
| REVIEW_CHECKLIST F (privacy, not-an-offer) | Privacy stated honestly; not-an-offer line present on long captions |
| Visual check of all cards (contact sheet) and sampled video frames | No overflow or overlap |
| CSV parse + media path check | All CSVs parse; every media path exists locally |

Reviewer: prepared and reviewed by Claude (agent) on 2026-10-22; re-run after the account update the same day (5 networks, Telegram/Discord removed): clean. **A second reviewer (the owner) must sign off** before the kit is scheduled (P-15); add an `Approved-by:` line below.

## 4. Claims changed or dropped because they could not be verified

- "Reproducible builds": not documented. Replaced with "release packages are built by GitHub Actions from the tagged source".
- Seed locations: the brief said Dallas, New York, Sydney, London and seed2. IP geolocation (2026-10-22) gives London, Chicago region (seed2), Piscataway NJ, Dallas and Sydney. Posts say "London, Chicago, Dallas, New York/NJ, Sydney" (three continents). Owner to confirm.
- Seed-phrase backups: not confirmed for the AMMOcoin wallet; dropped.
- "Lose the passphrase and the coins are gone": not stated in the docs; dropped.

## 5. Open items

| ID | Item | Status |
|---|---|---|
| S-01 | `discord.gg/ammocoin` returned "Unknown Invite" (Discord API code 10006) on 2026-10-22; `t.me/ammocoin` showed no channel title. | **Resolved by owner 2026-10-22:** there is no Telegram or Discord. Both were removed from the kit (Telegram CSV and Discord paste file dropped; Threads and Bluesky CSVs dropped too, no accounts). The Nov 19 post now points to GitHub issues, the docs and glibz.com/ammocoin. |
| S-02 | The live explorer (eIquidus) still ships price and market-cap panel templates in its page script. They are not displayed (only coin supply, masternodes and logo panels are on), but turning one on would contradict AMMO-D-2026-10-17-09. The explorer tour post does not mention them. | **Resolved 2026-10-22 (owner approved):** the four price/market-cap panel templates and the script that filled them were removed from the explorer's `views/layout.pug`; `/ext/getsummary` and `/ext/getbasicstats` no longer return price fields (backups `*.bak-20261022144313` on ammo-05). The same patch fixed a crash in `/ext/getsummary` (v1.1.1 has no `getnetworkhashps`). |
| S-03 | Owner sign-off on this kit (P-15). | **Resolved:** approved by the owner in chat on 2026-10-22, including the seed line "London, Chicago, Dallas, New York/NJ, Sydney". |

Approved-by: owner (everquin), 2026-10-22, given in the Claude Code session and recorded by Claude
