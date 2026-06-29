# Payouts API — sending AMMO out of the gateway

The payout endpoints settle **outbound** AMMO from the gateway hot wallet —
the on-chain leg of "sell Nuggets for AMMO" on Glibz. Unlike invoices
(inbound, monitored), a payout broadcasts a spend, so the design centers on
**idempotency** and a strict **safe-to-refund vs. ambiguous** contract.

Auth is the same Bearer API key as the rest of `/api/*`.

## Endpoints

### `POST /api/payouts`
Body:
```json
{
  "address": "A…",                 // destination AMMO address (required)
  "amount": 12.5,                   // AMMO, positive, rounded to 8 dp (required)
  "idempotency_key": "glibz_sell:42", // merchant-unique; replays never re-send (required)
  "memo": "GLiBz Nuggets sale",     // optional; passed as the tx comment
  "metadata": { "profile_id": 7 }   // optional; stored as JSON
}
```

Response contract — **the caller MUST branch on this**:

| HTTP | body | meaning | caller action |
|------|------|---------|---------------|
| 200 | `{status:"sent", txid}` | broadcast succeeded | mark paid |
| 200 | `{status:"failed", reason}` | **nothing broadcast** (bad address, insufficient float, over cap, daemon rejection) | **safe to refund** the user |
| 502 | `{status:"unknown"}` | **ambiguous** — send may have broadcast (network/timeout mid-send) | **hold for manual review; do NOT refund** |
| 400 | `{error}` | malformed request (no row created) | fix request |

Idempotency: a second `POST` with the same `(api key → merchant, idempotency_key)`
returns the **stored** record without re-broadcasting, whatever its state.

### `GET /api/payouts/:id`
Poll a payout (merchant-scoped). Use this to resolve a 502 later: the row
flips to `sent` (with `txid`) once it settles, or stays `sending` pending
manual reconciliation.

### `GET /api/payouts?limit=&offset=`
List the merchant's payouts, newest first.

## State machine
`sending` → `sent` (txid set) | `failed` (reason set). A row only ever leaves
`sending` once; `failed` is reserved for outcomes where **no AMMO left the
wallet**. A transport/timeout failure at send time leaves the row `sending`
(ambiguous) on purpose — it is never silently marked failed.

## Operational security (read before funding)
- **Encrypt the hot wallet** and set `GATEWAY_WALLET_PASSPHRASE`. The endpoint
  unlocks for a 30s window per send and re-locks immediately.
- **Hold only an operational float** in the gateway wallet; keep the reserve in
  a separate cold wallet. `MAX_PAYOUT_AMMO` caps any single send.
- **Use a dedicated API key** for the payout caller (Glibz), separate from
  invoice-only merchants. Anyone with a key that can reach `/api/payouts` can
  drain up to the float (bounded by `MAX_PAYOUT_AMMO`).
- The `payouts` table is the audit ledger — every attempt is recorded with its
  idempotency key, status, reason, and txid.

See `.env.example` for `GATEWAY_WALLET_PASSPHRASE`, `MAX_PAYOUT_AMMO`,
`MIN_PAYOUT_AMMO`. The Glibz caller lives in `ammo_exchange.php`
(`_ammoExchangeSellNuggets`), keyed by `glibz_sell:<txn_id>`.
