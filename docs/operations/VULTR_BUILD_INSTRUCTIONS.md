# Building AMMOcoin v1.1.0 on Vultr Ubuntu VM (seed1.ammocoin.build)

**Date:** January 1, 2026
**Target:** Linux x86_64 binaries with v1.1.0 genesis block
**Node:** seed1.ammocoin.build

---

## Step 1: Connect to Vultr VM

```bash
ssh root@seed1.ammocoin.build
# Or whatever your connection method is
```

---

## Step 2: Clean Up Any Existing v1.1.0 Code

**IMPORTANT:** We updated the genesis block, so we need to remove old code and start fresh.

```bash
# Stop any running daemon first
ammocoin-cli stop 2>/dev/null || killall ammocoind 2>/dev/null || true

# Remove old build directories (preserve wallet data if any)
cd ~
rm -rf AMMOcoin-build
rm -rf ammocoin-v1.1.0-temp

# Clear any cached build artifacts
rm -rf ~/.cargo/registry/cache
```

---

## Step 3: Clone Fresh Repository

```bash
# Clone the latest code with v1.1.0 genesis
cd ~
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git AMMOcoin-build
cd AMMOcoin-build

# Verify we have the correct genesis hash
grep -r "00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162" source/src/chainparams.cpp

# Should show the correct genesis hash - if not, stop here!
```

---

## Step 4: Install Build Dependencies (if not already installed)

```bash
# Update package list
sudo apt-get update

# Install essential build tools
sudo apt-get install -y \
    build-essential \
    autoconf \
    automake \
    libtool \
    pkg-config \
    git \
    curl \
    wget \
    libssl-dev \
    libboost-all-dev \
    libdb-dev \
    libdb++-dev \
    libevent-dev \
    libzmq3-dev \
    libminiupnpc-dev \
    libnatpmp-dev \
    libgmp-dev \
    libsodium-dev \
    python3

# Install Rust (if not already installed)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source ~/.cargo/env

# Verify installations
rustc --version
cargo --version
gcc --version
```

---

## Step 5: Build AMMOcoin v1.1.0 Binaries

```bash
# Navigate to build directory
cd ~/AMMOcoin-build/source

# Clean any previous build attempts
make clean 2>/dev/null || true
make distclean 2>/dev/null || true

# Generate build scripts
./autogen.sh

# Configure the build
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

# Build binaries (this will take 10-20 minutes on native hardware)
# Use all available CPU cores
make -j$(nproc) CARGO=$HOME/.cargo/bin/cargo RUSTC=$HOME/.cargo/bin/rustc

# Check if build succeeded
if [ -f src/ammocoind ] && [ -f src/ammocoin-cli ] && [ -f src/ammocoin-tx ]; then
    echo "✅ Build successful!"
    ls -lh src/ammocoin*
else
    echo "❌ Build failed - check output above for errors"
    exit 1
fi
```

---

## Step 6: Verify Genesis Block in Compiled Binaries

```bash
# Check that the correct genesis hash is embedded in the binary
strings src/ammocoind | grep "00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162"

# Should output: 00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162
# If not found, the build has the wrong genesis block!

# Also verify the version
src/ammocoind --version
# Should show: AMMOcoin Core Daemon version v1.1.0.0
```

---

## Step 7: Create Release Package

