/**
 * AMMOcoin Payment Gateway — Next.js Middleware
 *
 * Validates Bearer API key from the Authorization header for all
 * protected routes. The /api/health endpoint is public.
 */

import { NextRequest, NextResponse } from 'next/server';
import { validateApiKey } from './lib/api-key';

/** Routes that do NOT require authentication. */
const PUBLIC_PATHS = ['/api/health'];

export async function middleware(request: NextRequest) {
  const { pathname } = request.nextUrl;

  // Allow public endpoints through without auth
  if (PUBLIC_PATHS.some((p) => pathname.startsWith(p))) {
    return NextResponse.next();
  }

  // Only gate /api/* routes
  if (!pathname.startsWith('/api/')) {
    return NextResponse.next();
  }

  const authHeader = request.headers.get('authorization');
  if (!authHeader || !authHeader.startsWith('Bearer ')) {
    return NextResponse.json(
      { error: 'Missing or malformed Authorization header. Expected: Bearer <api_key>' },
      { status: 401 }
    );
  }

  const token = authHeader.slice(7); // strip "Bearer "

  try {
    const apiKey = await validateApiKey(token);
    if (!apiKey) {
      return NextResponse.json(
        { error: 'Invalid or revoked API key' },
        { status: 403 }
      );
    }

    // Attach merchant_id to a custom header so route handlers can read it
    const response = NextResponse.next();
    response.headers.set('x-merchant-id', apiKey.merchant_id);

    // Also forward via request headers for route handler access
    const requestHeaders = new Headers(request.headers);
    requestHeaders.set('x-merchant-id', apiKey.merchant_id);

    return NextResponse.next({
      request: { headers: requestHeaders },
    });
  } catch (err) {
    console.error('[middleware] API key validation error:', err);
    return NextResponse.json(
      { error: 'Internal authentication error' },
      { status: 500 }
    );
  }
}

export const config = {
  matcher: '/api/:path*',
};
