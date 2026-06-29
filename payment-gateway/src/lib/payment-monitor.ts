/**
 * AMMOcoin Payment Gateway — Payment Monitor
 *
 * Polls the AMMOcoin daemon for incoming payments to invoice addresses.
 * Runs as a singleton background loop with a configurable interval.
 *
 * Lifecycle:
 *   pending   → confirming  (unspent output detected at invoice address)
 *   confirming → confirmed  (>= REQUIRED_CONFIRMATIONS reached)
 *   pending   → expired     (past expires_at with no payment)
 */

import { getRPCClient } from './rpc';
import {
  getActiveInvoices,
  markConfirming,
  markConfirmed,
  updateConfirmations,
  expireOverdueInvoices,
} from './invoice-manager';
import { dispatchWebhook } from './webhook-dispatcher';
import type { Invoice, WebhookPayload } from '../types/invoice';

const DEFAULT_POLL_INTERVAL_MS = 15_000;
const DEFAULT_REQUIRED_CONFIRMATIONS = 6;

let _running = false;
let _timer: ReturnType<typeof setTimeout> | null = null;

/**
 * Perform one polling cycle: check pending + confirming invoices, expire stale ones.
 */
async function pollCycle(): Promise<void> {
  const rpc = getRPCClient();
  const requiredConf =
    Number(process.env.REQUIRED_CONFIRMATIONS) || DEFAULT_REQUIRED_CONFIRMATIONS;

  // 1. Expire overdue pending invoices
  const expiredIds = expireOverdueInvoices();
  if (expiredIds.length > 0) {
    console.log(`[monitor] Expired ${expiredIds.length} overdue invoice(s)`);
  }

  // 2. Fetch all active invoices
  const invoices = getActiveInvoices();
  if (invoices.length === 0) return;

  // Gather addresses for pending invoices so we can batch-query
  const pendingInvoices = invoices.filter((i) => i.status === 'pending');
  const confirmingInvoices = invoices.filter((i) => i.status === 'confirming');

  // 3. Check pending invoices for new payments via listunspent
  if (pendingInvoices.length > 0) {
    const addresses = pendingInvoices.map((i) => i.address);
    try {
      const utxos = await rpc.listUnspent(0, 9999999, addresses);

      for (const invoice of pendingInvoices) {
        // Find UTXOs paying to this invoice's address with sufficient amount
        const matching = utxos.filter((u) => u.address === invoice.address);
        const totalReceived = matching.reduce((sum, u) => sum + u.amount, 0);

        if (totalReceived >= invoice.amount && matching.length > 0) {
          // Use the first matching UTXO's txid
          const txid = matching[0].txid;
          const confirmations = matching[0].confirmations;

          console.log(
            `[monitor] Payment detected for invoice ${invoice.id}: txid=${txid}, amount=${totalReceived}, confs=${confirmations}`
          );

          if (confirmations >= requiredConf) {
            // Already has enough confirmations — jump straight to confirmed
            markConfirming(invoice.id, txid);
            markConfirmed(invoice.id, confirmations);
            await sendWebhook(invoice, 'payment.confirmed', txid, confirmations);
          } else {
            markConfirming(invoice.id, txid);
            await sendWebhook(invoice, 'payment.confirming', txid, confirmations);
          }
        }
      }
    } catch (err) {
      console.error('[monitor] Failed to query unspent outputs:', err);
    }
  }

  // 4. Check confirming invoices for updated confirmation count
  for (const invoice of confirmingInvoices) {
    if (!invoice.txid) continue;

    try {
      const tx = await rpc.getRawTransaction(invoice.txid, true);
      const confirmations = tx.confirmations ?? 0;

      if (confirmations !== invoice.confirmations) {
        updateConfirmations(invoice.id, confirmations);
      }

      if (confirmations >= requiredConf && invoice.status === 'confirming') {
        markConfirmed(invoice.id, confirmations);
        console.log(
          `[monitor] Invoice ${invoice.id} confirmed with ${confirmations} confirmations`
        );
        await sendWebhook(invoice, 'payment.confirmed', invoice.txid, confirmations);
      }
    } catch (err) {
      console.error(
        `[monitor] Failed to check tx ${invoice.txid} for invoice ${invoice.id}:`,
        err
      );
    }
  }
}

/**
 * Send a webhook to the merchant if configured.
 */
async function sendWebhook(
  invoice: Invoice,
  event: WebhookPayload['event'],
  txid: string | null,
  confirmations: number
): Promise<void> {
  if (!invoice.webhook_url || !invoice.webhook_secret) return;

  const payload: WebhookPayload = {
    event,
    invoice_id: invoice.id,
    txid,
    amount: invoice.amount,
    confirmations,
    address: invoice.address,
  };

  // Fire-and-forget — dispatchWebhook handles retries internally
  dispatchWebhook(invoice.webhook_url, invoice.webhook_secret, payload).catch(
    (err) =>
      console.error(
        `[monitor] Webhook dispatch error for invoice ${invoice.id}:`,
        err
      )
  );
}

/**
 * Start the payment monitor background loop.
 */
export function startMonitor(): void {
  if (_running) return;
  _running = true;

  const intervalMs =
    Number(process.env.POLL_INTERVAL_MS) || DEFAULT_POLL_INTERVAL_MS;

  console.log(`[monitor] Starting payment monitor (interval=${intervalMs}ms)`);

  async function loop(): Promise<void> {
    if (!_running) return;

    try {
      await pollCycle();
    } catch (err) {
      console.error('[monitor] Unhandled error in poll cycle:', err);
    }

    if (_running) {
      _timer = setTimeout(loop, intervalMs);
    }
  }

  // Run the first cycle immediately
  loop();
}

/**
 * Stop the payment monitor.
 */
export function stopMonitor(): void {
  _running = false;
  if (_timer) {
    clearTimeout(_timer);
    _timer = null;
  }
  console.log('[monitor] Payment monitor stopped');
}
