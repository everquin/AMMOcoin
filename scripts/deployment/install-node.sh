#!/usr/bin/env bash
# AMMOcoin v1.1.1 one-command node installer (Ubuntu 22.04+ / Debian 12+).
#
# Installs the daemon as a systemd service running as a dedicated "ammocoin" user,
# fetches and verifies the Sapling parameters, writes ammocoin.conf and opens P2P port 37020.
#
#   sudo ./install-node.sh --tarball <file-or-url> --sha256 <hex> [--role node|coldstaker|masternode]
#                          [--mnkey <masternode private key>] [--ip <public IPv4>] [--dry-run]
#
# Roles
#   node        relays blocks; stakes coins in its own wallet if you send any (default)
#   coldstaker  stakes coins delegated from an offline wallet; the owner keys never touch this server
#   masternode  needs --mnkey (from `createmasternodekey` in your controller wallet) and a public IPv4;
#               the 10,000 AMMO collateral stays in your controller wallet
set -euo pipefail

P2P_PORT=37020
RPC_PORT=51473
SVC_USER=ammocoin
SVC_HOME=/var/lib/ammocoin
DATADIR=$SVC_HOME/.ammocoincore
PARAMS_DIR=$SVC_HOME/.ammocoin-params
PARAMS_URL=https://download.z.cash/downloads
SPEND_SHA=8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13
OUTPUT_SHA=2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4

ROLE=node TARBALL="" SHA="" MNKEY="" IP="" DRY=0
die() { echo "error: $*" >&2; exit 1; }
run() { if [ "$DRY" = 1 ]; then echo "+ $*"; else "$@"; fi; }

while [ $# -gt 0 ]; do
  case "$1" in
    --tarball) TARBALL=$2; shift 2 ;;
    --sha256)  SHA=$2; shift 2 ;;
    --role)    ROLE=$2; shift 2 ;;
    --mnkey)   MNKEY=$2; shift 2 ;;
    --ip)      IP=$2; shift 2 ;;
    --dry-run) DRY=1; shift ;;
    -h|--help) sed -n '2,17p' "$0"; exit 0 ;;
    *) die "unknown option $1 (see --help)" ;;
  esac
done

[ "$(id -u)" = 0 ] || die "run as root (sudo)"
[ -n "$TARBALL" ] && [ -n "$SHA" ] || die "--tarball and --sha256 are required (checksums are on the release page)"
[[ $SHA =~ ^[0-9a-fA-F]{64}$ ]] || die "--sha256 must be the 64-character SHA-256 from the release page"
case "$ROLE" in node|coldstaker|masternode) ;; *) die "--role must be node, coldstaker or masternode" ;; esac

# v1.1.1 Linux builds need glibc 2.34+ (Ubuntu 22.04 or newer). 18.04/20.04 must be upgraded first.
GLIBC=$(ldd --version | head -1 | grep -oE '[0-9]+\.[0-9]+$')
[ "$(printf '%s\n2.34\n' "$GLIBC" | sort -V | head -1)" = 2.34 ] \
  || die "glibc $GLIBC is too old; v1.1.1 needs 2.34+ (Ubuntu 22.04 or newer)"

is_public_ipv4() {
  [[ $1 =~ ^([0-9]{1,3})\.([0-9]{1,3})\.[0-9]{1,3}\.[0-9]{1,3}$ ]] || return 1
  local a=${BASH_REMATCH[1]} b=${BASH_REMATCH[2]}
  ! { [ "$a" = 10 ] || [ "$a" = 127 ] || [ "$a" = 0 ] || { [ "$a" = 172 ] && [ "$b" -ge 16 ] && [ "$b" -le 31 ]; } \
      || { [ "$a" = 192 ] && [ "$b" = 168 ]; } || { [ "$a" = 169 ] && [ "$b" = 254 ]; } || { [ "$a" = 100 ] && [ "$b" -ge 64 ] && [ "$b" -le 127 ]; }; }
}
if [ "$ROLE" = masternode ]; then
  [ -n "$MNKEY" ] || die "--mnkey is required for a masternode (run createmasternodekey in your controller wallet)"
  [ -n "$IP" ] || IP=$(ip -4 route get 1.1.1.1 2>/dev/null | grep -oP 'src \K[0-9.]+' || true)
  is_public_ipv4 "${IP:-x}" || die "masternodes need a public IPv4 on port $P2P_PORT; pass --ip <public address> (got '${IP:-none}')"
fi

WORK=$(mktemp -d); trap 'rm -rf "$WORK"' EXIT
echo "==> Fetching and verifying $TARBALL"
case "$TARBALL" in
  http://*|https://*) curl -fsSL "$TARBALL" -o "$WORK/ammocoin.tar.gz" ;;
  *) cp "$TARBALL" "$WORK/ammocoin.tar.gz" ;;
esac
echo "$SHA  $WORK/ammocoin.tar.gz" | sha256sum -c --quiet - || die "checksum mismatch; do not use this file"
tar xzf "$WORK/ammocoin.tar.gz" -C "$WORK"
[ -x "$WORK/bin/ammocoind" ] || die "tarball has no bin/ammocoind"
VER=$("$WORK/bin/ammocoind" -version | head -1 | grep -oE 'v[0-9]+\.[0-9]+\.[0-9]+' || echo unknown)
PREFIX=/opt/ammocoin-$VER

