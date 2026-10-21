#!/usr/bin/env bash
#
# regtest-payouts.sh — end-to-end verification of the AMMO payout endpoint
# against a throwaway regtest ammocoind. Proves the happy path AND the
# safe-refund / idempotency contract before any real AMMO is at risk.
#
# WHAT IT DOES
#   1. boots a disposable regtest ammocoind (temp datadir, own ports)
#   2. mines coins into the gateway wallet
#   3. boots the gateway (next dev) against that daemon, with a temp DB
#   4. mints a gateway API key
#   5. runs assertions:
#        T1 happy     POST valid send                  -> 200 status=sent + txid
#        T2 idempotent repeat same idempotency_key     -> same txid, no re-send
#        T3 min       amount below MIN_PAYOUT_AMMO      -> 200 status=failed/minimum
#        T4 invalid   bad address                       -> 200 status=failed/invalid
#        T5 insufficient amount > wallet balance        -> 200 status=failed/insufficient
#        T6 cap       amount > MAX_PAYOUT_AMMO          -> 200 status=failed/maximum
#   6. tears everything down (always, via trap)
#
# PREREQUISITES
#   - ammocoind + ammocoin-cli built. Override discovery with:
#       AMMOCOIND=/path/to/ammocoind  AMMOCOIN_CLI=/path/to/ammocoin-cli
#   - node + npm; the gateway's node_modules (auto-installed if missing).
#   - This fork must support regtest mining (generatetoaddress/generate/
#     setgenerate). If funding fails the script stops with guidance.
#
# USAGE
#   bash scripts/regtest-payouts.sh
#
set -uo pipefail

# ── Config ───────────────────────────────────────────────────────────────────
GW_DIR="$(cd "$(dirname "$0")/.." && pwd)"
RPCPORT="${RPCPORT:-51475}"
RPCUSER="regtestuser"
RPCPASS="regtestpass_$$"
GW_PORT="${GW_PORT:-3100}"
API="http://127.0.0.1:${GW_PORT}"
WORK="$(mktemp -d "${TMPDIR:-/tmp}/ammo-regtest.XXXXXX")"
DATADIR="${WORK}/chain"
GWDB="${WORK}/regtest-gateway.db"
GW_LOG="${WORK}/gateway.log"
DAEMON_LOG="${WORK}/ammocoind.log"
mkdir -p "$DATADIR"

# Caps chosen so each failure mode is deterministic regardless of block subsidy.
export MAX_PAYOUT_AMMO="1000000000000000"   # 1e15 — only the explicit T6 exceeds it
export MIN_PAYOUT_AMMO="0.0001"

PASS=0; FAIL=0
GW_PID=""

# ── Locate binaries ──────────────────────────────────────────────────────────
find_bin() {
  local name="$1"; shift
  for c in "$@"; do [ -x "$c" ] && { echo "$c"; return 0; }; done
  command -v "$name" 2>/dev/null && return 0
  return 1
}
AMMOCOIND="${AMMOCOIND:-$(find_bin ammocoind \
  "${GW_DIR}/../source/src/ammocoind" \
  "${GW_DIR}/../../ammocoin-app/binaries/ammocoind")}"
AMMOCOIN_CLI="${AMMOCOIN_CLI:-$(find_bin ammocoin-cli \
  "${GW_DIR}/../source/src/ammocoin-cli" \
  "${GW_DIR}/../../ammocoin-app/binaries/ammocoin-cli")}"

if [ -z "${AMMOCOIND:-}" ] || [ -z "${AMMOCOIN_CLI:-}" ]; then
  echo "ERROR: ammocoind / ammocoin-cli not found." >&2
  echo "Build them or set AMMOCOIND=... AMMOCOIN_CLI=... and re-run." >&2
  exit 2
fi

acli() { "$AMMOCOIN_CLI" -regtest -datadir="$DATADIR" -rpcport="$RPCPORT" \
  -rpcuser="$RPCUSER" -rpcpassword="$RPCPASS" "$@"; }

