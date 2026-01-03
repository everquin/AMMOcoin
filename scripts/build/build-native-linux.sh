#!/bin/bash
# AMMOcoin v1.1.0 Native Linux Build Script
# Builds Linux binaries natively on the Linux host system

set -e  # Exit on error

# Setup PATH properly
export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/parallels/.cargo/bin"

# Navigate to build directory
cd "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"

echo "=========================================="
echo "AMMOcoin v1.1.0 Linux Native Build"
echo "=========================================="
echo ""

# Check Rust installation
echo "Checking Rust toolchain..."
rustc --version
cargo --version
echo ""

# Configure for Linux
echo "Configuring build system..."
./configure \
    --prefix=/usr/local \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    --disable-online-rust \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

echo ""
echo "Starting build (this will take 15-30 minutes)..."
echo ""

# Build with multiple cores (limit to avoid OOM)
make -j$(nproc) V=1

echo ""
echo "=========================================="
echo "Build Complete!"
echo "=========================================="
echo ""

# Create output directory
OUTPUT_DIR="/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/linux-binaries-v1.1.0"
mkdir -p "$OUTPUT_DIR"

# Copy binaries
echo "Copying binaries to $OUTPUT_DIR..."
cp src/ammocoind "$OUTPUT_DIR/"
cp src/ammocoin-cli "$OUTPUT_DIR/"
cp src/ammocoin-tx "$OUTPUT_DIR/"

# Strip binaries to reduce size
echo "Stripping debug symbols..."
strip "$OUTPUT_DIR"/ammocoin*

# Set executable permissions
chmod +x "$OUTPUT_DIR"/ammocoin*

echo ""
echo "Binary Information:"
ls -lh "$OUTPUT_DIR"/
echo ""

echo "Testing binaries..."
"$OUTPUT_DIR/ammocoind" --version
"$OUTPUT_DIR/ammocoin-cli" --version
"$OUTPUT_DIR/ammocoin-tx" --version

echo ""
echo "=========================================="
echo "SUCCESS! Linux binaries ready for deployment"
echo "=========================================="
echo "Location: $OUTPUT_DIR"
echo ""
echo "Binaries created:"
echo "  - ammocoind     (full node daemon)"
echo "  - ammocoin-cli  (command-line interface)"
echo "  - ammocoin-tx   (transaction utility)"
echo ""
