#!/bin/bash
# AMMOcoin v1.1.0 Universal Multi-Platform Build Script
# This script creates binaries for all platforms: Linux, Windows, ARM64/Raspberry Pi, and macOS

set -e  # Exit on any error

echo "🌍 AMMOcoin v1.1.0 Universal Multi-Platform Build"
echo "================================================="
echo ""

START_TIME=$(date +%s)

# Navigate to project root
cd "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin"

echo "🚀 Starting comprehensive multi-platform build..."
echo "Platforms: Linux x86_64, Windows x64, ARM64/Raspberry Pi, macOS ARM64"
echo ""

# Check if Docker is running
if ! docker info > /dev/null 2>&1; then
    echo "❌ Docker is not running. Please start Docker Desktop."
    exit 1
fi

echo "✅ Docker is running"

# Check if source directories exist
if [ ! -d "ammocoin-source" ] || [ ! -d "ammocoin-apps-from-ammocoin" ]; then
    echo "❌ Error: Source directories not found"
    echo "Expected: ammocoin-source/ and ammocoin-apps-from-ammocoin/"
    exit 1
fi

echo "✅ Source directories found"
echo ""

# Make all build scripts executable
chmod +x build-linux.sh build-windows.sh build-arm64.sh

# Build Linux x86_64
echo "🐧 === Building Linux x86_64 Binaries ==="
if ! ./build-linux.sh; then
    echo "❌ Linux build failed"
    exit 1
fi
echo ""

# Build Windows x64
echo "🏢 === Building Windows x64 Binaries ==="
if ! ./build-windows.sh; then
    echo "❌ Windows build failed"
    exit 1
fi
echo ""

# Build ARM64/Raspberry Pi
echo "🥧 === Building ARM64/Raspberry Pi Binaries ==="
if ! ./build-arm64.sh; then
    echo "❌ ARM64 build failed"
    exit 1
fi
echo ""

# Build macOS ARM64 (native)
echo "🍎 === Building macOS ARM64 Binaries ==="
echo "Building macOS native binaries..."
mkdir -p macos-binaries-v1.1.0

cd ammocoin-apps-from-ammocoin

# Clean previous build
make clean > /dev/null 2>&1 || true

# Configure for macOS
export LDFLAGS="-L/opt/homebrew/opt/berkeley-db@4/lib -L/opt/homebrew/lib"
export CPPFLAGS="-I/opt/homebrew/opt/berkeley-db@4/include -I/opt/homebrew/include"

if ! ./configure --disable-tests --disable-bench --without-gui --enable-wallet --with-incompatible-bdb > /dev/null 2>&1; then
    echo "❌ macOS configure failed"
    cd ..
    exit 1
fi

# Build macOS binaries
if ! make -j$(sysctl -n hw.ncpu) > /dev/null 2>&1; then
    echo "❌ macOS build failed"
    cd ..
    exit 1
fi

# Copy binaries
cp src/ammocoind ../macos-binaries-v1.1.0/
cp src/ammocoin-cli ../macos-binaries-v1.1.0/
cp src/ammocoin-tx ../macos-binaries-v1.1.0/

cd ..

echo "✅ macOS ARM64 build completed successfully!"
echo ""

# Summary
END_TIME=$(date +%s)
DURATION=$((END_TIME - START_TIME))

echo "🎉 === BUILD SUMMARY ==="
echo "Total build time: ${DURATION} seconds"
echo ""

echo "📦 All Platform Binaries Created:"
echo ""

if [ -d "linux-binaries-v1.1.0" ]; then
    echo "🐧 Linux x86_64:"
    for binary in linux-binaries-v1.1.0/ammocoin*; do
        if [ -f "$binary" ]; then
            echo "   $(basename "$binary"): $(du -h "$binary" | cut -f1)"
        fi
    done
    echo ""
fi

if [ -d "windows-binaries-v1.1.0" ]; then
    echo "🏢 Windows x64:"
    for binary in windows-binaries-v1.1.0/ammocoin*.exe; do
        if [ -f "$binary" ]; then
            echo "   $(basename "$binary"): $(du -h "$binary" | cut -f1)"
        fi
    done
    echo ""
fi

if [ -d "arm64-binaries-v1.1.0" ]; then
    echo "🥧 ARM64/Raspberry Pi:"
    for binary in arm64-binaries-v1.1.0/ammocoin*; do
        if [ -f "$binary" ]; then
            echo "   $(basename "$binary"): $(du -h "$binary" | cut -f1)"
        fi
    done
    echo ""
fi

if [ -d "macos-binaries-v1.1.0" ]; then
    echo "🍎 macOS ARM64:"
    for binary in macos-binaries-v1.1.0/ammocoin*; do
        if [ -f "$binary" ]; then
            echo "   $(basename "$binary"): $(du -h "$binary" | cut -f1)"
        fi
    done
    echo ""
fi

echo "🚀 DEPLOYMENT READY!"
echo ""
echo "Next steps:"
echo "1. Test binaries on target platforms"
echo "2. Package for distribution"
echo "3. Deploy to production environments"
echo ""
echo "💡 Quick test commands for each platform:"
echo "   Linux:       ./linux-binaries-v1.1.0/ammocoind -version"
echo "   Windows:     ./windows-binaries-v1.1.0/ammocoind.exe -version"
echo "   Raspberry:   ./arm64-binaries-v1.1.0/ammocoind -version"
echo "   macOS:       ./macos-binaries-v1.1.0/ammocoind -version"