# v1.0 airdrop claims log (public, anonymized)

This is the public list of every signed-message claim received for the v1.0 → v1.1 airdrop ([V1.0_BALANCE_AIRDROP.md](V1.0_BALANCE_AIRDROP.md), [AIRDROPS.md](../compliance/AIRDROPS.md) section 3). It lets anyone see that claims are answered and how, without exposing who made them (decision AMMO-D-2026-10-27-02).

**How to claim:** only if your v1.0 balance is missing after a full v1.1.1 sync. Email the four items in [CLAIM_TEMPLATE.md](CLAIM_TEMPLATE.md) to **claims@ammocoin.org**. Don't open a GitHub Issue for a claim: Issues are public.

A claim never involves sending coins, paying a fee, or sharing a private key, seed phrase or wallet file, and it has no deadline. Anyone who asks for any of these is not the project.

## What this log contains, and what it never contains

- **Contains:** a claim number, the date the email arrived, the status and the outcome.
- **Never contains:** names, email addresses, IP addresses, message text, v1.0 or v1.1 addresses, or signatures. Those stay in the owner's private claims records and are used only to check and pay the claim.
- **Paid claims:** the payout is an ordinary on-chain transaction. Its txid goes in the *Outcome* column, and the paid claim also appears in the airdrop's signed-message claims record ([AIRDROPS.md](../compliance/AIRDROPS.md) section 4). That record lists chain data only (addresses, amount, txid, date), never who the holder is.

## Statuses

| Status | Meaning |
|---|---|
| `received` | Email arrived; claim number sent back to the sender. |
| `checking` | Being checked with `scripts/migration/verify-claim.py` (signature, address in the snapshot, amount still owed). |
| `approved` | Checks passed; waiting for the next offline-signed payout batch. |
| `paid` | Paid. The outcome gives the payout txid. |
| `rejected` | Not paid. The outcome gives one reason from the list below. |
| `withdrawn` | The sender withdrew it. |

Rejection reasons: `signature does not verify`, `message text not exact`, `address not in snapshot`, `nothing owed (already paid)`, `duplicate of C-xxxx`, `not a claim` (for example a question, answered privately).

## Log

Newest last. One row per claim. Add the row when the claim arrives, and update it within 7 days of any change.

| Claim | Received (UTC date) | Status | Outcome | Updated |
|---|---|---|---|---|
| — | — | — | No claims received yet. | 2026-10-27 |

<!-- Row template (copy, fill in, keep personal data out):
| C-0001 | 2026-11-06 | received | — | 2026-11-06 |
| C-0001 | 2026-11-06 | paid | txid `<64 hex>` | 2026-11-12 |
| C-0002 | 2026-11-07 | rejected | signature does not verify | 2026-11-08 |
-->
