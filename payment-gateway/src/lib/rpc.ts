/**
 * AMMOcoin RPC Client — Payment Gateway
 *
 * Adapted from blockchain-explorer/src/lib/rpc.ts with wallet-specific
 * methods required for invoice address generation and payment monitoring.
 */

export interface RPCResponse<T = unknown> {
  result: T;
  error: { code: number; message: string } | null;
  id: string | number;
}

export interface RPCConfig {
  url: string;
  username: string;
  password: string;
}

export interface UnspentOutput {
  txid: string;
  vout: number;
  address: string;
  account?: string;
  scriptPubKey: string;
  amount: number;
  confirmations: number;
  spendable: boolean;
  solvable?: boolean;
}

export interface RawTransaction {
  txid: string;
  hash: string;
  size: number;
  vsize: number;
  version: number;
  locktime: number;
  vin: Array<{
    txid: string;
    vout: number;
    scriptSig: { asm: string; hex: string };
    sequence: number;
  }>;
  vout: Array<{
    value: number;
    n: number;
    scriptPubKey: {
      asm: string;
      hex: string;
      reqSigs?: number;
      type: string;
      addresses?: string[];
    };
  }>;
  blockhash?: string;
  confirmations?: number;
  time?: number;
  blocktime?: number;
}

export class AMMOcoinRPC {
  private config: RPCConfig;
  private requestId = 1;

  constructor(config: RPCConfig) {
    this.config = config;
  }

  /**
   * Make a JSON-RPC call to the AMMOcoin daemon.
   */
  async call<T = unknown>(method: string, params: unknown[] = []): Promise<T> {
    const requestBody = {
      jsonrpc: '1.0',
      id: this.requestId++,
      method,
      params,
    };

    const auth = Buffer.from(
      `${this.config.username}:${this.config.password}`
    ).toString('base64');

    try {
      const response = await fetch(this.config.url, {
        method: 'POST',
        headers: {
          'Content-Type': 'text/plain',
          Authorization: `Basic ${auth}`,
        },
        body: JSON.stringify(requestBody),
      });

      const data: RPCResponse<T> = await response.json().catch(() => {
        throw new Error(
          `RPC request failed: ${response.status} ${response.statusText}`
        );
      });

      if (data.error) {
        throw new Error(`RPC Error ${data.error.code}: ${data.error.message}`);
      }

      return data.result;
    } catch (error) {
      console.error('RPC call failed:', { method, params, error });
      throw error;
    }
  }

  // ── Blockchain info ──────────────────────────────────────────────────

  async getBlockchainInfo(): Promise<{
    chain: string;
    blocks: number;
    headers: number;
    bestblockhash: string;
  }> {
    return this.call('getblockchaininfo');
  }

  async getBlockCount(): Promise<number> {
    return this.call('getblockcount');
  }

  async getConnectionCount(): Promise<number> {
    return this.call('getconnectioncount');
  }

  async getNetworkInfo(): Promise<{ version: number; subversion: string; connections: number }> {
    return this.call('getnetworkinfo');
  }

  // ── Wallet methods (payment gateway specific) ────────────────────────

  /**
   * Generate a new receiving address in the gateway wallet.
   * @param label Optional account/label for the address.
   */
  async getNewAddress(label: string = ''): Promise<string> {
    return this.call<string>('getnewaddress', [label]);
  }

  /**
   * List unspent transaction outputs, optionally filtered to specific addresses.
   * @param minconf Minimum confirmations (default 0 to catch unconfirmed).
   * @param maxconf Maximum confirmations (default 9999999).
   * @param addresses Optional array of addresses to filter.
   */
  async listUnspent(
    minconf: number = 0,
    maxconf: number = 9999999,
    addresses: string[] = []
  ): Promise<UnspentOutput[]> {
    return this.call<UnspentOutput[]>('listunspent', [minconf, maxconf, addresses]);
  }

  /**
   * Get decoded raw transaction with full details.
   */
  async getRawTransaction(txid: string, verbose: boolean = true): Promise<RawTransaction> {
    return this.call<RawTransaction>('getrawtransaction', [txid, verbose]);
  }

  /**
   * Validate an address and return info about it.
   */
  async validateAddress(address: string): Promise<{ isvalid: boolean; address?: string }> {
    return this.call('validateaddress', [address]);
  }

  /**
   * Total spendable wallet balance (whole wallet, "*" account).
   * @param minconf Minimum confirmations to count (default 1).
   */
  async getBalance(minconf: number = 1): Promise<number> {
    return this.call<number>('getbalance', ['*', minconf]);
  }

  /**
   * Send AMMO from the gateway (hot) wallet to a destination address.
   * Returns the broadcast transaction id. Throws an `RPC Error …` if the
   * daemon REJECTS the spend (insufficient funds, bad address, fee, locked
   * wallet) — those throws are pre-broadcast, so the caller can treat them
   * as safe-to-fail. A non-"RPC Error" throw (network/timeout) is ambiguous:
   * the transaction MAY have been broadcast and must not be retried blindly.
   */
  async sendToAddress(
    address: string,
    amount: number,
    comment: string = '',
    commentTo: string = ''
  ): Promise<string> {
    return this.call<string>('sendtoaddress', [address, amount, comment, commentTo]);
  }

  /**
   * Unlock an encrypted wallet for `timeoutSec` seconds (no-op if the wallet
   * is not encrypted — the daemon returns an error, handled by the caller).
   */
  async walletPassphrase(passphrase: string, timeoutSec: number): Promise<void> {
    await this.call('walletpassphrase', [passphrase, timeoutSec]);
  }

  /** Re-lock an encrypted wallet immediately. */
  async walletLock(): Promise<void> {
    await this.call('walletlock');
  }
}

// ── Singleton instance ───────────────────────────────────────────────────

let _rpcClient: AMMOcoinRPC | null = null;

export function getRPCClient(): AMMOcoinRPC {
  if (!_rpcClient) {
    _rpcClient = new AMMOcoinRPC({
      url: process.env.AMMOCOIN_RPC_URL || 'http://localhost:51473',
      username: process.env.AMMOCOIN_RPC_USER || 'gateway',
      password: process.env.AMMOCOIN_RPC_PASSWORD || '',
    });
  }
  return _rpcClient;
}
