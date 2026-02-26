"use client";

import { useEffect, useState } from "react";
import Link from "next/link";
import { Blocks } from "lucide-react";

interface BlockData {
  hash: string;
  height: number;
  timestamp: number;
  size: number;
  transactionCount: number;
  difficulty: number;
}

export default function BlocksPage() {
  const [blocks, setBlocks] = useState<BlockData[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetch("/api/blocks")
      .then((r) => r.json())
      .then((d) => {
        if (d.success) setBlocks(d.data?.blocks || d.data || []);
      })
      .catch(() => {})
      .finally(() => setLoading(false));
  }, []);

  return (
    <div className="space-y-8">
      <div className="flex items-center space-x-3">
        <Blocks className="w-8 h-8 text-ammocoin-primary" />
        <h1 className="text-3xl font-bold text-ammocoin-white">Latest Blocks</h1>
      </div>

      {loading ? (
        <div className="text-center py-12">
          <div className="spinner mx-auto mb-4"></div>
          <p className="text-ammocoin-gray-400">Loading blocks...</p>
        </div>
      ) : (
        <div className="glass-card overflow-hidden">
          <table className="data-table">
            <thead>
              <tr>
                <th>Height</th>
                <th>Hash</th>
                <th>Time</th>
                <th>Txs</th>
                <th>Size</th>
              </tr>
            </thead>
            <tbody>
              {blocks.map((block) => (
                <tr key={block.height}>
                  <td>
                    <Link href={`/block/${block.height}`} className="text-ammocoin-primary hover:text-ammocoin-hover font-mono">
                      {block.height.toLocaleString()}
                    </Link>
                  </td>
                  <td className="font-mono text-sm text-ammocoin-gray-300">
                    <Link href={`/block/${block.hash}`} className="hover:text-ammocoin-primary">
                      {block.hash.slice(0, 20)}...
                    </Link>
                  </td>
                  <td className="text-ammocoin-gray-400 text-sm">
                    {new Date(block.timestamp * 1000).toLocaleString()}
                  </td>
                  <td className="text-ammocoin-gray-300">{block.transactionCount}</td>
                  <td className="text-ammocoin-gray-400 text-sm">{block.size.toLocaleString()} B</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
    </div>
  );
}
