#!/bin/bash
# AMMOcoin v1.1.0 - Complete Dependency Installation and Build Script
# This script installs all required dependencies and builds Linux binaries

set -e  # Exit on error

echo "=============================================="
echo "AMMOcoin v1.1.0 Complete Build Setup"
echo "=============================================="
echo ""

# Setup PATH
export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/parallels/.cargo/bin"

echo "Step 1: Installing missing dependencies..."
echo "This requires sudo access."
echo ""

# Install all missing dependencies
sudo apt-get update
sudo apt-get install -y \
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
    git

echo ""
echo "Step 2: Verifying Rust toolchain..."
if ! command -v rustc &> /dev/null; then
    echo "Installing Rust..."
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
    source "$HOME/.cargo/env"
fi

rustc --version
cargo --version

echo ""
echo "Step 3: Cleaning previous build..."
cd "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"
make distclean || true

echo ""
echo "Step 4: Configuring build system..."
./autogen.sh
./configure \
    --prefix=/usr/local \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    --disable-online-rust \
    BDB_LIBS="-L/usr/lib/aarch64-linux-gnu -ldb_cxx-5.3" \
    BDB_CFLAGS="-I/usr/include" \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

echo ""
echo "Step 5: Building AMMOcoin (this will take 15-30 minutes)..."
make -j$(nproc) V=1

echo ""
echo "Step 6: Creating binary package..."
OUTPUT_DIR="/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/linux-binaries-v1.1.0"
mkdir -p "$OUTPUT_DIR"

# Copy binaries
cp src/ammocoind "$OUTPUT_DIR/"
cp src/ammocoin-cli "$OUTPUT_DIR/"
cp src/ammocoin-tx "$OUTPUT_DIR/"

# Strip to reduce size
strip "$OUTPUT_DIR"/ammocoin*
chmod +x "$OUTPUT_DIR"/ammocoin*

echo ""
echo "Step 7: Testing binaries..."
"$OUTPUT_DIR/ammocoind" --version
"$OUTPUT_DIR/ammocoin-cli" --version
"$OUTPUT_DIR/ammocoin-tx" --version

echo ""
echo "=============================================="
echo "BUILD COMPLETE!"
echo "=============================================="
echo ""
echo "Linux binaries location: $OUTPUT_DIR"
echo ""
ls -lh "$OUTPUT_DIR"/
echo ""
echo "Binaries created:"
echo "  ✓ ammocoind     - Full node daemon with wallet"
echo "  ✓ ammocoin-cli  - Command-line interface"
echo "  ✓ ammocoin-tx   - Transaction utility"
echo ""
