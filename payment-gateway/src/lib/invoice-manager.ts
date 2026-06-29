/**
 * AMMOcoin Payment Gateway — Invoice Manager
 *
 * Handles invoice creation, lookup, status transitions, and expiry.
 */

import { v4 as uuidv4 } from 'uuid';
import { getDB } from './db';
import { getRPCClient } from './rpc';
import type {
  Invoice,
  InvoiceRow,
  InvoiceResponse,
  InvoiceStatus,
  CreateInvoiceRequest,
} from '../types/invoice';

const DEFAULT_EXPIRY_MINUTES = 30;

// ── Helpers ────────────────────────────────────────────────────────────────

function rowToInvoice(row: InvoiceRow): Invoice {
  return {
    ...row,
    metadata: row.metadata ? JSON.parse(row.metadata) : null,
  };
}

export function invoiceToResponse(inv: Invoice): InvoiceResponse {
  return {
    id: inv.id,
    merchant_id: inv.merchant_id,
    amount: inv.amount,
    memo: inv.memo,
    metadata: inv.metadata,
    address: inv.address,
    status: inv.status,
    txid: inv.txid,
    confirmations: inv.confirmations,
    qr_data: `ammocoin:${inv.address}?amount=${inv.amount}`,
    created_at: inv.created_at,
    expires_at: inv.expires_at,
    paid_at: inv.paid_at,
  };
}

// ── CRUD ───────────────────────────────────────────────────────────────────

/**
 * Create a new invoice. Generates a fresh on-chain address via RPC.
 */
export async function createInvoice(
  merchantId: string,
  req: CreateInvoiceRequest
): Promise<Invoice> {
  if (!req.amount || req.amount <= 0) {
    throw new Error('amount must be a positive number');
  }

  const rpc = getRPCClient();
  const id = uuidv4();

  // Generate a unique receive address labelled with the invoice id
  const address = await rpc.getNewAddress(`invoice:${id}`);

  const expiryMinutes = Number(process.env.INVOICE_EXPIRY_MINUTES) || DEFAULT_EXPIRY_MINUTES;
  const expiresAt = new Date(Date.now() + expiryMinutes * 60_000).toISOString();

  const db = getDB();
  db.prepare(
    `INSERT INTO invoices
       (id, merchant_id, amount, memo, metadata, address, status, expires_at, webhook_url, webhook_secret)
     VALUES
       (?, ?, ?, ?, ?, ?, 'pending', ?, ?, ?)`
  ).run(
    id,
    merchantId,
    req.amount,
    req.memo ?? null,
    req.metadata ? JSON.stringify(req.metadata) : null,
    address,
    expiresAt,
    req.webhook_url ?? null,
    req.webhook_secret ?? null
  );

  const row = db.prepare('SELECT * FROM invoices WHERE id = ?').get(id) as InvoiceRow;
  return rowToInvoice(row);
}

/**
 * Retrieve a single invoice by id, scoped to a merchant.
 */
export function getInvoice(invoiceId: string, merchantId: string): Invoice | null {
  const db = getDB();
  const row = db
    .prepare('SELECT * FROM invoices WHERE id = ? AND merchant_id = ?')
    .get(invoiceId, merchantId) as InvoiceRow | undefined;
  return row ? rowToInvoice(row) : null;
}

/**
 * List invoices for a merchant with optional status filter.
 */
export function listInvoices(
  merchantId: string,
  status?: InvoiceStatus,
  limit: number = 50,
  offset: number = 0
): Invoice[] {
  const db = getDB();

  let sql = 'SELECT * FROM invoices WHERE merchant_id = ?';
  const params: unknown[] = [merchantId];

  if (status) {
    sql += ' AND status = ?';
    params.push(status);
  }

  sql += ' ORDER BY created_at DESC LIMIT ? OFFSET ?';
  params.push(limit, offset);

  const rows = db.prepare(sql).all(...params) as InvoiceRow[];
  return rows.map(rowToInvoice);
}

// ── Status transitions (used by payment monitor) ──────────────────────────

/**
 * Mark an invoice as confirming with the detected txid.
 */
export function markConfirming(invoiceId: string, txid: string): void {
  const db = getDB();
  db.prepare(
    `UPDATE invoices
        SET status = 'confirming', txid = ?, paid_at = datetime('now')
      WHERE id = ? AND status = 'pending'`
  ).run(txid, invoiceId);
}

/**
 * Update the confirmation count on a confirming invoice.
 */
export function updateConfirmations(invoiceId: string, confirmations: number): void {
  const db = getDB();
  db.prepare(
    `UPDATE invoices SET confirmations = ? WHERE id = ?`
  ).run(confirmations, invoiceId);
}

/**
 * Mark an invoice as fully confirmed.
 */
export function markConfirmed(invoiceId: string, confirmations: number): void {
  const db = getDB();
  db.prepare(
    `UPDATE invoices
        SET status = 'confirmed', confirmations = ?
      WHERE id = ? AND status = 'confirming'`
  ).run(confirmations, invoiceId);
}

/**
 * Expire all pending invoices past their expiry time.
 * Returns the list of expired invoice ids.
 */
export function expireOverdueInvoices(): string[] {
  const db = getDB();
  const now = new Date().toISOString();

  const rows = db
    .prepare(
      `SELECT id FROM invoices
        WHERE status = 'pending' AND expires_at <= ?`
    )
    .all(now) as { id: string }[];

  if (rows.length > 0) {
    db.prepare(
      `UPDATE invoices
          SET status = 'expired'
        WHERE status = 'pending' AND expires_at <= ?`
    ).run(now);
  }

  return rows.map((r) => r.id);
}

/**
 * Get all invoices in 'pending' or 'confirming' state (active monitoring targets).
 */
export function getActiveInvoices(): Invoice[] {
  const db = getDB();
  const rows = db
    .prepare(
      `SELECT * FROM invoices WHERE status IN ('pending', 'confirming')`
    )
    .all() as InvoiceRow[];
  return rows.map(rowToInvoice);
}
