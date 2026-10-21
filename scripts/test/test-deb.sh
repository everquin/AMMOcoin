#!/usr/bin/env bash
# End-to-end test of the AMMOcoin .deb on a disposable Ubuntu 22.04+/Debian 12+ machine
# (CI runner or VM) with systemd. Installs the package, checks user/conf/params/service,
# waits for the node to answer RPC, reinstalls (conf must survive), removes, and purges.
#
#   sudo apt-get purge -y ammocoin; scripts/test/test-deb.sh ./AMMOcoin-v1.1.1-Linux-amd64.deb
#
# It starts a real mainnet node for up to ~3 minutes. Don't run it on a machine whose
# /var/lib/ammocoin you care about (it is left in place, but the service is stopped).
set -euo pipefail
DEB=${1:?path to the .deb}
case "$DEB" in /*|./*) ;; *) DEB=./$DEB ;; esac
CONF=/var/lib/ammocoin/.ammocoin11/ammocoin.conf
fail() { echo "FAIL: $*" >&2; sudo journalctl -u ammocoind --no-pager 2>/dev/null | tail -30 >&2 || true; exit 1; }
pass() { echo "ok: $*"; }

[ -d /run/systemd/system ] || fail "this test needs systemd"
echo "== glibc $(getconf GNU_LIBC_VERSION)"
dpkg-deb --field "$DEB" Package Version Architecture Depends
sudo apt-get install -y "$DEB"

id ammocoin >/dev/null || fail "user ammocoin not created"; pass "user ammocoin exists"
[ "$(getent passwd ammocoin | cut -d: -f6)" = /var/lib/ammocoin ] || fail "ammocoin HOME is not /var/lib/ammocoin"
[ "$(sudo stat -c '%a %U' "$CONF")" = "600 ammocoin" ] || fail "$CONF is not mode 600 owned by ammocoin"
sudo grep -qE '^rpcpassword=[A-Za-z0-9]{20,}$' "$CONF" || fail "no random rpcpassword"
{ sudo grep -qx 'port=37020' "$CONF" && sudo grep -qx 'rpcport=51473' "$CONF"; } || fail "ports not 37020/51473"
pass "conf $CONF"
ammocoin-fetch-params --dir /nonexistent --check || fail "packaged Sapling params missing/invalid"
pass "Sapling params in /usr/share/ammocoin"
VER=$(ammocoind -version | head -1); echo "   $VER"
case "$VER" in *v1.1.1*) ;; *) fail "ammocoind is not v1.1.1" ;; esac
case "$VER" in *dirty*) fail "version string is -dirty" ;; esac
systemctl cat ammocoind | grep -q '^Environment=HOME=/var/lib/ammocoin' || fail "unit lacks Environment=HOME"
systemctl is-enabled --quiet ammocoind || fail "service not enabled"

ok=0
for _ in $(seq 1 90); do
  if ammocoin-node-cli getblockcount >/dev/null 2>&1; then ok=1; break; fi
  systemctl is-active --quiet ammocoind || break
  sleep 2
done
[ "$ok" = 1 ] || { sudo tail -40 /var/lib/ammocoin/.ammocoin11/debug.log >&2 || true; fail "service did not answer RPC"; }
pass "service answers RPC, height $(ammocoin-node-cli getblockcount)"
sudo grep -q "Loaded Sapling parameters" /var/lib/ammocoin/.ammocoin11/debug.log || fail "Sapling params not loaded"
pass "Sapling params loaded by the service"

# a desktop user without ~/.ammocoin-params must also be able to start the node
U=$(mktemp -d); trap 'rm -rf "$U"' EXIT
mkdir -p "$U/data"
HOME=$U timeout 60 ammocoind -datadir="$U/data" -port=37990 -rpcport=51990 -listen=0 -connect=0 -daemon=0 \
  -printtoconsole=0 >/dev/null 2>&1 &
PID=$!
ok=0
for _ in $(seq 1 30); do
  if grep -q "Loaded Sapling parameters" "$U/data/debug.log" 2>/dev/null; then ok=1; break; fi
  kill -0 $PID 2>/dev/null || break
  sleep 2
done
kill $PID 2>/dev/null || true; wait $PID 2>/dev/null || true
[ "$ok" = 1 ] || { tail -20 "$U/data/debug.log" >&2 || true; fail "per-user node could not load the packaged params"; }
pass "per-user node finds the packaged params"

sudo cp "$CONF" /tmp/ammocoin.conf.before
sudo apt-get install -y --reinstall "$DEB"
sudo cmp -s /tmp/ammocoin.conf.before "$CONF" || fail "reinstall changed ammocoin.conf"
pass "reinstall kept ammocoin.conf"

sudo apt-get remove -y ammocoin
systemctl is-active --quiet ammocoind && fail "service still running after remove"
sudo test -f "$CONF" || fail "remove deleted the conf"
sudo apt-get purge -y ammocoin
sudo test -d /var/lib/ammocoin || fail "purge deleted /var/lib/ammocoin"
pass "remove/purge keep data and stop the service"
echo "ALL .deb TESTS PASSED"
