#!/bin/bash
# AMMOcoin v1.1.0 Network Launch Script
# Run this on seed1.ammocoin.org to deploy and start the network

set -e

echo "========================================"
echo "AMMOcoin v1.1.0 Network Launch"
echo "========================================"
echo ""

# Configuration
DATA_DIR="/root/.ammocoin-v1.1.0"
V1_DATA_DIR="/root/.ammocoin"
BINARY_PATH="/usr/local/bin"

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Helper functions
success() {
    echo -e "${GREEN}✓${NC} $1"
}

error() {
    echo -e "${RED}✗${NC} $1"
}

warning() {
    echo -e "${YELLOW}⚠${NC} $1"
}

# Step 1: Check if v1.0 wallet exists (backup warning)
echo "Step 1: Checking for v1.0 data..."
if [ -f "$V1_DATA_DIR/wallet.dat" ]; then
    warning "v1.0 wallet detected at $V1_DATA_DIR/wallet.dat"
    warning "This will NOT be touched - v1.1.0 uses separate directory"
    success "v1.0 data will be preserved"
else
    success "No v1.0 data detected (fresh install)"
fi
echo ""

# Step 2: Check if binaries are installed
echo "Step 2: Checking binaries..."
if command -v ammocoind &> /dev/null; then
    VERSION=$(ammocoind --version 2>&1 | head -1)
    success "Found: $VERSION"

    # Check if it's v1.1.0
    if echo "$VERSION" | grep -q "v1.1.0"; then
        success "Correct version: v1.1.0"
    else
        error "Wrong version detected!"
        echo "Please install v1.1.0 binaries first"
        exit 1
    fi
else
    error "ammocoind not found in PATH"
    echo "Please install binaries first:"
    echo "  Option 1: Download from GitHub Release"
    echo "  Option 2: Use binaries in /opt/AMMOcoin/ammocoin-source/src/"
    exit 1
fi
echo ""

# Step 3: Create data directory
echo "Step 3: Creating v1.1.0 data directory..."
if [ -d "$DATA_DIR" ]; then
    warning "Data directory already exists: $DATA_DIR"
else
    mkdir -p "$DATA_DIR"
    success "Created: $DATA_DIR"
fi
echo ""

# Step 4: Create configuration
echo "Step 4: Creating configuration..."
if [ -f "$DATA_DIR/ammocoin.conf" ]; then
    warning "Configuration already exists, backing up..."
    cp "$DATA_DIR/ammocoin.conf" "$DATA_DIR/ammocoin.conf.backup.$(date +%Y%m%d-%H%M%S)"
fi

# Generate strong RPC password
RPC_PASS=$(openssl rand -hex 32)

cat > "$DATA_DIR/ammocoin.conf" << EOF
# AMMOcoin v1.1.0 Seed Node Configuration
listen=1
server=1
daemon=1
dnsseed=1

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=51473

# Network
port=37020
maxconnections=250

# Performance
dbcache=1000
maxmempool=500

# Logging
debug=0
shrinkdebugfile=1

# Staking (enable for initial supply generation)
staking=1
EOF

chmod 600 "$DATA_DIR/ammocoin.conf"
success "Configuration created"

# Save credentials
CRED_FILE="/root/ammocoin-v1.1.0-credentials.txt"
cat > "$CRED_FILE" << EOF
AMMOcoin v1.1.0 Seed Node Credentials
======================================
Node: $(hostname)
Data Directory: $DATA_DIR
RPC User: ammocoinrpc
RPC Password: $RPC_PASS
RPC Port: 51473
P2P Port: 37020
Created: $(date)
EOF
chmod 600 "$CRED_FILE"
success "Credentials saved to $CRED_FILE"
echo ""

# Step 5: Install zkSNARK parameters
echo "Step 5: Installing zkSNARK parameters..."
PARAMS_DIR="/root/.ammocoin-params"
if [ -f "$PARAMS_DIR/sapling-spend.params" ] && [ -f "$PARAMS_DIR/sapling-output.params" ]; then
    success "zkSNARK parameters already installed"
else
    mkdir -p "$PARAMS_DIR"
    cd "$PARAMS_DIR"

    echo "  Downloading sapling-spend.params..."
    wget -q --show-progress https://download.z.cash/downloads/sapling-spend.params

    echo "  Downloading sapling-output.params..."
    wget -q --show-progress https://download.z.cash/downloads/sapling-output.params

    cd ~
    success "zkSNARK parameters installed"
fi
echo ""

# Step 6: Configure firewall
echo "Step 6: Configuring firewall..."
if command -v ufw &> /dev/null; then
    # Check if rule already exists
    if sudo ufw status | grep -q "37020"; then
        success "Firewall already configured for port 37020"
    else
        sudo ufw allow 37020/tcp comment 'AMMOcoin v1.1.0 P2P'
        success "Firewall rule added for port 37020"
    fi
