/**
 * /api/invoices
 *
 * POST — Create a new invoice
 * GET  — List invoices for the authenticated merchant
 */

import { NextRequest, NextResponse } from 'next/server';
import {
  createInvoice,
  listInvoices,
  invoiceToResponse,
} from '@/lib/invoice-manager';
import { startMonitor } from '@/lib/payment-monitor';
import type { CreateInvoiceRequest, InvoiceStatus } from '@/types/invoice';

// Ensure the payment monitor is running once the first request arrives.
let _monitorStarted = false;
function ensureMonitor() {
  if (!_monitorStarted) {
    _monitorStarted = true;
    startMonitor();
  }
}

/**
 * POST /api/invoices — Create a new invoice.
 *
 * Body: { amount, memo?, metadata?, webhook_url?, webhook_secret? }
 */
export async function POST(request: NextRequest) {
  ensureMonitor();

  const merchantId = request.headers.get('x-merchant-id');
  if (!merchantId) {
    return NextResponse.json({ error: 'Unauthorized' }, { status: 401 });
  }

  let body: CreateInvoiceRequest;
  try {
    body = await request.json();
  } catch {
    return NextResponse.json(
      { error: 'Invalid JSON body' },
      { status: 400 }
    );
  }

  // Validate required fields
  if (typeof body.amount !== 'number' || body.amount <= 0) {
    return NextResponse.json(
      { error: 'amount must be a positive number' },
      { status: 400 }
    );
  }

  if (body.webhook_url && !body.webhook_secret) {
    return NextResponse.json(
      { error: 'webhook_secret is required when webhook_url is provided' },
      { status: 400 }
    );
  }

  if (body.webhook_url) {
    try {
      new URL(body.webhook_url);
    } catch {
      return NextResponse.json(
        { error: 'webhook_url must be a valid URL' },
        { status: 400 }
      );
    }
  }

  try {
    const invoice = await createInvoice(merchantId, body);
    return NextResponse.json(invoiceToResponse(invoice), { status: 201 });
  } catch (err) {
    console.error('[POST /api/invoices] Error:', err);
    return NextResponse.json(
      { error: err instanceof Error ? err.message : 'Failed to create invoice' },
      { status: 500 }
    );
  }
}

/**
 * GET /api/invoices — List invoices for the authenticated merchant.
 *
 * Query params: status?, limit? (default 50), offset? (default 0)
 */
export async function GET(request: NextRequest) {
  ensureMonitor();

  const merchantId = request.headers.get('x-merchant-id');
  if (!merchantId) {
    return NextResponse.json({ error: 'Unauthorized' }, { status: 401 });
  }

  const { searchParams } = request.nextUrl;
  const status = searchParams.get('status') as InvoiceStatus | null;
  const limit = Math.min(Math.max(Number(searchParams.get('limit')) || 50, 1), 200);
  const offset = Math.max(Number(searchParams.get('offset')) || 0, 0);

  // Validate status if provided
  if (status && !['pending', 'confirming', 'confirmed', 'expired'].includes(status)) {
    return NextResponse.json(
      { error: 'Invalid status filter. Must be: pending, confirming, confirmed, or expired' },
      { status: 400 }
    );
  }

  try {
    const invoices = listInvoices(merchantId, status ?? undefined, limit, offset);
    return NextResponse.json({
      invoices: invoices.map(invoiceToResponse),
      count: invoices.length,
      limit,
      offset,
    });
  } catch (err) {
    console.error('[GET /api/invoices] Error:', err);
    return NextResponse.json(
      { error: 'Failed to list invoices' },
      { status: 500 }
    );
  }
}
