#!/bin/bash
# Quick Local Test Script for AMMOcoin v1.1.0 on macOS
# This sets up and starts a local test node

set -e

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
AMMOCOIN_SRC="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin/src"
AMMOCOIN_TEST_DATA="$HOME/.ammocoin-v1.1.0-test"
PARAMS_DIR="$HOME/.ammocoin-params"

echo "========================================"
echo "AMMOcoin v1.1.0 Local Test Node (macOS)"
echo "========================================"
echo ""

# Step 1: Verify binaries exist
echo -e "${BLUE}Step 1: Checking binaries...${NC}"
if [ ! -f "$AMMOCOIN_SRC/ammocoind" ]; then
    echo -e "${RED}✗ Binary not found at: $AMMOCOIN_SRC/ammocoind${NC}"
    exit 1
fi

VERSION=$("$AMMOCOIN_SRC/ammocoind" --version 2>&1 | head -1)
echo -e "${GREEN}✓ Found: $VERSION${NC}"

ARCH=$(file "$AMMOCOIN_SRC/ammocoind" | grep -o "arm64\|x86_64")
echo -e "${GREEN}✓ Architecture: $ARCH${NC}"
echo ""

# Step 2: Install zkSNARK parameters if needed
echo -e "${BLUE}Step 2: Checking zkSNARK parameters...${NC}"
if [ -f "$PARAMS_DIR/sapling-spend.params" ] && [ -f "$PARAMS_DIR/sapling-output.params" ]; then
    echo -e "${GREEN}✓ Parameters already installed${NC}"
else
    echo -e "${YELLOW}Installing zkSNARK parameters...${NC}"
    mkdir -p "$PARAMS_DIR"
    cd "$PARAMS_DIR"

    echo "  Downloading sapling-spend.params (48 MB)..."
    curl -# -O https://download.z.cash/downloads/sapling-spend.params

    echo "  Downloading sapling-output.params (3.6 MB)..."
    curl -# -O https://download.z.cash/downloads/sapling-output.params

    cd - > /dev/null
    echo -e "${GREEN}✓ Parameters installed${NC}"
fi
echo ""

# Step 3: Create test data directory
echo -e "${BLUE}Step 3: Setting up test environment...${NC}"
if [ -d "$AMMOCOIN_TEST_DATA" ]; then
    echo -e "${YELLOW}⚠ Test data directory already exists${NC}"
    read -p "Delete and start fresh? (y/n) " -n 1 -r
    echo ""
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        # Stop daemon if running
        if pgrep -f "ammocoind.*$AMMOCOIN_TEST_DATA" > /dev/null; then
            echo "Stopping existing test node..."
            "$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" stop 2>/dev/null || true
            sleep 3
        fi
        rm -rf "$AMMOCOIN_TEST_DATA"
        echo -e "${GREEN}✓ Cleaned up old test data${NC}"
    else
        echo "Keeping existing data..."
    fi
fi

mkdir -p "$AMMOCOIN_TEST_DATA"
echo -e "${GREEN}✓ Test directory: $AMMOCOIN_TEST_DATA${NC}"
echo ""

# Step 4: Create configuration
echo -e "${BLUE}Step 4: Creating test configuration...${NC}"

RPC_PASS=$(openssl rand -hex 32)

cat > "$AMMOCOIN_TEST_DATA/ammocoin.conf" << EOF
# AMMOcoin v1.1.0 Local Test Node
# ISOLATED TEST - Not connected to network

server=1
daemon=1
listen=0
connect=0

# RPC
rpcuser=ammocointest
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=8332

# Logging
debug=1

# Staking
staking=1
EOF

chmod 600 "$AMMOCOIN_TEST_DATA/ammocoin.conf"

# Save credentials
CRED_FILE="$HOME/ammocoin-test-credentials.txt"
cat > "$CRED_FILE" << EOF
AMMOcoin v1.1.0 Local Test Node
================================
Data Directory: $AMMOCOIN_TEST_DATA
RPC User: ammocointest
RPC Password: $RPC_PASS
RPC Port: 8332
Created: $(date)

Quick Commands:
---------------
# Get info:
$AMMOCOIN_SRC/ammocoin-cli -datadir=$AMMOCOIN_TEST_DATA getinfo

# Generate blocks:
$AMMOCOIN_SRC/ammocoin-cli -datadir=$AMMOCOIN_TEST_DATA generate 10

