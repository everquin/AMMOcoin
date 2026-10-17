#!/bin/bash
# AMMOcoin v1.1.1 - native macOS Apple Silicon (arm64) build using Homebrew deps.
# Usage: scripts/build/build-macos-arm64-v1.1.1.sh [configure|make|all]
# Run from a clean checkout/worktree so the version reads v1.1.1.0-<sha> (no -dirty).
set -euo pipefail
HB=$(brew --prefix)
SRC="$(cd "$(dirname "$0")/../../source" && pwd)"
FIXH="$(cd "$(dirname "$0")" && pwd)/macos-fix-relic.h"
cd "$SRC"
step=${1:-all}

export PATH="$HB/opt/qt@5/bin:$HOME/.cargo/bin:$PATH"
export PKG_CONFIG_PATH="$HB/opt/qt@5/lib/pkgconfig:$HB/opt/libevent/lib/pkgconfig:$HB/opt/zeromq/lib/pkgconfig:$HB/opt/qrencode/lib/pkgconfig:$HB/opt/libsodium/lib/pkgconfig:${PKG_CONFIG_PATH:-}"

if [ "$step" = configure ] || [ "$step" = all ]; then
  # configure/Makefile.in are tracked (pre-generated) - do not run autogen.sh.
  ./configure \
    --with-gui=qt5 --enable-wallet --with-incompatible-bdb \
    --disable-tests --disable-bench \
    --with-boost="$HB/opt/boost@1.85" --with-boost-libdir="$HB/opt/boost@1.85/lib" \
    LDFLAGS="-L$HB/opt/berkeley-db@4/lib -L$HB/opt/boost@1.85/lib -L$HB/lib" \
    CPPFLAGS="-I$HB/opt/berkeley-db@4/include -I$HB/opt/boost@1.85/include -I$HB/include -include $FIXH"
fi
if [ "$step" = make ] || [ "$step" = all ]; then
  make -j"$(sysctl -n hw.ncpu)"
fi
