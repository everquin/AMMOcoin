#!/usr/bin/env bash
# Package the Linux GUI wallet.
#
#   scripts/packaging/build-linux-qt-packages.sh <label: x86_64|ARM64> <ammocoin-qt> <params-dir> <out-dir>
#
# Always writes AMMOcoin-v1.1.1-Linux-<label>-Qt.tar.gz:
#   bin/ammocoin-qt  bin/ammocoin-fetch-params  install-desktop.sh  README.txt
#   share/applications/ammocoin-qt.desktop  share/icons/hicolor/256x256/apps/ammocoin.png
# With APPIMAGETOOL, APPIMAGE_RUNTIME and APPIMAGE_ARCH (x86_64|aarch64) set, also writes
# AMMOcoin-v1.1.1-Linux-<label>-Qt.AppImage, which bundles the SHA-256 checked Sapling params.
set -euo pipefail

LABEL=${1:?label} QT=${2:?ammocoin-qt binary} PARAMS=${3:?params dir} OUT=${4:?out dir}
HERE=$(cd "$(dirname "$0")" && pwd)
REPO=$(cd "$HERE/../.." && pwd)
NAME="AMMOcoin-v1.1.1-Linux-$LABEL-Qt"
ICON="$REPO/source/share/pixmaps/ammocoin256.png"
[ -x "$QT" ] || { echo "missing $QT" >&2; exit 1; }
mkdir -p "$OUT"; OUT=$(cd "$OUT" && pwd)

STAGE=$(mktemp -d "${TMPDIR:-/tmp}/ammocoin-qt.XXXXXX")
trap 'rm -rf "$STAGE"' EXIT

# tarball
T="$STAGE/tar"
install -d "$T/bin" "$T/share/applications" "$T/share/icons/hicolor/256x256/apps"
install -m 755 "$QT" "$T/bin/ammocoin-qt"
install -m 755 "$HERE/ammocoin-fetch-params" "$T/bin/ammocoin-fetch-params"
install -m 755 "$HERE/linux-qt/install-desktop.sh" "$T/install-desktop.sh"
install -m 644 "$HERE/linux-qt/ammocoin-qt.desktop" "$T/share/applications/ammocoin-qt.desktop"
install -m 644 "$ICON" "$T/share/icons/hicolor/256x256/apps/ammocoin.png"
sed "s/@ARCH@/$LABEL/g" "$HERE/linux-qt/README.txt" > "$T/README.txt"
rm -f "$OUT/$NAME.tar.gz"
(cd "$T" && tar -czf "$OUT/$NAME.tar.gz" bin share install-desktop.sh README.txt)
echo "built $OUT/$NAME.tar.gz"
tar -tzvf "$OUT/$NAME.tar.gz"

# AppImage
if [ -n "${APPIMAGETOOL:-}" ]; then
  : "${APPIMAGE_RUNTIME:?APPIMAGE_RUNTIME (type2 runtime file) required}" "${APPIMAGE_ARCH:?APPIMAGE_ARCH required}"
  sha() { if command -v sha256sum >/dev/null; then sha256sum "$1"; else shasum -a 256 "$1"; fi | awk '{print $1}'; }
  [ "$(sha "$PARAMS/sapling-spend.params")" = 8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13 ] \
    && [ "$(sha "$PARAMS/sapling-output.params")" = 2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4 ] \
    || { echo "Sapling params in $PARAMS missing or bad checksum" >&2; exit 1; }
  A="$STAGE/AMMOcoin.AppDir"
  install -d "$A/usr/bin" "$A/usr/share/ammocoin" "$A/usr/share/applications" "$A/usr/share/icons/hicolor/256x256/apps"
  install -m 755 "$QT" "$A/usr/bin/ammocoin-qt"
  install -m 755 "$HERE/ammocoin-fetch-params" "$A/usr/bin/ammocoin-fetch-params"
  install -m 755 "$HERE/linux-qt/AppRun" "$A/AppRun"
  install -m 644 "$PARAMS/sapling-spend.params" "$PARAMS/sapling-output.params" "$A/usr/share/ammocoin/"
  install -m 644 "$HERE/linux-qt/ammocoin-qt.desktop" "$A/usr/share/applications/ammocoin-qt.desktop"
  install -m 644 "$HERE/linux-qt/ammocoin-qt.desktop" "$A/ammocoin-qt.desktop"
  install -m 644 "$ICON" "$A/usr/share/icons/hicolor/256x256/apps/ammocoin.png"
  install -m 644 "$ICON" "$A/ammocoin.png"
  ln -s ammocoin.png "$A/.DirIcon"
  rm -f "$OUT/$NAME.AppImage"
  ARCH="$APPIMAGE_ARCH" "$APPIMAGETOOL" --no-appstream --runtime-file "$APPIMAGE_RUNTIME" "$A" "$OUT/$NAME.AppImage"
  chmod 755 "$OUT/$NAME.AppImage"
  echo "built $OUT/$NAME.AppImage ($(du -h "$OUT/$NAME.AppImage" | cut -f1))"
fi
