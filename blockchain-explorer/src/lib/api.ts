/**
 * AMMOcoin Blockchain API Service
 * High-level service functions for the explorer frontend
 */

import { rpcClient } from './rpc';
import type { Block, Transaction, Address, NetworkStats, TransactionInput, TransactionOutput } from '@/types/blockchain';

// Cache for frequently accessed data
const cache = new Map();
const CACHE_TTL = 30000; // 30 seconds

function getCached<T>(key: string): T | null {
  const item = cache.get(key);
  if (item && Date.now() - item.timestamp < CACHE_TTL) {
    return item.data;
  }
  cache.delete(key);
  return null;
}

function setCache<T>(key: string, data: T): void {
  cache.set(key, { data, timestamp: Date.now() });
}

/**
 * Get current blockchain statistics
 */
export async function getNetworkStats(): Promise<NetworkStats> {
  const cacheKey = 'network-stats';
  const cached = getCached<NetworkStats>(cacheKey);
  if (cached) return cached;

  try {
    // Use Promise.allSettled to handle methods that may not exist in this fork
    const results = await Promise.allSettled([
      rpcClient.getBlockchainInfo(),
      rpcClient.getNetworkInfo(),
      rpcClient.getMiningInfo().catch(() => ({ networkhashps: 0 })),
      rpcClient.getMasternodeCount().catch(() => ({ total: 0, enabled: 0 })),
      rpcClient.getMempoolInfo().catch(() => ({ size: 0, bytes: 0, usage: 0, maxmempool: 0, mempoolminfee: 0 })),
      rpcClient.getConnectionCount().catch(() => 0),
    ]);

    const getValue = <T>(r: PromiseSettledResult<T>, fallback: T): T =>
      r.status === 'fulfilled' ? r.value : fallback;

    const blockchainInfo = getValue(results[0], { blocks: 0, difficulty: 0, bestblockhash: '', chain: 'main', headers: 0, mediantime: 0, verificationprogress: 1, chainwork: '', size_on_disk: 0, moneysupply: 0 } as any);
    const networkInfo = getValue(results[1], {} as any);
    const miningInfo = getValue(results[2], { networkhashps: 0 } as any);
    const masternodeCount = getValue(results[3], { total: 0, enabled: 0 } as any);
    const mempoolInfo = getValue(results[4], { size: 0, bytes: 0, usage: 0, maxmempool: 0, mempoolminfee: 0 } as any);
    const connectionCount = getValue(results[5], 0 as any);

    const stats: NetworkStats = {
      height: blockchainInfo.blocks,
      difficulty: blockchainInfo.difficulty,
      hashrate: miningInfo.networkhashps || 0,
      totalSupply: blockchainInfo.moneysupply || 0,
      circulatingSupply: blockchainInfo.moneysupply || 0,
      nodes: typeof connectionCount === 'number' ? connectionCount : 0,
      mempool: {
        size: mempoolInfo.size || 0,
        bytes: mempoolInfo.bytes || 0,
        usage: mempoolInfo.usage || 0,
        maxmempool: mempoolInfo.maxmempool || 0,
        mempoolminfee: mempoolInfo.mempoolminfee || 0,
      },
      blockchain: {
        chain: blockchainInfo.chain || 'main',
        blocks: blockchainInfo.blocks,
        headers: blockchainInfo.headers || blockchainInfo.blocks,
        bestblockhash: blockchainInfo.bestblockhash,
        mediantime: blockchainInfo.mediantime || Math.floor(Date.now() / 1000),
        verificationprogress: blockchainInfo.verificationprogress || 1,
        chainwork: blockchainInfo.chainwork || '',
        size_on_disk: blockchainInfo.size_on_disk || 0,
      },
    };

    setCache(cacheKey, stats);
    return stats;
  } catch (error) {
    console.error('Failed to fetch network stats:', error);
    throw new Error('Unable to fetch network statistics');
  }
}

/**
 * Get block by height or hash
 */
