#!/usr/bin/env bash
# Build AMMOcoin-v1.1.1-Linux-<label>.tar.gz and .zip from a `make install` prefix.
#
#   scripts/packaging/build-linux-archives.sh <label: x86_64|ARM64> <dist-dir> <out-dir>
#
# Layout (install-node.sh expects bin/ammocoind at the top level):
#   bin/{ammocoind,ammocoin-cli,ammocoin-tx,ammocoin-fetch-params}  install-node.sh  README.txt
set -euo pipefail

LABEL=${1:?label} DIST=${2:?dist dir} OUT=${3:?out dir}
HERE=$(cd "$(dirname "$0")" && pwd)
REPO=$(cd "$HERE/../.." && pwd)
NAME="AMMOcoin-v1.1.1-Linux-$LABEL"

for b in ammocoind ammocoin-cli ammocoin-tx; do
  [ -x "$DIST/bin/$b" ] || { echo "missing $DIST/bin/$b" >&2; exit 1; }
done

STAGE=$(mktemp -d "${TMPDIR:-/tmp}/ammocoin-pkg.XXXXXX")
trap 'rm -rf "$STAGE"' EXIT
install -d "$STAGE/bin"
install -m 755 "$DIST/bin/ammocoind" "$DIST/bin/ammocoin-cli" "$DIST/bin/ammocoin-tx" "$STAGE/bin/"
if [ -x "$DIST/bin/ammocoin-qt" ]; then install -m 755 "$DIST/bin/ammocoin-qt" "$STAGE/bin/"; fi
install -m 755 "$HERE/ammocoin-fetch-params" "$STAGE/bin/ammocoin-fetch-params"
install -m 755 "$REPO/scripts/deployment/install-node.sh" "$STAGE/install-node.sh"
sed "s/@ARCH@/$LABEL/g" "$HERE/README-linux.txt" > "$STAGE/README.txt"

mkdir -p "$OUT"
OUT=$(cd "$OUT" && pwd)
rm -f "$OUT/$NAME.tar.gz" "$OUT/$NAME.zip"
(cd "$STAGE" && tar -czf "$OUT/$NAME.tar.gz" bin install-node.sh README.txt)
(cd "$STAGE" && zip -qr "$OUT/$NAME.zip" bin install-node.sh README.txt)
echo "built $OUT/$NAME.tar.gz and $OUT/$NAME.zip"
tar -tzvf "$OUT/$NAME.tar.gz"
