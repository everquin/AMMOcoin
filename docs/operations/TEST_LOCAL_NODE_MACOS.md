# Test AMMOcoin v1.1.0 Locally on macOS

**Quick guide to run and test v1.1.0 on your Mac (Apple Silicon)**

---

## 🎯 What We'll Do

1. Create a test data directory (separate from any existing installations)
2. Set up test configuration
3. Start a local test node
4. Verify it's running correctly with Path A genesis block
5. Test basic RPC commands

**Time:** 5 minutes
**Location:** Local Mac (not connected to production network yet)

---

## 📦 Binary Location

Your macOS ARM64 binaries are at:
```
/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin/src/
├── ammocoind
├── ammocoin-cli
└── ammocoin-tx
```

**Verified:**
- Architecture: ARM64 (Apple Silicon)
- Version: v1.1.0.0-f89ff1e
- Type: Mach-O 64-bit executable

---

## 🚀 QUICK START (Copy-Paste Commands)

### Step 1: Set Up Paths

Open Terminal and run:

```bash
# Set convenient aliases for this session
export AMMOCOIN_SRC="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin/src"
export AMMOCOIN_TEST_DATA="$HOME/.ammocoin-v1.1.0-test"

# Verify binaries exist
ls -lh "$AMMOCOIN_SRC/ammocoind"
ls -lh "$AMMOCOIN_SRC/ammocoin-cli"
```

---

### Step 2: Install zkSNARK Parameters (If Not Already Done)

```bash
# Check if already installed
if [ -f "$HOME/.ammocoin-params/sapling-spend.params" ]; then
    echo "✓ zkSNARK parameters already installed"
else
    echo "Installing zkSNARK parameters..."
    mkdir -p "$HOME/.ammocoin-params"
    cd "$HOME/.ammocoin-params"

    echo "Downloading sapling-spend.params (48 MB)..."
    curl -O https://download.z.cash/downloads/sapling-spend.params

    echo "Downloading sapling-output.params (3.6 MB)..."
    curl -O https://download.z.cash/downloads/sapling-output.params

    echo "✓ Parameters installed"
    cd ~
fi
```

---

### Step 3: Create Test Configuration

```bash
# Create test data directory
mkdir -p "$AMMOCOIN_TEST_DATA"

# Generate random RPC password
RPC_PASS=$(openssl rand -hex 32)

# Create test configuration
cat > "$AMMOCOIN_TEST_DATA/ammocoin.conf" << EOF
# AMMOcoin v1.1.0 Local Test Node
# This is for TESTING ONLY - isolated from production network

# Server settings
server=1
daemon=1
listen=0
connect=0

# RPC Settings
rpcuser=ammocointest
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=8332

# Network (disabled - local test only)
# port=37020

# Logging
debug=1

# Staking (enabled for testing)
staking=1
EOF

chmod 600 "$AMMOCOIN_TEST_DATA/ammocoin.conf"

# Save credentials
echo "Test Node RPC Password: $RPC_PASS" > "$HOME/ammocoin-test-credentials.txt"
chmod 600 "$HOME/ammocoin-test-credentials.txt"

echo "✓ Test configuration created at: $AMMOCOIN_TEST_DATA"
echo "✓ Credentials saved to: $HOME/ammocoin-test-credentials.txt"
```

---

### Step 4: Start Test Node

```bash
# Start the daemon
"$AMMOCOIN_SRC/ammocoind" -datadir="$AMMOCOIN_TEST_DATA" -daemon

echo "Waiting for startup (10 seconds)..."
sleep 10

# Check if it's running
ps aux | grep ammocoind | grep -v grep

echo "✓ Test node started"
```

---

### Step 5: Verify Node is Running

```bash
# Get basic info
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getinfo

# Verify correct genesis block (CRITICAL!)
GENESIS=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblockhash 0)
echo ""
echo "Genesis Block: $GENESIS"

# Check if it matches Path A
if [ "$GENESIS" = "00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570" ]; then
    echo "✅ CORRECT GENESIS BLOCK (Path A)"
else
    echo "❌ WRONG GENESIS BLOCK!"
fi
```

**Expected output:**
```json
{
  "version": 1010000,
  "protocolversion": 70016,
  "walletversion": 61000,
  "balance": 0.00000000,
  "blocks": 0,
  "timeoffset": 0,
  "connections": 0,
  "proxy": "",
  "difficulty": 0.0002441371325370145,
  "testnet": false,
  "moneysupply": 1000.00000000,
  ...
}
```

---

### Step 6: Test Basic Commands

```bash
# Get blockchain info
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblockchaininfo

# Get new address
TEST_ADDR=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getnewaddress "test")
echo "Test Address: $TEST_ADDR"

# Generate a few test blocks
echo "Generating 10 test blocks..."
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" generate 10

# Check balance
BALANCE=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getbalance)
echo "Balance: $BALANCE AMMO"

# List transactions
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" listtransactions "" 5
```

---

### Step 7: Monitor Logs

```bash
# Watch the debug log
tail -f "$AMMOCOIN_TEST_DATA/debug.log"

# Press Ctrl+C to exit when done
```

