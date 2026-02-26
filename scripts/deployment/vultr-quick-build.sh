#!/bin/bash
# AMMOcoin v1.1.0 Quick Build Script for Vultr Ubuntu VM
# Run this on seed1.ammocoin.build to compile Linux x86_64 binaries

set -e  # Exit on any error

echo "🚀 AMMOcoin v1.1.0 Linux Build Script"
echo "===================================="
echo ""

# Stop any running daemon
echo "⏸️  Stopping any running daemon..."
ammocoin-cli stop 2>/dev/null || killall ammocoind 2>/dev/null || true
sleep 2

# Clean up old builds
echo "🧹 Cleaning up old build directories..."
cd ~
rm -rf AMMOcoin-build ammocoin-v1.1.0-temp ammocoin-linux-release

# Clone fresh code
echo "📥 Cloning fresh v1.1.0 code from GitHub..."
git clone https://github.com/everquin/AMMOcoin.git AMMOcoin-build
cd AMMOcoin-build

# Verify genesis hash
echo "🔍 Verifying genesis block hash..."
if grep -q "00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162" source/src/chainparams.cpp; then
    echo "✅ Correct genesis hash found!"
else
    echo "❌ ERROR: Genesis hash not found in source code!"
    echo "The repository may not have the correct v1.1.0 code."
    exit 1
fi

# Ensure Rust is in PATH
echo "🦀 Setting up Rust environment..."
export PATH="$HOME/.cargo/bin:$PATH"
source ~/.cargo/env 2>/dev/null || true

# Check dependencies
echo "🔧 Checking build dependencies..."
if ! command -v rustc &> /dev/null; then
    echo "📦 Installing Rust..."
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
    source ~/.cargo/env
fi

# Navigate to build directory
cd ~/AMMOcoin-build/source

# Clean any previous attempts
echo "🧼 Cleaning previous build artifacts..."
make clean 2>/dev/null || true
make distclean 2>/dev/null || true

# Generate build scripts
echo "⚙️  Running autogen..."
./autogen.sh

# Configure
echo "🔨 Configuring build..."
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

# Build (use all CPU cores)
echo "🏗️  Building binaries (this will take 10-20 minutes)..."
echo "Using $(nproc) CPU cores..."
make -j$(nproc) CARGO=$HOME/.cargo/bin/cargo RUSTC=$HOME/.cargo/bin/rustc

# Check if build succeeded
if [ -f src/ammocoind ] && [ -f src/ammocoin-cli ] && [ -f src/ammocoin-tx ]; then
    echo ""
    echo "✅ BUILD SUCCESSFUL!"
    echo ""
    echo "📊 Binary Sizes:"
    ls -lh src/ammocoind src/ammocoin-cli src/ammocoin-tx
    echo ""
else
    echo ""
    echo "❌ BUILD FAILED!"
    echo "Binaries not found. Check output above for errors."
    exit 1
fi

# Verify genesis hash in compiled binary
echo "🔍 Verifying genesis hash in compiled binary..."
if strings src/ammocoind | grep -q "00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162"; then
    echo "✅ Genesis hash verified in binary!"
else
    echo "⚠️  WARNING: Genesis hash not found in binary!"
fi

# Show version
echo ""
echo "📋 Binary Version:"
src/ammocoind --version
echo ""

# Create release package
echo "📦 Creating release package..."
mkdir -p ~/ammocoin-linux-release/bin
cp src/ammocoind ~/ammocoin-linux-release/bin/
cp src/ammocoin-cli ~/ammocoin-linux-release/bin/
cp src/ammocoin-tx ~/ammocoin-linux-release/bin/

# Create README
cat > ~/ammocoin-linux-release/README.md << 'EOFREADME'
# AMMOcoin v1.1.0 - Linux x86_64

**Platform:** Linux x86_64 (Ubuntu 18.04+)
**Genesis Hash:** 00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162
**Genesis Reward:** 250,000,000 AMMO

## Binaries

- ammocoind - AMMOcoin daemon
- ammocoin-cli - Command-line interface
- ammocoin-tx - Transaction utility

## Installation

```bash
sudo cp bin/* /usr/local/bin/
sudo chmod +x /usr/local/bin/ammocoin*
```

## Quick Start

```bash
ammocoind -daemon
ammocoin-cli getinfo
```
EOFREADME

# Create archive
echo "🗜️  Creating compressed archive..."
cd ~/ammocoin-linux-release
tar -czf ~/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz .

# Generate checksum
echo "🔐 Generating SHA256 checksum..."
cd ~
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz > AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "🎉 BUILD COMPLETE!"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "📦 Release Archive:"
ls -lh ~/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
echo ""
echo "🔐 Checksum:"
cat ~/AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt
echo ""
echo "📂 Binary Directory: ~/ammocoin-linux-release/bin/"
echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "📥 Download to Mac:"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "On your Mac, run:"
echo ""
echo "scp root@seed1.ammocoin.build:~/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/"
echo "scp root@seed1.ammocoin.build:~/AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/"
echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
