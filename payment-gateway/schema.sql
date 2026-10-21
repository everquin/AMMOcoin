-- AMMOcoin Payment Gateway — SQLite Schema

CREATE TABLE IF NOT EXISTS invoices (
  id              TEXT PRIMARY KEY,                -- UUID v4
  merchant_id     TEXT NOT NULL,                   -- merchant identifier from api_keys
  amount          REAL NOT NULL,                   -- AMMO amount requested
  memo            TEXT,                            -- optional memo / description
  metadata        TEXT,                            -- arbitrary JSON from merchant
  address         TEXT NOT NULL UNIQUE,             -- unique receive address
  status          TEXT NOT NULL DEFAULT 'pending', -- pending | confirming | confirmed | expired
  txid            TEXT,                            -- blockchain transaction id once detected
  confirmations   INTEGER NOT NULL DEFAULT 0,      -- current confirmation count
  webhook_url     TEXT,                            -- merchant callback URL
  webhook_secret  TEXT,                            -- HMAC secret for signing webhook payloads
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
  id          TEXT PRIMARY KEY,                -- UUID v4
  key_hash    TEXT NOT NULL,                   -- bcrypt hash of the API key
  merchant_id TEXT NOT NULL,                   -- merchant identifier
  label       TEXT,                            -- human-readable label
  created_at  TEXT NOT NULL DEFAULT (datetime('now')),
  revoked_at  TEXT                             -- NULL if active, timestamp if revoked
);

CREATE INDEX IF NOT EXISTS idx_api_keys_merchant ON api_keys(merchant_id);

CREATE TABLE IF NOT EXISTS payouts (
  id              TEXT PRIMARY KEY,                -- UUID v4
  merchant_id     TEXT NOT NULL,                   -- merchant identifier from api_keys
  idempotency_key TEXT NOT NULL,                   -- merchant-unique; replays never re-broadcast
  address         TEXT NOT NULL,                   -- destination AMMO address
  amount          REAL NOT NULL,                   -- AMMO amount sent
  memo            TEXT,                            -- optional memo (passed as the tx comment)
  metadata        TEXT,                            -- arbitrary JSON from merchant
  status          TEXT NOT NULL DEFAULT 'sending', -- sending | sent | failed
  txid            TEXT,                            -- broadcast transaction id once sent
  reason          TEXT,                            -- failure reason when status='failed'
  created_at      TEXT NOT NULL DEFAULT (datetime('now')),
  completed_at    TEXT,

  CHECK (status IN ('sending', 'sent', 'failed')),
  CHECK (amount > 0)
);

CREATE UNIQUE INDEX IF NOT EXISTS idx_payouts_idem ON payouts(merchant_id, idempotency_key);
CREATE INDEX IF NOT EXISTS idx_payouts_status ON payouts(status);
CREATE INDEX IF NOT EXISTS idx_payouts_merchant ON payouts(merchant_id);
