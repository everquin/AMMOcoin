#!/bin/bash
# AMMOcoin v1.1.0 ARM64/Raspberry Pi Build Script
# This script creates ARM64 binaries using Docker for cross-platform compilation

set -e  # Exit on any error

echo "🥧 AMMOcoin v1.1.0 ARM64/Raspberry Pi Build"
echo "==========================================="

# Navigate to project root
cd "/Volumes/CRUCIAL_2TB/  _GITHUB/AMMOcoin"

# Check if source directories exist
if [ ! -d "ammocoin-source" ] || [ ! -d "ammocoin-apps-from-ammocoin" ]; then
    echo "❌ Error: Source directories not found"
    echo "Expected: ammocoin-source/ and ammocoin-apps-from-ammocoin/"
    exit 1
fi

echo "✅ Source directories found"

# Build Docker image for ARM64 compilation
echo "🔨 Building Docker image for ARM64/Raspberry Pi compilation..."
docker build -f Dockerfile.arm64 -t ammocoin-arm64-builder:v1.1.0 .

if [ $? -ne 0 ]; then
    echo "❌ Docker build failed"
    exit 1
fi

echo "✅ Docker image built successfully"

# Create output directory
mkdir -p arm64-binaries-v1.1.0

# Extract binaries from Docker container
echo "📦 Extracting ARM64 binaries..."
docker run --rm -v "$(pwd)/arm64-binaries-v1.1.0:/host-output" ammocoin-arm64-builder:v1.1.0 bash -c "
    cp /output/* /host-output/ &&
    echo '✅ Binaries copied to host' &&
    ls -la /host-output/
"

if [ $? -eq 0 ]; then
    echo ""
    echo "🎉 ARM64/Raspberry Pi build completed successfully!"
    echo "📍 Binaries available in: $(pwd)/arm64-binaries-v1.1.0/"
    echo ""
    echo "📊 Binary Information:"
    cd arm64-binaries-v1.1.0
    for binary in ammocoin*; do
        if [ -f "$binary" ]; then
            echo "  🥧 $binary: $(du -h "$binary" | cut -f1) ($(file "$binary" | cut -d: -f2- | xargs))"
        fi
    done
    echo ""
    echo "🚀 Ready for deployment on Raspberry Pi 4+ (64-bit)!"
    echo "💡 Run these on Raspberry Pi:"
    echo "   ./ammocoind -daemon"
    echo "   ./ammocoin-cli getinfo"
else
    echo "❌ Failed to extract binaries"
    exit 1
fi