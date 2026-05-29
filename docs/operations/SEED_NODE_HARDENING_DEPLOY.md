# Seed Node Deploy Checklist — RPC Hardening Patch

Deploy the hardening patch (tasks 1–7 from the production-readiness audit)
to **one** seed node first, verify, then roll forward. The patch contains
no consensus changes — patched and unpatched v1.1 nodes interoperate
identically on the wire.

**What's in the patch:**
- OP_RETURN size-check fix (`sendopreturn` / `createrawtransaction "data"`)
- RPC server hardening: per-IP brute-force lockout, HTTP body cap 32 MiB → 8 MiB, secure cookie file creation, `createrawtransaction` input/output count cap
- Tunables added: `-rpcmaxbodysize`, `-rpcauthmaxfails`, `-rpcauthfailwindow`, `-rpcauthlockout`

## Pre-flight (on the seed node)

```bash
# 1. Identify the current binary and its version
which ammocoind
ammocoind --version
ammocoin-cli getnetworkinfo | jq .version
ammocoin-cli getblockchaininfo | jq '{blocks, bestblockhash, chain}'

# 2. Record peer count and a few peer IPs (baseline for rollback verification)
ammocoin-cli getpeerinfo | jq '[.[] | {addr, subver, synced_blocks}] | .[0:5]'
ammocoin-cli getconnectioncount

# 3. Confirm RPC clients in use (so we don't surprise anything)
sudo lsof -i:51473 | grep -v ESTABLISHED   # mainnet RPC port
journalctl -u ammocoind --since "1 hour ago" | grep -iE "rpc|auth|error"

# 4. Snapshot wallet.dat (small; takes seconds)
sudo cp ~ammocoin/.ammocoin/wallet.dat /var/backups/wallet.dat.pre-hardening.$(date +%F)
sudo chmod 600 /var/backups/wallet.dat.pre-hardening.*

# 5. Snapshot the current binary (rollback artifact)
sudo cp $(which ammocoind) /var/backups/ammocoind.pre-hardening
sudo cp $(which ammocoin-cli) /var/backups/ammocoin-cli.pre-hardening
sudo cp $(which ammocoin-tx) /var/backups/ammocoin-tx.pre-hardening
```

## Build the Linux binary (on a builder VM)

Run on a clean Ubuntu 22.04 VM (or use your existing `vultr-quick-build.sh`
host). Do **not** build on the seed node itself — building consumes CPU
and RAM that the daemon needs.

```bash
# On the builder VM, fresh clone
git clone https://github.com/everquin/AMMOcoin.git AMMOcoin-hardening
cd AMMOcoin-hardening
# Apply the local patch if it's not yet pushed — see "Apply local patch" below.

cd source
./autogen.sh
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

# Use all cores; ~15-20 min on a 4-vCPU Vultr
make -j$(nproc) CARGO=$HOME/.cargo/bin/cargo RUSTC=$HOME/.cargo/bin/rustc

# Verify binary works and is the patched version
src/ammocoind --version
src/ammocoind -help-debug | grep -E "rpcauthmaxfails|rpcmaxbodysize"
# Expect both new options to appear — confirms the patch is in.

sha256sum src/ammocoind src/ammocoin-cli src/ammocoin-tx > checksums.txt
cat checksums.txt
```

Copy the three binaries + `checksums.txt` to the seed node:

```bash
scp src/ammocoind src/ammocoin-cli src/ammocoin-tx checksums.txt \
    root@seed1.ammocoin.org:/tmp/hardening/
```

## Apply the deploy on the seed node

```bash
# 1. Verify checksums match what the builder reported
cd /tmp/hardening
sha256sum -c checksums.txt  # expect: 3x OK

# 2. Stop the daemon cleanly. The systemd unit (per scripts/deployment/setup-seed-node.sh)
#    is named `ammocoin.service`. Adjust if your unit is named differently.
sudo systemctl stop ammocoin
# Confirm it's down (wait up to 60s for clean shutdown)
sleep 5 && pgrep -af ammocoind || echo "stopped"

# 3. Swap binaries
sudo install -m 755 /tmp/hardening/ammocoind   $(which ammocoind)
sudo install -m 755 /tmp/hardening/ammocoin-cli $(which ammocoin-cli)
sudo install -m 755 /tmp/hardening/ammocoin-tx  $(which ammocoin-tx)

# 4. (Optional) Pre-set the new tunables in ammocoin.conf if you want
#    non-default values. The defaults are fine for production:
#      -rpcauthmaxfails=5  -rpcauthfailwindow=60  -rpcauthlockout=300
#      -rpcmaxbodysize=8388608  (8 MiB)
#    If RPC is behind a reverse proxy on this host, set:
#      rpcauthmaxfails=0
#    to disable the per-IP lockout (avoids one bad client locking everyone out
#    via the shared proxy IP).
sudo nano /etc/ammocoin/ammocoin.conf   # only if changing defaults

# 5. Start the daemon
sudo systemctl start ammocoin

# 6. Wait ~10s for RPC to come up, then verify
sleep 10
ammocoin-cli getnetworkinfo | jq '{version, subversion, connections}'
ammocoin-cli getblockchaininfo | jq '{blocks, bestblockhash, headers}'
```

