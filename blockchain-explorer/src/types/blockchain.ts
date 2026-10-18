// AMMOcoin Blockchain Explorer Types

export interface Block {
  hash: string;
  height: number;
  timestamp: number;
  size: number;
  transactionCount: number;
  difficulty: number;
  nonce: number;
  merkleRoot: string;
  previousBlockHash?: string;
  nextBlockHash?: string;
  confirmations: number;
  reward: number;
  fees: number;
  version: number;
  bits: string;
  chainwork: string;
  miner?: string;
}

export interface Transaction {
  txid: string;
  version: number;
  locktime: number;
  size: number;
  vsize: number;
  weight: number;
  fee: number;
  timestamp: number;
  blockHash?: string;
  blockHeight?: number;
  confirmations: number;
  status: 'confirmed' | 'pending' | 'failed';
  inputs: TransactionInput[];
  outputs: TransactionOutput[];
  totalInput: number;
  totalOutput: number;
}

export interface TransactionInput {
  txid: string;
  vout: number;
  scriptSig: {
    asm: string;
    hex: string;
  };
  sequence: number;
  witness?: string[];
  address?: string;
  value?: number;
  prevout?: TransactionOutput;
}

export interface TransactionOutput {
  value: number;
  n: number;
  scriptPubKey: {
    asm: string;
    hex: string;
    type: string;
    addresses?: string[];
    address?: string;
  };
  spent?: boolean;
  spentTxid?: string;
  spentIndex?: number;
}

export interface Address {
  address: string;
  type: 'pubkeyhash' | 'scripthash' | 'witness_v0_keyhash' | 'witness_v0_scripthash' | 'unknown';
  balance: number;
  totalReceived: number;
  totalSent: number;
  transactionCount: number;
  unconfirmedBalance: number;
  firstSeen?: number;
  lastSeen?: number;
  utxos: UTXO[];
}

export interface UTXO {
  txid: string;
  vout: number;
  value: number;
  confirmations: number;
  height: number;
  scriptPubKey: string;
  address: string;
}

export interface NetworkStats {
  height: number;
  difficulty: number;
  hashrate: number;
  totalSupply: number;
  circulatingSupply: number;
  // No price or market-cap fields: the explorer shows no price, market cap or fiat
  // value for AMMO (docs/compliance AMMO-P-03, AMMO-D-2026-10-17-09).
  nodes: number;
  mempool: {
    size: number;
    bytes: number;
    usage: number;
    maxmempool: number;
    mempoolminfee: number;
  };
  blockchain: {
    chain: string;
    blocks: number;
    headers: number;
    bestblockhash: string;
    mediantime: number;
    verificationprogress: number;
    chainwork: string;
    size_on_disk: number;
  };
}

export interface MempoolTransaction {
  txid: string;
  fee: number;
  feeRate: number;
  size: number;
  vsize: number;
  weight: number;
  time: number;
  height: number;
  descendantcount: number;
  descendantsize: number;
  ancestorcount: number;
  ancestorsize: number;
  wtxid: string;
  depends: string[];
  spentby: string[];
}

export interface SearchResult {
  type: 'block' | 'transaction' | 'address';
  data: Block | Transaction | Address;
}

export interface PaginatedResponse<T> {
  data: T[];
  total: number;
  page: number;
  limit: number;
  hasNext: boolean;
  hasPrevious: boolean;
}

export interface ChartDataPoint {
  timestamp: number;
  value: number;
  label?: string;
}

// API Response types
export interface ApiResponse<T = any> {
  success: boolean;
  data?: T;
  error?: string;
  message?: string;
}

export interface BlocksResponse extends ApiResponse {
  data: {
    blocks: Block[];
    total: number;
    page: number;
    limit: number;
  };
}

export interface TransactionsResponse extends ApiResponse {
  data: {
    transactions: Transaction[];
    total: number;
    page: number;
    limit: number;
  };
}

// Rich list and top addresses
export interface RichListEntry {
  address: string;
  balance: number;
  percentage: number;
  rank: number;
  label?: string;
  type?: 'exchange' | 'whale' | 'contract' | 'unknown';
}

// Staking information (specific to AMMOcoin PoS)
export interface StakingInfo {
  enabled: boolean;
  staking: boolean;
  errors: string;
  currentblocktx: number;
  pooledtx: number;
  difficulty: number;
  'search-interval': number;
  weight: number;
  netstakeweight: number;
  expectedtime: number;
}

// Masternode information (specific to AMMOcoin)
export interface Masternode {
  txhash: string;
  outputidx: number;
  netaddr: string;
  addr: string;
  status: string;
  message: string;
  version: number;
  lastseen: number;
  activetime: number;
  rank: number;
  protocol: number;
}

export interface MasternodeStats {
  total: number;
  enabled: number;
  qualified: number;
  total_collateral: number;
  avg_block_time: number;
  reward_frequency: number;
}

// Privacy transaction types (Sapling support)
export interface PrivacyTransaction {
  txid: string;
  type: 'transparent' | 'shielded' | 'mixed';
  shieldedInputs: number;
  shieldedOutputs: number;
  transparentInputs: number;
  transparentOutputs: number;
  shieldedValue?: number;
  transparentValue: number;
  fee: number;
  timestamp: number;
  blockHeight?: number;
  confirmations: number;
}

// Export utility types
export type TransactionStatus = Transaction['status'];
export type AddressType = Address['type'];
export type SearchType = SearchResult['type'];