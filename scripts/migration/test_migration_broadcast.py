#!/usr/bin/env python3
"""Tests for migration-broadcast.py (no daemon: cli() and input() are stubbed;
nothing is signed, sent or contacted).

Run: python3 scripts/migration/test_migration_broadcast.py
"""
import contextlib
import importlib.util
import io
import json
import subprocess
import sys
import tempfile
from pathlib import Path

spec = importlib.util.spec_from_file_location("bc", Path(__file__).with_name("migration-broadcast.py"))
bc = importlib.util.module_from_spec(spec)
spec.loader.exec_module(bc)
real_cli = bc.cli
bc.time.sleep = lambda s: None
bc.input = lambda prompt="": "BROADCAST"


def txid(i):
    return f"{i:064x}"


def make_batch(i, payout=True):
    return {"batch_index": i if payout else f"fanout-{i}", "signed_txid": txid(i + 1), "signed_hex": f"hex{i}",
            "outputs": {f"Arecipient{i}": "10.00000000"}, "recipients": [{"address": f"Arecipient{i}"}]}


class Chain:
    """A stub node: which txids are in a block or the mempool, and which outpoints are spent."""
    def __init__(self, batches):
        self.batches = {b["signed_hex"]: b for b in batches}
        self.in_block: dict[str, int] = {}      # txid -> confirmations
        self.in_mempool: set[str] = set()
        self.orphaned: set[str] = set()         # txindex still points at a block that is no longer active
        self.spent: set[str] = set()            # "txid:vout"
        self.sent: list[str] = []
        self.send_error: str | None = None
        self.calls: list[tuple] = []

    def inputs(self, b):
        return [{"txid": "ee" * 32, "vout": int(str(b["batch_index"]).split("-")[-1])}]

    def broadcast(self, b):  # what a successful earlier run left behind
        self.in_block[b["signed_txid"]] = 3
        for i in self.inputs(b):
            self.spent.add(f"{i['txid']}:{i['vout']}")

    def __call__(self, binary, *args):
        self.calls.append(args)
        cmd = args[0]
        if cmd == "decoderawtransaction":
            b = self.batches[args[1]]
            vout = [{"value": float(v), "scriptPubKey": {"addresses": [a], "hex": "76a9"}} for a, v in b["outputs"].items()
                    if a not in (b.get("decoded_cold") or {})]
            vout += [{"value": float(c["amount"]), "scriptPubKey": {"addresses": [c["staker"], o], "hex": c["script_hex"]}}
                     for o, c in (b.get("decoded_cold") or {}).items()]
            return json.dumps({"txid": b["signed_txid"], "vin": self.inputs(b), "vout": vout})
        if cmd == "getrawtransaction":
            t = args[1]
            if t in self.in_mempool:
                return json.dumps({"txid": t})
            if t in self.in_block:
                return json.dumps({"txid": t, "blockhash": "bb", "confirmations": self.in_block[t]})
            if t in self.orphaned:
                return json.dumps({"txid": t, "blockhash": "bb", "confirmations": 0})
            raise RuntimeError("No such mempool or blockchain transaction")
        if cmd == "gettransaction":
            raise RuntimeError("Invalid or non-wallet transaction id")
        if cmd == "gettxout":
            return "" if f"{args[1]}:{args[2]}" in self.spent else '{"value": 10}'
        if cmd == "sendrawtransaction":
            b = self.batches[args[1]]
            if self.send_error:
                err, self.send_error = self.send_error, None
                raise RuntimeError(err)
            self.sent.append(b["signed_txid"])
            self.broadcast(b)
            return b["signed_txid"]
        raise AssertionError(args)


def run(batches, chain, *extra):
    with tempfile.TemporaryDirectory() as d:
        inp, log = Path(d) / "signed.json", Path(d) / "log.json"
        inp.write_text(json.dumps({"schema_version": "1", "sum_of_balances_ammo": "30", "batches": batches}))
        bc.cli = chain
        sys.argv = ["migration-broadcast.py", "--input", str(inp), "--log", str(log), "--pause", "0", *extra]
        with contextlib.redirect_stdout(io.StringIO()):
            rc = bc.main()
        return rc, json.loads(log.read_text()) if log.exists() else []


# 1. Resume a part-sent payout: batches 0 and 1 are already on chain (their inputs are
#    spent by these same txs). They are marked SENT and skipped; only batch 2 is sent.
batches = [make_batch(i) for i in range(3)]
chain = Chain(batches)
chain.broadcast(batches[0]); chain.broadcast(batches[1])
rc, log = run(batches, chain)
assert rc == 0, rc
assert chain.sent == [txid(3)], chain.sent
assert [e["status"] for e in log] == ["already_sent", "already_sent", "accepted"], log
assert log[0]["txid"] == txid(1) and log[0]["where"] == "block" and log[0]["confirmations"] == 3
assert "checked_at" in log[0]

