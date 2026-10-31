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
prep.cli = fake_cli([{"txid": "r", "vout": 0, "amount": 250000000, "scriptPubKey": "51"}])
try:
    prep.build_batches("x", chunks, "Achange")
    raise SystemExit("expected refusal: one UTXO cannot fund several batches")
except RuntimeError as e:
    assert "fan-out" in str(e)

# 3. Fan-out from many cold-staked 50,000 outputs: <= MAX_INPUTS_PER_TX inputs per tx,
#    every batch address funded exactly to its need, change only to the change address.
reserve = [{"txid": f"r{i}", "vout": 0, "amount": 50000.0, "address": "Areserve", "scriptPubKey": "51"} for i in range(1200)]
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
for t in txs:  # the offline signer needs each input's script and amount
    assert [(p["txid"], p["vout"]) for p in t["prevouts"]] == [(i["txid"], i["vout"]) for i in t["inputs"]]
    assert all(p["scriptPubKey"] and Decimal(p["amount"]) == 50000 for p in t["prevouts"])
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
state["mempool"] = [{"txid": "m", "vout": n, "amount": float(Decimal(v)), "address": a, "scriptPubKey": "51"}
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
            conf.append({"txid": t["batch_index"], "vout": n, "amount": float(Decimal(v)), "address": a, "scriptPubKey": "51"})
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

# ---------------------------------------------------------------------------
# 7. The node CLI string is split like the other scripts (shlex), and every call
#    gets the configurable timeout (default 300 s, not 60 s).
import os
import subprocess
import tempfile

spec2 = importlib.util.spec_from_file_location("prep2", Path(__file__).with_name("migration-prepare.py"))
prep2 = importlib.util.module_from_spec(spec2)
spec2.loader.exec_module(prep2)  # a fresh copy with the real cli()
calls = []
class _P:
    returncode, stdout, stderr = 0, "[]\n", ""
def fake_run(argv, **kw):
    calls.append((argv, kw))
    return _P()
real_run = subprocess.run
subprocess.run = fake_run
try:
    assert prep2.CLI_TIMEOUT_SEC == 300 == prep2.DEFAULT_CLI_TIMEOUT_SEC
    prep2.list_watch_utxos('ammocoin-cli -datadir="/Volumes/x y/builder" -conf=/c.conf')
    argv, kw = calls[-1]
    assert argv[:3] == ["ammocoin-cli", "-datadir=/Volumes/x y/builder", "-conf=/c.conf"], argv
    assert argv[3:] == ["listunspent", "1", "9999999", "[]", "2", "{}", "false"], argv
    assert kw["timeout"] == 300
    prep2.cli("ammocoin-cli", "getblockcount")
    assert calls[-1][0] == ["ammocoin-cli", "getblockcount"]
    with tempfile.TemporaryDirectory() as d:  # an existing path with a space stays one program
        wrapper = Path(d) / "my cli.sh"
        wrapper.write_text("#!/bin/sh\n")
        prep2.cli(str(wrapper), "getblockcount")
        assert calls[-1][0] == [str(wrapper), "getblockcount"]
    prep2.CLI_TIMEOUT_SEC = 900
    prep2.cli("ammocoin-cli", "listunspent")
    assert calls[-1][1]["timeout"] == 900
finally:
    subprocess.run = real_run
try:
    prep2.cli_argv("   ")
    raise SystemExit("expected refusal: empty CLI command")
except ValueError:
    pass

# 8. Timeout: --cli-timeout wins over AMMO_CLI_TIMEOUT, which wins over the default.
assert prep.resolve_timeout(None, {}) == 300
assert prep.resolve_timeout(None, {"AMMO_CLI_TIMEOUT": "600"}) == 600
assert prep.resolve_timeout(120, {"AMMO_CLI_TIMEOUT": "600"}) == 120
assert prep.resolve_timeout(None, {"AMMO_CLI_TIMEOUT": ""}) == 300
for bad in ({"AMMO_CLI_TIMEOUT": "abc"}, {"AMMO_CLI_TIMEOUT": "0"}):
    try:
        prep.resolve_timeout(None, bad)
        raise AssertionError(f"expected refusal for {bad}")
    except SystemExit as e:
        assert "AMMO_CLI_TIMEOUT" in str(e) or "positive" in str(e)
try:
    prep.resolve_timeout(-5, {})
    raise AssertionError("expected refusal for a negative timeout")
except SystemExit:
    pass

# 9. P2CS script: rebuild the reserve's published cold-stake script
#    (scripts/migration/README.md, RESERVES.md: owner AGkC8…, staker SUr6…) byte for byte.
RESERVE_P2CS = ("76a97b63d11452da7b2840e451a37d750ece77eb4a0d94cdea3f67140aa6bab8b080064897a63eca2edbffb6aac514576888ac")
readme = Path(__file__).with_name("README.md").read_text()
assert RESERVE_P2CS in readme, "README's reserve script changed; update this test"
OWNER, STAKER = "AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME", "SUr6AuNGxozrTP5jL94narQVJPfrLDSiqY"
staker_h, owner_h = prep.parse_p2cs(bytes.fromhex(RESERVE_P2CS))
assert prep.b58check_encode(prep.PUBKEY_ADDRESS_PREFIX, owner_h) == OWNER
assert prep.b58check_encode(prep.STAKING_ADDRESS_PREFIX, staker_h) == STAKER
assert prep.b58check_decode(OWNER) == (23, owner_h) and prep.b58check_decode(STAKER) == (63, staker_h)
assert prep.cold_stake_script_for(OWNER, STAKER).hex() == RESERVE_P2CS
assert prep.p2cs_script(staker_h, owner_h, lof=False).hex() == RESERVE_P2CS[:8] + "d2" + RESERVE_P2CS[10:]
assert prep.parse_p2cs(prep.p2cs_script(staker_h, owner_h, lof=False)) == (staker_h, owner_h)
assert prep.p2pkh_script(owner_h).hex() == "76a914" + owner_h.hex() + "88ac"
for bad_owner, bad_staker in ((STAKER, STAKER), (OWNER, OWNER), (OWNER, STAKER[:-1] + "r"), ("0OIl", STAKER)):
    try:
        prep.cold_stake_script_for(bad_owner, bad_staker)
        raise AssertionError(f"expected refusal for owner {bad_owner} staker {bad_staker}")
    except ValueError:
        pass
try:
    prep.parse_p2cs(prep.p2pkh_script(owner_h))
    raise AssertionError("a P2PKH script is not P2CS")
except ValueError:
    pass

# 10. The tx parser round-trips real legacy transactions byte for byte
#     (Bitcoin-format vectors from source/src/test/data/tx_valid.json; AMMOcoin's
#     int16 version 1 + int16 type 0 serialize as the same 01000000 header).
vec = json.loads((Path(__file__).resolve().parents[2] / "source/src/test/data/tx_valid.json").read_text())
legacy = [e[1] for e in vec if len(e) >= 2 and isinstance(e[0], list) and str(e[1]).startswith("01000000")]
n_ok = 0
for h in legacy:
    try:
        t = prep.parse_tx(h)
    except ValueError:
        continue  # e.g. segwit-marker vectors, which this chain doesn't use
    assert prep.serialize_tx(t) == h
    n_ok += 1
assert n_ok >= 20, n_ok
for h in ("02000000" + legacy[0][8:], "01000100" + legacy[0][8:], legacy[0] + "00"):
    try:
        prep.parse_tx(h)
        raise AssertionError("expected refusal: sapling/special version or trailing bytes")
    except ValueError:
        pass

# 11. Payout batches with cold-stake recipients (pools 3-5), end to end with a
#     stub node that serializes real transactions and decodes P2CS like core_write.cpp.
import hashlib
def addr(prefix, seed):
    return prep.b58check_encode(prefix, hashlib.new("ripemd160", seed.encode()).digest()
                                if "ripemd160" in hashlib.algorithms_available else hashlib.sha256(seed.encode()).digest()[:20])
def stub_ser(inputs, outputs):  # independent of prep.serialize_tx
    b = bytes.fromhex("01000000") + bytes([len(inputs)])
    for i in inputs:
        b += bytes.fromhex(i["txid"])[::-1] + i["vout"].to_bytes(4, "little") + b"\x00" + b"\xff" * 4
    b += bytes([len(outputs)])
    for a, v in outputs.items():
        spk = bytes.fromhex("76a914") + prep.b58check_decode(a)[1] + bytes.fromhex("88ac")
        b += int(Decimal(v) * 100_000_000).to_bytes(8, "little") + bytes([len(spk)]) + spk
    return (b + b"\x00" * 4).hex()
def stub_decode(h):
    t = prep.parse_tx(h)
    vout = []
    for value, spk in t["vout"]:
        try:
            s_h, o_h = prep.parse_p2cs(spk)
            pk = {"hex": spk.hex(), "type": "coldstake",
                  "addresses": [prep.b58check_encode(63, s_h), prep.b58check_encode(23, o_h)]}
        except ValueError:
            pk = {"hex": spk.hex(), "type": "pubkeyhash", "addresses": [prep.b58check_encode(23, spk[3:23])]}
        vout.append({"value": value / 1e8, "scriptPubKey": pk})
    return {"txid": "t", "vout": vout}
def fake_cli3(utxos, tamper=False):
    def cli(binary, *args):
        if args[0] == "listunspent":
            return json.dumps(utxos)
        if args[0] == "createrawtransaction":
            return stub_ser(json.loads(args[1]), json.loads(args[2]))
        if args[0] == "decoderawtransaction":
            d = stub_decode(args[1])
            if tamper:
                for v in d["vout"]:
                    if v["scriptPubKey"]["type"] == "coldstake":
                        v["scriptPubKey"]["addresses"].reverse()
            return json.dumps(d)
        raise AssertionError(args)
    return cli
P3, P4, P5 = (addr(23, f"pool{i}") for i in (3, 4, 5))
STK2 = addr(63, "other-staker")
pools = [{"address": P3, "balance": "31052139.91421180"}, {"address": P4, "balance": "38815174.89276473"},
         {"address": P5, "balance": "41700.00000000", "staker": STK2}]
assert prep.apply_staker(pools, STAKER) == 3
assert [h["staker"] for h in pools] == [STAKER, STAKER, STK2], "a holder's own staker wins over the flag"
pm, pe = prep.split_oversize(pools)
assert all(h["staker"] for h in pm + pe), "oversize parts keep the staker"
pchunks = prep.plan_chunks(pm, pe)
assert len(pchunks) == 7
pfan = [addr(23, f"fan{i}") for i in range(len(pchunks))]
CHANGE = addr(23, "change")
putxos = [{"txid": hashlib.sha256(f"u{k}".encode()).hexdigest(), "vout": 0, "address": a, "scriptPubKey": "51",
           "amount": float(prep.chunk_need(c))} for k, (c, a) in enumerate(zip(pchunks, pfan))]
prep.cli = fake_cli3(putxos)
pb = prep.build_batches("x", pchunks, CHANGE, pfan)
assert len(pb) == 7
total_cs = Decimal(0)
for b, c in zip(pb, pchunks):
    t = prep.parse_tx(b["unsigned_hex"])
    assert len(t["vout"]) == len(b["outputs"]) == len(c), "funded exactly: no change output"
    assert set(b["cold_stake"]) == {h["address"] for h in c}
    for k, h in enumerate(c):  # createrawtransaction keeps the outputs object's order
        want = prep.cold_stake_script_for(h["address"], h["staker"])
        assert t["vout"][k][1] == want and t["vout"][k][0] == prep.to_sat(h["balance"])
        assert b["cold_stake"][h["address"]] == {"staker": h["staker"], "script_hex": want.hex(),
                                                 "amount": f"{Decimal(h['balance']):.8f}"}
        total_cs += Decimal(h["balance"])
assert total_cs == sum(Decimal(h["balance"]) for h in pools)
# what the offline signer checks (decoded addresses -> amount) still matches batch["outputs"]
d = stub_decode(pb[0]["unsigned_hex"])
assert d["vout"][0]["scriptPubKey"]["addresses"] == [STAKER, P3]

# Mixed batch: one cold-stake recipient among plain ones; plain outputs untouched.
mixed = [{"address": addr(23, f"m{i}"), "balance": "10"} for i in range(4)]
mixed[2]["staker"] = STAKER
mutxo = [{"txid": "ab" * 32, "vout": 1, "address": "Afund", "scriptPubKey": "51", "amount": 40.002}]
prep.cli = fake_cli3(mutxo)
mb = prep.build_batches("x", [mixed], CHANGE, ["Afund"])[0]
mt = prep.parse_tx(mb["unsigned_hex"])
plain = prep.parse_tx(stub_ser(mb["inputs"], mb["outputs"]))
for k, (o, p) in enumerate(zip(mt["vout"], plain["vout"])):
    assert o[0] == p[0]
    assert (o[1] == p[1]) == (k != 2)
assert list(mb["cold_stake"]) == [mixed[2]["address"]]
assert mt["vin"] == plain["vin"] and mt["locktime"] == plain["locktime"]

# Without any staker nothing changes: the plain path is byte-identical.
prep.cli = fake_cli3(mutxo)
nb = prep.build_batches("x", [[{"address": h["address"], "balance": h["balance"]} for h in mixed]], CHANGE, ["Afund"])[0]
assert "cold_stake" not in nb and nb["unsigned_hex"] == stub_ser(nb["inputs"], nb["outputs"])

# Refusals: below the 1 AMMO consensus minimum; a node decode that disagrees; bad staker.
tiny = [{"address": addr(23, "tiny"), "balance": "0.5", "staker": STAKER}]
prep.cli = fake_cli3([{"txid": "cd" * 32, "vout": 0, "address": "Afund", "scriptPubKey": "51", "amount": 0.502}])
try:
    prep.build_batches("x", [tiny], CHANGE, ["Afund"])
    raise AssertionError("expected refusal: cold-stake output below 1 AMMO")
except RuntimeError as e:
    assert "minimum" in str(e)
prep.cli = fake_cli3(mutxo, tamper=True)
try:
    prep.build_batches("x", [mixed], CHANGE, ["Afund"])
    raise AssertionError("expected refusal: node decode disagrees")
except RuntimeError as e:
    assert "does not decode" in str(e)
for bad in ([{"address": OWNER, "balance": "5", "staker": OWNER}], [{"address": STAKER, "balance": "5", "staker": STAKER}]):
    try:
        prep.apply_staker(bad, None)
        raise AssertionError("expected refusal: staker must be an S... address and owner an A... address")
    except ValueError:
        pass
plain_holders = [{"address": OWNER, "balance": "5"}]
assert prep.apply_staker(plain_holders, None) == 0 and "staker" not in plain_holders[0]
print("migration-prepare: ok")
