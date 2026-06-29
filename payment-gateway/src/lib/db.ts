/**
 * AMMOcoin Payment Gateway — SQLite Database Layer
 *
 * Uses better-sqlite3 for synchronous, fast SQLite access.
 * The database file is created automatically on first access.
 */

import Database from 'better-sqlite3';
import path from 'node:path';
import fs from 'node:fs';

const SCHEMA = `
CREATE TABLE IF NOT EXISTS invoices (
  id              TEXT PRIMARY KEY,
  merchant_id     TEXT NOT NULL,
  amount          REAL NOT NULL,
  memo            TEXT,
  metadata        TEXT,
  address         TEXT NOT NULL UNIQUE,
  status          TEXT NOT NULL DEFAULT 'pending',
  txid            TEXT,
  confirmations   INTEGER NOT NULL DEFAULT 0,
  webhook_url     TEXT,
  webhook_secret  TEXT,
  created_at      TEXT NOT NULL DEFAULT (datetime('now')),
  expires_at      TEXT NOT NULL,
  paid_at         TEXT,
  CHECK (status IN ('pending', 'confirming', 'confirmed', 'expired')),
  CHECK (amount > 0)
);

CREATE INDEX IF NOT EXISTS idx_invoices_status ON invoices(status);
CREATE INDEX IF NOT EXISTS idx_invoices_address ON invoices(address);
CREATE INDEX IF NOT EXISTS idx_invoices_merchant ON invoices(merchant_id);

CREATE TABLE IF NOT EXISTS api_keys (
  id          TEXT PRIMARY KEY,
  key_hash    TEXT NOT NULL,
  merchant_id TEXT NOT NULL,
  label       TEXT,
  created_at  TEXT NOT NULL DEFAULT (datetime('now')),
  revoked_at  TEXT
);

CREATE INDEX IF NOT EXISTS idx_api_keys_merchant ON api_keys(merchant_id);

CREATE TABLE IF NOT EXISTS payouts (
  id              TEXT PRIMARY KEY,
  merchant_id     TEXT NOT NULL,
  idempotency_key TEXT NOT NULL,
  address         TEXT NOT NULL,
  amount          REAL NOT NULL,
  memo            TEXT,
  metadata        TEXT,
  status          TEXT NOT NULL DEFAULT 'sending',
  txid            TEXT,
  reason          TEXT,
  created_at      TEXT NOT NULL DEFAULT (datetime('now')),
  completed_at    TEXT,
  CHECK (status IN ('sending', 'sent', 'failed')),
  CHECK (amount > 0)
);

CREATE UNIQUE INDEX IF NOT EXISTS idx_payouts_idem ON payouts(merchant_id, idempotency_key);
CREATE INDEX IF NOT EXISTS idx_payouts_status ON payouts(status);
CREATE INDEX IF NOT EXISTS idx_payouts_merchant ON payouts(merchant_id);
`;

let _db: Database.Database | null = null;

/**
 * Return the singleton database connection, initializing schema on first call.
 */
export function getDB(): Database.Database {
  if (_db) return _db;

  const dbPath = process.env.DATABASE_PATH
    ? path.resolve(process.env.DATABASE_PATH)
    : path.resolve(process.cwd(), 'data', 'gateway.db');

  // Ensure parent directory exists
  const dir = path.dirname(dbPath);
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir, { recursive: true });
  }

  _db = new Database(dbPath);

  // Performance pragmas for server workload
  _db.pragma('journal_mode = WAL');
  _db.pragma('synchronous = NORMAL');
  _db.pragma('foreign_keys = ON');

  // Apply schema
  _db.exec(SCHEMA);

  return _db;
}

/**
 * Close the database connection (for graceful shutdown).
 */
export function closeDB(): void {
  if (_db) {
    _db.close();
    _db = null;
  }
}