echo "==> Installing $VER to $PREFIX"
run install -d "$PREFIX/bin"
run install -m 755 "$WORK/bin/ammocoind" "$WORK/bin/ammocoin-cli" "$PREFIX/bin/"
[ -f "$WORK/bin/ammocoin-tx" ] && run install -m 755 "$WORK/bin/ammocoin-tx" "$PREFIX/bin/"
run ln -sf "$PREFIX/bin/ammocoind" /usr/local/bin/ammocoind

id "$SVC_USER" >/dev/null 2>&1 || run useradd --system --home-dir "$SVC_HOME" --create-home --shell /usr/sbin/nologin "$SVC_USER"
run install -d -m 700 -o "$SVC_USER" -g "$SVC_USER" "$DATADIR" "$PARAMS_DIR"

echo "==> Sapling parameters"
for f in sapling-spend.params:$SPEND_SHA sapling-output.params:$OUTPUT_SHA; do
  name=${f%%:*} sum=${f#*:}
  if [ -f "$PARAMS_DIR/$name" ] && echo "$sum  $PARAMS_DIR/$name" | sha256sum -c --quiet - 2>/dev/null; then
    echo "    $name ok"; continue
  fi
  run curl -fsSL "$PARAMS_URL/$name" -o "$WORK/$name"
  [ "$DRY" = 1 ] || echo "$sum  $WORK/$name" | sha256sum -c --quiet - || die "$name checksum mismatch"
  run install -m 600 -o "$SVC_USER" -g "$SVC_USER" "$WORK/$name" "$PARAMS_DIR/$name"
done

CONF=$DATADIR/ammocoin.conf
if [ -f "$CONF" ]; then
  echo "==> Keeping existing $CONF"
else
  echo "==> Writing $CONF ($ROLE)"
  {
    echo "server=1"; echo "listen=1"; echo "port=$P2P_PORT"
    echo "rpcport=$RPC_PORT"; echo "rpcbind=127.0.0.1"; echo "rpcallowip=127.0.0.1"
    echo "rpcuser=ammocoin"; echo "rpcpassword=$(head -c 24 /dev/urandom | base64 | tr -dc A-Za-z0-9)"
    if [ "$ROLE" = masternode ]; then
      echo "staking=0"; echo "masternode=1"; echo "masternodeprivkey=$MNKEY"
      echo "masternodeaddr=$IP:$P2P_PORT"; echo "externalip=$IP"
    else
      echo "staking=1"
    fi
  } > "$WORK/ammocoin.conf"
  run install -m 600 -o "$SVC_USER" -g "$SVC_USER" "$WORK/ammocoin.conf" "$CONF"
fi

echo "==> systemd service ammocoind"
cat > "$WORK/ammocoind.service" <<EOF
[Unit]
Description=AMMOcoin node ($ROLE)
After=network-online.target
Wants=network-online.target

[Service]
User=$SVC_USER
Group=$SVC_USER
# The node looks for Sapling parameters under \$HOME; without this it exits at startup.
Environment=HOME=$SVC_HOME
ExecStart=$PREFIX/bin/ammocoind -datadir=$DATADIR -daemon=0
ExecStop=$PREFIX/bin/ammocoin-cli -datadir=$DATADIR stop
Restart=on-failure
RestartSec=30
TimeoutStopSec=120

[Install]
WantedBy=multi-user.target
EOF
run install -m 644 "$WORK/ammocoind.service" /etc/systemd/system/ammocoind.service

# `ammocoin-cli` for admins: runs as the service user against the service's data folder.
cat > "$WORK/ammocoin-cli" <<EOF
#!/bin/sh
exec sudo -u $SVC_USER HOME=$SVC_HOME $PREFIX/bin/ammocoin-cli -datadir=$DATADIR "\$@"
EOF
run install -m 755 "$WORK/ammocoin-cli" /usr/local/bin/ammocoin-cli

if command -v ufw >/dev/null && ufw status | grep -q "Status: active"; then
  run ufw allow "$P2P_PORT"/tcp
else
  echo "    note: no active ufw; make sure TCP $P2P_PORT is open in your provider's firewall"
fi

run systemctl daemon-reload
run systemctl enable --now ammocoind

echo
echo "AMMOcoin $VER installed as '$ROLE'. Check progress with:  ammocoin-cli getblockcount"
case "$ROLE" in
  coldstaker) echo "Next: ammocoin-cli getnewstakingaddress   then, in your own wallet:"
              echo "      delegatestake <that S... address> <amount>   (coins stake after 600 confirmations)" ;;
  masternode) echo "Next: once synced, add this line to masternode.conf in your controller wallet and restart it:"
              echo "      <alias> $IP:$P2P_PORT <masternode key> <collateral txid> <index>   (from getmasternodeoutputs)"
              echo "      then run: startmasternode alias false <alias>" ;;
  node)       echo "To stake here, send coins to an address from: ammocoin-cli getnewaddress (they stake after 600 confirmations)." ;;
esac
