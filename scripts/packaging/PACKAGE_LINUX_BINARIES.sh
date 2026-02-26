#!/bin/bash
# Package Linux binaries for distribution
# Run this AFTER downloading binaries with DOWNLOAD_LINUX_BINARIES.sh

set -e

REPO_ROOT="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin"
BINARY_DIR="$REPO_ROOT/binaries-linux-v1.1.0"
RELEASE_DIR="$REPO_ROOT/releases"
VERSION="v1.1.0"

echo "================================================"
echo "AMMOcoin Linux Binary Packaging Script"
echo "Version: $VERSION"
echo "================================================"
echo ""

# Check if binaries exist
if [ ! -f "$BINARY_DIR/ammocoind" ]; then
    echo "❌ ERROR: Binaries not found in $BINARY_DIR"
    echo ""
    echo "Please run ./DOWNLOAD_LINUX_BINARIES.sh first to download binaries from VM"
    exit 1
fi

echo "✓ Found binaries in $BINARY_DIR"
echo ""

# Verify binaries
echo "Verifying binaries..."
ls -lh "$BINARY_DIR"
echo ""

# Check if they are Linux ELF binaries
echo "Checking binary format..."
file "$BINARY_DIR/ammocoind"
file "$BINARY_DIR/ammocoin-cli"
file "$BINARY_DIR/ammocoin-tx"
echo ""

# Create releases directory if it doesn't exist
mkdir -p "$RELEASE_DIR"

# Package as tar.gz
echo "Creating tar.gz archive..."
cd "$BINARY_DIR"
tar -czf "$RELEASE_DIR/AMMOcoin-Linux-x86_64.tar.gz" ammocoind ammocoin-cli ammocoin-tx
echo "✓ Created: $RELEASE_DIR/AMMOcoin-Linux-x86_64.tar.gz"
ls -lh "$RELEASE_DIR/AMMOcoin-Linux-x86_64.tar.gz"
echo ""

# Package as zip
echo "Creating zip archive..."
zip -q "$RELEASE_DIR/AMMOcoin-Linux-x86_64.zip" ammocoind ammocoin-cli ammocoin-tx
echo "✓ Created: $RELEASE_DIR/AMMOcoin-Linux-x86_64.zip"
ls -lh "$RELEASE_DIR/AMMOcoin-Linux-x86_64.zip"
echo ""

# Generate checksums
echo "Generating checksums..."
cd "$RELEASE_DIR"

# Linux binaries checksums
sha256sum AMMOcoin-Linux-x86_64.tar.gz >> CHECKSUMS-Linux.txt
sha256sum AMMOcoin-Linux-x86_64.zip >> CHECKSUMS-Linux.txt

echo "✓ Checksums written to CHECKSUMS-Linux.txt"
echo ""
cat CHECKSUMS-Linux.txt
echo ""

# Summary
echo "================================================"
echo "✅ Linux Binary Packaging Complete!"
echo "================================================"
echo ""
echo "Created files:"
echo "  📦 $RELEASE_DIR/AMMOcoin-Linux-x86_64.tar.gz"
echo "  📦 $RELEASE_DIR/AMMOcoin-Linux-x86_64.zip"
echo "  🔐 $RELEASE_DIR/CHECKSUMS-Linux.txt"
echo ""
echo "Next steps:"
echo "  1. Verify archives can be extracted successfully"
echo "  2. Add these files to git"
echo "  3. Commit and push to GitHub"
echo "  4. Create GitHub release with these binaries"
echo ""
echo "To add to git:"
echo "  cd $REPO_ROOT"
echo "  git add releases/AMMOcoin-Linux-x86_64.*"
echo "  git add releases/CHECKSUMS-Linux.txt"
echo "  git commit -m 'Add Linux x86_64 binaries for v1.1.0'"
echo "  git push origin main"
echo ""
