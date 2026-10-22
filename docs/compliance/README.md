# AMMOcoin compliance record

This folder is the auditable record of how AMMOcoin is deliberately built and described so that it is **not pay-to-play, not an ICO or token sale, and not presented as having a value or a return**, and of the decisions that keep it that way. Changes that touch economics, rewards, the block-1 reserve, the structured release, governance or public copy must be checked against it.

> **Not legal advice.** This record was written by the project to document its own intent and the code and copy that carry it out. It is not a legal opinion and has not been reviewed by counsel.
>
> **Counsel review status: PENDING.** No lawyer has reviewed these principles, decisions or the programmes they describe. Until counsel has reviewed them, treat every programme that moves reserve AMMO to people (tier positions, contributor rewards, NUGGETS swaps) as needing review before it is switched on or widened.

## Scope

| Repository | What it covers | Compliance folder |
|---|---|---|
| **everquin/AMMOcoin** (this repo) | Node source, consensus rules, release notes, white papers, payment gateway, explorer | `docs/compliance/` (**canonical** principles) |
| everquin/ammocoin_website | ammocoin.org public copy | `docs/compliance/` (site-specific record, same principle IDs) |
| everquin/AMMOcoin_App | Desktop wallet app | `docs/compliance/` (app-specific record, same principle IDs) |
| GLiBz (glibz.com) | NUGGETS, swap, reward catalogue, tiers terms | The GLiBz repository keeps its own record for the NUGGETS economy |

Principle IDs (`AMMO-P-xx`) are the same in all three AMMOcoin repositories. This repository holds the canonical wording; the site and app records point back here.

## Files

| File | Use |
|---|---|
| [PRINCIPLES.md](PRINCIPLES.md) | The binding principles. Every change must comply. |
| [DECISIONS.md](DECISIONS.md) | Dated decision log (ADR style) with evidence: commit SHAs and file:line enforcement points. Includes a list of known gaps. |
| [REVIEW_CHECKLIST.md](REVIEW_CHECKLIST.md) | Pre-merge checklist for any change that touches rewards, the reserve, prices, payments, exchanges, privacy claims or copy. |
| [AIRDROPS.md](AIRDROPS.md) | The v1.0 -> v1.1 migration airdrop: how it works, what is published (placeholders marked TO BE PUBLISHED), why it is not a sale. |
| [RESERVES.md](RESERVES.md) | Every project-held pool of AMMO, its purpose, addresses and movements (D-2026-10-24-04). |
| [SOCIAL_KIT_2026-11.md](SOCIAL_KIT_2026-11.md) | The Oct 24 -> Nov 20, 2026 social kit (X, Facebook, YouTube, Instagram, TikTok): content rules, claim sources, review results and owner sign-off. |

## How to use this folder in reviews

1. **Before opening a PR** that touches anything in the checklist's trigger list, read [PRINCIPLES.md](PRINCIPLES.md) and run through [REVIEW_CHECKLIST.md](REVIEW_CHECKLIST.md). The PR template has a compliance section; tick it honestly or explain.
2. **If a change alters a principle or makes a new economic decision**, add an entry to [DECISIONS.md](DECISIONS.md) in the same PR: new ID, date, decision, context, rationale, alternatives rejected, enforcement (file:line, commit SHA), and owner approval. Never edit an old entry's decision; supersede it with a new entry that names the old ID.
3. **If code or copy is found that contradicts a principle**, add it to the *Known gaps* table in DECISIONS.md with file:line, even if it is not fixed in the same PR. A recorded gap is better than a silent one.
4. **Where the white paper and the code disagree, the code wins** and the paper is corrected (2nd Edition, rev. 2026/10/17). The same rule applies to these records: if this folder and the code disagree, record the gap and fix one of them.
5. **No release or deploy without review.** A release that changes issuance, rewards or the reserve needs a reviewer other than the author to sign off on the checklist.

## Evidence conventions

- **Commit SHAs** are abbreviated SHAs in this repository unless a repository is named (e.g. `website afb24a5`, `app 88dc399`).
- **file:line** references are to the tree at the commit this folder was added in; line numbers drift, so search for the quoted text if a line moves.
- **UNVERIFIED** marks a statement that could not be confirmed from the repositories (for example, an off-chain transfer or a verbal approval).