```bash
# Create output directory
mkdir -p ~/ammocoin-linux-release/bin

# Copy binaries
cp src/ammocoind ~/ammocoin-linux-release/bin/
cp src/ammocoin-cli ~/ammocoin-linux-release/bin/
cp src/ammocoin-tx ~/ammocoin-linux-release/bin/

# Check binary sizes
ls -lh ~/ammocoin-linux-release/bin/

# Create README
cat > ~/ammocoin-linux-release/README.md << 'EOF'
# AMMOcoin v1.1.0 - Linux x86_64

**Built on:** $(date)
**Platform:** Linux x86_64 (Ubuntu 18.04+)
**Genesis Hash:** 00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162

## Package Contents

- ammocoind - AMMOcoin daemon
- ammocoin-cli - Command-line interface
- ammocoin-tx - Transaction utility

## Installation

```bash
# Extract binaries
sudo cp bin/* /usr/local/bin/
sudo chmod +x /usr/local/bin/ammocoin*

# Verify installation
ammocoind --version
```

## Quick Start

```bash
# Start daemon
ammocoind -daemon

# Check status
ammocoin-cli getinfo

# Stop daemon
ammocoin-cli stop
```

## Network Parameters

- Max Supply: 9,999,999,999 AMMO
- Genesis Premine: 250,000,000 AMMO
- Block Time: 3 minutes
- RPC Port: 37020
- P2P Port: 37019

Built with ❤️ for the AMMOcoin community
EOF

# Create archive
cd ~/ammocoin-linux-release
tar -czf ../AMMOcoin-v1.1.0-Linux-x86_64.tar.gz .
cd ~

# Verify archive
ls -lh AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Generate checksum
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz > AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt
cat AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt
```

---

## Step 8: Transfer Binaries to Development Machine

**On your Mac (where you're running Claude Code):**

```bash
# Create directory for Linux binaries
mkdir -p /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/linux-x86_64

# Download from Vultr VM
scp root@seed1.ammocoin.build:~/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/
scp root@seed1.ammocoin.build:~/AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/

# Or if you want individual binaries:
scp root@seed1.ammocoin.build:~/ammocoin-linux-release/bin/* /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/linux-x86_64/

# Verify download
ls -lh /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
cat /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases/AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt
```

---

## Step 9: Verify on Linux

**Back on the Vultr VM, test the binaries:**

```bash
# Create test directory
mkdir -p /tmp/ammocoin-v1.1.0-test

# Create minimal config
cat > /tmp/ammocoin-v1.1.0-test/ammocoin.conf << EOF
regtest=0
testnet=0
listen=1
server=1
rpcuser=test_user
rpcpassword=test_pass_$(date +%s)
rpcallowip=127.0.0.1
rpcport=37020
dnsseed=1
EOF

# Start daemon with test directory
~/ammocoin-linux-release/bin/ammocoind -datadir=/tmp/ammocoin-v1.1.0-test -daemon

# Wait a few seconds
sleep 5

# Check it's running
~/ammocoin-linux-release/bin/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test getinfo

# Verify genesis block
~/ammocoin-linux-release/bin/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test getblockhash 0
# Should return: 00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162

# Check genesis block details
~/ammocoin-linux-release/bin/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test getblock $(~/ammocoin-linux-release/bin/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test getblockhash 0) 2

# Look for: "value": 250000000.00 in the genesis transaction

# Stop test daemon
~/ammocoin-linux-release/bin/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test stop

# Cleanup test data
rm -rf /tmp/ammocoin-v1.1.0-test
```

---

## Expected Build Time

- **Native x86_64 Ubuntu:** 10-20 minutes (depending on CPU)
- **With SSD:** Faster
- **With multiple cores:** Use `make -j$(nproc)` for parallel compilation

---

## Troubleshooting

### Build Fails with "command not found"
```bash
# Make sure Rust is in PATH
source ~/.cargo/env
```

### Build Fails with Missing Libraries
```bash
# Re-run dependency installation
sudo apt-get update
sudo apt-get install -y libboost-all-dev libdb-dev libdb++-dev
```

### Build Fails with Autotools Errors
```bash
# Clean and regenerate
make distclean
./autogen.sh
```

### Genesis Hash Not Found in Binary
```bash
# You have the wrong source code - pull fresh from GitHub
cd ~
rm -rf AMMOcoin-build
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git AMMOcoin-build
```

---

## What to Tell Claude Code After Build Completes

```
I've completed the Linux x86_64 build on seed1.ammocoin.build. The binaries are at:
- ~/ammocoin-linux-release/bin/ammocoind
- ~/ammocoin-linux-release/bin/ammocoin-cli
- ~/ammocoin-linux-release/bin/ammocoin-tx

Archive: ~/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
Checksum: ~/AMMOcoin-v1.1.0-Linux-x86_64-CHECKSUM.txt

Genesis hash verified: 00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162

Daemon tested and working. Ready to download to Mac and add to release.
```

---

**Built by:** seed1.ammocoin.build
**Last Updated:** 2026-01-01
