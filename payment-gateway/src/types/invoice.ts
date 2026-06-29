/**
 * AMMOcoin Payment Gateway — Invoice Types
 */

export type InvoiceStatus = 'pending' | 'confirming' | 'confirmed' | 'expired';

export interface Invoice {
  id: string;
  merchant_id: string;
  amount: number;
  memo: string | null;
  metadata: Record<string, unknown> | null;
  address: string;
  status: InvoiceStatus;
  txid: string | null;
  confirmations: number;
  webhook_url: string | null;
  webhook_secret: string | null;
  created_at: string;
  expires_at: string;
  paid_at: string | null;
}

/** Row stored in SQLite (metadata is a JSON string) */
export interface InvoiceRow {
  id: string;
  merchant_id: string;
  amount: number;
  memo: string | null;
  metadata: string | null;
  address: string;
  status: InvoiceStatus;
  txid: string | null;
  confirmations: number;
  webhook_url: string | null;
  webhook_secret: string | null;
  created_at: string;
  expires_at: string;
  paid_at: string | null;
}

export interface CreateInvoiceRequest {
  amount: number;
  memo?: string;
  metadata?: Record<string, unknown>;
  webhook_url?: string;
  webhook_secret?: string;
}

/** Public-facing invoice response (never exposes webhook_secret) */
export interface InvoiceResponse {
  id: string;
  merchant_id: string;
  amount: number;
  memo: string | null;
  metadata: Record<string, unknown> | null;
  address: string;
  status: InvoiceStatus;
  txid: string | null;
  confirmations: number;
  qr_data: string;
  created_at: string;
  expires_at: string;
  paid_at: string | null;
}

export interface WebhookPayload {
  event: 'payment.confirmed' | 'payment.confirming' | 'invoice.expired';
  invoice_id: string;
  txid: string | null;
  amount: number;
  confirmations: number;
  address: string;
}

export interface ApiKey {
  id: string;
  key_hash: string;
  merchant_id: string;
  label: string | null;
  created_at: string;
  revoked_at: string | null;
}
