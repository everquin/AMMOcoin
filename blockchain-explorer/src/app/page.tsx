"use client";

import { Activity, Blocks, Users, Shield, Clock, Zap, Eye } from "lucide-react";
import Link from "next/link";
import { SearchBar } from "@/components/ui/SearchBar";
import { useEffect, useState } from "react";

interface NetworkStats {
  height: number;
  difficulty: number;
  hashrate: number;
  totalSupply: number;
  circulatingSupply: number;
  nodes: number;
  mempool: {
    size: number;
    bytes: number;
  };
  blockchain: {
    chain: string;
    blocks: number;
    headers: number;
    bestblockhash: string;
    mediantime: number;
    verificationprogress: number;
  };
}

interface BlockSummary {
  height: number;
  hash: string;
  time?: number;
  timestamp?: number;
  tx?: number;
  transactionCount?: number;
  size: number;
}

interface TxSummary {
  txid: string;
  time?: number;
  timestamp?: number;
  vout?: { value: number }[];
  totalOutput?: number;
}

function formatTimeAgo(timestamp: number) {
  const now = Math.floor(Date.now() / 1000);
  const diff = now - timestamp;
  if (diff < 60) return "Just now";
  const minutes = Math.floor(diff / 60);
  if (minutes === 1) return "1 minute ago";
  if (minutes < 60) return `${minutes} minutes ago`;
  const hours = Math.floor(minutes / 60);
  if (hours === 1) return "1 hour ago";
  return `${hours} hours ago`;
}

function formatHash(hash: string, length = 16) {
  if (!hash) return "...";
  return `${hash.slice(0, length)}...`;
}

function formatNumber(num: number) {
  return new Intl.NumberFormat().format(num);
}

function formatSupply(num: number) {
  if (num <= 0) return "—";
  if (num >= 1_000_000) return `${(num / 1_000_000).toFixed(2)}M AMMO`;
  return `${formatNumber(Math.floor(num))} AMMO`;
}

