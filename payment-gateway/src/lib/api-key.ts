/**
 * AMMOcoin Payment Gateway — API Key Management
 *
 * Generates bearer tokens for merchants and validates them via bcrypt.
 */

import { randomBytes } from 'node:crypto';
import { v4 as uuidv4 } from 'uuid';
import bcrypt from 'bcryptjs';
import { getDB } from './db';
import type { ApiKey } from '../types/invoice';

const BCRYPT_ROUNDS = 12;

/** Prefix makes keys recognizable in logs / env vars. */
const KEY_PREFIX = 'ammo_live_';

/**
 * Generate a new API key for a merchant.
 * Returns the plaintext key (show once to the merchant) and the stored record.
 */
export async function generateApiKey(
  merchantId: string,
  label?: string
): Promise<{ plaintextKey: string; record: ApiKey }> {
  const rawKey = randomBytes(32).toString('hex');
  const plaintextKey = `${KEY_PREFIX}${rawKey}`;
  const keyHash = await bcrypt.hash(plaintextKey, BCRYPT_ROUNDS);
  const id = uuidv4();

  const db = getDB();
  db.prepare(
    `INSERT INTO api_keys (id, key_hash, merchant_id, label)
     VALUES (?, ?, ?, ?)`
  ).run(id, keyHash, merchantId, label ?? null);

  const record = db
    .prepare('SELECT * FROM api_keys WHERE id = ?')
    .get(id) as ApiKey;

  return { plaintextKey, record };
}

/**
 * Validate a bearer token against all active (non-revoked) keys.
 * Returns the matching ApiKey row, or null if invalid.
 */
export async function validateApiKey(
  bearerToken: string
): Promise<ApiKey | null> {
  if (!bearerToken.startsWith(KEY_PREFIX)) return null;

  const db = getDB();
  const keys = db
    .prepare('SELECT * FROM api_keys WHERE revoked_at IS NULL')
    .all() as ApiKey[];

  for (const key of keys) {
    const match = await bcrypt.compare(bearerToken, key.key_hash);
    if (match) return key;
  }

  return null;
}

/**
 * Revoke an API key by its id.
 */
export function revokeApiKey(keyId: string): void {
  const db = getDB();
  db.prepare(
    `UPDATE api_keys SET revoked_at = datetime('now') WHERE id = ?`
  ).run(keyId);
}
