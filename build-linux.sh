#!/bin/bash
# AMMOcoin v1.1.0 Linux Build Script for Vultr VPS Masternodes
# This script creates Linux binaries using Docker for cross-platform compilation

set -e  # Exit on any error

echo "🚀 AMMOcoin v1.1.0 Linux Build for Vultr VPS Masternodes"
echo "=========================================================="

# Navigate to project root (use script's directory)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Check if source directories exist
if [ ! -d "ammocoin-source" ] || [ ! -d "ammocoin-apps-from-ammocoin" ]; then
    echo "❌ Error: Source directories not found"
    echo "Expected: ammocoin-source/ and ammocoin-apps-from-ammocoin/"
    exit 1
fi

echo "✅ Source directories found"

# Build Docker image for Linux x86_64 compilation
echo "🔨 Building Docker image for Linux x86_64 compilation..."
docker buildx build --platform linux/amd64 -f Dockerfile.linux -t ammocoin-linux-builder:v1.1.0 . --load

if [ $? -ne 0 ]; then
    echo "❌ Docker build failed"
    exit 1
fi

echo "✅ Docker image built successfully"

# Create output directory
mkdir -p linux-binaries-v1.1.0

# Extract binaries from Docker container
echo "📦 Extracting Linux binaries..."
docker run --rm -v "$(pwd)/linux-binaries-v1.1.0:/host-output" ammocoin-linux-builder:v1.1.0 bash -c "
    cp /output/* /host-output/ &&
    echo '✅ Binaries copied to host' &&
    ls -la /host-output/
"

if [ $? -eq 0 ]; then
    echo ""
    echo "🎉 Linux build completed successfully!"
    echo "📍 Binaries available in: $(pwd)/linux-binaries-v1.1.0/"
    echo ""
    echo "📊 Binary Information:"
    cd linux-binaries-v1.1.0
    for binary in ammocoin*; do
        if [ -f "$binary" ]; then
            echo "  📱 $binary: $(du -h "$binary" | cut -f1) ($(file "$binary" | cut -d: -f2- | xargs))"
        fi
    done
    echo ""
    echo "🚀 Ready for deployment to Vultr VPS masternodes!"
    echo "💡 Upload these binaries to your VPS and run:"
    echo "   ./ammocoind -daemon"
    echo "   ./ammocoin-cli getinfo"
else
    echo "❌ Failed to extract binaries"
    exit 1
fi