# 2. Same, with the first batch still in the mempool.
chain = Chain(batches)
chain.in_mempool.add(txid(1)); chain.spent.add(f"{'ee' * 32}:0")
rc, log = run(batches, chain)
assert rc == 0 and chain.sent == [txid(2), txid(3)]
assert log[0] == {**log[0], "status": "already_sent", "where": "mempool", "confirmations": 0}

# 3. Genuinely stale: batch 1's input was spent by a DIFFERENT tx (ours is nowhere). Stop.
chain = Chain(batches)
chain.broadcast(batches[0])
chain.spent.add(f"{'ee' * 32}:1")
rc, log = run(batches, chain)
assert rc == 1
assert chain.sent == [], "nothing sent after a stale batch"
assert [e["status"] for e in log] == ["already_sent", "stale"]
assert log[1]["spent_inputs"] == [f"{'ee' * 32}:1"]
assert not any(c[0] == "sendrawtransaction" for c in chain.calls)

# 4. A tx whose block left the active chain (confirmations 0 with a blockhash) is
#    not counted as sent; with its input spent by the conflicting tx, it is STALE.
chain = Chain(batches)
chain.orphaned.add(txid(1)); chain.spent.add(f"{'ee' * 32}:0")
rc, log = run(batches, chain)
assert rc == 1 and [e["status"] for e in log] == ["stale"] and chain.sent == []

# 5. --no-skip-sent: the old strict behavior (an already-sent batch reads as STALE).
chain = Chain(batches)
chain.broadcast(batches[0])
rc, log = run(batches, chain, "--no-skip-sent")
assert rc == 1 and [e["status"] for e in log] == ["stale"] and chain.sent == []
assert not any(c[0] == "getrawtransaction" for c in chain.calls)

# 6. Race: the node says "transaction already in block chain" and the lookup then
#    finds it. Marked SENT; the run goes on.
class RaceChain(Chain):
    def __call__(self, binary, *args):
        if args[0] == "sendrawtransaction" and self.send_error:
            b = self.batches[args[1]]
            self.broadcast(b)  # it got in through another path just now
        return super().__call__(binary, *args)
chain = RaceChain(batches)
chain.send_error = "transaction already in block chain"
rc, log = run(batches, chain)
assert rc == 0 and [e["status"] for e in log] == ["already_sent", "accepted", "accepted"], log

# 7. A real rejection still stops the run (and is not mistaken for "already sent").
chain = Chain(batches)
chain.send_error = "min relay fee not met"
rc, log = run(batches, chain)
assert rc == 1 and [e["status"] for e in log] == ["rejected"] and chain.sent == []

# 8. Fan-out files resume the same way: sent ones skipped, then a stake-spent one is STALE.
fb = [make_batch(i, payout=False) for i in range(3)]
chain = Chain(fb)
chain.broadcast(fb[0]); chain.spent.add(f"{'ee' * 32}:1")
rc, log = run(fb, chain)
assert rc == 1 and [e["status"] for e in log] == ["already_sent", "stale"] and chain.sent == []

# 9. Cold-stake outputs are checked script for script before anything is sent.
cs = make_batch(0)
cs["cold_stake"] = {"Apool3": {"staker": "Sstaker", "script_hex": "76a97b63d114" + "11" * 20 + "6714" + "22" * 20 + "6888ac",
                               "amount": "10.00000000"}}
cs["outputs"] = {"Apool3": "10.00000000"}
cs["decoded_cold"] = cs["cold_stake"]
chain = Chain([cs])
rc, log = run([cs], chain)
assert rc == 0 and chain.sent == [txid(1)]
bad = json.loads(json.dumps(cs))
bad["decoded_cold"] = {"Apool3": {**cs["cold_stake"]["Apool3"], "script_hex": "76a97b63d114" + "33" * 20 + "6714" + "22" * 20 + "6888ac"}}
chain = Chain([bad])
try:
    run([bad], chain)
    raise AssertionError("expected refusal: cold-stake script differs")
except RuntimeError as e:
    assert "cold-stake" in str(e)
assert chain.sent == []

# 10. --cli is split like the other scripts (shlex); an existing path stays one program.
calls = []
class _P:
    returncode, stdout, stderr = 0, "ok\n", ""
real_run = subprocess.run
subprocess.run = lambda argv, **kw: (calls.append(argv), _P())[1]
try:
    real_cli('ammocoin-cli -datadir="/Volumes/x y/b"', "getblockcount")
    assert calls[-1] == ["ammocoin-cli", "-datadir=/Volumes/x y/b", "getblockcount"], calls[-1]
    with tempfile.TemporaryDirectory() as d:
        w = Path(d) / "cli wrapper"
        w.write_text("#!/bin/sh\n")
        real_cli(str(w), "getblockcount")
        assert calls[-1] == [str(w), "getblockcount"]
finally:
    subprocess.run = real_run

print("migration-broadcast: ok")
