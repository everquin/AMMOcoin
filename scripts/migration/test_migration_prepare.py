#!/usr/bin/env python3
"""Tests for migration-prepare.py batching (no daemon: cli() is stubbed).

Run: python3 scripts/migration/test_migration_prepare.py
"""
import importlib.util
import json
from decimal import Decimal
from pathlib import Path

spec = importlib.util.spec_from_file_location("prep", Path(__file__).with_name("migration-prepare.py"))
prep = importlib.util.module_from_spec(spec)
spec.loader.exec_module(prep)

created = []


def fake_cli(utxos):
    def cli(binary, *args):
        if args[0] == "listunspent":
            return json.dumps(utxos)
        if args[0] == "createrawtransaction":
            created.append((json.loads(args[1]), json.loads(args[2])))
            return "00" * 10
        raise AssertionError(args)
    return cli


# 1. Oversize split: 24.7M -> parts <= 10M, exact sum, extras in own txs.
holders = [{"address": "Abig", "balance": "24713345.21078793"}] + \
          [{"address": f"A{i}", "balance": "1.5"} for i in range(120)]
main, extras = prep.split_oversize(holders)
parts = [Decimal(main[0]["balance"])] + [Decimal(x["balance"]) for x in extras]
assert len(parts) == 3 and sum(parts) == Decimal("24713345.21078793")
assert all(p <= prep.MAX_PER_RECIPIENT_AMMO for p in parts)
chunks = prep.plan_chunks(main, extras)
assert len(chunks) == 3 + 2  # 121 holders -> 3 chunks of <=50, plus 2 single-part txs
assert sum(1 for c in chunks for h in c if h["address"] == "Abig") == 3
for c in chunks:
    a = [h["address"] for h in c]
    assert len(a) == len(set(a))

# 2. Without a fan-out, one reserve UTXO can't serve every batch: refuse.
prep.cli = fake_cli([{"txid": "r", "vout": 0, "amount": 250000000}])
try:
    prep.build_batches("x", chunks, "Achange")
    raise SystemExit("expected refusal: one UTXO cannot fund several batches")
except RuntimeError as e:
    assert "fan-out" in str(e)

# 3. Fan-out from many cold-staked 50,000 outputs: <= MAX_INPUTS_PER_TX inputs per tx,
#    every batch address funded exactly to its need, change only to the change address.
reserve = [{"txid": f"r{i}", "vout": 0, "amount": 50000.0, "address": "Areserve"} for i in range(1200)]
def fake_cli2(state):
    def cli(binary, *args):
        if args[0] == "listunspent":
            return json.dumps(state["mempool"] + reserve if args[1] == "0" else reserve)
        if args[0] == "createrawtransaction":
            created.append((json.loads(args[1]), json.loads(args[2])))
            return "00" * 10
        raise AssertionError(args)
    return cli
big = [{"address": f"B{i}", "balance": "9000000"} for i in range(5)] + \
      [{"address": f"S{i}", "balance": "1234.5"} for i in range(140)]
bmain, bextras = prep.split_oversize(big)
bchunks = prep.plan_chunks(bmain, bextras)
fan = [f"Afan{i}" for i in range(len(bchunks))]
state = {"mempool": []}
prep.cli = fake_cli2(state)
created.clear()
txs = prep.build_fanout("x", bchunks, fan, "Achange")
assert len(txs) >= 2, "45M+ from 50k pieces must need several txs"
assert all(len(t["inputs"]) <= prep.MAX_INPUTS_PER_TX for t in txs)
ins = [(i["txid"], i["vout"]) for t in txs for i in t["inputs"]]
assert len(ins) == len(set(ins)), "a reserve output used twice"
funded = {}
for t in txs:
    assert len(t["outputs"]) == len(set(t["outputs"]))
    for a, v in t["outputs"].items():
        if a != "Achange":
            funded[a] = funded.get(a, Decimal(0)) + Decimal(v)
    spent = sum(Decimal("50000") for _ in t["inputs"])
    assert spent == sum(Decimal(v) for v in t["outputs"].values()) + Decimal(t["fee"]) or "Achange" not in t["outputs"]
assert [funded.get(a, Decimal(0)) for a in fan] == [prep.chunk_need(c) for c in bchunks]

# 4. Idempotent: rerun after the first tx was broadcast funds only what is missing.
first = txs[0]
state["mempool"] = [{"txid": "m", "vout": n, "amount": float(Decimal(v)), "address": a}
                    for n, (a, v) in enumerate(first["outputs"].items()) if a != "Achange"]
txs2 = prep.build_fanout("x", bchunks, fan, "Achange")
assert len(txs2) == len(txs) - 1
funded2 = dict((a, v) for a, v in ((m["address"], Decimal(str(m["amount"]))) for m in state["mempool"]))
for t in txs2:
    for a, v in t["outputs"].items():
        if a != "Achange":
            funded2[a] = funded2.get(a, Decimal(0)) + Decimal(v)
assert [funded2.get(a, Decimal(0)) for a in fan] == [prep.chunk_need(c) for c in bchunks]
assert len(prep.build_fanout("x", bchunks, fan, "Achange", max_txs=1)) == 1

# 5. Payout batches spend every confirmed output at their own funding address.
conf = []
for t in txs:
    for n, (a, v) in enumerate(t["outputs"].items()):
        if a != "Achange":
            conf.append({"txid": t["batch_index"], "vout": n, "amount": float(Decimal(v)), "address": a})
reserve[:] = conf
created.clear()
batches = prep.build_batches("x", bchunks, "Achange", fan)
assert len(batches) == len(bchunks)
used = [(i["txid"], i["vout"]) for b in batches for i in b["inputs"]]
assert len(used) == len(set(used)) == len(conf)
paid = sum(Decimal(v) for b in batches for k, v in b["outputs"].items() if k != "Achange")
assert paid == sum((Decimal(h["balance"]) for h in big), Decimal(0))
assert not any("Achange" in b["outputs"] for b in batches), "exact funding leaves no change"

# 6. Fees: a 450-input fan-out is under 100 kB and pays at least the relay fee.
size = 10 + 450 * prep.INPUT_BYTES + 60 * prep.OUTPUT_BYTES
assert size < 100_000 and prep.tx_fee(450, 60) >= Decimal("0.0001") * (size // 1000 + 1)
assert Decimal(str(prep.FEE_PER_TX_AMMO)) >= prep.tx_fee(10, 51)
print("migration-prepare: ok")
