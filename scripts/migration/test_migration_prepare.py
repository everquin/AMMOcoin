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

# 3. Fan-out: one output per batch to distinct addresses + change.
created.clear()
fan = prep.build_fanout("x", chunks, [f"Afan{i}" for i in range(len(chunks))], "Achange")
outs = fan["outputs"]
assert len(outs) == len(chunks) + 1 and "Achange" in outs
needs = [prep.chunk_need(c) for c in chunks]
assert [Decimal(outs[f"Afan{i}"]) for i in range(len(chunks))] == needs

# 4. After fan-out: each batch spends its own UTXO, none reused.
utxos = [{"txid": "f", "vout": i, "amount": float(n)} for i, n in enumerate(needs)]
prep.cli = fake_cli(utxos)
created.clear()
batches = prep.build_batches("x", chunks, "Achange")
used = [(b["inputs"][0]["txid"], b["inputs"][0]["vout"]) for b in batches]
assert len(used) == len(set(used)) == len(chunks)
paid = sum(Decimal(v) for b in batches for k, v in b["outputs"].items() if k != "Achange")
assert paid == sum((Decimal(h["balance"]) for h in holders), Decimal(0))
print("migration-prepare: ok")