export default function HomePage() {
  const [stats, setStats] = useState<NetworkStats | null>(null);
  const [recentBlocks, setRecentBlocks] = useState<BlockSummary[]>([]);
  const [recentTxs, setRecentTxs] = useState<TxSummary[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    async function fetchData() {
      try {
        const [statsRes, blocksRes, txsRes] = await Promise.all([
          fetch("/api/stats").then((r) => r.json()).catch(() => null),
          fetch("/api/blocks").then((r) => r.json()).catch(() => null),
          fetch("/api/transactions").then((r) => r.json()).catch(() => null),
        ]);

        if (statsRes?.success) setStats(statsRes.data);
        if (blocksRes?.success) setRecentBlocks(blocksRes.data?.blocks?.slice(0, 5) || blocksRes.data?.slice?.(0, 5) || []);
        if (txsRes?.success) setRecentTxs(txsRes.data?.transactions?.slice(0, 5) || txsRes.data?.slice?.(0, 5) || []);
      } catch (err) {
        console.error("Failed to fetch data:", err);
      } finally {
        setLoading(false);
      }
    }

    fetchData();
    const interval = setInterval(fetchData, 30000); // refresh every 30s
    return () => clearInterval(interval);
  }, []);

  const blockHeight = stats?.height || 0;
  const totalNodes = stats?.nodes || 0;
  const difficulty = stats?.difficulty || 0;
  const mempoolSize = stats?.mempool?.size || 0;
  const totalSupply = stats?.totalSupply || 0;
  const bestHash = stats?.blockchain?.bestblockhash || "";

  return (
    <div className="space-y-12">
      {/* Hero Section */}
      <section className="text-center py-12">
        <h1 className="text-4xl md:text-6xl font-bold mb-6 bg-ammocoin-gradient bg-clip-text text-transparent">
          AMMOcoin Explorer
        </h1>
        <p className="text-xl text-ammocoin-gray-300 mb-8 max-w-3xl mx-auto">
          Explore the AMMOcoin blockchain with privacy-focused features, shielded transactions,
          and real-time network statistics.
        </p>
        <div className="max-w-2xl mx-auto">
          <SearchBar placeholder="Search blocks, transactions, addresses..." />
        </div>
        <div className="mt-6 flex flex-wrap justify-center gap-4 text-sm text-ammocoin-gray-400">
          <span>• Block Height: {loading ? "..." : formatNumber(blockHeight)}</span>
          <span>• Network: Mainnet</span>
          <span>• Consensus: Proof of Stake</span>
          <span>• Privacy: Shielded Transactions</span>
        </div>
      </section>

      {/* Network Statistics */}
      <section>
        <h2 className="text-2xl font-bold mb-6 text-ammocoin-white">Network Statistics</h2>
        <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
          <div className="stat-card">
            <div className="flex items-center justify-between mb-2">
              <Blocks className="w-5 h-5 text-ammocoin-primary" />
              <span className="text-xs text-ammocoin-gray-400">BLOCKS</span>
            </div>
            <div className="text-2xl font-bold text-ammocoin-white">
              {loading ? "..." : formatNumber(blockHeight)}
            </div>
            <div className="text-sm text-ammocoin-gray-400">Current Height</div>
          </div>

          <div className="stat-card">
            <div className="flex items-center justify-between mb-2">
              <Activity className="w-5 h-5 text-ammocoin-primary" />
              <span className="text-xs text-ammocoin-gray-400">DIFFICULTY</span>
            </div>
            <div className="text-2xl font-bold text-ammocoin-white">
              {loading ? "..." : difficulty.toFixed(6)}
            </div>
            <div className="text-sm text-ammocoin-gray-400">Network Difficulty</div>
          </div>

          <div className="stat-card">
            <div className="flex items-center justify-between mb-2">
              <Users className="w-5 h-5 text-ammocoin-primary" />
              <span className="text-xs text-ammocoin-gray-400">MEMPOOL</span>
            </div>
            <div className="text-2xl font-bold text-ammocoin-white">
              {loading ? "..." : formatNumber(mempoolSize)}
            </div>
            <div className="text-sm text-ammocoin-gray-400">Pending Transactions</div>
          </div>

          <div className="stat-card">
            <div className="flex items-center justify-between mb-2">
              <Shield className="w-5 h-5 text-ammocoin-primary" />
              <span className="text-xs text-ammocoin-gray-400">NODES</span>
            </div>
            <div className="text-2xl font-bold text-ammocoin-white">
              {loading ? "..." : formatNumber(totalNodes)}
            </div>
            <div className="text-sm text-ammocoin-gray-400">Connected Peers</div>
          </div>
        </div>
      </section>

      {/* Key Features */}
      <section>
        <h2 className="text-2xl font-bold mb-6 text-ammocoin-white">AMMOcoin Features</h2>
        <div className="grid md:grid-cols-2 lg:grid-cols-4 gap-6">
          <div className="glass-card p-6 hover:border-ammocoin-primary/50 transition-all">
            <Shield className="w-8 h-8 text-ammocoin-primary mb-4" />
            <h3 className="text-lg font-semibold text-ammocoin-white mb-2">Privacy First</h3>
            <p className="text-ammocoin-gray-400 text-sm">
              Shielded transactions enable completely private transfers with advanced cryptographic privacy.
            </p>
          </div>

          <div className="glass-card p-6 hover:border-ammocoin-primary/50 transition-all">
            <Zap className="w-8 h-8 text-ammocoin-primary mb-4" />
            <h3 className="text-lg font-semibold text-ammocoin-white mb-2">Proof of Stake</h3>
            <p className="text-ammocoin-gray-400 text-sm">
              Energy-efficient consensus with staking rewards and masternode infrastructure.
            </p>
          </div>

          <div className="glass-card p-6 hover:border-ammocoin-primary/50 transition-all">
            <Clock className="w-8 h-8 text-ammocoin-primary mb-4" />
            <h3 className="text-lg font-semibold text-ammocoin-white mb-2">Fast Blocks</h3>
            <p className="text-ammocoin-gray-400 text-sm">
              60-second block times ensure quick transaction confirmation.
            </p>
          </div>

          <div className="glass-card p-6 hover:border-ammocoin-primary/50 transition-all">
            <Eye className="w-8 h-8 text-ammocoin-primary mb-4" />
            <h3 className="text-lg font-semibold text-ammocoin-white mb-2">Transparent</h3>
            <p className="text-ammocoin-gray-400 text-sm">
              Full blockchain transparency with optional privacy features.
            </p>
          </div>
        </div>
      </section>

      {/* Recent Activity */}
      <div className="grid lg:grid-cols-2 gap-8">
        {/* Recent Blocks */}
        <section>
          <div className="flex items-center justify-between mb-6">
            <h2 className="text-xl font-bold text-ammocoin-white">Recent Blocks</h2>
            <Link
              href="/blocks"
              className="text-ammocoin-primary hover:text-ammocoin-hover transition-colors text-sm"
            >
              View All →
            </Link>
          </div>
          <div className="space-y-4">
            {loading ? (
              <div className="block-card text-center text-ammocoin-gray-400 py-8">
                <div className="spinner mx-auto mb-3"></div>
                Loading blocks...
              </div>
            ) : recentBlocks.length === 0 ? (
              <div className="block-card text-center text-ammocoin-gray-400 py-8">
                No blocks available
              </div>
            ) : (
              recentBlocks.map((block) => (
                <div key={block.height} className="block-card">
                  <div className="flex items-center justify-between mb-2">
                    <Link
                      href={`/block/${block.height}`}
                      className="text-ammocoin-primary hover:text-ammocoin-hover font-mono text-lg"
                    >
                      #{formatNumber(block.height)}
                    </Link>
                    <span className="text-sm text-ammocoin-gray-400">
                      {formatTimeAgo(block.timestamp || block.time || 0)}
                    </span>
                  </div>
                  <div className="space-y-2">
                    <div className="hash-display">
                      {formatHash(block.hash)}
                    </div>
                    <div className="flex justify-between text-sm">
                      <span className="text-ammocoin-gray-400">
                        {block.transactionCount || block.tx || 0} transaction{(block.transactionCount || block.tx || 0) !== 1 ? "s" : ""}
                      </span>
                      <span className="text-ammocoin-gray-400">
                        {formatNumber(block.size)} bytes
                      </span>
                    </div>
                  </div>
                </div>
              ))
            )}
          </div>
        </section>

        {/* Recent Transactions */}
        <section>
          <div className="flex items-center justify-between mb-6">
            <h2 className="text-xl font-bold text-ammocoin-white">Recent Transactions</h2>
            <Link
              href="/transactions"
              className="text-ammocoin-primary hover:text-ammocoin-hover transition-colors text-sm"
            >
              View All →
            </Link>
          </div>
          <div className="space-y-4">
            {loading ? (
              <div className="block-card text-center text-ammocoin-gray-400 py-8">
                <div className="spinner mx-auto mb-3"></div>
                Loading transactions...
              </div>
            ) : recentTxs.length === 0 ? (
              <div className="block-card text-center text-ammocoin-gray-400 py-8">
                No recent transactions
              </div>
            ) : (
              recentTxs.map((tx) => (
                <div key={tx.txid} className="block-card">
                  <div className="flex items-center justify-between mb-2">
                    <Link
                      href={`/tx/${tx.txid}`}
                      className="text-ammocoin-primary hover:text-ammocoin-hover font-mono"
                    >
                      {formatHash(tx.txid, 12)}
                    </Link>
                    <span className="text-sm text-ammocoin-gray-400">
                      {formatTimeAgo(tx.timestamp || tx.time || 0)}
                    </span>
                  </div>
                  <div className="flex justify-between items-center">
                    <span className="text-ammocoin-white font-semibold">
                      {tx.totalOutput
                        ? tx.totalOutput.toFixed(2)
                        : tx.vout
                        ? tx.vout.reduce((sum: number, o: { value: number }) => sum + (o.value || 0), 0).toFixed(2)
                        : "0.00"}{" "}
                      AMMO
                    </span>
                  </div>
                </div>
              ))
            )}
          </div>
        </section>
      </div>

      {/* Supply Information */}
      <section>
        <h2 className="text-2xl font-bold mb-6 text-ammocoin-white">Supply Information</h2>
        <div className="grid md:grid-cols-3 gap-6">
          <div className="stat-card">
            <div className="text-2xl font-bold text-ammocoin-primary mb-2">
              {loading ? "..." : formatSupply(totalSupply)}
            </div>
            <div className="text-sm text-ammocoin-gray-400">Total Supply</div>
          </div>
          <div className="stat-card">
            <div className="text-2xl font-bold text-ammocoin-primary mb-2">
              {loading ? "..." : bestHash ? formatHash(bestHash, 20) : "—"}
            </div>
            <div className="text-sm text-ammocoin-gray-400">Best Block Hash</div>
          </div>
          <div className="stat-card">
            <div className="text-2xl font-bold text-ammocoin-primary mb-2">
              60s
            </div>
            <div className="text-sm text-ammocoin-gray-400">Target Block Time</div>
          </div>
        </div>
      </section>
    </div>
  );
}