else
    warning "ufw not found, skipping firewall configuration"
fi
echo ""

# Step 7: Start the daemon
echo "Step 7: Starting v1.1.0 daemon..."

# Check if already running
if pgrep -f "ammocoind.*$DATA_DIR" > /dev/null; then
    warning "Daemon already running!"
    echo "Current processes:"
    ps aux | grep "ammocoind.*$DATA_DIR" | grep -v grep
    echo ""
    read -p "Stop and restart? (y/n) " -n 1 -r
    echo ""
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        echo "Stopping daemon..."
        ammocoin-cli -datadir="$DATA_DIR" stop
        sleep 5
    else
        echo "Skipping daemon start"
        exit 0
    fi
fi

echo "Starting daemon with datadir: $DATA_DIR"
ammocoind -datadir="$DATA_DIR" -daemon

success "Daemon started"
echo ""

# Step 8: Wait for startup
echo "Step 8: Waiting for daemon startup..."
sleep 10

# Check if running
if pgrep -f "ammocoind.*$DATA_DIR" > /dev/null; then
    success "Daemon is running"
else
    error "Daemon failed to start!"
    echo "Check logs: tail -100 $DATA_DIR/debug.log"
    exit 1
fi
echo ""

# Step 9: Verify deployment
echo "Step 9: Verifying deployment..."

# Get node info
echo "Getting node info..."
if ! ammocoin-cli -datadir="$DATA_DIR" getinfo &> /dev/null; then
    error "Cannot connect to daemon!"
    echo "Waiting 10 more seconds..."
    sleep 10
fi

# Verify genesis block
echo "Verifying genesis block..."
GENESIS=$(ammocoin-cli -datadir="$DATA_DIR" getblockhash 0 2>/dev/null || echo "error")

EXPECTED_GENESIS="000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329"

if [ "$GENESIS" = "$EXPECTED_GENESIS" ]; then
    success "Correct genesis block (Path A)"
else
    error "WRONG GENESIS BLOCK!"
    echo "Expected: $EXPECTED_GENESIS"
    echo "Got: $GENESIS"
    exit 1
fi

# Get blockchain info
echo ""
echo "Current blockchain status:"
ammocoin-cli -datadir="$DATA_DIR" getblockchaininfo | grep -E "chain|blocks|headers|difficulty"

echo ""
echo "Wallet info:"
ammocoin-cli -datadir="$DATA_DIR" getwalletinfo | grep -E "balance|txcount"

echo ""

# Step 10: Generate initial address
echo "Step 10: Generating initial supply address..."
SUPPLY_ADDRESS=$(ammocoin-cli -datadir="$DATA_DIR" getnewaddress "initial_supply")
success "Initial supply address: $SUPPLY_ADDRESS"

# Save address
echo "$SUPPLY_ADDRESS" > /root/initial-supply-address.txt
echo "Initial Supply Address: $SUPPLY_ADDRESS" >> "$CRED_FILE"
echo ""

# Step 11: Offer to generate initial blocks
echo "Step 11: Initial block generation..."
echo ""
read -p "Generate 100 blocks now for initial supply? (y/n) " -n 1 -r
echo ""
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo "Generating 100 blocks..."
    ammocoin-cli -datadir="$DATA_DIR" generate 100

    echo ""
    echo "Checking balance..."
    BALANCE=$(ammocoin-cli -datadir="$DATA_DIR" getbalance)
    success "Current balance: $BALANCE AMMO"

    BLOCKS=$(ammocoin-cli -datadir="$DATA_DIR" getblockcount)
    success "Current block height: $BLOCKS"
else
    echo "Skipping block generation"
    echo "You can generate blocks later with:"
    echo "  ammocoin-cli -datadir=$DATA_DIR generate 100"
fi
echo ""

# Final status
echo "========================================"
echo "🎉 Network Launch Complete!"
echo "========================================"
echo ""
echo "Node Status:"
ammocoin-cli -datadir="$DATA_DIR" getinfo
echo ""
echo "Genesis Block: $GENESIS"
echo "Initial Supply Address: $SUPPLY_ADDRESS"
echo ""
echo "Credentials saved to: $CRED_FILE"
echo "Logs: tail -f $DATA_DIR/debug.log"
echo ""
echo "Next steps:"
echo "  1. Monitor network: watch -n 5 'ammocoin-cli -datadir=$DATA_DIR getinfo'"
echo "  2. Generate more blocks if needed: ammocoin-cli -datadir=$DATA_DIR generate [count]"
echo "  3. Check balance: ammocoin-cli -datadir=$DATA_DIR getbalance"
echo "  4. Prepare for distribution once sufficient supply is generated"
echo ""
echo "For distribution, you need:"
echo "  - Top 61 holders: 218.7M AMMO"
echo "  - Migration fund: 13.7M AMMO"
echo "  - Total required: 232.4M AMMO"
echo ""
echo "✅ Network is LIVE!"
echo "========================================"
