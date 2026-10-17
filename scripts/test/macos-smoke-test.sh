#!/bin/bash
# AMMOcoin macOS package smoke test - regtest only, throwaway datadirs, never mainnet.
#
#   scripts/test/macos-smoke-test.sh <bin-dir> <AMMOcoin-Qt.app> <params-dir> <work-dir>
#
#   1. ammocoind -regtest: getblockchaininfo, generate 5, getnewaddress, getnewshieldaddress, stop
#   2. AMMOcoin-Qt -version (offscreen)
#   3. AMMOcoin-Qt -regtest (offscreen, Sapling params from the app bundle), RPC check, stop
# Each node is started with an argument array; before any RPC the script proves the process
# opened <work-dir>/.../regtest/debug.log, and aborts (killing it) otherwise.
set -euo pipefail
BIN=${1:?bin dir}; APP=${2:?app path}; PARAMS=${3:?params dir}; WORK=${4:?work dir}
BIN="$(cd "$BIN" && pwd)"; APP="$(cd "$APP" && pwd)"; PARAMS="$(cd "$PARAMS" && pwd)"
mkdir -p "$WORK"; WORK="$(cd "$WORK" && pwd)"
[ -n "$WORK" ] && [ "$WORK" != / ] && [ "$WORK" != "$HOME" ] || { echo "refusing work dir $WORK" >&2; exit 1; }
QTBIN="$APP/Contents/MacOS/AMMOcoin-Qt"
PORT=${SMOKE_PORT:-39424}

NODEPID=
cleanup() { [ -n "$NODEPID" ] && kill "$NODEPID" 2>/dev/null || true; }
trap cleanup EXIT

wait_datadir() { # pid datadir
  for _ in $(seq 1 120); do
    # (capture first: with pipefail, grep -q closing the pipe early fails the lsof side)
    open_files=$(lsof -p "$1" 2>/dev/null || true)
    if grep -qF "$2/regtest/debug.log" <<<"$open_files"; then return 0; fi
    kill -0 "$1" 2>/dev/null || { echo "process $1 exited early" >&2; return 1; }
    sleep 0.5
  done
  echo "process $1 did not open $2/regtest/debug.log - wrong datadir/network? killing it" >&2
  kill "$1" 2>/dev/null || true; return 1
}
wait_rpc() { for _ in $(seq 1 180); do "$BIN/ammocoin-cli" "$@" getblockcount >/dev/null 2>&1 && return 0; sleep 1; done; return 1; }

echo "=== 1. ammocoind -regtest"
DD="$WORK/regtest-daemon"; rm -rf "$DD"; mkdir -p "$DD"
ARGS=(-regtest "-datadir=$DD" "-port=$PORT" "-rpcport=$((PORT+1))" -rpcuser=smoke -rpcpassword=smoke
      -listen=0 -dnsseed=0 -connect=0 -upnp=0 -natpmp=0)
"$BIN/ammocoind" "${ARGS[@]}" "-paramsdir=$PARAMS" -printtoconsole=0 &
NODEPID=$!
wait_datadir "$NODEPID" "$DD"
cli() { "$BIN/ammocoin-cli" "${ARGS[@]}" "$@"; }
wait_rpc "${ARGS[@]}"
chain=$(cli getblockchaininfo | python3 -c 'import json,sys; print(json.load(sys.stdin)["chain"])')
echo "chain: $chain"; [ "$chain" = regtest ] || { echo "not regtest!" >&2; exit 1; }
cli generate 5 >/dev/null
blocks=$(cli getblockcount); echo "blocks after generate 5: $blocks"; [ "$blocks" = 5 ]
echo "getnewaddress: $(cli getnewaddress)"
z=$(cli getnewshieldaddress); echo "getnewshieldaddress: $z"; [[ "$z" == ptestsapling1* ]]
cli stop >/dev/null; wait "$NODEPID"; NODEPID=
grep -E "version v|Loaded Sapling parameters|Shutdown: done" "$DD/regtest/debug.log"

echo "=== 2. AMMOcoin-Qt -version (offscreen)"
QT_QPA_PLATFORM=offscreen "$QTBIN" -version | head -1

echo "=== 3. AMMOcoin-Qt -regtest (offscreen)"
QD="$WORK/regtest-qt"; EMPTY="$WORK/empty-paramsdir"; rm -rf "$QD" "$EMPTY"; mkdir -p "$QD" "$EMPTY"
QARGS=(-regtest "-datadir=$QD" "-port=$((PORT+10))" "-rpcport=$((PORT+11))" -server=1 -rpcuser=smoke -rpcpassword=smoke
       -listen=0 -dnsseed=0 -connect=0 -upnp=0 -natpmp=0)
# Pre-create the wallet so the GUI skips its interactive first-run tutorial.
"$BIN/ammocoind" "${QARGS[@]}" "-paramsdir=$PARAMS" -printtoconsole=0 &
NODEPID=$!; wait_datadir "$NODEPID" "$QD"; wait_rpc "${QARGS[@]}"
"$BIN/ammocoin-cli" "${QARGS[@]}" stop >/dev/null; wait "$NODEPID"; NODEPID=
mv "$QD/regtest/debug.log" "$QD/regtest/debug-daemon.log"
# An existing but empty -paramsdir makes the GUI fall back to the params inside the app bundle.
QT_QPA_PLATFORM=offscreen "$QTBIN" "${QARGS[@]}" "-paramsdir=$EMPTY" &
NODEPID=$!
wait_datadir "$NODEPID" "$QD"
wait_rpc "${QARGS[@]}"
qchain=$("$BIN/ammocoin-cli" "${QARGS[@]}" getblockchaininfo | python3 -c 'import json,sys; print(json.load(sys.stdin)["chain"])')
echo "qt chain: $qchain"; [ "$qchain" = regtest ]
echo "qt getnewshieldaddress: $("$BIN/ammocoin-cli" "${QARGS[@]}" getnewshieldaddress)"
"$BIN/ammocoin-cli" "${QARGS[@]}" stop >/dev/null
for _ in $(seq 1 60); do kill -0 "$NODEPID" 2>/dev/null || break; sleep 1; done
kill -0 "$NODEPID" 2>/dev/null && { echo "AMMOcoin-Qt did not quit" >&2; exit 1; }
wait "$NODEPID" || true; NODEPID=
grep -E "version v|params in app bundle|Loaded Sapling parameters|Shutdown: done" "$QD/regtest/debug.log"
pix=$(grep -c "Could not create pixmap" "$QD/regtest/debug.log" || true)
echo "missing pixmaps: $pix"; [ "$pix" = 0 ]
echo "=== smoke test passed"
