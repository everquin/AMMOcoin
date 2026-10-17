#!/bin/bash
# AMMOcoin v1.1.1 - native macOS build (arm64 or x86_64) against dependencies built by
# scripts/build/macos-deps.sh, so every binary carries the same minimum macOS.
#
#   scripts/build/build-macos.sh <deps-prefix> [configure|make|all]
#
# Environment: MACOSX_DEPLOYMENT_TARGET (default 13.0), JOBS.
# Run from a clean checkout: the version must read v1.1.1.0-<sha>, not -dirty. configure rewrites
# a few tracked files; scripts/ci/mark-tracked-build-outputs.sh marks them assume-unchanged.
set -euo pipefail
DEPS=${1:?usage: $0 <deps-prefix> [configure|make|all]}
DEPS="$(cd "$DEPS" && pwd)"
step=${2:-all}
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
SRC="$ROOT/source"
cd "$SRC"

export MACOSX_DEPLOYMENT_TARGET=${MACOSX_DEPLOYMENT_TARGET:-13.0}
ARCH=$(uname -m)
JOBS=${JOBS:-$(sysctl -n hw.ncpu)}
SDK="$(xcrun --sdk macosx --show-sdk-path)"
FLAGS="-arch $ARCH -mmacosx-version-min=$MACOSX_DEPLOYMENT_TARGET -isysroot $SDK"
export PKG_CONFIG_LIBDIR="$DEPS/lib/pkgconfig:$DEPS/qt/lib/pkgconfig"
unset PKG_CONFIG_PATH
export PATH="$DEPS/qt/bin:$HOME/.cargo/bin:$PATH"
# Do not regenerate the committed autotools output.
export ACLOCAL=: AUTOCONF=: AUTOMAKE=: AUTOHEADER=:

if [ "$step" = configure ] || [ "$step" = all ]; then
  # BREW=no: configure.ac otherwise adds Homebrew's gmp/bdb/qt paths on macOS.
  ./configure \
    --with-gui=qt5 --enable-wallet --with-incompatible-bdb --disable-tests --disable-bench \
    --disable-maintainer-mode \
    --with-boost="$DEPS" --with-boost-libdir="$DEPS/lib" \
    --with-qt-bindir="$DEPS/qt/bin" --with-qt-plugindir="$DEPS/qt/plugins" \
    --with-qt-translationdir="$DEPS/qt/translations" \
    BREW=no \
    BDB_CFLAGS="-I$DEPS/include" BDB_LIBS="-L$DEPS/lib -ldb_cxx-4.8" \
    CFLAGS="-O2 $FLAGS" CXXFLAGS="-O2 $FLAGS" OBJCXXFLAGS="-O2 $FLAGS" \
    CPPFLAGS="-I$DEPS/include -include $HERE/macos-fix-relic.h" \
    LDFLAGS="$FLAGS -L$DEPS/lib"
  "$ROOT/scripts/ci/mark-tracked-build-outputs.sh"
fi
if [ "$step" = make ] || [ "$step" = all ]; then
  make -j"$JOBS"
  # make can rewrite more tracked files after genbuild.sh ran: re-mark and re-stamp.
  if grep -q -- '-dirty' src/obj/build.h; then
    "$ROOT/scripts/ci/mark-tracked-build-outputs.sh"
    rm -f src/obj/build.h
    make -j"$JOBS"
  fi
  "$ROOT/scripts/ci/check-build-version.sh" src/obj/build.h src/ammocoind src/ammocoin-cli src/qt/ammocoin-qt
fi
