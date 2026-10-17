#!/bin/bash
# AMMOcoin v1.1.1 - package a native macOS build (arm64 or x86_64).
#
#   scripts/packaging/macos/package-macos.sh <output-dir>
#
# Environment:
#   QT_PREFIX   Qt 5 used for the build (default: $(brew --prefix)/opt/qt@5); its macdeployqt is used
#   MAX_MINOS   fail if any Mach-O in the package needs a newer macOS than this (e.g. 13.0)
#
# Produces a self-contained AMMOcoin-Qt.app (macdeployqt), bin/ (any non-system dylibs are copied
# into bin/lib by dylibbundler), ad-hoc signatures, and AMMOcoin-v1.1.1-macOS-<ARCH>.{dmg,tar.gz,zip,SHA256}.
# Fails on any reference to Homebrew / /usr/local paths, or a -dirty version.
set -euo pipefail
OUT=${1:?usage: $0 <output-dir>}
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
SRC="$ROOT/source"
QT_PREFIX=${QT_PREFIX:-$(brew --prefix 2>/dev/null)/opt/qt@5}
VER=1.1.1
case "$(uname -m)" in arm64) ARCHNAME=ARM64 ;; x86_64) ARCHNAME=x86_64 ;; *) echo "unknown arch" >&2; exit 1 ;; esac
NAME=AMMOcoin-v$VER-macOS-$ARCHNAME
minos_of() { otool -l "$1" | awk '/LC_BUILD_VERSION/{b=1} b&&/minos/{print $2; exit} /LC_VERSION_MIN_MACOSX/{v=1} v&&/version/{print $2; exit}'; }

mkdir -p "$OUT"; OUT="$(cd "$OUT" && pwd)"
ST="$OUT/staging-$ARCHNAME"; rm -rf "$ST"; mkdir -p "$ST/dmg" "$ST/$NAME/bin"

# --- GUI bundle ---
( cd "$SRC" && PATH="$QT_PREFIX/bin:$PATH" ACLOCAL=: AUTOCONF=: AUTOMAKE=: AUTOHEADER=: make appbundle >/dev/null )
"$ROOT/scripts/ci/check-build-version.sh" "$SRC/src/obj/build.h" "$SRC/AMMOcoin-Qt.app/Contents/MacOS/AMMOcoin-Qt"
MINOS=$(minos_of "$SRC/src/qt/ammocoin-qt")
APP="$ST/dmg/AMMOcoin-Qt.app"
ditto "$SRC/AMMOcoin-Qt.app" "$APP"
/usr/libexec/PlistBuddy -c "Set :LSMinimumSystemVersion $MINOS" "$APP/Contents/Info.plist"
# The GUI loads its icons as SVG through the qsvg image plugin, which macdeployqt does not
# pick up on its own (the executable has no direct QtSvg link). Without it every SVG icon is
# blank ("Could not create pixmap from ://ic-..."). Add it and let macdeployqt fix its links.
QT_PLUGINS="$("$QT_PREFIX/bin/qmake" -query QT_INSTALL_PLUGINS)"
# Also ship the offscreen platform plugin so the wallet can run headless
# (QT_QPA_PLATFORM=offscreen, used by the CI smoke test); cocoa stays the default.
mkdir -p "$APP/Contents/PlugIns/imageformats" "$APP/Contents/PlugIns/platforms"
cp "$QT_PLUGINS/imageformats/libqsvg.dylib" "$APP/Contents/PlugIns/imageformats/"
cp "$QT_PLUGINS/platforms/libqoffscreen.dylib" "$APP/Contents/PlugIns/platforms/"
"$QT_PREFIX/bin/macdeployqt" "$APP" -verbose=1 \
  -executable="$APP/Contents/PlugIns/imageformats/libqsvg.dylib" \
  -executable="$APP/Contents/PlugIns/platforms/libqoffscreen.dylib"
# Plugin dylibs keep their build-time install-name id; rewrite it, and drop absolute LC_RPATHs.
( cd "$APP/Contents"
  find PlugIns -name '*.dylib' | while read -r f; do install_name_tool -id "@executable_path/../$f" "$f" 2>/dev/null; done
  find . -type f | while read -r f; do
    [[ "$(file -b "$f")" == *Mach-O* ]] || continue
    otool -l "$f" | awk '/LC_RPATH/{getline;getline;print $2}' | { grep -E "^/" || true; } | while read -r rp; do
      install_name_tool -delete_rpath "$rp" "$f" 2>/dev/null; done
  done )
