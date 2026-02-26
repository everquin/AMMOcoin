"use client";

import { useEffect, useState } from "react";
import Link from "next/link";
import { Activity } from "lucide-react";

interface TxData {
  txid: string;
  timestamp: number;
  confirmations: number;
  totalOutput: number;
  size: number;
  blockHash: string;
}

export default function TransactionsPage() {
  const [txs, setTxs] = useState<TxData[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetch("/api/transactions")
      .then((r) => r.json())
      .then((d) => {
        if (d.success) setTxs(d.data?.transactions || d.data || []);
      })
      .catch(() => {})
      .finally(() => setLoading(false));
  }, []);

  return (
    <div className="space-y-8">
      <div className="flex items-center space-x-3">
        <Activity className="w-8 h-8 text-ammocoin-primary" />
        <h1 className="text-3xl font-bold text-ammocoin-white">Latest Transactions</h1>
      </div>

      {loading ? (
        <div className="text-center py-12">
          <div className="spinner mx-auto mb-4"></div>
          <p className="text-ammocoin-gray-400">Loading transactions...</p>
        </div>
      ) : (
        <div className="glass-card overflow-hidden">
          <table className="data-table">
            <thead>
              <tr>
                <th>Transaction ID</th>
                <th>Time</th>
                <th>Amount</th>
                <th>Confirmations</th>
              </tr>
            </thead>
            <tbody>
              {txs.map((tx) => (
                <tr key={tx.txid}>
                  <td className="font-mono text-sm">
                    <Link href={`/tx/${tx.txid}`} className="text-ammocoin-primary hover:text-ammocoin-hover">
                      {tx.txid.slice(0, 24)}...
                    </Link>
                  </td>
                  <td className="text-ammocoin-gray-400 text-sm">
                    {new Date(tx.timestamp * 1000).toLocaleString()}
                  </td>
                  <td className="text-ammocoin-white font-semibold">
                    {(tx.totalOutput || 0).toFixed(2)} AMMO
                  </td>
                  <td>
                    <span className={tx.confirmations > 0 ? "status-confirmed" : "status-pending"}>
                      {tx.confirmations > 0 ? `${tx.confirmations} conf` : "pending"}
                    </span>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
    </div>
  );
}
