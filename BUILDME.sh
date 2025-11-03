#!/bin/bash
# AMMOcoin v1.1.0 - User-Interactive Build Script
# Run this script in your terminal with: sudo bash BUILDME.sh

set -e

echo "=============================================="
echo "AMMOcoin v1.1.0 Complete Build"
echo "=============================================="
echo ""
echo "This script will:"
echo "1. Install all required dependencies"
echo "2. Build Linux binaries for ARM64"
echo "3. Prepare binaries for deployment"
echo ""
read -p "Press Enter to continue or Ctrl+C to cancel..."

# Ensure we have sudo
if [ "$EUID" -ne 0 ]; then
    echo "Please run with sudo: sudo bash BUILDME.sh"
    exit 1
fi

# Setup environment
export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/parallels/.cargo/bin"
USER_HOME="/home/parallels"

echo ""
echo "Installing dependencies..."
apt-get update -qq
apt-get install -y \
    build-essential \
    libtool \
    autotools-dev \
    automake \
    pkg-config \
    bsdmainutils \
    python3 \
    libssl-dev \
    libevent-dev \
    libboost-all-dev \
    libzmq3-dev \
    libgmp-dev \
    libsodium-dev \
    libqrencode-dev \
    libprotobuf-dev \
    protobuf-compiler \
    libdb5.3-dev \
    libdb5.3++-dev \
    libminiupnpc-dev \
    libnatpmp-dev \
    ccache \
    curl \
    git \
    coreutils

echo ""
echo "Setting up Rust for user parallels..."
if [ ! -f "$USER_HOME/.cargo/bin/rustc" ]; then
    su - parallels -c 'curl --proto "=https" --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y'
fi

echo ""
echo "Building AMMOcoin..."
cd "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"

# Run as user (not root) for the build
su - parallels -c "
export PATH='/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$USER_HOME/.cargo/bin'
cd '/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin'

make distclean || true

./autogen.sh

./configure \
    --prefix=/usr/local \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    --disable-online-rust \
    BDB_LIBS='-L/usr/lib/aarch64-linux-gnu -ldb_cxx-5.3' \
    BDB_CFLAGS='-I/usr/include' \
    CXXFLAGS='-O2 -g' \
    LDFLAGS='-static-libgcc -static-libstdc++'

make -j\$(nproc) V=1
"

echo ""
echo "Packaging binaries..."
OUTPUT_DIR="/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/linux-binaries-v1.1.0"
mkdir -p "$OUTPUT_DIR"

cp src/ammocoind "$OUTPUT_DIR/"
cp src/ammocoin-cli "$OUTPUT_DIR/"
cp src/ammocoin-tx "$OUTPUT_DIR/"

strip "$OUTPUT_DIR"/ammocoin*
chmod +x "$OUTPUT_DIR"/ammocoin*
chown parallels:parallels "$OUTPUT_DIR"/ammocoin*

echo ""
echo "Testing binaries..."
su - parallels -c "$OUTPUT_DIR/ammocoind --version"
su - parallels -c "$OUTPUT_DIR/ammocoin-cli --version"
su - parallels -c "$OUTPUT_DIR/ammocoin-tx --version"

echo ""
echo "=============================================="
echo "BUILD SUCCESSFUL!"
echo "=============================================="
echo ""
echo "Binaries location: $OUTPUT_DIR"
ls -lh "$OUTPUT_DIR"/
echo ""
echo "✓ Linux ARM64 binaries ready for deployment"
echo ""