# ── Cleanup (always) ─────────────────────────────────────────────────────────
cleanup() {
  echo ""
  echo "── tearing down ──"
  [ -n "$GW_PID" ] && kill "$GW_PID" 2>/dev/null
  # kill any child next/node under the gateway pid group
  pkill -P "${GW_PID:-0}" 2>/dev/null
  acli stop >/dev/null 2>&1
  sleep 2
  rm -rf "$WORK"
  echo "removed $WORK"
}
trap cleanup EXIT INT TERM

# ── JSON field helper (node is already a dependency) ─────────────────────────
jget() {
  node -e 'let s="";process.stdin.on("data",d=>s+=d).on("end",()=>{let o;try{o=JSON.parse(s)}catch(e){process.stdout.write("");return}let v=o;for(const k of process.argv[1].split("."))v=(v==null?undefined:v[k]);process.stdout.write(v==null?"":String(v))})' "$1"
}
assert_eq()       { if [ "$2" = "$3" ]; then echo "  PASS: $1"; PASS=$((PASS+1)); else echo "  FAIL: $1 (expected '$2', got '$3')"; FAIL=$((FAIL+1)); fi; }
assert_contains() { case "$3" in *"$2"*) echo "  PASS: $1"; PASS=$((PASS+1));; *) echo "  FAIL: $1 (expected to contain '$2', got '$3')"; FAIL=$((FAIL+1));; esac; }
assert_nonempty() { if [ -n "$2" ]; then echo "  PASS: $1"; PASS=$((PASS+1)); else echo "  FAIL: $1 (was empty)"; FAIL=$((FAIL+1)); fi; }

CODE=""; BODY=""
post_payout() { # addr amount key
  local resp
  resp=$(curl -s -w $'\n%{http_code}' -X POST "${API}/api/payouts" \
    -H "Authorization: Bearer ${APIKEY}" -H 'Content-Type: application/json' \
    -d "{\"address\":\"$1\",\"amount\":$2,\"idempotency_key\":\"$3\"}")
  CODE="${resp##*$'\n'}"; BODY="${resp%$'\n'*}"
}

# ── 1. Boot regtest daemon ───────────────────────────────────────────────────
echo "── starting regtest ammocoind ──"
"$AMMOCOIND" -regtest -datadir="$DATADIR" -rpcport="$RPCPORT" \
  -rpcuser="$RPCUSER" -rpcpassword="$RPCPASS" -server=1 -listen=0 \
  -txindex=1 -daemon >"$DAEMON_LOG" 2>&1 || { echo "ammocoind failed to start; see $DAEMON_LOG" >&2; exit 1; }

echo -n "  waiting for RPC"
for i in $(seq 1 30); do
  if acli getblockchaininfo >/dev/null 2>&1; then echo " ok"; break; fi
  echo -n "."; sleep 1
  [ "$i" = 30 ] && { echo " timeout"; echo "RPC never came up; see $DAEMON_LOG" >&2; exit 1; }
done

# ── 2. Fund the wallet ───────────────────────────────────────────────────────
echo "── mining coins ──"
MINEADDR="$(acli getnewaddress 2>/dev/null)"
acli generatetoaddress 250 "$MINEADDR" >/dev/null 2>&1 \
  || acli generate 250 >/dev/null 2>&1 \
  || acli setgenerate true 250 >/dev/null 2>&1 \
  || echo "  (warning: standard mining RPCs failed — checking balance anyway)"
BAL="$(acli getbalance 2>/dev/null || echo 0)"
echo "  wallet balance: ${BAL} AMMO"
if ! node -e "process.exit(Number(process.argv[1])>=1?0:1)" "$BAL"; then
  echo "ERROR: wallet has <1 AMMO after mining — regtest funding failed." >&2
  echo "This fork may use a different mining RPC; inspect: $DAEMON_LOG" >&2
  exit 1
fi

# ── 3. Boot the gateway ──────────────────────────────────────────────────────
echo "── starting gateway (next dev) ──"
if [ ! -d "${GW_DIR}/node_modules" ]; then
  echo "  installing gateway deps (one-time)…"
  ( cd "$GW_DIR" && npm install >"${WORK}/npm-install.log" 2>&1 ) || { echo "npm install failed; see ${WORK}/npm-install.log" >&2; exit 1; }
