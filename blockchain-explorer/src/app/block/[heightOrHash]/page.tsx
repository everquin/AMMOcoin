"use client";

import { useEffect, useState } from "react";
import { useParams } from "next/navigation";
import Link from "next/link";
import { Blocks } from "lucide-react";

interface BlockDetail {
  hash: string;
  height: number;
  timestamp: number;
  size: number;
  transactionCount: number;
  difficulty: number;
  nonce: number;
  merkleRoot: string;
  previousBlockHash: string;
  nextBlockHash?: string;
  transactions: string[];
}

export default function BlockPage() {
  const params = useParams();
  const [block, setBlock] = useState<BlockDetail | null>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState("");

  useEffect(() => {
    if (!params.heightOrHash) return;
    fetch(`/api/block/${params.heightOrHash}`)
      .then((r) => r.json())
      .then((d) => {
        if (d.success) setBlock(d.data);
        else setError(d.error || "Block not found");
      })
      .catch(() => setError("Failed to fetch block"))
      .finally(() => setLoading(false));
  }, [params.heightOrHash]);

  if (loading) {
    return (
      <div className="text-center py-12">
        <div className="spinner mx-auto mb-4"></div>
        <p className="text-ammocoin-gray-400">Loading block...</p>
      </div>
    );
  }

  if (error || !block) {
    return (
      <div className="text-center py-12">
        <p className="text-error text-xl mb-4">{error || "Block not found"}</p>
        <Link href="/blocks" className="text-ammocoin-primary hover:text-ammocoin-hover">
          Back to blocks
        </Link>
      </div>
    );
  }

  return (
    <div className="space-y-8">
      <div className="flex items-center space-x-3">
        <Blocks className="w-8 h-8 text-ammocoin-primary" />
        <h1 className="text-3xl font-bold text-ammocoin-white">Block #{block.height.toLocaleString()}</h1>
      </div>

      {/* Navigation */}
      <div className="flex justify-between">
        {block.previousBlockHash ? (
          <Link href={`/block/${block.height - 1}`} className="text-ammocoin-primary hover:text-ammocoin-hover text-sm">
            &larr; Block {(block.height - 1).toLocaleString()}
          </Link>
        ) : <span />}
        {block.nextBlockHash ? (
          <Link href={`/block/${block.height + 1}`} className="text-ammocoin-primary hover:text-ammocoin-hover text-sm">
            Block {(block.height + 1).toLocaleString()} &rarr;
          </Link>
        ) : <span className="text-ammocoin-gray-400 text-sm">Latest block</span>}
      </div>

      {/* Block Details */}
      <div className="glass-card p-6">
        <h2 className="text-xl font-bold text-ammocoin-white mb-4">Block Details</h2>
        <div className="space-y-3">
          <div className="flex flex-col md:flex-row md:justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Hash</span>
            <span className="text-ammocoin-primary font-mono text-sm break-all">{block.hash}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Height</span>
            <span className="text-ammocoin-white font-mono">{block.height.toLocaleString()}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Timestamp</span>
            <span className="text-ammocoin-white font-mono">{new Date(block.timestamp * 1000).toLocaleString()}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Transactions</span>
            <span className="text-ammocoin-white font-mono">{block.transactionCount}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Size</span>
            <span className="text-ammocoin-white font-mono">{block.size.toLocaleString()} bytes</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Difficulty</span>
            <span className="text-ammocoin-white font-mono">{block.difficulty}</span>
          </div>
          <div className="flex justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Nonce</span>
            <span className="text-ammocoin-white font-mono">{block.nonce}</span>
          </div>
          <div className="flex flex-col md:flex-row md:justify-between py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
            <span className="text-ammocoin-gray-400">Merkle Root</span>
            <span className="text-ammocoin-white font-mono text-sm break-all">{block.merkleRoot}</span>
          </div>
          {block.previousBlockHash && (
            <div className="flex flex-col md:flex-row md:justify-between py-2">
              <span className="text-ammocoin-gray-400">Previous Block</span>
              <Link href={`/block/${block.previousBlockHash}`} className="text-ammocoin-primary font-mono text-sm break-all hover:text-ammocoin-hover">
                {block.previousBlockHash}
              </Link>
            </div>
          )}
        </div>
      </div>

      {/* Transaction List */}
      {block.transactions && block.transactions.length > 0 && (
        <div className="glass-card p-6">
          <h2 className="text-xl font-bold text-ammocoin-white mb-4">Transactions ({block.transactions.length})</h2>
          <div className="space-y-2">
            {block.transactions.map((txid) => (
              <div key={txid} className="py-2 border-b" style={{ borderColor: "rgba(50,205,50,0.15)" }}>
                <Link href={`/tx/${txid}`} className="text-ammocoin-primary hover:text-ammocoin-hover font-mono text-sm break-all">
                  {txid}
                </Link>
              </div>
            ))}
          </div>
        </div>
      )}
    </div>
  );
}
