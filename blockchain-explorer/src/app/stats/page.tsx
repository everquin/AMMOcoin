"use client";

import { useEffect, useState } from "react";
import { BarChart3, Blocks, Activity, Shield, Users, Clock } from "lucide-react";

interface Stats {
  height: number;
  difficulty: number;
  hashrate: number;
  nodes: number;
  mempool: { size: number; bytes: number; mempoolminfee: number };
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

export default function StatsPage() {
  const [stats, setStats] = useState<Stats | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    function fetchStats() {
      fetch("/api/stats")
        .then((r) => r.json())
        .then((d) => { if (d.success) setStats(d.data); })
        .catch(() => {})
        .finally(() => setLoading(false));
    }
    fetchStats();
    const interval = setInterval(fetchStats, 15000);
    return () => clearInterval(interval);
  }, []);

  if (loading) {
    return (
      <div className="text-center py-12">
        <div className="spinner mx-auto mb-4"></div>
        <p className="text-ammocoin-gray-400">Loading network statistics...</p>
      </div>
    );
  }

  if (!stats) {
    return <div className="text-center py-12 text-ammocoin-gray-400">Failed to load statistics</div>;
  }

  return (
    <div className="space-y-8">
      <div className="flex items-center space-x-3">
        <BarChart3 className="w-8 h-8 text-ammocoin-primary" />
        <h1 className="text-3xl font-bold text-ammocoin-white">Network Statistics</h1>
      </div>

      {/* Primary Stats */}
      <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-4 gap-4">
        <div className="stat-card">
          <Blocks className="w-5 h-5 text-ammocoin-primary mb-2" />
          <div className="text-2xl font-bold text-ammocoin-white">{stats.height.toLocaleString()}</div>
          <div className="text-sm text-ammocoin-gray-400">Block Height</div>
        </div>
        <div className="stat-card">
          <Activity className="w-5 h-5 text-ammocoin-primary mb-2" />
          <div className="text-2xl font-bold text-ammocoin-white">{stats.difficulty.toFixed(6)}</div>
          <div className="text-sm text-ammocoin-gray-400">Difficulty</div>
        </div>
        <div className="stat-card">
          <Users className="w-5 h-5 text-ammocoin-primary mb-2" />
          <div className="text-2xl font-bold text-ammocoin-white">{stats.nodes}</div>
          <div className="text-sm text-ammocoin-gray-400">Connected Peers</div>
        </div>
        <div className="stat-card">
          <Shield className="w-5 h-5 text-ammocoin-primary mb-2" />
          <div className="text-2xl font-bold text-ammocoin-white">{stats.mempool.size}</div>
          <div className="text-sm text-ammocoin-gray-400">Mempool Transactions</div>
        </div>
      </div>

      {/* Blockchain Details */}
      <div className="glass-card p-6">
        <h2 className="text-xl font-bold text-ammocoin-white mb-4">Blockchain Details</h2>
        <div className="space-y-3">
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Chain</span>
            <span className="text-ammocoin-white font-mono">{stats.blockchain.chain}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Blocks</span>
            <span className="text-ammocoin-white font-mono">{stats.blockchain.blocks.toLocaleString()}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Headers</span>
            <span className="text-ammocoin-white font-mono">{stats.blockchain.headers.toLocaleString()}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Best Block Hash</span>
            <span className="text-ammocoin-primary font-mono text-sm break-all">{stats.blockchain.bestblockhash}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Verification Progress</span>
            <span className="text-ammocoin-white font-mono">{(stats.blockchain.verificationprogress * 100).toFixed(4)}%</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Median Time</span>
            <span className="text-ammocoin-white font-mono">{new Date(stats.blockchain.mediantime * 1000).toLocaleString()}</span>
          </div>
          {stats.blockchain.size_on_disk > 0 && (
            <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
              <span className="text-ammocoin-gray-400">Size on Disk</span>
              <span className="text-ammocoin-white font-mono">{(stats.blockchain.size_on_disk / 1024 / 1024).toFixed(2)} MB</span>
            </div>
          )}
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Min Mempool Fee</span>
            <span className="text-ammocoin-white font-mono">{stats.mempool.mempoolminfee} AMMO</span>
          </div>
          <div className="flex justify-between py-2">
            <span className="text-ammocoin-gray-400">Consensus</span>
            <span className="text-ammocoin-white font-mono">Proof of Stake</span>
          </div>
        </div>
      </div>

      {/* Network Info */}
      <div className="glass-card p-6">
        <h2 className="text-xl font-bold text-ammocoin-white mb-4">Network Info</h2>
        <div className="grid md:grid-cols-2 gap-4">
          <div>
            <span className="text-ammocoin-gray-400 text-sm">P2P Port</span>
            <div className="text-ammocoin-white font-mono">37020</div>
          </div>
          <div>
            <span className="text-ammocoin-gray-400 text-sm">RPC Port</span>
            <div className="text-ammocoin-white font-mono">51473</div>
          </div>
          <div>
            <span className="text-ammocoin-gray-400 text-sm">Genesis Hash</span>
            <div className="text-ammocoin-primary font-mono text-xs break-all">000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2</div>
          </div>
          <div>
            <span className="text-ammocoin-gray-400 text-sm">Target Block Time</span>
            <div className="text-ammocoin-white font-mono">60 seconds</div>
          </div>
        </div>
      </div>
    </div>
  );
}
