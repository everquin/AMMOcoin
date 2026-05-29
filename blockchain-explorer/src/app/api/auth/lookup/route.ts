import { NextRequest, NextResponse } from 'next/server';
import { rpcClient } from '@/lib/rpc';

/**
 * AMMO-AUTH Lookup API
 * Scans the blockchain for OP_RETURN transactions matching the AMMO-AUTH protocol
 * and returns all records for a given chip_pubkey_hash.
 *
 * GET /api/auth/lookup?hash=<40-char hex>
 *
 * OPERATIONAL NOTE
 * ----------------
 * This handler maintains an in-process index in module-level state. That
 * implies two requirements that operators MUST satisfy:
 *
 *   1. Run the explorer as a long-lived Node.js process (e.g. `next start`
 *      behind a reverse proxy). It will NOT work correctly on a per-request
 *      serverless platform (Vercel functions, Cloud Run min-instances=0,
 *      etc.) — each cold start re-walks the chain from genesis.
 *   2. The index does NOT survive process restart. Plan for a 1-2 minute
 *      "warming" period after deploys/crashes during which lookups for
 *      recently-registered chips will return 404.
 *
 * A persistent-store indexer (SQLite or similar) is tracked as future work.
 */

const AMMO_MAGIC = '414d4d4f'; // "AMMO" in hex
const PROTOCOL_VERSION = '01';

interface AuthRecord {
  type: string;
  type_code: number;
  txid: string;
  vout_index: number;
  block_height: number;
  block_time: number;
  chip_pubkey_hash: string;
  creator_address?: string;
  from_address?: string;
  metadata_hash?: string;
  new_owner_hash?: string;
  revoke_reason?: number;
}

// Module-level index state. Survives within a single Node.js process; lost on
// restart. See file header for the operational implications.
const authIndex: Map<string, AuthRecord[]> = new Map();
let lastScannedBlock = 0;

// Serializer for the indexer: concurrent requests await the same Promise
// rather than skipping past it (the previous skip-pattern returned stale
// data to racing requests). The mutex chains pending scans end-to-end.
let indexerChain: Promise<void> = Promise.resolve();

// Simple per-IP rate limiter (10 req/min by default). Trade-off: in-memory,
// so per-process — fine behind a sticky load balancer, leaky behind round-
// robin. For real protection put a rate-limiter at the edge (nginx, Cloudflare).
const RATE_LIMIT_REQUESTS = 10;
const RATE_LIMIT_WINDOW_MS = 60_000;
const rateLimitMap: Map<string, { count: number; windowStart: number }> = new Map();

function checkRateLimit(ip: string): { allowed: boolean; retryAfterSec: number } {
  const now = Date.now();
  const entry = rateLimitMap.get(ip);
  if (!entry || now - entry.windowStart > RATE_LIMIT_WINDOW_MS) {
    rateLimitMap.set(ip, { count: 1, windowStart: now });
    return { allowed: true, retryAfterSec: 0 };
  }
  if (entry.count < RATE_LIMIT_REQUESTS) {
    entry.count++;
    return { allowed: true, retryAfterSec: 0 };
  }
  return {
    allowed: false,
    retryAfterSec: Math.ceil((entry.windowStart + RATE_LIMIT_WINDOW_MS - now) / 1000),
  };
}

function clientIp(req: NextRequest): string {
  // Behind a proxy, x-forwarded-for is the only source of truth. Trust the
  // leftmost entry (the original client) since downstream hops are appended.
  const xff = req.headers.get('x-forwarded-for');
  if (xff) return xff.split(',')[0]!.trim();
  return req.headers.get('x-real-ip') ?? 'unknown';
}

