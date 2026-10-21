/**
 * AMMOcoin Payment Gateway — Payout Manager
 *
 * Sends AMMO out of the gateway hot wallet, idempotently and with a clear
 * safe-to-refund vs. ambiguous distinction. See ../types/payout.ts for the
 * state machine.
 *
 * Safety invariants:
 *   1. One (merchant_id, idempotency_key) ⇒ at most one broadcast. Replays
 *      return the stored record without re-sending.
 *   2. Every failure BEFORE the sendtoaddress call, and every daemon
 *      *rejection* (`RPC Error …`), marks the row `failed` — no AMMO moved,
 *      caller may refund.
 *   3. A non-rejection throw at send time (network/timeout) leaves the row
 *      `sending` and raises AmbiguousPayoutError — caller must NOT refund.
 */

import { v4 as uuidv4 } from 'uuid';
import { getDB } from './db';
import { getRPCClient } from './rpc';
import {
  AmbiguousPayoutError,
  type Payout,
  type PayoutRow,
  type PayoutResponse,
  type CreatePayoutRequest,
} from '../types/payout';

/** Hard ceiling on a single payout, as a blast-radius limit if a merchant
 *  key is compromised. Override with MAX_PAYOUT_AMMO. */
const DEFAULT_MAX_PAYOUT_AMMO = 100_000;
/** Dust floor — reject sub-fee amounts. Override with MIN_PAYOUT_AMMO. */
const DEFAULT_MIN_PAYOUT_AMMO = 0.0001;
/** Seconds to keep an encrypted wallet unlocked for a send. */
const WALLET_UNLOCK_SECONDS = 30;

// ── Helpers ────────────────────────────────────────────────────────────────

function rowToPayout(row: PayoutRow): Payout {
  return {
    ...row,
    metadata: row.metadata ? JSON.parse(row.metadata) : null,
  };
}

export function payoutToResponse(p: Payout): PayoutResponse {
  return {
    id: p.id,
    merchant_id: p.merchant_id,
    idempotency_key: p.idempotency_key,
    address: p.address,
    amount: p.amount,
    memo: p.memo,
    metadata: p.metadata,
    status: p.status,
    txid: p.txid,
    reason: p.reason,
    created_at: p.created_at,
    completed_at: p.completed_at,
  };
}

/** Round to AMMO's 8 decimal places to avoid float dust on the wire. */
function round8(n: number): number {
  return Math.round(n * 1e8) / 1e8;
}

/** A daemon rejection (vs. a transport failure) — pre-broadcast, safe-to-fail. */
function isDaemonRejection(err: unknown): boolean {
  return err instanceof Error && err.message.startsWith('RPC Error');
}

function getPayoutById(id: string): Payout | null {
  const db = getDB();
  const row = db.prepare('SELECT * FROM payouts WHERE id = ?').get(id) as
    | PayoutRow
    | undefined;
  return row ? rowToPayout(row) : null;
}

function findByIdempotencyKey(merchantId: string, key: string): Payout | null {
  const db = getDB();
  const row = db
    .prepare('SELECT * FROM payouts WHERE merchant_id = ? AND idempotency_key = ?')
    .get(merchantId, key) as PayoutRow | undefined;
  return row ? rowToPayout(row) : null;
}

function markSent(id: string, txid: string): void {
  getDB()
    .prepare(
      `UPDATE payouts SET status = 'sent', txid = ?, completed_at = datetime('now')
         WHERE id = ? AND status = 'sending'`
    )
    .run(txid, id);
}

function markFailed(id: string, reason: string): void {
  getDB()
    .prepare(
      `UPDATE payouts SET status = 'failed', reason = ?, completed_at = datetime('now')
         WHERE id = ? AND status = 'sending'`
    )
    .run(reason.slice(0, 500), id);
}

// ── Public API ───────────────────────────────────────────────────────────────

export function getPayout(payoutId: string, merchantId: string): Payout | null {
  const db = getDB();
  const row = db
    .prepare('SELECT * FROM payouts WHERE id = ? AND merchant_id = ?')
    .get(payoutId, merchantId) as PayoutRow | undefined;
  return row ? rowToPayout(row) : null;
}

export function listPayouts(
  merchantId: string,
  limit = 50,
  offset = 0
): Payout[] {
  const rows = getDB()
    .prepare(
      'SELECT * FROM payouts WHERE merchant_id = ? ORDER BY created_at DESC LIMIT ? OFFSET ?'
    )
    .all(merchantId, limit, offset) as PayoutRow[];
  return rows.map(rowToPayout);
}