export async function getBlock(heightOrHash: string | number): Promise<Block> {
  const cacheKey = `block-${heightOrHash}`;
  const cached = getCached<Block>(cacheKey);
  if (cached) return cached;

  try {
    let blockData;

    if (typeof heightOrHash === 'number') {
      blockData = await rpcClient.getBlockByHeight(heightOrHash);
    } else if (heightOrHash.length === 64) {
      // Assume it's a hash
      blockData = await rpcClient.getBlock(heightOrHash);
    } else {
      // Try as height
      const height = parseInt(heightOrHash);
      if (isNaN(height)) {
        throw new Error('Invalid block identifier');
      }
      blockData = await rpcClient.getBlockByHeight(height);
    }

    const block: Block = {
      hash: blockData.hash,
      height: blockData.height,
      timestamp: blockData.time,
      size: blockData.size,
      transactionCount: blockData.tx?.length || 0,
      difficulty: blockData.difficulty,
      nonce: blockData.nonce,
      merkleRoot: blockData.merkleroot,
      previousBlockHash: blockData.previousblockhash,
      nextBlockHash: blockData.nextblockhash,
      confirmations: blockData.confirmations,
      reward: 0, // Calculate from coinbase transaction
      fees: 0, // Calculate from transactions
      version: blockData.version || 1,
      bits: blockData.bits || '',
      chainwork: blockData.chainwork || '',
      miner: undefined,
    };

    setCache(cacheKey, block);
    return block;
  } catch (error) {
    console.error('Failed to fetch block:', error);
    throw new Error(`Block not found: ${heightOrHash}`);
  }
}

/**
 * Get latest blocks
 */
export async function getLatestBlocks(count: number = 10): Promise<Block[]> {
  try {
    const currentHeight = await rpcClient.getBlockCount();
    const blocks = [];

    for (let i = 0; i < count; i++) {
      const height = currentHeight - i;
      if (height >= 0) {
        try {
          const block = await getBlock(height);
          blocks.push(block);
        } catch (error) {
          console.error(`Failed to fetch block ${height}:`, error);
        }
      }
    }

    return blocks;
  } catch (error) {
    console.error('Failed to fetch latest blocks:', error);
    throw new Error('Unable to fetch latest blocks');
  }
}

/**
 * Get transaction by hash
 */
export async function getTransaction(txid: string): Promise<Transaction> {
  const cacheKey = `tx-${txid}`;
  const cached = getCached<Transaction>(cacheKey);
  if (cached) return cached;

  try {
    const txData = await rpcClient.getRawTransaction(txid, true);

    // Map inputs
    const inputs: TransactionInput[] = txData.vin?.map((vin: any) => ({
      txid: vin.txid,
      vout: vin.vout,
      scriptSig: vin.scriptSig || { asm: '', hex: '' },
      sequence: vin.sequence,
      witness: vin.witness,
      address: undefined, // Would need to fetch from previous transaction
      value: undefined, // Would need to fetch from previous transaction
      prevout: undefined,
    })) || [];

    // Map outputs
    const outputs: TransactionOutput[] = txData.vout?.map((vout: any) => ({
      value: vout.value,
      n: vout.n,
      scriptPubKey: {
        asm: vout.scriptPubKey?.asm || '',
        hex: vout.scriptPubKey?.hex || '',
        type: vout.scriptPubKey?.type || 'unknown',
        addresses: vout.scriptPubKey?.addresses,
        address: vout.scriptPubKey?.address,
      },
      spent: false, // Would need additional RPC call to determine
      spentTxid: undefined,
      spentIndex: undefined,
    })) || [];

    const transaction: Transaction = {
      txid: txData.txid,
      version: txData.version,
      locktime: txData.locktime,
      size: txData.size,
      vsize: txData.vsize || txData.size,
      weight: txData.weight || txData.size * 4,
      fee: 0, // Calculate from inputs - outputs
      timestamp: txData.time || txData.blocktime,
      blockHash: txData.blockhash,
      blockHeight: txData.height,
      confirmations: txData.confirmations || 0,
      status: txData.confirmations > 0 ? 'confirmed' : 'pending',
      inputs,
      outputs,
      totalInput: inputs.reduce((sum, input) => sum + (input.value || 0), 0),
      totalOutput: outputs.reduce((sum, output) => sum + (output.value || 0), 0),
    };

    setCache(cacheKey, transaction);
    return transaction;
  } catch (error) {
    console.error('Failed to fetch transaction:', error);
    throw new Error(`Transaction not found: ${txid}`);
  }
}

/**
 * Get recent transactions from mempool and latest blocks
 */
