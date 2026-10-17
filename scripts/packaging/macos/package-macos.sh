#!/bin/bash
# AMMOcoin v1.1.1 - package a native macOS build (arm64 or x86_64).
#
#   scripts/packaging/macos/package-macos.sh <output-dir>
#
# Environment:
#   QT_PREFIX   Qt 5 used for the build (default: $(brew --prefix)/opt/qt@5); its macdeployqt is used
#   MAX_MINOS   fail if any Mach-O in the package needs a newer macOS than this (e.g. 13.0)
#   SIGN_IDENTITY  codesign identity (name or SHA-1), e.g.
#               "Developer ID Application: Adam Pletcher (2M3TZTXUSL)". Default "-" = ad-hoc.
#               A real identity signs every Mach-O inside-out with the hardened runtime
#               (--options runtime) and a secure timestamp, then signs the .dmg.
#   KEYCHAIN    keychain holding SIGN_IDENTITY (optional; default search list)
#   NOTARIZE=1  notarize with an App Store Connect API key (needs a real SIGN_IDENTITY and
#               APPLE_API_KEY_PATH (.p8 file), APPLE_API_KEY_ID, APPLE_API_ISSUER_ID):
#               the .app is notarized and stapled before it goes into the DMG, the command-line
#               binaries are notarized as a zip (bare executables cannot be stapled), and the
#               .dmg is notarized and stapled.
#
# Produces a self-contained AMMOcoin-Qt.app (macdeployqt), bin/ (any non-system dylibs are copied
# into bin/lib by dylibbundler), signatures, and AMMOcoin-v1.1.1-macOS-<ARCH>.{dmg,tar.gz,zip,SHA256}.
# Fails on any reference to Homebrew / /usr/local paths, or a -dirty version.
set -euo pipefail

# Apple's ticket lookup (CloudKit) drops connections on some CI runners and a fresh ticket can
# take a minute to propagate after "Accepted": retry staple/validate with growing waits (~7 min max).
apple_staple() { # apple_staple staple|validate <path>
  local i
  for i in 1 2 3 4 5 6; do
    xcrun stapler "$1" "$2" && return 0
    echo "stapler $1 $2: Apple lookup failed (try $i/6)"; sleep $((i * 20))
  done
  return 1
}
OUT=${1:?usage: $0 <output-dir>}
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
SRC="$ROOT/source"
QT_PREFIX=${QT_PREFIX:-$(brew --prefix 2>/dev/null)/opt/qt@5}
VER=1.1.1
case "$(uname -m)" in arm64) ARCHNAME=ARM64 ;; x86_64) ARCHNAME=x86_64 ;; *) echo "unknown arch" >&2; exit 1 ;; esac
NAME=AMMOcoin-v$VER-macOS-$ARCHNAME
SIGN_IDENTITY=${SIGN_IDENTITY:--}
NOTARIZE=${NOTARIZE:-0}
if [ "$SIGN_IDENTITY" = - ]; then
  [ "$NOTARIZE" = 1 ] && { echo "NOTARIZE=1 needs a Developer ID SIGN_IDENTITY" >&2; exit 1; }
  echo "WARNING: ad-hoc signing (SIGN_IDENTITY not set) - the package is not Developer ID signed or notarized" >&2
fi
if [ "$NOTARIZE" = 1 ]; then
  : "${APPLE_API_KEY_PATH:?NOTARIZE=1 needs APPLE_API_KEY_PATH}" "${APPLE_API_KEY_ID:?}" "${APPLE_API_ISSUER_ID:?}"
  # secrets pasted into `gh secret set` can carry spaces or a newline; notarytool rejects them
  APPLE_API_KEY_ID=$(printf %s "$APPLE_API_KEY_ID" | tr -d '[:space:]')
  APPLE_API_ISSUER_ID=$(printf %s "$APPLE_API_ISSUER_ID" | tr -d '[:space:]')
  [[ $APPLE_API_ISSUER_ID =~ ^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$ ]] \
    || { echo "::error::APPLE_API_ISSUER_ID is not a UUID (App Store Connect > Users and Access > Integrations > Issuer ID)"; exit 1; }
  [[ $APPLE_API_KEY_ID =~ ^[A-Z0-9]{10}$ ]] || { echo "::error::APPLE_API_KEY_ID should be the 10-character key ID"; exit 1; }
fi
KCARGS=(); [ -n "${KEYCHAIN:-}" ] && KCARGS=(--keychain "$KEYCHAIN")
ENT="$HERE/entitlements.plist"

