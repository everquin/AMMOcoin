/**
 * /api/payouts
 *
 * POST — Send AMMO from the gateway hot wallet to an address (the "sell
 *        Nuggets for AMMO" settlement leg). Idempotent on `idempotency_key`.
 * GET  — List payouts for the authenticated merchant.
 *
 * Response contract the caller relies on:
 *   200 {status:'sent', txid}   → done.
 *   200 {status:'failed', reason}→ nothing broadcast; safe to refund the user.
 *   502 {error, status:'unknown'}→ AMBIGUOUS; hold for manual review, do NOT
 *                                  refund. Re-querying the same idempotency_key
 *                                  later returns the resolved record.
 */

import { NextRequest, NextResponse } from 'next/server';
import {
  createPayout,
  listPayouts,
  payoutToResponse,
} from '@/lib/payout-manager';
import { AmbiguousPayoutError, type CreatePayoutRequest } from '@/types/payout';

/**
 * POST /api/payouts
 * Body: { address, amount, idempotency_key, memo?, metadata? }
 */
export async function POST(request: NextRequest) {
  const merchantId = request.headers.get('x-merchant-id');
  if (!merchantId) {
    return NextResponse.json({ error: 'Unauthorized' }, { status: 401 });
  }

  let body: CreatePayoutRequest;
  try {
    body = await request.json();
  } catch {
    return NextResponse.json({ error: 'Invalid JSON body' }, { status: 400 });
  }

  // Malformed requests (caller's responsibility) → 400. No row is created.
  if (typeof body.address !== 'string' || body.address.trim() === '') {
    return NextResponse.json({ error: 'address is required' }, { status: 400 });
  }
  if (typeof body.amount !== 'number' || !Number.isFinite(body.amount) || body.amount <= 0) {
    return NextResponse.json(
      { error: 'amount must be a positive number' },
      { status: 400 }
    );
  }
  if (typeof body.idempotency_key !== 'string' || body.idempotency_key.trim() === '') {
    return NextResponse.json(
      { error: 'idempotency_key is required' },
      { status: 400 }
    );
  }

  try {
    const payout = await createPayout(merchantId, {
      address: body.address.trim(),
      amount: body.amount,
      idempotency_key: body.idempotency_key.trim(),
      memo: body.memo,
      metadata: body.metadata,
    });
    // Both 'sent' and 'failed' are definitive, safe outcomes for the caller.
    return NextResponse.json(payoutToResponse(payout), { status: 200 });
  } catch (err) {
    if (err instanceof AmbiguousPayoutError) {
      // The spend may have broadcast — caller must hold, not refund.
      return NextResponse.json(
        { error: err.message, status: 'unknown', payout_id: err.payoutId },
        { status: 502 }
      );
    }
    console.error('[POST /api/payouts] Error:', err);
    return NextResponse.json(
      { error: err instanceof Error ? err.message : 'Failed to create payout', status: 'unknown' },
      { status: 500 }
    );
  }
}

/**
 * GET /api/payouts — List payouts for the authenticated merchant.
 * Query params: limit? (default 50, max 200), offset? (default 0)
 */
export async function GET(request: NextRequest) {
  const merchantId = request.headers.get('x-merchant-id');
  if (!merchantId) {
    return NextResponse.json({ error: 'Unauthorized' }, { status: 401 });
  }

  const { searchParams } = request.nextUrl;
  const limit = Math.min(Math.max(Number(searchParams.get('limit')) || 50, 1), 200);
  const offset = Math.max(Number(searchParams.get('offset')) || 0, 0);

  try {
    const payouts = listPayouts(merchantId, limit, offset);
    return NextResponse.json({
      payouts: payouts.map(payoutToResponse),
      count: payouts.length,
      limit,
      offset,
    });
  } catch (err) {
    console.error('[GET /api/payouts] Error:', err);
    return NextResponse.json({ error: 'Failed to list payouts' }, { status: 500 });
  }
}
