/**
 * AMMOcoin Payment Gateway — Webhook Dispatcher
 *
 * Sends HMAC-SHA256-signed payloads to merchant callback URLs
 * with exponential-backoff retries.
 */

import { createHmac } from 'node:crypto';
import type { WebhookPayload } from '../types/invoice';

const DEFAULT_TIMEOUT_MS = 10_000;
const DEFAULT_MAX_RETRIES = 5;

/**
 * Sign a JSON payload string with HMAC-SHA256.
 * Returns the signature in the format `sha256=<hex>`.
 */
export function signPayload(payload: string, secret: string): string {
  const hmac = createHmac('sha256', secret);
  hmac.update(payload, 'utf-8');
  return `sha256=${hmac.digest('hex')}`;
}

/**
 * Dispatch a webhook to the merchant.
 * Retries up to MAX_RETRIES times with exponential backoff.
 *
 * @returns true if delivered successfully (2xx), false otherwise.
 */
export async function dispatchWebhook(
  url: string,
  secret: string,
  payload: WebhookPayload
): Promise<boolean> {
  const maxRetries =
    Number(process.env.WEBHOOK_MAX_RETRIES) || DEFAULT_MAX_RETRIES;
  const timeoutMs =
    Number(process.env.WEBHOOK_TIMEOUT_MS) || DEFAULT_TIMEOUT_MS;

  const body = JSON.stringify(payload);
  const signature = signPayload(body, secret);

  for (let attempt = 0; attempt <= maxRetries; attempt++) {
    try {
      const controller = new AbortController();
      const timer = setTimeout(() => controller.abort(), timeoutMs);

      const response = await fetch(url, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'X-AMMO-Signature': signature,
          'X-AMMO-Event': payload.event,
        },
        body,
        signal: controller.signal,
      });

      clearTimeout(timer);

      if (response.ok) {
        console.log(
          `[webhook] Delivered ${payload.event} for invoice ${payload.invoice_id} to ${url} (attempt ${attempt + 1})`
        );
        return true;
      }

      console.warn(
        `[webhook] Non-2xx response (${response.status}) from ${url} — attempt ${attempt + 1}/${maxRetries + 1}`
      );
    } catch (err) {
      console.warn(
        `[webhook] Request failed for ${url} — attempt ${attempt + 1}/${maxRetries + 1}:`,
        err instanceof Error ? err.message : err
      );
    }

    // Exponential backoff: 1s, 2s, 4s, 8s, 16s …
    if (attempt < maxRetries) {
      const delayMs = Math.pow(2, attempt) * 1000;
      await new Promise((resolve) => setTimeout(resolve, delayMs));
    }
  }

  console.error(
    `[webhook] Exhausted all retries for invoice ${payload.invoice_id} → ${url}`
  );
  return false;
}
