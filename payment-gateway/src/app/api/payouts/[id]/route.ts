/**
 * /api/payouts/[id]
 *
 * GET — Poll a single payout's status, scoped to the authenticated merchant.
 *       Use this to resolve an earlier AMBIGUOUS (502) response: once the
 *       send settles, the record flips to 'sent' (with txid) or stays
 *       'sending' pending manual reconciliation.
 */

import { NextRequest, NextResponse } from 'next/server';
import { getPayout, payoutToResponse } from '@/lib/payout-manager';

export async function GET(
  request: NextRequest,
  { params }: { params: { id: string } }
) {
  const merchantId = request.headers.get('x-merchant-id');
  if (!merchantId) {
    return NextResponse.json({ error: 'Unauthorized' }, { status: 401 });
  }

  try {
    const payout = getPayout(params.id, merchantId);
    if (!payout) {
      return NextResponse.json({ error: 'Payout not found' }, { status: 404 });
    }
    return NextResponse.json(payoutToResponse(payout));
  } catch (err) {
    console.error('[GET /api/payouts/:id] Error:', err);
    return NextResponse.json({ error: 'Failed to fetch payout' }, { status: 500 });
  }
}
