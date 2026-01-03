#!/bin/bash
# AMMOcoin v1.1.0 - Windows Cross-Compilation (MinGW already installed)
set -e

echo "=============================================="
echo "AMMOcoin v1.1.0 Windows Build"
echo "=============================================="
echo ""

export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/parallels/.cargo/bin"

# Verify MinGW is installed
if ! command -v x86_64-w64-mingw32-g++ &> /dev/null; then
    echo "ERROR: MinGW not found. Please install it first:"
    echo "sudo apt-get install -y g++-mingw-w64-x86-64 mingw-w64-x86-64-dev nsis zip"
    exit 1
fi

echo "✓ MinGW found: $(x86_64-w64-mingw32-g++ --version | head -1)"
echo ""

cd "/media/psf/CRUCIAL_2TB/  _GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin"

echo "Step 1: Building Windows dependencies (15-20 minutes)..."
cd depends
make HOST=x86_64-w64-mingw32 -j$(nproc) V=1
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
echo "Step 4: Building Windows binaries (10-15 minutes)..."
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