# Stop node:
$AMMOCOIN_SRC/ammocoin-cli -datadir=$AMMOCOIN_TEST_DATA stop
EOF

chmod 600 "$CRED_FILE"
echo -e "${GREEN}✓ Configuration created${NC}"
echo -e "${GREEN}✓ Credentials saved to: $CRED_FILE${NC}"
echo ""

# Step 5: Start daemon
echo -e "${BLUE}Step 5: Starting test node...${NC}"

# Check if already running
if pgrep -f "ammocoind.*$AMMOCOIN_TEST_DATA" > /dev/null; then
    echo -e "${YELLOW}⚠ Test node already running!${NC}"
    read -p "Restart it? (y/n) " -n 1 -r
    echo ""
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        echo "Stopping..."
        "$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" stop
        sleep 3
    else
        echo "Skipping daemon start"
        exit 0
    fi
fi

"$AMMOCOIN_SRC/ammocoind" -datadir="$AMMOCOIN_TEST_DATA" -daemon

echo "Waiting for startup..."
sleep 10

# Verify it's running
if pgrep -f "ammocoind.*$AMMOCOIN_TEST_DATA" > /dev/null; then
    echo -e "${GREEN}✓ Daemon started successfully${NC}"
else
    echo -e "${RED}✗ Daemon failed to start${NC}"
    echo "Check logs: tail -50 $AMMOCOIN_TEST_DATA/debug.log"
    exit 1
fi
echo ""

# Step 6: Verify deployment
echo -e "${BLUE}Step 6: Verifying deployment...${NC}"

# Wait a bit more for RPC to be ready
sleep 5

# Get info
echo "Getting node info..."
if ! "$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getinfo > /dev/null 2>&1; then
    echo -e "${YELLOW}⚠ RPC not ready yet, waiting 10 more seconds...${NC}"
    sleep 10
fi

# Verify genesis block
echo "Verifying genesis block..."
GENESIS=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblockhash 0 2>/dev/null || echo "error")

EXPECTED_GENESIS="0000075a4b9573ee2b4401c0ae785fb451d8355c91b6ed7d7a3420fe590cad58"

if [ "$GENESIS" = "$EXPECTED_GENESIS" ]; then
    echo -e "${GREEN}✓ CORRECT GENESIS BLOCK (Path A)${NC}"
else
    echo -e "${RED}✗ WRONG GENESIS BLOCK!${NC}"
    echo "Expected: $EXPECTED_GENESIS"
    echo "Got: $GENESIS"
    exit 1
fi
echo ""

# Show status
echo -e "${BLUE}Node Status:${NC}"
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getinfo
echo ""

# Step 7: Optional block generation
echo -e "${BLUE}Step 7: Generate test blocks?${NC}"
read -p "Generate 10 test blocks now? (y/n) " -n 1 -r
echo ""
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo "Generating 10 blocks..."
    "$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" generate 10

    echo ""
    BALANCE=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getbalance)
    echo -e "${GREEN}✓ Balance: $BALANCE AMMO${NC}"

    BLOCKS=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblockcount)
    echo -e "${GREEN}✓ Block height: $BLOCKS${NC}"
fi
echo ""

# Final summary
echo "========================================"
echo -e "${GREEN}🎉 Test Node Running Successfully!${NC}"
echo "========================================"
echo ""
echo "Genesis Block: $GENESIS"
echo "Data Directory: $AMMOCOIN_TEST_DATA"
echo "Credentials: $CRED_FILE"
echo ""
echo -e "${YELLOW}Quick Commands:${NC}"
echo ""
echo "# Get node info:"
echo "$AMMOCOIN_SRC/ammocoin-cli -datadir=$AMMOCOIN_TEST_DATA getinfo"
echo ""
echo "# Generate blocks:"
echo "$AMMOCOIN_SRC/ammocoin-cli -datadir=$AMMOCOIN_TEST_DATA generate 100"
echo ""
echo "# Get balance:"
echo "$AMMOCOIN_SRC/ammocoin-cli -datadir=$AMMOCOIN_TEST_DATA getbalance"
echo ""
echo "# Watch logs:"
echo "tail -f $AMMOCOIN_TEST_DATA/debug.log"
echo ""
echo "# Stop node:"
echo "$AMMOCOIN_SRC/ammocoin-cli -datadir=$AMMOCOIN_TEST_DATA stop"
echo ""
echo "========================================"
echo -e "${GREEN}✅ Local test node is ready!${NC}"
echo "========================================"
