#!/bin/bash

# AMMOcoin Multi-Platform Build Script
# Builds AMMOcoin binaries for Linux, Windows, and ARM64/Raspberry Pi

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
SOURCE_DIR="$PROJECT_ROOT/source"
OUTPUT_DIR="$PROJECT_ROOT/releases"

echo "🚀 AMMOcoin Multi-Platform Build Starting..."
echo "Project Root: $PROJECT_ROOT"
echo "Source Directory: $SOURCE_DIR"
echo "Output Directory: $OUTPUT_DIR"

# Create output directory
mkdir -p "$OUTPUT_DIR"

# Function to build for a specific platform
build_platform() {
    local platform=$1
    local dockerfile=$2
    local output_subdir=$3

    echo ""
    echo "🔨 Building AMMOcoin for $platform..."
    echo "=================================="

    # Build Docker image
    echo "📦 Building Docker image for $platform..."
    docker build -t "ammocoin-build-$platform" -f "$SCRIPT_DIR/$dockerfile" "$SOURCE_DIR"

    # Run the build
    echo "⚙️  Running build for $platform..."
    docker run --rm -v "$OUTPUT_DIR:/output" "ammocoin-build-$platform" bash -c "
        # Copy binaries to output
        mkdir -p /output/$output_subdir
        cp -r /build/$output_subdir/bin/* /output/$output_subdir/ 2>/dev/null || true

        # Show build results
        echo 'Build completed for $platform:'
        ls -la /build/$output_subdir/bin/ 2>/dev/null || echo 'No binaries found in expected location'

        # Try alternative locations
        find /build -name 'ammocoin*' -type f -executable 2>/dev/null || echo 'No AMMOcoin binaries found'
    "

    echo "✅ $platform build completed!"
}

# Check Docker availability
if ! command -v docker &> /dev/null; then
    echo "❌ Docker is required but not installed. Please install Docker first."
    exit 1
fi

echo "🐳 Docker detected. Starting builds..."

# Build for all platforms
echo ""
echo "🎯 Building for all target platforms..."
echo "======================================"

# Linux x64
build_platform "Linux x64" "Dockerfile.linux" "linux-x64"

# Windows x64
build_platform "Windows x64" "Dockerfile.windows" "windows-x64"

# ARM64 (Raspberry Pi)
build_platform "ARM64/Raspberry Pi" "Dockerfile.arm64" "arm64"

# Create release packages
echo ""
echo "📦 Creating release packages..."
echo "=============================="

cd "$OUTPUT_DIR"

# Create version info
VERSION="1.1.0"
BUILD_DATE=$(date -u +"%Y-%m-%d %H:%M:%S UTC")

cat > VERSION.txt << EOF
AMMOcoin v$VERSION Multi-Platform Release
Built: $BUILD_DATE

Platforms included:
- Linux x64 (Ubuntu/Debian)
- Windows x64
- ARM64 (Raspberry Pi/aarch64)

Built with BLS stub compatibility layer for maximum portability.
EOF

# Create individual platform packages
for platform in linux-x64 windows-x64 arm64; do
    if [ -d "$platform" ] && [ "$(ls -A $platform 2>/dev/null)" ]; then
        echo "📦 Packaging $platform..."

        # Create platform-specific directory
        mkdir -p "AMMOcoin-v$VERSION-$platform"
        cp -r "$platform"/* "AMMOcoin-v$VERSION-$platform/"
        cp ../paper-wallet-generator/* "AMMOcoin-v$VERSION-$platform/" 2>/dev/null || true
        cp VERSION.txt "AMMOcoin-v$VERSION-$platform/"

        # Create README for platform
        cat > "AMMOcoin-v$VERSION-$platform/README.txt" << EOF
AMMOcoin v$VERSION - $platform

This package contains:
- ammocoind: AMMOcoin Core daemon
- ammocoin-cli: Command-line interface
- ammocoin-tx: Transaction utility
- Paper wallet generator (HTML)

Installation:
1. Extract this package
2. Run the binaries from command line
3. For paper wallets, open index.html in a web browser

For more information, visit the AMMOcoin project repository.
EOF

        # Create archive
        if command -v zip &> /dev/null; then
            zip -r "AMMOcoin-v$VERSION-$platform.zip" "AMMOcoin-v$VERSION-$platform/"
            echo "✅ Created AMMOcoin-v$VERSION-$platform.zip"
        fi

        if command -v tar &> /dev/null; then
            tar -czf "AMMOcoin-v$VERSION-$platform.tar.gz" "AMMOcoin-v$VERSION-$platform/"
            echo "✅ Created AMMOcoin-v$VERSION-$platform.tar.gz"
        fi

        # Clean up directory
        rm -rf "AMMOcoin-v$VERSION-$platform"
    else
        echo "⚠️  No binaries found for $platform"
    fi
done

# Create combined release
echo ""
echo "📦 Creating combined multi-platform release..."
mkdir -p "AMMOcoin-v$VERSION-MultiPlatform"
cp -r linux-x64 windows-x64 arm64 "AMMOcoin-v$VERSION-MultiPlatform/" 2>/dev/null || true
cp ../paper-wallet-generator/* "AMMOcoin-v$VERSION-MultiPlatform/" 2>/dev/null || true
cp VERSION.txt "AMMOcoin-v$VERSION-MultiPlatform/"

cat > "AMMOcoin-v$VERSION-MultiPlatform/README.txt" << EOF
AMMOcoin v$VERSION - Multi-Platform Release

This package contains binaries for all supported platforms:

linux-x64/: Linux x64 binaries
windows-x64/: Windows x64 binaries (.exe)
arm64/: ARM64/Raspberry Pi binaries

Paper Wallet Generator:
- index.html: Secure offline paper wallet generator
- README.md: Paper wallet documentation

Each platform directory contains:
- ammocoind: AMMOcoin Core daemon
- ammocoin-cli: Command-line interface
- ammocoin-tx: Transaction utility

Choose the appropriate platform directory for your system.
For paper wallets, open index.html in any modern web browser.
EOF

if command -v zip &> /dev/null; then
    zip -r "AMMOcoin-v$VERSION-MultiPlatform.zip" "AMMOcoin-v$VERSION-MultiPlatform/"
    echo "✅ Created AMMOcoin-v$VERSION-MultiPlatform.zip"
fi

if command -v tar &> /dev/null; then
    tar -czf "AMMOcoin-v$VERSION-MultiPlatform.tar.gz" "AMMOcoin-v$VERSION-MultiPlatform/"
    echo "✅ Created AMMOcoin-v$VERSION-MultiPlatform.tar.gz"
fi

rm -rf "AMMOcoin-v$VERSION-MultiPlatform"

# Summary
echo ""
echo "🎉 AMMOcoin Multi-Platform Build Complete!"
echo "========================================"
echo ""
echo "📁 Release files created in: $OUTPUT_DIR"
echo ""
echo "📊 Build Summary:"
echo "=================="

for platform in linux-x64 windows-x64 arm64; do
    if [ -d "$platform" ] && [ "$(ls -A $platform 2>/dev/null)" ]; then
        echo "✅ $platform: Success"
        echo "   Files: $(ls $platform 2>/dev/null | wc -l) binaries"
    else
        echo "❌ $platform: Failed or no output"
    fi
done

echo ""
echo "📦 Release Packages:"
echo "==================="
ls -la *.zip *.tar.gz 2>/dev/null || echo "No packages created"

echo ""
echo "🔗 Next Steps:"
echo "=============="
echo "1. Test binaries on target platforms"
echo "2. Verify paper wallet functionality"
echo "3. Upload releases to distribution channels"
echo "4. Update documentation"

echo ""
echo "✨ Build process completed successfully!"