codesign --force --deep -s - "$APP"
codesign --verify --deep --strict "$APP"

# --- command-line tools ---
BIN="$ST/$NAME/bin"
cp "$SRC/src/ammocoind" "$SRC/src/ammocoin-cli" "$SRC/src/ammocoin-tx" "$BIN/"
strip "$BIN"/ammocoin*
if otool -L "$BIN"/ammocoin* | awk 'NF>1{print $1}' | grep -qEv '^(/System/|/usr/lib/|@)'; then
  command -v dylibbundler >/dev/null || { echo "binaries link non-system dylibs; install dylibbundler" >&2; exit 1; }
  ( cd "$BIN" && dylibbundler -od -b -cd -x ./ammocoind -x ./ammocoin-cli -x ./ammocoin-tx -d ./lib/ -p @executable_path/lib/ >/dev/null )
fi
for f in "$BIN"/lib/*.dylib "$BIN"/ammocoin*; do [ -e "$f" ] && codesign --force -s - "$f" 2>/dev/null; done
cp "$HERE/fetch-params.sh" "$ST/$NAME/"
sed -e "s/@MINOS@/$MINOS/g" -e "s/@ARCH@/$ARCHNAME/g" \
    -e "s/@ARCHDESC@/$([ $ARCHNAME = ARM64 ] && echo 'Apple Silicon (M-series)' || echo 'Intel (x86_64)')/g" \
    "$HERE/README.txt" > "$ST/$NAME/README.txt"
chmod +x "$ST/$NAME/fetch-params.sh"

# --- checks: no Homebrew / /usr/local references, minimum macOS ---
bad=0; n=0; maxseen=0
while IFS= read -r -d '' f; do
  [[ "$(file -b "$f")" == *Mach-O* ]] || continue
  n=$((n+1))
  id=$(otool -D "$f" | tail -n +2)
  ext=$(otool -L "$f" | tail -n +2 | awk '{print $1}' | grep -Ev '^(/System/|/usr/lib/|@)' || true)
  if [ -n "$ext" ]; then echo "EXTERNAL: $f: $ext"; bad=1; fi
  if [[ "$id" == /* ]]; then echo "ABSOLUTE ID: $f: $id"; bad=1; fi
  if otool -l "$f" | awk '/LC_RPATH/{getline;getline;print $2}' | grep -qE '^/'; then echo "RPATH: $f"; bad=1; fi
  m=$(minos_of "$f")
  if [ -n "${MAX_MINOS:-}" ] && [ "$(printf '%s\n%s\n' "$m" "$MAX_MINOS" | sort -V | tail -1)" != "$MAX_MINOS" ]; then
    echo "MINOS $m > $MAX_MINOS: $f"; bad=1
  fi
  [ "$(printf '%s\n%s\n' "$m" "$maxseen" | sort -V | tail -1)" = "$m" ] && maxseen=$m
done < <(find "$ST" -type f -print0)
echo "checked $n Mach-O files; highest minos $maxseen"
[ $bad = 0 ] || { echo "package check failed" >&2; exit 1; }

# --- archives ---
cd "$OUT"; rm -f "$NAME".dmg "$NAME".tar.gz "$NAME".zip "$NAME".SHA256
tar -C "$ST" -czf "$NAME.tar.gz" "$NAME"
( cd "$ST" && ditto -c -k --sequesterRsrc --keepParent "$NAME" "$OUT/$NAME.zip" )
ditto "$ST/$NAME/bin" "$ST/dmg/bin"
cp "$ST/$NAME/fetch-params.sh" "$ST/$NAME/README.txt" "$ST/dmg/"
ln -s /Applications "$ST/dmg/Applications"
hdiutil create -volname "AMMOcoin v$VER" -srcfolder "$ST/dmg" -fs HFS+ -format UDZO -imagekey zlib-level=9 -ov "$NAME.dmg" >/dev/null
shasum -a 256 "$NAME.dmg" "$NAME.tar.gz" "$NAME.zip" > "$NAME.SHA256"
cat "$NAME.SHA256"
