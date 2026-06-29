/**
 * AMMOcoin Payment Gateway — Payout Types
 *
 * Payouts move AMMO OUT of the gateway (hot) wallet to a merchant-supplied
 * address — the settlement leg for "sell Nuggets for AMMO" on Glibz. Unlike
 * invoices (inbound), a payout broadcasts a spend, so the state machine is
 * built around a single idempotent send.
 */

/**
 *  sending — claimed; broadcast attempted (or in flight). Treat as AMBIGUOUS:
 *            the spend may or may not have hit the chain.
 *  sent    — broadcast succeeded; `txid` is set.
 *  failed  — the daemon rejected the spend BEFORE broadcast, or a pre-send
 *            check failed. No AMMO left the wallet → safe for the merchant to
 *            refund the user.
 */
export type PayoutStatus = 'sending' | 'sent' | 'failed';

export interface Payout {
  id: string;
  merchant_id: string;
  idempotency_key: string;
  address: string;
  amount: number;
  memo: string | null;
  metadata: Record<string, unknown> | null;
  status: PayoutStatus;
  txid: string | null;
  reason: string | null;
  created_at: string;
  completed_at: string | null;
}

/** Row stored in SQLite (metadata is a JSON string). */
export interface PayoutRow {
  id: string;
  merchant_id: string;
  idempotency_key: string;
  address: string;
  amount: number;
  memo: string | null;
  metadata: string | null;
  status: PayoutStatus;
  txid: string | null;
  reason: string | null;
  created_at: string;
  completed_at: string | null;
}

export interface CreatePayoutRequest {
  /** Destination AMMO address. */
  address: string;
  /** AMMO amount to send (positive; rounded to 8 decimals). */
  amount: number;
  /** Merchant-unique key — replays with the same key never re-broadcast. */
  idempotency_key: string;
  memo?: string;
  metadata?: Record<string, unknown>;
}

/** Public-facing payout response. */
export interface PayoutResponse {
  id: string;
  merchant_id: string;
  idempotency_key: string;
  address: string;
  amount: number;
  memo: string | null;
  metadata: Record<string, unknown> | null;
  status: PayoutStatus;
  txid: string | null;
  reason: string | null;
  created_at: string;
  completed_at: string | null;
}

/**
 * Thrown by the payout manager when the outcome is genuinely ambiguous (the
 * send may have broadcast). The route maps this to a 5xx so the merchant
 * holds the transaction for manual review instead of refunding.
 */
export class AmbiguousPayoutError extends Error {
  constructor(
    message: string,
    public readonly payoutId: string
  ) {
    super(message);
    this.name = 'AmbiguousPayoutError';
  }
}
