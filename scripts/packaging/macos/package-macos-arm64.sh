#!/bin/bash
# AMMOcoin v1.1.1 - package a native macOS arm64 build (after build-macos-arm64-v1.1.1.sh).
# Produces a self-contained AMMOcoin-Qt.app (macdeployqt), bin/ with bundled dylibs
# (dylibbundler), ad-hoc signatures, and DMG / tar.gz / zip / SHA256.
# Usage: package-macos-arm64.sh <output-dir>
# Needs: brew install qt@5 dylibbundler
set -euo pipefail
OUT=${1:?usage: $0 <output-dir>}
HERE="$(cd "$(dirname "$0")" && pwd)"
SRC="$(cd "$HERE/../../../source" && pwd)"
HB=$(brew --prefix)
VER=1.1.1
NAME=AMMOcoin-v$VER-macOS-ARM64
MINOS=${MINOS:-$(otool -l "$SRC/src/qt/ammocoin-qt" | awk '/minos/{print $2; exit}')}

mkdir -p "$OUT"; OUT="$(cd "$OUT" && pwd)"
ST="$OUT/staging"; rm -rf "$ST"; mkdir -p "$ST/dmg" "$ST/$NAME/bin"

# --- GUI bundle ---
( cd "$SRC" && PATH="$HB/opt/qt@5/bin:$PATH" make appbundle >/dev/null )
APP="$ST/dmg/AMMOcoin-Qt.app"
ditto "$SRC/AMMOcoin-Qt.app" "$APP"
# Declare the real minimum macOS (Homebrew-built dependencies set it).
/usr/libexec/PlistBuddy -c "Set :LSMinimumSystemVersion $MINOS" "$APP/Contents/Info.plist"
"$HB/opt/qt@5/bin/macdeployqt" "$APP" -verbose=0
# Plugin dylibs keep their Homebrew install-name id; rewrite it, and drop stray LC_RPATHs.
( cd "$APP/Contents"
  find PlugIns -name '*.dylib' | while read -r f; do install_name_tool -id "@executable_path/../$f" "$f" 2>/dev/null; done
  find . -type f | while read -r f; do
    [[ "$(file -b "$f")" == *Mach-O* ]] || continue
    otool -l "$f" | awk '/LC_RPATH/{getline;getline;print $2}' | { grep -E "^/(opt|usr/local)" || true; } | while read -r rp; do
      install_name_tool -delete_rpath "$rp" "$f" 2>/dev/null; done
  done )
codesign --force --deep -s - "$APP"
codesign --verify --deep --strict "$APP"

# --- command-line tools ---
BIN="$ST/$NAME/bin"
cp "$SRC/src/ammocoind" "$SRC/src/ammocoin-cli" "$SRC/src/ammocoin-tx" "$BIN/"
strip "$BIN"/ammocoin*
( cd "$BIN" && dylibbundler -od -b -cd -x ./ammocoind -x ./ammocoin-cli -x ./ammocoin-tx -d ./lib/ -p @executable_path/lib/ >/dev/null )
for f in "$BIN"/lib/*.dylib "$BIN"/ammocoin*; do codesign --force -s - "$f" 2>/dev/null; done
cp "$HERE/fetch-params.sh" "$HERE/README.txt" "$ST/$NAME/"
chmod +x "$ST/$NAME/fetch-params.sh"

# --- external-reference check (fails the build on any Homebrew/usr-local path) ---
bad=0
while IFS= read -r -d '' f; do
  [[ "$(file -b "$f")" == *Mach-O* ]] || continue
  id=$(otool -D "$f" | tail -n +2)
  ext=$(otool -L "$f" | tail -n +2 | awk '{print $1}' | grep -Ev '^(/System/|/usr/lib/|@)' || true)
  if [ -n "$ext" ]; then echo "EXTERNAL: $f: $ext"; bad=1; fi
  if [[ "$id" == /opt/* || "$id" == /usr/local/* ]]; then echo "EXTERNAL ID: $f: $id"; bad=1; fi
  if otool -l "$f" | awk '/LC_RPATH/{getline;getline;print $2}' | grep -qE '^/(opt|usr/local)'; then echo "RPATH: $f"; bad=1; fi
done < <(find "$ST" -type f -print0)
[ $bad = 0 ] || { echo "external references found" >&2; exit 1; }

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
