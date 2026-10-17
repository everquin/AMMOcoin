#!/bin/bash
# AMMOcoin Linux Qt wallet smoke test - regtest only, throwaway datadir, never mainnet.
#
#   scripts/test/linux-qt-smoke-test.sh <ammocoin-qt> <bin-dir> <params-dir> <work-dir>
#
#   <bin-dir> must contain ammocoind and ammocoin-cli for the same architecture.
#
#   1. ammocoind -regtest creates the wallet in <work-dir>/regtest-qt, then stops. With a
#      wallet.dat present the GUI skips its interactive first-run tutorial (ammocoin.cpp:
#      "Check if at least one wallet exists, otherwise prompt tutorial"); passing -datadir
#      skips the data-directory intro (Intro::pickDataDirectory).
#   2. ammocoin-qt -regtest under xvfb-run on that datadir: the script proves the GUI process
#      opened <datadir>/regtest/debug.log, waits for "Loaded Sapling parameters" and RPC,
#      checks the chain is regtest, calls getnewshieldaddress, then stops it via RPC.
# Any failure exits non-zero. HOME/XDG dirs point into <work-dir> so QSettings and the
# default ~/.ammocoin* paths of the runner are never touched.
set -euo pipefail
QTBIN=${1:?ammocoin-qt binary}; BIN=${2:?bin dir}; PARAMS=${3:?params dir}; WORK=${4:?work dir}
QTBIN="$(cd "$(dirname "$QTBIN")" && pwd)/$(basename "$QTBIN")"
BIN="$(cd "$BIN" && pwd)"; PARAMS="$(cd "$PARAMS" && pwd)"
mkdir -p "$WORK"; WORK="$(cd "$WORK" && pwd -P)"  # physical path: compared with /proc/<pid>/fd links
[ -n "$WORK" ] && [ "$WORK" != / ] && [ "$WORK" != "$HOME" ] || { echo "refusing work dir $WORK" >&2; exit 1; }
for f in "$QTBIN" "$BIN/ammocoind" "$BIN/ammocoin-cli"; do
  [ -x "$f" ] || { echo "missing or not executable: $f" >&2; exit 1; }
done
for f in sapling-spend.params sapling-output.params; do
  [ -s "$PARAMS/$f" ] || { echo "missing $PARAMS/$f" >&2; exit 1; }
done
command -v xvfb-run >/dev/null || { echo "xvfb-run not installed" >&2; exit 1; }
PORT=${SMOKE_PORT:-39524}
QD="$WORK/regtest-qt"; FAKEHOME="$WORK/home"
rm -rf "$QD" "$FAKEHOME"; mkdir -p "$QD" "$FAKEHOME"
export HOME="$FAKEHOME" XDG_CONFIG_HOME="$FAKEHOME/.config" XDG_DATA_HOME="$FAKEHOME/.local/share"

ARGS=(-regtest "-datadir=$QD" "-port=$PORT" "-rpcport=$((PORT+1))" -rpcuser=smoke -rpcpassword=smoke
      -listen=0 -dnsseed=0 -connect=0 -upnp=0 -natpmp=0 "-paramsdir=$PARAMS")
cli() { "$BIN/ammocoin-cli" -regtest "-datadir=$QD" "-rpcport=$((PORT+1))" -rpcuser=smoke -rpcpassword=smoke "$@"; }
LOG="$QD/regtest/debug.log"

XPID=; NODEPID=
cleanup() {
  [ -n "$NODEPID" ] && kill "$NODEPID" 2>/dev/null || true
  [ -n "$XPID" ] && kill "$XPID" 2>/dev/null || true
  pkill -f -- "-datadir=$QD" 2>/dev/null || true
}
trap cleanup EXIT