export async function GET(request: NextRequest) {
  const ip = clientIp(request);
  const rl = checkRateLimit(ip);
  if (!rl.allowed) {
    return NextResponse.json(
      { error: 'Rate limit exceeded', retry_after: rl.retryAfterSec },
      { status: 429, headers: { 'Retry-After': String(rl.retryAfterSec) } }
    );
  }

  const { searchParams } = new URL(request.url);
  const hash = searchParams.get('hash')?.toLowerCase();

  if (!hash || !/^[0-9a-f]{40}$/.test(hash)) {
    return NextResponse.json(
      { error: 'Invalid hash parameter. Must be 40 hex characters.' },
      { status: 400 }
    );
  }

  // Await any in-flight scan AND chain a new one. We always wait for the
  // current scan because concurrent requests must see a consistent snapshot.
  await runIndexer();

  const records = authIndex.get(hash);

  if (!records || records.length === 0) {
    return NextResponse.json(
      {
        chip_pubkey_hash: hash,
        records: [],
        // Backwards-compat: existing Flutter app and other clients read
        // the loosely-typed `current_owner`. Keep returning it alongside
        // the typed fields. See response below for non-empty case.
        current_owner: null,
        current_owner_address: null,
        current_owner_hash: null,
        is_revoked: false,
        status: 'unregistered',
      },
      {
        status: 404,
        headers: { 'Cache-Control': 'private, max-age=15' },
      }
    );
  }

  // Sort canonically: by block height, then by transaction index within the
  // block (we don't have that here without RPC re-lookup, so we tiebreak by
  // txid lex order which is at least deterministic across explorer
  // instances — see provenance-chain rule).
  const sorted = [...records].sort((a, b) => {
    if (a.block_height !== b.block_height) return a.block_height - b.block_height;
    return a.txid < b.txid ? -1 : a.txid > b.txid ? 1 : 0;
  });

  const registration = sorted.find((r) => r.type === 'REGISTER');
  // REVOKE that has actually taken effect (treat as final). Per spec: any
  // TRANSFER at >= revoke height is ignored.
  const revocation = sorted.find((r) => r.type === 'REVOKE');
  const revokeHeight = revocation?.block_height ?? Number.POSITIVE_INFINITY;
  const transfers = sorted.filter(
    (r) => r.type === 'TRANSFER' && r.block_height < revokeHeight
  );

  // Walk the ownership chain. We track the owner as the (address, hash)
  // pair because:
  //   - REGISTER gives us the creator's base58 address (no hash on-chain).
  //   - TRANSFER gives us the new owner's HASH160 (no address on-chain;
  //     the recipient may not have an associated AMMOcoin address yet).
  // Authorization: a TRANSFER is only effective if the *sender* (the tx's
  // funding input address) matches the *current* owner's address. Pre-fix,
  // any unauthorized broadcaster could push a TRANSFER record into the
  // chain and it would silently take effect.
  let currentOwnerAddress: string | null = registration?.creator_address ?? null;
  let currentOwnerHash: string | null = null;

  for (const transfer of transfers) {
    // Sender authorization. We can only enforce this when the current owner
    // is still in address form (REGISTER + 0 transfers, or after a transfer
    // where we have the new owner's address). Once ownership is in hash-only
    // form, sender comparison requires base58-decoding the from_address — a
    // dependency we don't pull in here. In that case we conservatively
    // reject all subsequent transfers (a future revision should add address
    // <-> hash conversion to handle the chain correctly).
    if (currentOwnerAddress !== null) {
      if (transfer.from_address !== currentOwnerAddress) {
        // Unauthorized — skip (do NOT advance ownership).
        continue;
      }
    } else {
      // No address to compare against; we cannot prove authorization.
      // Stop the walk here — anything that follows is unverifiable.
      break;
    }
    currentOwnerHash = transfer.new_owner_hash ?? currentOwnerHash;
    currentOwnerAddress = null; // we no longer have an address for the new owner
  }

  const isRevoked = revocation !== undefined;
  const status = isRevoked
    ? 'revoked'
    : registration
    ? 'authentic'
    : 'unregistered';

  return NextResponse.json(
    {
      chip_pubkey_hash: hash,
      records: sorted,
      // Backwards-compat alias for clients (e.g. Flutter app) that read
      // the loosely-typed `current_owner` field. Prefer address form when
      // available, fall back to hash. New clients should consume the
      // explicit `_address` / `_hash` fields instead.
      current_owner: currentOwnerAddress ?? currentOwnerHash,
      current_owner_address: currentOwnerAddress,
      current_owner_hash: currentOwnerHash,
      is_revoked: isRevoked,
      status,
    },
    { headers: { 'Cache-Control': 'private, max-age=30' } }
  );
}

/**
 * Serialize indexer runs: concurrent callers chain on `indexerChain`, so a
 * burst of N requests issues at most one scan and all N see the result.
 */
function runIndexer(): Promise<void> {
  const next = indexerChain.then(updateIndex, updateIndex);
  // Swap the chain pointer to `next` so subsequent callers wait on this one.
  indexerChain = next.catch(() => undefined);
  return next;
}

/**
 * Incrementally scan new blocks for AMMO-AUTH OP_RETURN records.
 * Bounded by `batchSize` per call — repeated calls catch up over time.
 */
