#!/bin/bash
# AMMOcoin v1.1.0 - macOS Native Build Script
# Run this on your Mac to create macOS binaries and DMG

set -e

echo "=============================================="
echo "AMMOcoin v1.1.0 macOS Build"
echo "=============================================="
echo ""

# Navigate to source directory
cd "/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"

# Check if Homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Error: Homebrew not installed"
    echo "Install from: https://brew.sh"
    exit 1
fi

echo "Step 1: Installing dependencies via Homebrew..."
brew install \
    automake \
    berkeley-db@4 \
    libtool \
    boost \
    miniupnpc \
    pkg-config \
    python \
    qt@5 \
    libevent \
    qrencode \
    libsodium \
    gmp \
    zeromq \
    protobuf

# Install Rust if not present
if ! command -v rustc &> /dev/null; then
    echo "Installing Rust..."
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
    source "$HOME/.cargo/env"
fi

echo ""
echo "Step 2: Cleaning previous build..."
make distclean || true

echo ""
echo "Step 3: Generating build system..."
./autogen.sh

echo ""
echo "Step 4: Configuring for macOS..."
./configure \
    --prefix=/usr/local \
    --enable-wallet \
    --with-gui=qt5 \
    --with-qrencode \
    --with-incompatible-bdb \
    --disable-online-rust \
    LDFLAGS="-L/opt/homebrew/opt/berkeley-db@4/lib -L/opt/homebrew/lib" \
    CPPFLAGS="-I/opt/homebrew/opt/berkeley-db@4/include -I/opt/homebrew/include" \
    PKG_CONFIG_PATH="/opt/homebrew/opt/qt@5/lib/pkgconfig"

echo ""
echo "Step 5: Building AMMOcoin (15-30 minutes)..."
make -j$(sysctl -n hw.ncpu) V=1

echo ""
echo "Step 6: Creating macOS application bundle and DMG..."
make deploy

echo ""
echo "Step 7: Packaging binaries..."
OUTPUT_DIR="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/macos-binaries-v1.1.0"
mkdir -p "$OUTPUT_DIR"

# Copy command-line binaries
cp src/ammocoind "$OUTPUT_DIR/"
cp src/ammocoin-cli "$OUTPUT_DIR/"
cp src/ammocoin-tx "$OUTPUT_DIR/"

# Copy DMG if created
if [ -f "AMMOcoin-Qt.dmg" ]; then
    cp AMMOcoin-Qt.dmg "$OUTPUT_DIR/"
elif [ -f "src/AMMOcoin-Qt.dmg" ]; then
    cp src/AMMOcoin-Qt.dmg "$OUTPUT_DIR/"
fi

# Copy app bundle
if [ -d "AMMOcoin-Qt.app" ]; then
    cp -r AMMOcoin-Qt.app "$OUTPUT_DIR/"
elif [ -d "src/qt/AMMOcoin-Qt.app" ]; then
    cp -r src/qt/AMMOcoin-Qt.app "$OUTPUT_DIR/"
fi

echo ""
echo "Step 8: Testing binaries..."
"$OUTPUT_DIR/ammocoind" --version
"$OUTPUT_DIR/ammocoin-cli" --version
"$OUTPUT_DIR/ammocoin-tx" --version

echo ""
echo "=============================================="
echo "macOS Build Complete!"
echo "=============================================="
echo ""
echo "Output: $OUTPUT_DIR"
ls -lh "$OUTPUT_DIR"
echo ""
echo "✓ macOS binaries ready"
echo "✓ AMMOcoin-Qt.app (GUI application)"
echo "✓ AMMOcoin-Qt.dmg (installer)"
echo "✓ Command-line tools (ammocoind, ammocoin-cli, ammocoin-tx)"
echo ""
echo "To install:"
echo "  1. Open AMMOcoin-Qt.dmg"
echo "  2. Drag AMMOcoin-Qt.app to Applications folder"
echo "  3. Command-line tools can be copied to /usr/local/bin"
echo ""
