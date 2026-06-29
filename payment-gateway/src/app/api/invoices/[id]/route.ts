/**
 * /api/invoices/:id
 *
 * GET — Retrieve a single invoice by ID.
 */

import { NextRequest, NextResponse } from 'next/server';
import { getInvoice, invoiceToResponse } from '@/lib/invoice-manager';

interface RouteParams {
  params: { id: string };
}

/**
 * GET /api/invoices/:id — Get invoice status.
 */
export async function GET(request: NextRequest, { params }: RouteParams) {
  const merchantId = request.headers.get('x-merchant-id');
  if (!merchantId) {
    return NextResponse.json({ error: 'Unauthorized' }, { status: 401 });
  }

  const { id } = params;

  if (!id || typeof id !== 'string') {
    return NextResponse.json({ error: 'Invalid invoice ID' }, { status: 400 });
  }

  try {
    const invoice = getInvoice(id, merchantId);
    if (!invoice) {
      return NextResponse.json({ error: 'Invoice not found' }, { status: 404 });
    }

    return NextResponse.json(invoiceToResponse(invoice));
  } catch (err) {
    console.error(`[GET /api/invoices/${id}] Error:`, err);
    return NextResponse.json(
      { error: 'Failed to retrieve invoice' },
      { status: 500 }
    );
  }
}
