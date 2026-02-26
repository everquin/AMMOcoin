/**
 * AMMOcoin RPC Client
 * Connects to AMMOcoin daemon via JSON-RPC
 */

export interface RPCResponse<T = any> {
  result: T;
  error: {
    code: number;
    message: string;
  } | null;
  id: string | number;
}

export interface RPCConfig {
  url: string;
  username: string;
  password: string;
}

export class AMMOcoinRPC {
  private config: RPCConfig;
  private requestId = 1;

  constructor(config: RPCConfig) {
    this.config = config;
  }

  /**
   * Make a JSON-RPC call to the AMMOcoin daemon
   */
  async call<T = any>(method: string, params: any[] = []): Promise<T> {
    const requestBody = {
      jsonrpc: "1.0",
      id: this.requestId++,
      method,
      params,
    };

    const auth = Buffer.from(`${this.config.username}:${this.config.password}`).toString('base64');

    try {
      const response = await fetch(this.config.url, {
        method: 'POST',
        headers: {
          'Content-Type': 'text/plain',
          'Authorization': `Basic ${auth}`,
        },
        body: JSON.stringify(requestBody),
      });

      // Bitcoin/PIVX-based daemons may return 404 for unknown methods
      // or 500 for RPC errors - still try to parse the JSON response
      const data: RPCResponse<T> = await response.json().catch(() => {
        throw new Error(`RPC request failed: ${response.status} ${response.statusText}`);
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

  // Blockchain info methods
  async getBlockchainInfo() {
    return this.call('getblockchaininfo');
  }

  async getNetworkInfo() {
    return this.call('getnetworkinfo');
  }

  async getMiningInfo() {
    return this.call('getmininginfo');
  }

  async getMasternodeCount() {
    return this.call('getmasternodecount');
  }

  // Block methods
  async getBlockCount(): Promise<number> {
    return this.call('getblockcount');
  }

  async getBlockHash(height: number): Promise<string> {
    return this.call('getblockhash', [height]);
  }

  async getBlock(hash: string, verbosity: number = 1) {
    return this.call('getblock', [hash, verbosity]);
  }

  async getBlockByHeight(height: number) {
    const hash = await this.getBlockHash(height);
    return this.getBlock(hash);
  }

  // Transaction methods
  async getRawTransaction(txid: string, verbose: boolean = true, blockHash?: string) {
    const params = [txid, verbose];
    if (blockHash) params.push(blockHash);
    return this.call('getrawtransaction', params);
  }

  async getTxOut(txid: string, vout: number, includeMempool: boolean = true) {
    return this.call('gettxout', [txid, vout, includeMempool]);
  }

  async getTxOutProof(txids: string[], blockHash?: string) {
    const params: any[] = [txids];
    if (blockHash) params.push(blockHash);
    return this.call('gettxoutproof', params);
  }

  // Address methods
  async validateAddress(address: string) {
    return this.call('validateaddress', [address]);
  }

  async getAddressInfo(address: string) {
    return this.call('getaddressinfo', [address]);
  }

  // Mempool methods
  async getMempoolInfo() {
    return this.call('getmempoolinfo');
  }

  async getRawMempool(verbose: boolean = false) {
    return this.call('getrawmempool', [verbose]);
  }

  async getMempoolEntry(txid: string) {
    return this.call('getmempoolentry', [txid]);
  }

  // Utility methods
  async estimateSmartFee(confTarget: number, estimateMode: string = 'CONSERVATIVE') {
    return this.call('estimatesmartfee', [confTarget, estimateMode]);
  }

  async getConnectionCount(): Promise<number> {
    return this.call('getconnectioncount');
  }

  async getPeerInfo() {
    return this.call('getpeerinfo');
  }

  // Sapling/Privacy methods
  async getShieldedBalance(address?: string) {
    return this.call('z_getbalance', address ? [address] : []);
  }

  async listShieldedAddresses() {
    return this.call('z_listaddresses');
  }

  async getShieldedTransaction(txid: string) {
    return this.call('z_gettransaction', [txid]);
  }

  // Masternode methods
  async getMasternodeList(filter: string = 'enabled') {
    return this.call('listmasternodes', [filter]);
  }

  async getMasternodeStatus() {
    return this.call('getmasternodestatus');
  }

  async getMasternodeWinners(blocks?: number, filter?: string) {
    const params = [];
    if (blocks !== undefined) params.push(blocks);
    if (filter !== undefined) params.push(filter);
    return this.call('getmasternodewinners', params);
  }
}

// Create default RPC client instance
export const createRPCClient = (): AMMOcoinRPC => {
  const config: RPCConfig = {
    url: process.env.NEXT_PUBLIC_AMMOCOIN_RPC_URL || 'http://localhost:51473', // AMMOcoin v1.1.0 mainnet RPC port
    username: process.env.NEXT_PUBLIC_AMMOCOIN_RPC_USER || 'explorer',
    password: process.env.NEXT_PUBLIC_AMMOCOIN_RPC_PASSWORD || '',
  };

  return new AMMOcoinRPC(config);
};

export const rpcClient = createRPCClient();