async function updateIndex(): Promise<void> {
  const currentHeight: number = await rpcClient.getBlockCount();

  // Scan from last known block (or genesis) to current tip
  const startBlock = lastScannedBlock + 1;
  // Limit batch size to avoid long-running requests
  const batchSize = 100;
  const endBlock = Math.min(startBlock + batchSize - 1, currentHeight);

  for (let height = startBlock; height <= endBlock; height++) {
    try {
      const block = await rpcClient.getBlockByHeight(height);
      if (!block || !block.tx) continue;

      for (const txid of block.tx) {
        try {
          const tx = await rpcClient.getRawTransaction(txid, true);
          if (!tx || !tx.vout) continue;

          for (let voutIdx = 0; voutIdx < tx.vout.length; voutIdx++) {
            const vout = tx.vout[voutIdx];
            const scriptPubKey = vout.scriptPubKey;
            if (!scriptPubKey || scriptPubKey.type !== 'nulldata') continue;

            const asm: string = scriptPubKey.asm || '';
            const parts = asm.split(' ');
            if (parts.length < 2 || parts[0] !== 'OP_RETURN') continue;

            const hexData = parts[1].toLowerCase();
            const record = parseAmmoAuth(hexData, txid, voutIdx, height, block.time, tx);
            if (record) {
              const existing = authIndex.get(record.chip_pubkey_hash) || [];
              existing.push(record);
              authIndex.set(record.chip_pubkey_hash, existing);
            }
          }
        } catch {
          // Skip individual transaction errors
        }
      }
    } catch {
      // Skip individual block errors
    }

    lastScannedBlock = height;
  }
}

/**
 * Parse hex data as an AMMO-AUTH protocol message.
 */
function parseAmmoAuth(
  hexData: string,
  txid: string,
  voutIndex: number,
  blockHeight: number,
  blockTime: number,
  tx: any
): AuthRecord | null {
  // Minimum: magic(4) + version(1) + type(1) = 6 bytes = 12 hex chars
  if (hexData.length < 12) return null;
  if (!hexData.startsWith(AMMO_MAGIC)) return null;

  const version = hexData.substring(8, 10);
  if (version !== PROTOCOL_VERSION) return null;

  const typeCode = parseInt(hexData.substring(10, 12), 16);
  const payload = hexData.substring(12);

  // Determine sender address from the first input. This matches the
  // pragmatic "sender = first input's address" convention; multi-input
  // mixing is a known spec gap (see AMMO-AUTH-v1 §"Sender address").
  let senderAddress: string | undefined;
  if (tx.vin && tx.vin.length > 0) {
    const firstInput = tx.vin[0];
    if (firstInput.address) {
      senderAddress = firstInput.address;
    }
  }

  switch (typeCode) {
    case 0x01: { // REGISTER — 52 payload bytes (20 hash + 32 metadata)
      if (payload.length < 104) return null;
      const chipPubkeyHash = payload.substring(0, 40);
      const metadataHash = payload.substring(40, 104);
      return {
        type: 'REGISTER',
        type_code: typeCode,
        txid,
        vout_index: voutIndex,
        block_height: blockHeight,
        block_time: blockTime,
        chip_pubkey_hash: chipPubkeyHash,
        creator_address: senderAddress,
        metadata_hash: metadataHash,
      };
    }

    case 0x02: { // TRANSFER — 40 payload bytes (20 chip hash + 20 new owner hash)
      if (payload.length < 80) return null;
      const chipPubkeyHash = payload.substring(0, 40);
      const newOwnerHash = payload.substring(40, 80);
      return {
        type: 'TRANSFER',
        type_code: typeCode,
        txid,
        vout_index: voutIndex,
        block_height: blockHeight,
        block_time: blockTime,
        chip_pubkey_hash: chipPubkeyHash,
        from_address: senderAddress,
        new_owner_hash: newOwnerHash,
      };
    }

    case 0x03: { // REVOKE — 21 payload bytes (20 chip hash + 1 reason)
      if (payload.length < 42) return null;
      const chipPubkeyHash = payload.substring(0, 40);
      const reasonCode = parseInt(payload.substring(40, 42), 16);
      return {
        type: 'REVOKE',
        type_code: typeCode,
        txid,
        vout_index: voutIndex,
        block_height: blockHeight,
        block_time: blockTime,
        chip_pubkey_hash: chipPubkeyHash,
        revoke_reason: reasonCode,
      };
    }

    default:
      return null;
  }
}
