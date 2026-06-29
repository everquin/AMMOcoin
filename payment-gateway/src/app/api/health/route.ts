/**
 * GET /api/health — Public health check endpoint
 *
 * Returns gateway status, RPC connectivity, and database health.
 */

import { NextResponse } from 'next/server';
import { getRPCClient } from '@/lib/rpc';
import { getDB } from '@/lib/db';

export async function GET() {
  const checks: Record<string, unknown> = {
    status: 'ok',
    timestamp: new Date().toISOString(),
    version: '1.0.0',
  };

  // Check database
  try {
    const db = getDB();
    const row = db.prepare("SELECT COUNT(*) as count FROM invoices").get() as { count: number };
    checks.database = { status: 'ok', invoices: row.count };
  } catch (err) {
    checks.database = { status: 'error', message: err instanceof Error ? err.message : 'unknown' };
    checks.status = 'degraded';
  }

  // Check RPC connectivity
  try {
    const rpc = getRPCClient();
    const info = await rpc.getBlockchainInfo();
    checks.rpc = {
      status: 'ok',
      chain: info.chain,
      blocks: info.blocks,
      headers: info.headers,
    };
  } catch (err) {
    checks.rpc = { status: 'error', message: err instanceof Error ? err.message : 'unknown' };
    checks.status = 'degraded';
  }

  const httpStatus = checks.status === 'ok' ? 200 : 503;
  return NextResponse.json(checks, { status: httpStatus });
}