## Smoke tests (run within 5 minutes of restart)

```bash
# A. Block sync — should be catching up if it was offline
ammocoin-cli getblockchaininfo | jq '{blocks, headers, verificationprogress}'

# B. P2P peers — should be re-connecting; expect 8-25 within a minute
ammocoin-cli getpeerinfo | jq 'length'
ammocoin-cli getpeerinfo | jq '[.[] | .subver] | unique'

# C. RPC auth lockout doesn't false-positive — try a legit RPC call repeatedly
for i in {1..10}; do ammocoin-cli getblockcount; done
# Expect: 10 consecutive blockcount outputs, no auth errors.

# D. HTTP body cap accepts a sizeable payload — test with sendrawtransaction
#    using a non-broadcast (decode-only) call on a real tx
EXAMPLE_TXID=$(ammocoin-cli getblockhash 1 | xargs ammocoin-cli getblock | jq -r '.tx[0]')
RAW=$(ammocoin-cli getrawtransaction "$EXAMPLE_TXID")
ammocoin-cli decoderawtransaction "$RAW" | jq '.txid'
# Expect: txid printed, no error.

# E. OP_RETURN size check still works for the AMMO-AUTH payload size
#    (this is a dry-run via createrawtransaction; nothing is broadcast)
UTXO=$(ammocoin-cli listunspent | jq -r '.[0]')
[ -n "$UTXO" ] && {
  TXID=$(echo "$UTXO" | jq -r '.txid')
  VOUT=$(echo "$UTXO" | jq -r '.vout')
  # 58-byte payload (AMMO-AUTH REGISTER size) — should succeed
  ammocoin-cli createrawtransaction \
    "[{\"txid\":\"$TXID\",\"vout\":$VOUT}]" \
    "{\"data\":\"$(printf 'ab%.0s' {1..58})\"}" >/dev/null \
    && echo "✓ 58-byte OP_RETURN accepted"
  # 100-byte payload — should be rejected with a clear error
  ammocoin-cli createrawtransaction \
    "[{\"txid\":\"$TXID\",\"vout\":$VOUT}]" \
    "{\"data\":\"$(printf 'ab%.0s' {1..100})\"}" 2>&1 \
    | grep -q "scriptPubKey too large" \
    && echo "✓ 100-byte OP_RETURN rejected with clear error"
}

# F. Check debug.log for any new errors in the last 60s
tail -200 ~ammocoin/.ammocoin/debug.log | grep -iE "error|fatal|warning" | tail -20
```

## What to watch for over the first 24 hours

```bash
# Run periodically:
journalctl -u ammocoin --since "10 minutes ago" \
  | grep -iE "rpc|locking out|cookie|insufficient|denied" \
  | tail -50

# Peer count should match the pre-deploy baseline (±a few)
ammocoin-cli getconnectioncount

# Should match other seed nodes (consensus check)
ammocoin-cli getbestblockhash
# Cross-check against another seed
```

**Red flags that should trigger immediate rollback:**
- `getbestblockhash` diverges from other seeds for more than 5 blocks
- `getconnectioncount` stays at <2 for more than 5 minutes after start
- Repeated `cookie authentication file` errors in debug.log
- Any kind of crash / segfault / `assert` in the log

## Rollback

```bash
sudo systemctl stop ammocoin
sudo install -m 755 /var/backups/ammocoind.pre-hardening   $(which ammocoind)
sudo install -m 755 /var/backups/ammocoin-cli.pre-hardening $(which ammocoin-cli)
sudo install -m 755 /var/backups/ammocoin-tx.pre-hardening  $(which ammocoin-tx)
sudo systemctl start ammocoin
sleep 10 && ammocoin-cli getblockchaininfo | jq '{blocks, bestblockhash}'
```

Wallet.dat is on-disk and unchanged by the binary swap — no wallet
restore needed under rollback.

## After 24h of success on the first seed

Repeat steps "Apply the deploy on the seed node" → "Smoke tests" on each
remaining seed, one at a time, with a 15-minute gap between to confirm
each is healthy before moving to the next. Block 51473 RPC port from
external networks (or keep it loopback-only) so the new auth lockout
isn't accidentally fed real attack traffic during the rollout.