/**
 * Create and broadcast a payout. Returns the resulting record for `sent` and
 * `failed` (both safe outcomes the caller can act on). Throws
 * AmbiguousPayoutError only when the broadcast outcome is unknown.
 */
export async function createPayout(
  merchantId: string,
  req: CreatePayoutRequest
): Promise<Payout> {
  const amount = round8(req.amount);
  const db = getDB();

  // 1. Idempotency: a prior record for this key wins, no matter its state.
  const prior = findByIdempotencyKey(merchantId, req.idempotency_key);
  if (prior) return prior;

  // 2. Claim the key by inserting a `sending` row. The UNIQUE(merchant_id,
  //    idempotency_key) index makes concurrent duplicate claims race-safe.
  const id = uuidv4();
  try {
    db.prepare(
      `INSERT INTO payouts
         (id, merchant_id, idempotency_key, address, amount, memo, metadata, status)
       VALUES (?, ?, ?, ?, ?, ?, ?, 'sending')`
    ).run(
      id,
      merchantId,
      req.idempotency_key,
      req.address,
      amount,
      req.memo ?? null,
      req.metadata ? JSON.stringify(req.metadata) : null
    );
  } catch (err) {
    // Lost the race — another request claimed this key. Return its record.
    const existing = findByIdempotencyKey(merchantId, req.idempotency_key);
    if (existing) return existing;
    throw err;
  }

  const rpc = getRPCClient();
  const walletPass = process.env.GATEWAY_WALLET_PASSPHRASE;
  let unlocked = false;

  // 3. Pre-send checks. EVERYTHING here is before sendtoaddress, so any
  //    failure means no AMMO moved → mark `failed` (safe to refund).
  try {
    const maxPayout = Number(process.env.MAX_PAYOUT_AMMO) || DEFAULT_MAX_PAYOUT_AMMO;
    const minPayout = Number(process.env.MIN_PAYOUT_AMMO) || DEFAULT_MIN_PAYOUT_AMMO;

    if (!Number.isFinite(amount) || amount < minPayout) {
      markFailed(id, `amount below minimum payout (${minPayout} AMMO)`);
      return getPayoutById(id)!;
    }
    if (amount > maxPayout) {
      markFailed(id, `amount exceeds maximum payout (${maxPayout} AMMO)`);
      return getPayoutById(id)!;
    }

    const valid = await rpc.validateAddress(req.address);
    if (!valid.isvalid) {
      markFailed(id, 'invalid AMMO address');
      return getPayoutById(id)!;
    }

    const balance = await rpc.getBalance(1);
    if (balance < amount) {
      markFailed(id, 'insufficient gateway wallet balance');
      return getPayoutById(id)!;
    }

    // Unlock the (possibly encrypted) wallet for the send window. A wrong
    // passphrase throws here, pre-broadcast → still safe.
    if (walletPass) {
      await rpc.walletPassphrase(walletPass, WALLET_UNLOCK_SECONDS);
      unlocked = true;
    }
  } catch (preSendErr) {
    // No broadcast happened. Safe to fail (and thus refund).
    const msg = preSendErr instanceof Error ? preSendErr.message : String(preSendErr);
    markFailed(id, `pre-send check failed: ${msg}`);
    if (unlocked) await rpc.walletLock().catch(() => {});
    return getPayoutById(id)!;
  }

  // 4. THE send. This is the only point where an ambiguous outcome is possible.
  try {
    const txid = await rpc.sendToAddress(req.address, amount, req.memo ?? '');
    markSent(id, txid);
    return getPayoutById(id)!;
  } catch (sendErr) {
    if (isDaemonRejection(sendErr)) {
      // Daemon responded with a rejection ⇒ nothing broadcast ⇒ safe to fail.
      markFailed(id, sendErr instanceof Error ? sendErr.message : 'send rejected');
      return getPayoutById(id)!;
    }
    // Transport/timeout: the spend MAY have broadcast. Leave the row `sending`
    // and signal the caller to hold for manual review (never refund).
    throw new AmbiguousPayoutError(
      sendErr instanceof Error ? sendErr.message : 'send outcome unknown',
      id
    );
  } finally {
    if (unlocked) await rpc.walletLock().catch(() => {});
  }
}
