#!/bin/bash
# AMMOcoin - build every macOS dependency from source with a fixed deployment target.
#
#   scripts/build/macos-deps.sh <prefix> [workdir]
#
# Environment:
#   MACOSX_DEPLOYMENT_TARGET  minimum macOS (default 13.0); every library gets this LC_BUILD_VERSION minos
#   ARCH                      arm64 or x86_64 (default: uname -m); native builds only
#   JOBS                      parallel jobs (default: hw.ncpu)
#   SOURCES_DIR               tarball cache (default: <workdir>/sources)
#
# Produces <prefix>/{include,lib} with static boost, Berkeley DB 4.8, libevent, gmp, libsodium,
# zeromq, miniupnpc, libnatpmp and qrencode, and <prefix>/qt with shared Qt 5.15 frameworks
# (qtbase with bundled libpng/libjpeg/freetype/pcre/harfbuzz - no glib, zstd, dbus or ICU -
# plus qtsvg, qtcharts, lrelease and macdeployqt). Nothing is taken from Homebrew, so the
# resulting app runs on any macOS >= MACOSX_DEPLOYMENT_TARGET. All downloads are SHA256-pinned.
# A stamp file per package makes re-runs incremental; delete <prefix> to rebuild from scratch.
set -euo pipefail

PREFIX=${1:?usage: $0 <prefix> [workdir]}
mkdir -p "$PREFIX"; PREFIX="$(cd "$PREFIX" && pwd)"
WORK=${2:-$PREFIX/../macos-deps-work}
mkdir -p "$WORK"; WORK="$(cd "$WORK" && pwd)"
SOURCES_DIR=${SOURCES_DIR:-$WORK/sources}
mkdir -p "$SOURCES_DIR" "$PREFIX/stamps"
HERE="$(cd "$(dirname "$0")" && pwd)"
CONFIG_GUESS_DIR="$HERE/../../source/depends"   # modern config.guess/config.sub (BDB's are from 2009)

export MACOSX_DEPLOYMENT_TARGET=${MACOSX_DEPLOYMENT_TARGET:-13.0}
ARCH=${ARCH:-$(uname -m)}
JOBS=${JOBS:-$(sysctl -n hw.ncpu)}
case "$ARCH" in arm64) HOST=aarch64-apple-darwin ;; x86_64) HOST=x86_64-apple-darwin ;; *) echo "bad ARCH $ARCH" >&2; exit 1 ;; esac
[ "$ARCH" = "$(uname -m)" ] || { echo "only native builds are supported (ARCH=$ARCH, host $(uname -m))" >&2; exit 1; }

SDK="$(xcrun --sdk macosx --show-sdk-path)"
export SDKROOT="$SDK"   # also for bare preprocessor runs ($CC -E) that do not see CFLAGS
export CC="$(xcrun -f clang)" CXX="$(xcrun -f clang++)"
BASEFLAGS="-arch $ARCH -mmacosx-version-min=$MACOSX_DEPLOYMENT_TARGET -isysroot $SDK"
export CFLAGS="$BASEFLAGS -O2 -fPIC"
export CXXFLAGS="$BASEFLAGS -O2 -fPIC"
export LDFLAGS="$BASEFLAGS"
export CPPFLAGS="-I$PREFIX/include"
# Never let a Homebrew/MacPorts .pc file leak into the build.
export PKG_CONFIG_LIBDIR="$PREFIX/lib/pkgconfig"
unset PKG_CONFIG_PATH
export PATH="/usr/bin:/bin:/usr/sbin:/sbin:$(dirname "$(command -v cmake)"):$(dirname "$(command -v pkg-config 2>/dev/null || echo /usr/bin/true)")"

log() { echo "==> [$(date +%H:%M:%S)] $*"; }

fetch() { # name url sha256
  local f="$SOURCES_DIR/$1"
  if [ ! -f "$f" ] || [ "$(shasum -a 256 "$f" | awk '{print $1}')" != "$3" ]; then
    log "download $1"
    curl -fL --retry 5 --retry-delay 5 -o "$f.part" "$2"
    mv -f "$f.part" "$f"
  fi
  local got; got=$(shasum -a 256 "$f" | awk '{print $1}')
  [ "$got" = "$3" ] || { echo "SHA256 mismatch for $1: got $got want $3" >&2; exit 1; }
}

