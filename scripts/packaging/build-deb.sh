#!/usr/bin/env bash
# Build the AMMOcoin .deb (headless node + CLI tools + Sapling params + systemd service).
#
#   scripts/packaging/build-deb.sh <amd64|arm64> <bin-dir> <params-dir> <output.deb>
#
# <bin-dir> holds ammocoind, ammocoin-cli, ammocoin-tx; <params-dir> holds the two Sapling
# .params files (both are SHA-256 checked). Used by build-linux-static.yml and build-arm64.yml;
# runs anywhere dpkg-deb exists (Linux, or macOS with Homebrew dpkg).
set -euo pipefail

ARCH=${1:?arch (amd64|arm64)} BIN=${2:?bin dir} PARAMS=${3:?params dir} OUT=${4:?output .deb}
VERSION=${DEB_VERSION:-1.1.1-2}
HERE=$(cd "$(dirname "$0")" && pwd)
REPO=$(cd "$HERE/../.." && pwd)
SPEND_SHA=8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13
OUTPUT_SHA=2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4

die() { echo "build-deb: $*" >&2; exit 1; }
sha256_of() { if command -v sha256sum >/dev/null; then sha256sum "$1"; else shasum -a 256 "$1"; fi | awk '{print $1}'; }

case "$ARCH" in amd64|arm64) ;; *) die "arch must be amd64 or arm64" ;; esac
for b in ammocoind ammocoin-cli ammocoin-tx; do [ -x "$BIN/$b" ] || die "missing $BIN/$b"; done
[ "$(sha256_of "$PARAMS/sapling-spend.params")" = "$SPEND_SHA" ] || die "sapling-spend.params missing or bad checksum"
[ "$(sha256_of "$PARAMS/sapling-output.params")" = "$OUTPUT_SHA" ] || die "sapling-output.params missing or bad checksum"

STAGE=$(mktemp -d "${TMPDIR:-/tmp}/ammocoin-deb.XXXXXX")
trap 'rm -rf "$STAGE"' EXIT
ROOT="$STAGE/ammocoin_${VERSION}_${ARCH}"
DOC="$ROOT/usr/share/doc/ammocoin"
install -d "$ROOT/DEBIAN" "$ROOT/usr/bin" "$ROOT/usr/share/ammocoin" "$ROOT/lib/systemd/system" "$DOC/examples"

install -m 755 "$BIN/ammocoind" "$BIN/ammocoin-cli" "$BIN/ammocoin-tx" "$ROOT/usr/bin/"
install -m 755 "$HERE/ammocoin-fetch-params" "$ROOT/usr/bin/ammocoin-fetch-params"
install -m 755 "$HERE/deb/ammocoin-node-cli" "$ROOT/usr/bin/ammocoin-node-cli"
install -m 644 "$PARAMS/sapling-spend.params" "$PARAMS/sapling-output.params" "$ROOT/usr/share/ammocoin/"
install -m 644 "$HERE/deb/ammocoind.service" "$ROOT/lib/systemd/system/ammocoind.service"
install -m 644 "$HERE/deb/README.Debian" "$DOC/README.Debian"
install -m 644 "$REPO/source/contrib/debian/examples/ammocoin.conf" "$DOC/examples/ammocoin.conf"
install -m 644 "$REPO/source/COPYING" "$DOC/copyright"
for s in postinst prerm postrm; do install -m 755 "$HERE/deb/$s" "$ROOT/DEBIAN/$s"; done

INSTALLED_SIZE=$(du -sk "$ROOT" | cut -f1)
cat > "$ROOT/DEBIAN/control" <<EOF
Package: ammocoin
Version: $VERSION
Architecture: $ARCH
Maintainer: AMMOcoin Core <dev@ammocoin.org>
Depends: libc6 (>= 2.34), adduser, ca-certificates, curl | wget
Recommends: systemd
Section: net
Priority: optional
Homepage: https://www.ammocoin.org
Installed-Size: $INSTALLED_SIZE
Description: AMMOcoin v1.1.1 node and command-line tools (Proof of Stake)
 AMMOcoin is a Proof-of-Stake cryptocurrency (v1.1.1 PoS hard fork) with
 staking, cold staking and masternodes.
 .
 This package provides the headless node (ammocoind), the RPC client
 (ammocoin-cli), the transaction tool (ammocoin-tx), the Sapling parameters
 and a systemd service that runs the node as the "ammocoin" user with its
 data in /var/lib/ammocoin/.ammocoin11. The GUI wallet is not included.
 Binaries link libstdc++/libgcc and all other libraries statically; only
 glibc 2.34+ is needed.
EOF

# dpkg-deb wants root-owned files; --root-owner-group needs dpkg >= 1.19
dpkg-deb --root-owner-group -Zxz --build "$ROOT" "$OUT" >/dev/null
echo "built $OUT ($(du -h "$OUT" | cut -f1))"