---

## 🔧 Useful Test Commands

### Node Status:

```bash
# Quick status check
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getinfo

# Detailed blockchain info
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblockchaininfo

# Wallet info
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getwalletinfo

# Staking info
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getstakinginfo
```

---

### Block Generation:

```bash
# Generate blocks (for testing supply generation)
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" generate 100

# Check current block height
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblockcount

# Get specific block
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblock $("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getblockhash 1)
```

---

### Wallet Operations:

```bash
# Get new address
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getnewaddress

# Get balance
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getbalance

# Send AMMO (after generating blocks)
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" sendtoaddress "address" 10.0

# List all transactions
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" listtransactions

# Backup wallet
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" backupwallet "$HOME/test-wallet-backup.dat"
```

---

## 🛑 Stop Test Node

```bash
# Graceful shutdown
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" stop

# Wait for clean shutdown
sleep 5

# Verify it's stopped
ps aux | grep ammocoind | grep -v grep || echo "✓ Daemon stopped"
```

---

## 🧹 Clean Up Test Data (Optional)

```bash
# If you want to start fresh
rm -rf "$AMMOCOIN_TEST_DATA"
rm -f "$HOME/ammocoin-test-credentials.txt"

echo "✓ Test data cleaned up"
```

---

## 🔍 What to Verify

### ✅ Success Criteria:

1. **Binary runs:** `ammocoind --version` shows v1.1.0
2. **Daemon starts:** Process appears in `ps aux | grep ammocoind`
3. **RPC works:** `ammocoin-cli getinfo` returns JSON
4. **Correct genesis:** Block 0 hash is `0x0000075a...`
5. **Can generate blocks:** `generate 10` creates 10 blocks
6. **Balance increases:** After generating blocks, balance > 0
7. **Wallet works:** Can create addresses, send transactions

---

## 📊 Test Scenarios

### Scenario 1: Test Block Generation Speed

```bash
# Time how long it takes to generate 100 blocks
time "$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" generate 100
```

---

### Scenario 2: Test Supply Generation

```bash
# Generate significant supply
for i in {1..10}; do
    echo "Batch $i: Generating 1000 blocks..."
    "$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" generate 1000
    BALANCE=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getbalance)
    echo "Current balance: $BALANCE AMMO"
done
```

---

### Scenario 3: Test Transaction Creation

```bash
# Generate supply first
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" generate 100

# Create two addresses
ADDR1=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getnewaddress "test1")
ADDR2=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getnewaddress "test2")

# Send transaction
TXID=$("$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" sendtoaddress "$ADDR2" 100.0)
echo "Transaction ID: $TXID"

# Get transaction details
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" gettransaction "$TXID"

# Generate a block to confirm
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" generate 1

# Check transaction confirmations
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" gettransaction "$TXID" | grep confirmations
```

---

## 🆘 Troubleshooting

### Daemon won't start:

```bash
# Check logs
tail -50 "$AMMOCOIN_TEST_DATA/debug.log"

# Check if port is in use
lsof -i :8332

# Kill any stuck processes
pkill -f ammocoind
```

---

### Wrong genesis block:

```bash
# Check what's in the binary
strings "$AMMOCOIN_SRC/ammocoind" | grep "0000075a"

# If wrong, you may need to rebuild from the correct source
```

---

### RPC connection refused:

```bash
# Check if daemon is running
ps aux | grep ammocoind

# Check config file
cat "$AMMOCOIN_TEST_DATA/ammocoin.conf"

# Try with explicit RPC credentials
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" -rpcuser=ammocointest -rpcpassword=YOUR_PASSWORD getinfo
```

---

## 📁 File Locations

```
Local Test Setup:
├── Binaries: /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin/src/
├── Test Data: ~/.ammocoin-v1.1.0-test/
├── Parameters: ~/.ammocoin-params/
├── Credentials: ~/ammocoin-test-credentials.txt
└── Config: ~/.ammocoin-v1.1.0-test/ammocoin.conf
```

**NOTE:** This is completely separate from:
- Production data (when you run production node)
- Any existing v1.0 installation
- The seed node deployment

---

## ✅ Next Steps After Testing

Once you've verified the macOS binaries work:

1. **Test complete?** Binaries are confirmed working ✓
2. **Deploy to seed node** (Linux binaries on Vultr VM)
3. **Connect local Mac to seed node** (optional)
4. **Run production node locally** (if desired)

---

## 🔗 Connect to Seed Node (After Seed is Deployed)

To connect your local test node to the production seed:

```bash
# Edit config to enable networking
cat >> "$AMMOCOIN_TEST_DATA/ammocoin.conf" << EOF

# Connect to production seed
listen=1
connect=1
addnode=seed1.ammocoin.org:37020
EOF

# Restart daemon
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" stop
sleep 5
"$AMMOCOIN_SRC/ammocoind" -datadir="$AMMOCOIN_TEST_DATA" -daemon

# Check connections
"$AMMOCOIN_SRC/ammocoin-cli" -datadir="$AMMOCOIN_TEST_DATA" getpeerinfo
```

---

**Ready to test?** Copy-paste the commands starting from Step 1!

