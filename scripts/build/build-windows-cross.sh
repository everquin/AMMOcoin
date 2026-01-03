#!/bin/bash
# AMMOcoin v1.1.0 - Windows Cross-Compilation Script
# Builds Windows EXE binaries from Linux

set -e

echo "=============================================="
echo "AMMOcoin v1.1.0 Windows Build"
echo "=============================================="
echo ""

export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/parallels/.cargo/bin"

# Install Windows cross-compilation tools
echo "Installing Windows cross-compilation tools..."
sudo apt-get install -y \
    g++-mingw-w64-x86-64 \
    mingw-w64-x86-64-dev \
    nsis \
    zip

cd "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/source"

echo ""
echo "Step 1: Building Windows dependencies..."
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc)
cd ..

echo ""
echo "Step 2: Cleaning previous build..."
make distclean || true
./autogen.sh

echo ""
echo "Step 3: Configuring for Windows..."
CONFIG_SITE=$(pwd)/depends/x86_64-w64-mingw32/share/config.site \
./configure \
    --prefix=/ \
    --disable-ccache \
    --disable-maintainer-mode \
    --disable-dependency-tracking \
    --enable-reduce-exports \
    --disable-bench \
    --disable-gui-tests \
    --disable-online-rust

echo ""
echo "Step 4: Building Windows binaries (15-30 minutes)..."
make -j$(nproc) V=1

echo ""
echo "Step 5: Packaging Windows binaries..."
OUTPUT_DIR="/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/windows-binaries-v1.1.0"
mkdir -p "$OUTPUT_DIR"

# Copy Windows executables
cp src/ammocoind.exe "$OUTPUT_DIR/"
cp src/ammocoin-cli.exe "$OUTPUT_DIR/"
cp src/ammocoin-tx.exe "$OUTPUT_DIR/"

# Strip Windows binaries
x86_64-w64-mingw32-strip "$OUTPUT_DIR"/*.exe

echo ""
echo "Step 6: Creating deployment package..."
cd "$OUTPUT_DIR"
zip -r AMMOcoin-v1.1.0-Windows-x86_64.zip *.exe

echo ""
echo "=============================================="
echo "Windows Build Complete!"
echo "=============================================="
echo ""
echo "Output: $OUTPUT_DIR"
ls -lh "$OUTPUT_DIR"
echo ""
echo "✓ Windows x86_64 binaries ready"
echo "✓ Deployment package: AMMOcoin-v1.1.0-Windows-x86_64.zip"
echo ""