fi
(
  cd "$GW_DIR"
  AMMOCOIN_RPC_URL="http://127.0.0.1:${RPCPORT}" \
  AMMOCOIN_RPC_USER="$RPCUSER" \
  AMMOCOIN_RPC_PASSWORD="$RPCPASS" \
  DATABASE_PATH="$GWDB" \
  npm run dev
) >"$GW_LOG" 2>&1 &
GW_PID=$!

echo -n "  waiting for /api/health"
HEALTHY=0
for i in $(seq 1 60); do
  H="$(curl -s "${API}/api/health" 2>/dev/null)"
  if [ "$(echo "$H" | jget status)" = "ok" ]; then echo " ok"; HEALTHY=1; break; fi
  echo -n "."; sleep 1
done
if [ "$HEALTHY" != 1 ]; then
  echo " timeout"; echo "gateway never became healthy; see $GW_LOG" >&2; tail -20 "$GW_LOG" >&2; exit 1
fi

# ── 4. Mint an API key ───────────────────────────────────────────────────────
APIKEY="$(cd "$GW_DIR" && DATABASE_PATH="$GWDB" MERCHANT_ID="glibz-regtest" node scripts/create-api-key.mjs 2>/dev/null)"
[ -n "$APIKEY" ] || { echo "ERROR: failed to mint API key" >&2; exit 1; }
echo "  minted API key: ${APIKEY:0:18}…"

DEST="$(acli getnewaddress 2>/dev/null)"

# ── 5. Assertions ────────────────────────────────────────────────────────────
echo ""
echo "── running payout assertions ──"

echo "T1 happy path:"
post_payout "$DEST" 1 "k-happy"
assert_eq       "T1 http 200"        "200"     "$CODE"
assert_eq       "T1 status sent"     "sent"    "$(echo "$BODY" | jget status)"
TXID1="$(echo "$BODY" | jget txid)"; ID1="$(echo "$BODY" | jget id)"
assert_nonempty "T1 txid present"    "$TXID1"
acli generatetoaddress 1 "$MINEADDR" >/dev/null 2>&1 || acli generate 1 >/dev/null 2>&1 || true
S="$(curl -s "${API}/api/payouts/${ID1}" -H "Authorization: Bearer ${APIKEY}")"
assert_eq       "T1 status endpoint" "sent"    "$(echo "$S" | jget status)"

echo "T2 idempotency (same key, must NOT re-send):"
post_payout "$DEST" 1 "k-happy"
assert_eq       "T2 status sent"     "sent"    "$(echo "$BODY" | jget status)"
assert_eq       "T2 same id"         "$ID1"    "$(echo "$BODY" | jget id)"
assert_eq       "T2 same txid"       "$TXID1"  "$(echo "$BODY" | jget txid)"

echo "T3 below minimum:"
post_payout "$DEST" 0.00000001 "k-min"
assert_eq       "T3 http 200"        "200"     "$CODE"
assert_eq       "T3 status failed"   "failed"  "$(echo "$BODY" | jget status)"
assert_contains "T3 reason minimum"  "minimum" "$(echo "$BODY" | jget reason)"

echo "T4 invalid address:"
post_payout "definitely_not_a_valid_ammo_address" 1 "k-invalid"
assert_eq       "T4 status failed"   "failed"  "$(echo "$BODY" | jget status)"
assert_contains "T4 reason invalid"  "invalid" "$(echo "$BODY" | jget reason)"

echo "T5 insufficient funds:"
OVER="$(node -e "console.log(Number(process.argv[1])+1000)" "$BAL")"
post_payout "$DEST" "$OVER" "k-insufficient"
assert_eq       "T5 status failed"       "failed"        "$(echo "$BODY" | jget status)"
assert_contains "T5 reason insufficient" "insufficient"  "$(echo "$BODY" | jget reason)"

echo "T6 over per-payout cap:"
post_payout "$DEST" 2000000000000000 "k-cap"
assert_eq       "T6 status failed"   "failed"  "$(echo "$BODY" | jget status)"
assert_contains "T6 reason maximum"  "maximum" "$(echo "$BODY" | jget reason)"

# ── Report ───────────────────────────────────────────────────────────────────
echo ""
echo "════════════════════════════════════════"
echo "  PASS: ${PASS}   FAIL: ${FAIL}"
echo "════════════════════════════════════════"
[ "$FAIL" -eq 0 ] && exit 0 || exit 1