export async function getRecentTransactions(count: number = 10): Promise<Transaction[]> {
  try {
    // Get mempool transactions
    const mempool = await rpcClient.getRawMempool(false);
    const transactions = [];

    // Add mempool transactions first
    for (const txid of mempool.slice(0, Math.min(5, count))) {
      try {
        const tx = await getTransaction(txid);
        transactions.push(tx);
      } catch (error) {
        console.error(`Failed to fetch mempool transaction ${txid}:`, error);
      }
    }

    // Fill remaining with transactions from recent blocks
    if (transactions.length < count) {
      const recentBlocks = await getLatestBlocks(5);
      for (const block of recentBlocks) {
        if (transactions.length >= count) break;

        // Get block details with transaction list
        const blockDetails = await rpcClient.getBlock(block.hash, 1);
        const txList = blockDetails.tx || [];

        for (const txid of txList.slice(0, 3)) {
          if (transactions.length >= count) break;
          if (transactions.some(tx => tx.txid === txid)) continue;

          try {
            const tx = await getTransaction(txid);
            transactions.push(tx);
          } catch (error) {
            console.error(`Failed to fetch block transaction ${txid}:`, error);
          }
        }
      }
    }

    return transactions.slice(0, count);
  } catch (error) {
    console.error('Failed to fetch recent transactions:', error);
    throw new Error('Unable to fetch recent transactions');
  }
}

/**
 * Get address information
 */
export async function getAddressInfo(address: string): Promise<Address> {
  const cacheKey = `address-${address}`;
  const cached = getCached<Address>(cacheKey);
  if (cached) return cached;

  try {
    const validation = await rpcClient.validateAddress(address);

    if (!validation.isvalid) {
      throw new Error('Invalid address');
    }

    // Note: Getting full address history requires additional indexing
    // This is a simplified implementation
    const addressInfo: Address = {
      address,
      type: validation.type || 'unknown',
      balance: 0,
      totalReceived: 0,
      totalSent: 0,
      transactionCount: 0,
      unconfirmedBalance: 0,
      firstSeen: undefined,
      lastSeen: undefined,
      utxos: [],
    };

    setCache(cacheKey, addressInfo);
    return addressInfo;
  } catch (error) {
    console.error('Failed to fetch address info:', error);
    throw new Error(`Address not found or invalid: ${address}`);
  }
}

/**
 * Search for block, transaction, or address
 */
export async function search(query: string): Promise<{
  type: 'block' | 'transaction' | 'address' | 'unknown';
  data?: any;
  error?: string;
}> {
  try {
    // Block hash or transaction hash (64 characters, hexadecimal)
    if (/^[0-9a-fA-F]{64}$/.test(query)) {
      try {
        const block = await getBlock(query);
        return { type: 'block', data: block };
      } catch {
        try {
          const transaction = await getTransaction(query);
          return { type: 'transaction', data: transaction };
        } catch {
          return { type: 'unknown', error: 'Hash not found' };
        }
      }
    }

    // Block height (numeric)
    if (/^\d+$/.test(query)) {
      try {
        const block = await getBlock(parseInt(query));
        return { type: 'block', data: block };
      } catch {
        return { type: 'unknown', error: 'Block height not found' };
      }
    }

    // Address (25-35 characters)
    if (/^[A-Za-z0-9]{25,35}$/.test(query)) {
      try {
        const address = await getAddressInfo(query);
        return { type: 'address', data: address };
      } catch {
        return { type: 'unknown', error: 'Address not found or invalid' };
      }
    }

    return { type: 'unknown', error: 'Invalid search query format' };
  } catch (error) {
    console.error('Search failed:', error);
    return { type: 'unknown', error: 'Search failed' };
  }
}

/**
 * Get masternode list
 */
export async function getMasternodes(): Promise<any[]> {
  try {
    const masternodes = await rpcClient.getMasternodeList('enabled');
    return Array.isArray(masternodes) ? masternodes : Object.values(masternodes);
  } catch (error) {
    console.error('Failed to fetch masternodes:', error);
    return [];
  }
}

/**
 * Get mempool information
 */
export async function getMempoolInfo(): Promise<{
  size: number;
  bytes: number;
  usage: number;
  maxmempool: number;
  mempoolminfee: number;
}> {
  try {
    const info = await rpcClient.getMempoolInfo();
    return {
      size: info.size || 0,
      bytes: info.bytes || 0,
      usage: info.usage || 0,
      maxmempool: info.maxmempool || 0,
      mempoolminfee: info.mempoolminfee || 0,
    };
  } catch (error) {
    console.error('Failed to fetch mempool info:', error);
    return {
      size: 0,
      bytes: 0,
      usage: 0,
      maxmempool: 0,
      mempoolminfee: 0,
    };
  }
}