# Wait until <pid> has <file> open (proves it is using the throwaway regtest datadir).
wait_open() { # pid file
  for _ in $(seq 1 120); do
    for fd in "/proc/$1/fd"/*; do
      [ "$(readlink "$fd" 2>/dev/null)" = "$2" ] && return 0
    done
    kill -0 "$1" 2>/dev/null || { echo "process $1 exited early" >&2; return 1; }
    sleep 0.5
  done
  echo "process $1 did not open $2 - wrong datadir/network? killing it" >&2
  kill "$1" 2>/dev/null || true; return 1
}
wait_rpc() { # pid
  for _ in $(seq 1 180); do
    cli getblockcount >/dev/null 2>&1 && return 0
    kill -0 "$1" 2>/dev/null || { echo "process $1 exited before RPC came up" >&2; return 1; }
    sleep 1
  done
  echo "RPC did not come up within 180s" >&2; return 1
}
wait_exit() { # pid seconds
  for _ in $(seq 1 "$2"); do kill -0 "$1" 2>/dev/null || return 0; sleep 1; done; return 1
}
check_regtest() {
  local chain
  chain=$(cli getblockchaininfo | python3 -c 'import json,sys; print(json.load(sys.stdin)["chain"])')
  echo "chain: $chain"; [ "$chain" = regtest ] || { echo "not regtest!" >&2; exit 1; }
}

echo "=== 1. ammocoind -regtest: create the wallet so the GUI skips its first-run tutorial"
"$BIN/ammocoind" "${ARGS[@]}" -printtoconsole=0 &
NODEPID=$!
wait_open "$NODEPID" "$LOG"
wait_rpc "$NODEPID"
check_regtest
cli stop >/dev/null; wait "$NODEPID"; NODEPID=
[ -f "$QD/regtest/wallet.dat" ] || [ -f "$QD/regtest/wallets/wallet.dat" ] \
  || { echo "ammocoind did not create a regtest wallet.dat" >&2; ls -la "$QD/regtest" >&2; exit 1; }
mv "$LOG" "$QD/regtest/debug-daemon.log"

echo "=== 2. ammocoin-qt -regtest (Xvfb)"
xvfb-run -a -s "-screen 0 1280x1024x24" "$QTBIN" "${ARGS[@]}" -server=1 \
  > "$WORK/qt-stdout.log" 2>&1 &
XPID=$!
QTPID=
for _ in $(seq 1 60); do
  QTPID=$(pgrep -P "$XPID" -f -- "-datadir=$QD" | head -1 || true)
  [ -n "$QTPID" ] && break
  kill -0 "$XPID" 2>/dev/null || break
  sleep 0.5
done
[ -n "$QTPID" ] || { echo "ammocoin-qt did not start under xvfb-run" >&2; cat "$WORK/qt-stdout.log" >&2; exit 1; }
echo "ammocoin-qt pid $QTPID"
fail() { echo "$1" >&2; tail -40 "$LOG" >&2 2>/dev/null || true; cat "$WORK/qt-stdout.log" >&2; exit 1; }
wait_open "$QTPID" "$LOG" || fail "ammocoin-qt is not using $QD/regtest"
for _ in $(seq 1 120); do
  grep -q "Loaded Sapling parameters" "$LOG" 2>/dev/null && break
  kill -0 "$QTPID" 2>/dev/null || fail "ammocoin-qt exited before loading the Sapling params"
  sleep 1
done
grep -q "Loaded Sapling parameters" "$LOG" || fail "ammocoin-qt did not reach 'Loaded Sapling parameters' within 120s"
wait_rpc "$QTPID" || fail "ammocoin-qt RPC not ready"
check_regtest
z=$(cli getnewshieldaddress); echo "qt getnewshieldaddress: $z"
[[ "$z" == ptestsapling1* ]] || fail "unexpected shield address: $z"
cli stop >/dev/null
wait_exit "$QTPID" 90 || fail "ammocoin-qt did not quit after RPC stop"
wait_exit "$XPID" 30 || fail "xvfb-run did not exit after ammocoin-qt quit"
wait "$XPID" || true; XPID=
grep -E "version v|Loaded Sapling parameters|Shutdown: done" "$LOG"
grep -q "Shutdown: done" "$LOG" || fail "ammocoin-qt did not shut down cleanly"
pix=$(grep -c "Could not create pixmap" "$LOG" || true)
echo "missing pixmaps: $pix"; [ "$pix" = 0 ] || fail "ammocoin-qt is missing pixmaps"
echo "=== Linux Qt smoke test passed"
