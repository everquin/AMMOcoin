#!/usr/bin/env node
/**
 * Mint a gateway API key directly into the SQLite DB.
 *
 * Mirrors src/lib/api-key.ts (bcrypt hash, ammo_live_ prefix) but standalone
 * so test/ops scripts can create a key without the Next.js runtime. Ensures
 * the minimal schema exists, then prints the PLAINTEXT key to stdout (only
 * shown once — capture it).
 *
 *   DATABASE_PATH=./data/regtest.db MERCHANT_ID=glibz node scripts/create-api-key.mjs
 */
import Database from 'better-sqlite3';
import bcrypt from 'bcryptjs';
import { randomBytes, randomUUID } from 'node:crypto';
import path from 'node:path';
import fs from 'node:fs';

const KEY_PREFIX = 'ammo_live_';
const BCRYPT_ROUNDS = 12;

const dbPath = process.env.DATABASE_PATH
  ? path.resolve(process.env.DATABASE_PATH)
  : path.resolve(process.cwd(), 'data', 'gateway.db');
const merchantId = process.env.MERCHANT_ID || 'merchant';
const label = process.env.KEY_LABEL || 'script-generated';

fs.mkdirSync(path.dirname(dbPath), { recursive: true });

const db = new Database(dbPath);
db.exec(`
  CREATE TABLE IF NOT EXISTS api_keys (
    id TEXT PRIMARY KEY, key_hash TEXT NOT NULL, merchant_id TEXT NOT NULL,
    label TEXT, created_at TEXT NOT NULL DEFAULT (datetime('now')), revoked_at TEXT
  );
`);

const rawKey = randomBytes(32).toString('hex');
const plaintextKey = `${KEY_PREFIX}${rawKey}`;
const keyHash = bcrypt.hashSync(plaintextKey, BCRYPT_ROUNDS);

db.prepare(
  'INSERT INTO api_keys (id, key_hash, merchant_id, label) VALUES (?, ?, ?, ?)'
).run(randomUUID(), keyHash, merchantId, label);

// Plaintext key on stdout; everything else to stderr so callers can capture it.
process.stderr.write(`Created API key for merchant "${merchantId}" in ${dbPath}\n`);
process.stdout.write(plaintextKey + '\n');