unpack() { # tarball dir -> cd into fresh source dir
  rm -rf "$WORK/$2"
  tar -C "$WORK" -xf "$SOURCES_DIR/$1"
  cd "$WORK/$2"
}

done_() { [ -f "$PREFIX/stamps/$1" ]; }
stamp() { touch "$PREFIX/stamps/$1"; log "$1 done"; }

# ---------------------------------------------------------------- boost (static)
if ! done_ boost; then
  fetch boost_1_85_0.tar.bz2 https://archives.boost.io/release/1.85.0/source/boost_1_85_0.tar.bz2 \
    7009fe1faa1697476bdc7027703a2badb84e849b7b0baad5086b087b971f8617
  unpack boost_1_85_0.tar.bz2 boost_1_85_0
  log "build boost"
  ./bootstrap.sh --with-toolset=clang --with-libraries=system,filesystem,thread,chrono,atomic >/dev/null
  ./b2 -j"$JOBS" -d0 --prefix="$PREFIX" toolset=clang variant=release link=static threading=multi \
    runtime-link=shared address-model=64 architecture=$([ "$ARCH" = arm64 ] && echo arm || echo x86) \
    cxxflags="$CXXFLAGS -std=c++14" cflags="$CFLAGS" linkflags="$LDFLAGS" install
  stamp boost
fi

# ---------------------------------------------------------------- Berkeley DB 4.8 (static, C++)
if ! done_ bdb; then
  fetch db-4.8.30.NC.tar.gz https://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz \
    12edc0df75bf9abd7f82f821795bcee50f42cb2e5f76a6a281b85732798364ef
  unpack db-4.8.30.NC.tar.gz db-4.8.30.NC
  log "build bdb"
  # Same fixes as source/depends/packages/bdb.mk (clang builtin name clashes, ancient config.guess).
  sed -i.old 's/__atomic_compare_exchange/__atomic_compare_exchange_db/' dbinc/atomic.h
  sed -i.old 's/atomic_init/atomic_init_db/' dbinc/atomic.h mp/mp_region.c mp/mp_mvcc.c mp/mp_fget.c mutex/mut_method.c mutex/mut_tas.c
  cp -f "$CONFIG_GUESS_DIR/config.guess" "$CONFIG_GUESS_DIR/config.sub" dist/
  cd build_unix
  CFLAGS="$CFLAGS -Wno-error=implicit-function-declaration -Wno-error=implicit-int -Wno-error=incompatible-function-pointer-types" \
  CXXFLAGS="$CXXFLAGS -std=c++11" \
    ../dist/configure --host=$HOST --prefix="$PREFIX" --disable-shared --enable-static --enable-cxx \
      --disable-replication --disable-atomicsupport --with-pic >/dev/null
  make -j"$JOBS" libdb_cxx-4.8.a libdb-4.8.a >/dev/null
  make install_lib install_include >/dev/null
  rm -f "$PREFIX"/lib/libdb*.dylib "$PREFIX"/lib/libdb*.la
  stamp bdb
fi

autotools_static() { # tarball dir [configure args...]
  local tb=$1 dir=$2; shift 2
  unpack "$tb" "$dir"
  ./configure --host=$HOST --prefix="$PREFIX" --disable-shared --enable-static --with-pic "$@" >/dev/null
  make -j"$JOBS" >/dev/null
  make install >/dev/null
}

if ! done_ libevent; then
  fetch libevent-2.1.12-stable.tar.gz \
    https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz \
    92e6de1be9ec176428fd2367677e61ceffc2ee1cb119035037a27d346b0403bb
  log "build libevent"
  autotools_static libevent-2.1.12-stable.tar.gz libevent-2.1.12-stable \
    --disable-openssl --disable-libevent-regress --disable-samples --disable-debug-mode
  stamp libevent
fi

if ! done_ gmp; then
  fetch gmp-6.3.0.tar.xz https://ftpmirror.gnu.org/gnu/gmp/gmp-6.3.0.tar.xz \
    a3c2b80201b89e68616f4ad30bc66aee4927c3ce50e33929ca819d5c43538898
  log "build gmp"
  autotools_static gmp-6.3.0.tar.xz gmp-6.3.0
  stamp gmp
fi

if ! done_ libsodium; then
  fetch libsodium-1.0.20.tar.gz https://download.libsodium.org/libsodium/releases/libsodium-1.0.20.tar.gz \
    ebb65ef6ca439333c2bb41a0c1990587288da07f6c7fd07cb3a18cc18d30ce19
  log "build libsodium"
  autotools_static libsodium-1.0.20.tar.gz libsodium-1.0.20
  stamp libsodium
