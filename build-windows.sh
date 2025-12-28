#!/bin/bash
# AMMOcoin v1.1.0 Windows Cross-Compilation Build Script
# This script creates Windows binaries using Docker for cross-platform compilation

set -e  # Exit on any error

echo "🏢 AMMOcoin v1.1.0 Windows x64 Build"
echo "====================================="

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

# Build Docker image for Windows compilation
echo "🔨 Building Docker image for Windows cross-compilation..."
docker build -f Dockerfile.windows -t ammocoin-windows-builder:v1.1.0 .

if [ $? -ne 0 ]; then
    echo "❌ Docker build failed"
    exit 1
fi

echo "✅ Docker image built successfully"

# Create output directory
mkdir -p windows-binaries-v1.1.0

# Extract binaries from Docker container
echo "📦 Extracting Windows binaries..."
docker run --rm -v "$(pwd)/windows-binaries-v1.1.0:/host-output" ammocoin-windows-builder:v1.1.0 bash -c "
    cp /output/* /host-output/ &&
    echo '✅ Binaries copied to host' &&
    ls -la /host-output/
"

if [ $? -eq 0 ]; then
    echo ""
    echo "🎉 Windows build completed successfully!"
    echo "📍 Binaries available in: $(pwd)/windows-binaries-v1.1.0/"
    echo ""
    echo "📊 Binary Information:"
    cd windows-binaries-v1.1.0
    for binary in ammocoin*.exe; do
        if [ -f "$binary" ]; then
            echo "  💻 $binary: $(du -h "$binary" | cut -f1) ($(file "$binary" | cut -d: -f2- | xargs))"
        fi
    done
    echo ""
    echo "🚀 Ready for deployment on Windows systems!"
    echo "💡 Run these on Windows:"
    echo "   ./ammocoind.exe -daemon"
    echo "   ./ammocoin-cli.exe getinfo"
else
    echo "❌ Failed to extract binaries"
    exit 1
fi