# sign <path>: ad-hoc, or Developer ID with hardened runtime + secure timestamp
sign() {
  if [ "$SIGN_IDENTITY" = - ]; then
    codesign --force --sign - "$1"
  else
    codesign --force --sign "$SIGN_IDENTITY" ${KCARGS[@]+"${KCARGS[@]}"} --options runtime --timestamp \
      --entitlements "$ENT" "$1"
  fi
}
# sign_app <app>: inside-out - plugins and loose dylibs, frameworks, then the bundle itself
sign_app() {
  local app=$1 f
  while IFS= read -r -d '' f; do
    [[ "$(file -b "$f")" == *Mach-O* ]] && sign "$f"
  done < <(find "$app/Contents/PlugIns" "$app/Contents/Frameworks" -type f -name '*.dylib' -print0 2>/dev/null)
  for f in "$app"/Contents/Frameworks/*.framework; do [ -d "$f" ] && sign "$f"; done
  sign "$app"
  codesign --verify --deep --strict --verbose=1 "$app"
}
# notarize <file.zip|file.dmg>: submit with the API key, wait, fail (with the log) unless Accepted
notarize() {
  local f=$1 out id status
  echo "notarizing $(basename "$f") ..."
  out=$(xcrun notarytool submit "$f" --key "$APPLE_API_KEY_PATH" --key-id "$APPLE_API_KEY_ID" \
        --issuer "$APPLE_API_ISSUER_ID" --wait --timeout 2h --output-format json)
  id=$(python3 -c 'import json,sys; print(json.loads(sys.argv[1]).get("id",""))' "$out")
  status=$(python3 -c 'import json,sys; print(json.loads(sys.argv[1]).get("status",""))' "$out")
  echo "notarization $id: $status"
  if [ "$status" != Accepted ]; then
    [ -n "$id" ] && xcrun notarytool log "$id" --key "$APPLE_API_KEY_PATH" --key-id "$APPLE_API_KEY_ID" \
      --issuer "$APPLE_API_ISSUER_ID" || true
    echo "notarization of $(basename "$f") failed" >&2; exit 1
  fi
}

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

# --- command-line tools ---
BIN="$ST/$NAME/bin"
cp "$SRC/src/ammocoind" "$SRC/src/ammocoin-cli" "$SRC/src/ammocoin-tx" "$BIN/"
strip "$BIN"/ammocoin*
if otool -L "$BIN"/ammocoin* | awk 'NF>1{print $1}' | grep -qEv '^(/System/|/usr/lib/|@)'; then
  command -v dylibbundler >/dev/null || { echo "binaries link non-system dylibs; install dylibbundler" >&2; exit 1; }
  ( cd "$BIN" && dylibbundler -od -b -cd -x ./ammocoind -x ./ammocoin-cli -x ./ammocoin-tx -d ./lib/ -p @executable_path/lib/ >/dev/null )
fi
cp "$HERE/fetch-params.sh" "$ST/$NAME/"
FIRST_LAUNCH="$HERE/README-first-launch-$([ "$NOTARIZE" = 1 ] && echo signed || echo unsigned).txt"
python3 - "$HERE/README.txt" "$FIRST_LAUNCH" "$ST/$NAME/README.txt" "$MINOS" "$ARCHNAME" <<'PY'
import sys
tpl, first, out, minos, arch = sys.argv[1:]
desc = "Apple Silicon (M-series)" if arch == "ARM64" else "Intel (x86_64)"
s = open(tpl).read().replace("@FIRST_LAUNCH@", open(first).read().rstrip("\n"))
s = s.replace("@MINOS@", minos).replace("@ARCHDESC@", desc).replace("@ARCH@", arch)
open(out, "w").write(s)
PY
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

# --- signing (+ notarization of the app and the command-line binaries) ---
sign_app "$APP"
for f in "$BIN"/lib/*.dylib "$BIN"/ammocoin*; do [ -e "$f" ] && sign "$f"; done
for f in "$BIN"/ammocoin*; do codesign --verify --strict "$f"; done
if [ "$NOTARIZE" = 1 ]; then
  NZ="$ST/notarize"; mkdir -p "$NZ"
  ditto -c -k --keepParent "$APP" "$NZ/AMMOcoin-Qt.app.zip"
  notarize "$NZ/AMMOcoin-Qt.app.zip"
  apple_staple staple "$APP"
  apple_staple validate "$APP"
  ( cd "$ST/$NAME" && ditto -c -k --keepParent bin "$NZ/$NAME-bin.zip" )
  notarize "$NZ/$NAME-bin.zip"
  rm -rf "$NZ"
fi

# --- archives ---
cd "$OUT"; rm -f "$NAME".dmg "$NAME".tar.gz "$NAME".zip "$NAME".SHA256
tar -C "$ST" -czf "$NAME.tar.gz" "$NAME"
( cd "$ST" && ditto -c -k --sequesterRsrc --keepParent "$NAME" "$OUT/$NAME.zip" )
ditto "$ST/$NAME/bin" "$ST/dmg/bin"
cp "$ST/$NAME/fetch-params.sh" "$ST/$NAME/README.txt" "$ST/dmg/"
ln -s /Applications "$ST/dmg/Applications"
hdiutil create -volname "AMMOcoin v$VER" -srcfolder "$ST/dmg" -fs HFS+ -format UDZO -imagekey zlib-level=9 -ov "$NAME.dmg" >/dev/null
if [ "$SIGN_IDENTITY" != - ]; then
  codesign --force --sign "$SIGN_IDENTITY" ${KCARGS[@]+"${KCARGS[@]}"} --timestamp "$NAME.dmg"
  codesign --verify --strict --verbose=1 "$NAME.dmg"
fi
if [ "$NOTARIZE" = 1 ]; then
  notarize "$NAME.dmg"
  apple_staple staple "$NAME.dmg"
  apple_staple validate "$NAME.dmg"
  spctl -a -vvv -t install "$NAME.dmg"
  spctl -a -vvv -t exec "$APP"
fi
shasum -a 256 "$NAME.dmg" "$NAME.tar.gz" "$NAME.zip" > "$NAME.SHA256"
cat "$NAME.SHA256"