fi

if ! done_ zeromq; then
  fetch zeromq-4.3.5.tar.gz https://github.com/zeromq/libzmq/releases/download/v4.3.5/zeromq-4.3.5.tar.gz \
    6653ef5910f17954861fe72332e68b03ca6e4d9c7160eb3a8de5a5a913bfab43
  log "build zeromq"
  autotools_static zeromq-4.3.5.tar.gz zeromq-4.3.5 \
    --without-libsodium --disable-curve --without-docs --disable-libunwind --disable-Werror \
    --disable-perf --disable-drafts --disable-libbsd
  stamp zeromq
fi

if ! done_ miniupnpc; then
  fetch miniupnpc-2.2.8.tar.gz https://miniupnp.tuxfamily.org/files/miniupnpc-2.2.8.tar.gz \
    05b929679091b9921b6b6c1f25e39e4c8d1f4d46c8feb55a412aa697aee03a93
  log "build miniupnpc"
  unpack miniupnpc-2.2.8.tar.gz miniupnpc-2.2.8
  # The Makefiles append their own flags to CFLAGS/CPPFLAGS from the environment.
  make -j"$JOBS" CC="$CC" build/libminiupnpc.a >/dev/null
  mkdir -p "$PREFIX/include/miniupnpc"
  cp include/*.h "$PREFIX/include/miniupnpc/"
  cp build/libminiupnpc.a "$PREFIX/lib/"
  stamp miniupnpc
fi

if ! done_ libnatpmp; then
  fetch libnatpmp-20230423.tar.gz https://miniupnp.tuxfamily.org/files/libnatpmp-20230423.tar.gz \
    0684ed2c8406437e7519a1bd20ea83780db871b3a3a5d752311ba3e889dbfc70
  log "build libnatpmp"
  unpack libnatpmp-20230423.tar.gz libnatpmp-20230423
  make -j"$JOBS" CC="$CC" libnatpmp.a >/dev/null
  cp natpmp.h natpmp_declspec.h "$PREFIX/include/"
  cp libnatpmp.a "$PREFIX/lib/"
  stamp libnatpmp
fi

if ! done_ qrencode; then
  fetch libqrencode-4.1.1.tar.gz https://github.com/fukuchi/libqrencode/archive/refs/tags/v4.1.1.tar.gz \
    5385bc1b8c2f20f3b91d258bf8ccc8cf62023935df2d2676b5b67049f31a049c
  log "build qrencode"
  unpack libqrencode-4.1.1.tar.gz libqrencode-4.1.1
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$PREFIX" \
    -DCMAKE_OSX_ARCHITECTURES=$ARCH -DCMAKE_OSX_DEPLOYMENT_TARGET=$MACOSX_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_SYSROOT="$SDK" -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
    -DBUILD_SHARED_LIBS=OFF -DWITH_TOOLS=NO -DWITH_TESTS=NO -DCMAKE_DISABLE_FIND_PACKAGE_PNG=ON \
    -DCMAKE_DISABLE_FIND_PACKAGE_Iconv=ON >/dev/null
  cmake --build build -j"$JOBS" >/dev/null
  cmake --install build >/dev/null
  # cmake writes the .pc with an empty prefix on some versions; regenerate it.
  mkdir -p "$PREFIX/lib/pkgconfig"
  cat > "$PREFIX/lib/pkgconfig/libqrencode.pc" <<EOF
prefix=$PREFIX
libdir=\${prefix}/lib
includedir=\${prefix}/include
Name: libqrencode
Description: A QR Code encoding library
Version: 4.1.1
Libs: -L\${libdir} -lqrencode
Cflags: -I\${includedir}
EOF
  stamp qrencode
fi

# ---------------------------------------------------------------- Qt 5.15 (shared frameworks)
QTVER=5.15.19
QTURL=https://download.qt.io/archive/qt/5.15/$QTVER/submodules
QTP="$PREFIX/qt"
if ! done_ qtbase; then
  fetch qtbase-everywhere-opensource-src-$QTVER.tar.xz $QTURL/qtbase-everywhere-opensource-src-$QTVER.tar.xz \
    51e91c73abacab81e64efd01bf95794e79c0e605ad80947a024769f0dd620a32
  unpack qtbase-everywhere-opensource-src-$QTVER.tar.xz qtbase-everywhere-src-$QTVER
  log "build qtbase (slow)"
  # Xcode 26 SDK has no AGL framework (backport of qtbase cdb33c3d, as Homebrew's qt@5 does).
  sed -i.old -e 's|    /System/Library/Frameworks/OpenGL.framework/Headers \\|    /System/Library/Frameworks/OpenGL.framework/Headers|' \
             -e '/AGL.framework\/Headers/d' \
             -e 's|-framework OpenGL -framework AGL|-framework OpenGL|' mkspecs/common/mac.conf
  # Qt's own CFLAGS come from the mkspec; ours would add a second -arch/-isysroot.
  env -u CFLAGS -u CXXFLAGS -u LDFLAGS -u CPPFLAGS ./configure -prefix "$QTP" -release -opensource -confirm-license \
    -nomake examples -nomake tests -no-rpath -pkg-config \
    -no-dbus -no-glib -no-icu -no-cups -no-zstd -no-openssl \
    -qt-libpng -qt-libjpeg -qt-freetype -qt-pcre -qt-harfbuzz -system-zlib \
    -no-sql-sqlite -no-sql-odbc -no-sql-psql -no-sql-mysql \
    QMAKE_APPLE_DEVICE_ARCHS=$ARCH QMAKE_MACOSX_DEPLOYMENT_TARGET=$MACOSX_DEPLOYMENT_TARGET \
    >"$WORK/qtbase-configure.log" 2>&1 || { tail -50 "$WORK/qtbase-configure.log"; exit 1; }
  env -u CFLAGS -u CXXFLAGS -u LDFLAGS -u CPPFLAGS make -j"$JOBS" >"$WORK/qtbase-make.log" 2>&1 || { grep -m20 -B2 -A5 'error:' "$WORK/qtbase-make.log"; exit 1; }
  env -u CFLAGS -u CXXFLAGS -u LDFLAGS -u CPPFLAGS make install >/dev/null
  stamp qtbase
fi

qt_module() { # name sha256 [subdir-of-module ...]
  local m=$1 sha=$2; shift 2
  fetch $m-everywhere-opensource-src-$QTVER.tar.xz $QTURL/$m-everywhere-opensource-src-$QTVER.tar.xz "$sha"
  unpack $m-everywhere-opensource-src-$QTVER.tar.xz $m-everywhere-src-$QTVER
  log "build $m"
  local Q="env -u CFLAGS -u CXXFLAGS -u LDFLAGS -u CPPFLAGS"
  $Q "$QTP/bin/qmake" >"$WORK/$m-qmake.log" 2>&1 || { tail -30 "$WORK/$m-qmake.log"; exit 1; }
  if [ $# -eq 0 ]; then
    $Q make -j"$JOBS" >"$WORK/$m-make.log" 2>&1 || { grep -m20 -B2 -A5 'error' "$WORK/$m-make.log"; exit 1; }
    $Q make install >/dev/null
  else
    # Only selected sub-projects: generate every Makefile (module config included), build those.
    $Q make qmake_all >>"$WORK/$m-qmake.log" 2>&1
    for s in "$@"; do
      $Q make -C "$s" -j"$JOBS" >>"$WORK/$m-make.log" 2>&1 || { grep -m20 -B2 -A5 'error' "$WORK/$m-make.log"; exit 1; }
      $Q make -C "$s" install >/dev/null
    done
  fi
}

done_ qtsvg    || { qt_module qtsvg    cabc95fc12fa84c92e95f08660742a0ce297e6db3deadbefbe7fbec4769b8c13; stamp qtsvg; }
done_ qtcharts || { qt_module qtcharts 6cbe053a3127f6b6092c2a055cd468e7c9a1484bdc8320da564034c160a943f1; stamp qtcharts; }
# Only the tools the build and packaging need (lrelease for translations, macdeployqt).
done_ qttools  || { qt_module qttools  2694af886130d63b8a42bcd138f4035fd8108273ebd16781f87300da352f1aa6 \
                      src/linguist/lrelease src/linguist/lupdate src/linguist/lconvert src/macdeployqt; stamp qttools; }

log "dependencies ready in $PREFIX (MACOSX_DEPLOYMENT_TARGET=$MACOSX_DEPLOYMENT_TARGET, $ARCH)"
