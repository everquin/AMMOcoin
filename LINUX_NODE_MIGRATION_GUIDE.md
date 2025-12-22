# AMMOcoin v1.1.0 - Complete Linux Node Migration Guide

**Target:** Existing Linux node running AMMOcoin v1.0
**Goal:** Migrate to AMMOcoin v1.1.0
**Time Required:** 60-90 minutes (including build time)

---

## ⚠️ CRITICAL: READ THIS FIRST

This is a **complete network replacement**. v1.0 and v1.1.0 are **incompatible**.

- Your v1.0 balance will NOT automatically transfer
- You MUST follow the migration process to claim your funds
- **BACKUP YOUR WALLET FIRST** (cannot be stressed enough!)
- Migration window: 90 days from launch

---

## 🔍 Ubuntu 18.04 Users - READ THIS!

**If you are running Ubuntu 18.04.6 LTS**, please see the dedicated guide:
**`UBUNTU_18.04_MIGRATION_NOTES.md`**

Ubuntu 18.04 requires additional steps:
- Installing newer dependencies (libnatpmp, Rust, possibly GCC 9)
- Special build configuration flags
- Performance tuning for older systems

**Recommendation:** Upgrade to Ubuntu 20.04 or 22.04 LTS before migrating for easier setup.

If you're on Ubuntu 20.04 or 22.04, continue with this guide below.

---

## STEP 1: BACKUP YOUR v1.0 WALLET (CRITICAL!)

```bash
# 1. Check if v1.0 daemon is running
ps aux | grep ammocoind

# 2. Find your v1.0 data directory
ls -la ~/.ammocoin/

# 3. CREATE BACKUP (DO NOT SKIP!)
mkdir -p ~/ammocoin-backups
cp ~/.ammocoin/wallet.dat ~/ammocoin-backups/wallet-v1.0-$(date +%Y%m%d-%H%M%S).dat

# 4. Also backup configuration
cp ~/.ammocoin/ammocoin.conf ~/ammocoin-backups/ammocoin-v1.0.conf 2>/dev/null || echo "No config file found"
cp ~/.ammocoin/masternode.conf ~/ammocoin-backups/masternode-v1.0.conf 2>/dev/null || echo "No masternode config found"

# 5. VERIFY BACKUP EXISTS
ls -lh ~/ammocoin-backups/
```

**CRITICAL:** Copy this backup to an external location (USB drive, cloud, etc.)

```bash
# If you have external storage mounted at /mnt/backup
cp ~/ammocoin-backups/* /mnt/backup/
```

---

## STEP 2: STOP v1.0 DAEMON

```bash
# Try graceful shutdown
ammocoin-cli stop 2>/dev/null || echo "CLI not responding"

# Wait 30 seconds
sleep 30

# Verify it stopped
ps aux | grep ammocoind

# If still running, force kill
pkill ammocoind
sleep 10
ps aux | grep ammocoind  # Should show nothing
```

---

## STEP 3: CHECK YOUR v1.0 BALANCE (IMPORTANT!)

Before proceeding, you need to know your v1.0 address and balance for migration.

```bash
# If you stopped the daemon, start it temporarily
ammocoind -daemon
sleep 15

# Check your balance
ammocoin-cli getbalance

# List all your addresses with balances
ammocoin-cli listaddressgroupings

# Save this information!
ammocoin-cli listaddressgroupings > ~/ammocoin-backups/v1.0-addresses-$(date +%Y%m%d).txt

# Stop it again
ammocoin-cli stop
sleep 10
```

**Write down your main v1.0 address and balance - you'll need this!**

---

## STEP 4: PREPARE YOUR SYSTEM FOR v1.1.0 BUILD

```bash
# Update system
sudo apt update
sudo apt upgrade -y

# Install build dependencies
sudo apt install -y build-essential autoconf autoconf-archive automake \
    libtool pkg-config git curl wget

# Install required libraries
sudo apt install -y libssl-dev libboost-all-dev libdb-dev libdb++-dev \
    libevent-dev libzmq3-dev libminiupnpc-dev libnatpmp-dev \
    libgmp-dev libsodium-dev python3 python3-pip

# Install Rust (required for Sapling features)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env

# Verify Rust installed
rustc --version
cargo --version
```

---

## STEP 5: DOWNLOAD AND BUILD AMMOCOIN v1.1.0

```bash
# Navigate to home directory
cd ~

# Clone the repository (or download source archive)
git clone https://github.com/ammocoin/ammocoin.git ammocoin-v1.1.0
cd ammocoin-v1.1.0

# If git clone doesn't work, you can extract from source archive:
# tar -xzf ammocoin-v1.1.0-source.tar.gz
# cd ammocoin-v1.1.0

# Generate build scripts
./autogen.sh

# Configure the build
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    --with-boost \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

# Build (this takes 20-60 minutes depending on your CPU)
# Adjust -j based on CPU cores: -j2 for 2 cores, -j4 for 4 cores, etc.
make -j$(nproc)
```

**Note:** Build will take 20-60 minutes. If it fails with memory errors:
```bash
make clean
make -j1  # Single-threaded build (slower but more stable)
```

---

## STEP 6: INSTALL v1.1.0 BINARIES

```bash
# Create local bin directory
mkdir -p ~/ammocoin-bin

# Copy binaries
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx ~/ammocoin-bin/

# Update PATH
echo 'export PATH="$HOME/ammocoin-bin:$PATH"' >> ~/.bashrc
source ~/.bashrc

# Verify installation
ammocoind --version
# Expected: AMMOcoin Core Daemon version v1.1.0.0-xxxxxxx
```

---

## STEP 7: PREPARE v1.1.0 DATA DIRECTORY

```bash
# Rename old v1.0 directory (keeps it safe)
mv ~/.ammocoin ~/.ammocoin-v1.0

# Create new v1.1.0 directory
mkdir -p ~/.ammocoin

# Copy your v1.0 wallet to v1.1.0
cp ~/.ammocoin-v1.0/wallet.dat ~/.ammocoin/

# Create v1.1.0 configuration file
cat > ~/.ammocoin/ammocoin.conf << 'EOF'
# AMMOcoin v1.1.0 Configuration

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=CHANGE_THIS_TO_RANDOM_PASSWORD
rpcallowip=127.0.0.1

# Network
listen=1
server=1
daemon=1

# Seed nodes (will be provided at launch)
# addnode=seed1.ammocoin.org
# addnode=seed2.ammocoin.org
# addnode=seed3.ammocoin.org
EOF

# Generate random RPC password
RPCPASS=$(openssl rand -base64 32)
sed -i "s/CHANGE_THIS_TO_RANDOM_PASSWORD/$RPCPASS/" ~/.ammocoin/ammocoin.conf

echo "Configuration created with RPC password: $RPCPASS"
echo "Save this password if you need it: $RPCPASS" > ~/ammocoin-backups/v1.1.0-rpc-password.txt
```

---

## STEP 8: START AMMOCOIN v1.1.0

```bash
# Start the v1.1.0 daemon
ammocoind -daemon

# Wait for startup (20-30 seconds on Linux)
sleep 20

# Check status
ammocoin-cli getinfo

# You should see v1.1.0 version and it starting to sync
```

---

## STEP 9: VERIFY YOUR v1.0 BALANCE IN v1.1.0 WALLET

```bash
# Check if your v1.0 balance shows
ammocoin-cli getbalance

# List addresses
ammocoin-cli listaddressgroupings

# Check sync status
ammocoin-cli getblockchaininfo
```

**IMPORTANT:** The balance you see is from your v1.0 wallet. This does NOT mean you have those coins on the v1.1.0 network! You must complete the migration claim process.

---

## STEP 10: GENERATE NEW v1.1.0 ADDRESS FOR MIGRATION

```bash
# Create new v1.1.0 receiving address
NEW_ADDRESS=$(ammocoin-cli getnewaddress "Migrated from v1.0")
echo "Your NEW v1.1.0 address: $NEW_ADDRESS"

# SAVE THIS ADDRESS!
echo $NEW_ADDRESS > ~/ammocoin-backups/v1.1.0-address.txt
cat ~/ammocoin-backups/v1.1.0-address.txt
```

---

## STEP 11: PROVE OWNERSHIP OF v1.0 ADDRESS (CRYPTOGRAPHIC SIGNATURE)

```bash
# Replace with YOUR v1.0 address from Step 3
V10_ADDRESS="YOUR_V1.0_ADDRESS_HERE"

# Sign a message proving you own this address
SIGNATURE=$(ammocoin-cli signmessage "$V10_ADDRESS" "I am migrating to AMMOcoin v1.1.0")

# Display your migration claim information
echo "================================"
echo "Migration Claim Information"
echo "================================"
echo "v1.0 Address: $V10_ADDRESS"
echo "Message: I am migrating to AMMOcoin v1.1.0"
echo "Signature: $SIGNATURE"
echo "v1.1.0 Address: $NEW_ADDRESS"
echo "================================"

# Save this to a file
cat > ~/ammocoin-backups/migration-claim.txt << EOF
AMMOcoin v1.0 to v1.1.0 Migration Claim

v1.0 Address: $V10_ADDRESS
Message: I am migrating to AMMOcoin v1.1.0
Signature: $SIGNATURE
v1.1.0 Address: $NEW_ADDRESS
Date: $(date)
Server: $(hostname)
EOF

# Display the file
cat ~/ammocoin-backups/migration-claim.txt
```

---

## STEP 12: SUBMIT YOUR MIGRATION CLAIM

**Option A: Via Web Form** (Easiest if available)

1. Open browser and go to: https://ammocoin.org/migrate
2. Fill in the information from `~/ammocoin-backups/migration-claim.txt`
3. Submit

**Option B: Via Email**

```bash
# Send email (if mail is configured)
cat ~/ammocoin-backups/migration-claim.txt | mail -s "Migration Claim - $V10_ADDRESS" support@ammocoin.org
```

Or manually:
1. Email to: support@ammocoin.org
2. Subject: `Migration Claim - [YOUR_V1.0_ADDRESS]`
3. Body: Paste contents of `~/ammocoin-backups/migration-claim.txt`

---

## STEP 13: WAIT FOR MIGRATION PROCESSING

Migration claims are processed within 24-48 hours.

**Monitor your balance:**

```bash
# Check balance every 30 seconds (press Ctrl+C to stop)
watch -n 30 'ammocoin-cli getbalance'

# Or check manually
ammocoin-cli getbalance
```

When your migration is processed, you'll see your balance appear in the v1.1.0 wallet!

---

## STEP 14: SET UP AUTO-START (OPTIONAL)

Make the v1.1.0 daemon start automatically on boot:

```bash
# Create systemd service
sudo tee /etc/systemd/system/ammocoind.service > /dev/null << EOF
[Unit]
Description=AMMOcoin v1.1.0 Daemon
After=network.target

[Service]
Type=forking
User=$USER
Group=$USER
ExecStart=$HOME/ammocoin-bin/ammocoind -daemon -conf=$HOME/.ammocoin/ammocoin.conf -datadir=$HOME/.ammocoin
ExecStop=$HOME/ammocoin-bin/ammocoin-cli -conf=$HOME/.ammocoin/ammocoin.conf -datadir=$HOME/.ammocoin stop
Restart=on-failure
RestartSec=30

[Install]
WantedBy=multi-user.target
EOF

# Enable and start service
sudo systemctl daemon-reload
sudo systemctl enable ammocoind
sudo systemctl start ammocoind

# Check status
sudo systemctl status ammocoind

# View logs
journalctl -u ammocoind -f
```

---

## DAILY USAGE COMMANDS

```bash
# Check daemon status
ammocoin-cli getinfo

# Check balance
ammocoin-cli getbalance

# Get blockchain sync status
ammocoin-cli getblockchaininfo

# Send AMMO to an address
ammocoin-cli sendtoaddress "RECIPIENT_ADDRESS" AMOUNT

# Get new receiving address
ammocoin-cli getnewaddress "Label"

# List recent transactions
ammocoin-cli listtransactions

# Backup wallet
ammocoin-cli backupwallet "$HOME/ammocoin-backups/wallet-backup-$(date +%Y%m%d).dat"

# Stop daemon
ammocoin-cli stop

# Start daemon (if not using systemd)
ammocoind -daemon
```

---

## TROUBLESHOOTING

### Build Failed

**Error: "configure: error: libdb_cxx headers missing"**
```bash
sudo apt install -y libdb++-dev
```

**Error: "Rust compiler not found"**
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env
```

**Error: "virtual memory exhausted" (on low-memory systems)**
```bash
# Use single-threaded build
make clean
make -j1
```

### Runtime Issues

**"Cannot obtain a lock on data directory"**
```bash
# Another instance is running
ammocoin-cli stop
sleep 10
ammocoind -daemon
```

**"Connection refused" when using ammocoin-cli**
```bash
# Daemon not running
ps aux | grep ammocoind

# Start it
ammocoind -daemon
sleep 15
ammocoin-cli getinfo
```

**No network connections**
```bash
# Check peer count
ammocoin-cli getconnectioncount

# Add seed nodes manually (once they're provided)
ammocoin-cli addnode "seed1.ammocoin.org" "add"
ammocoin-cli addnode "seed2.ammocoin.org" "add"
ammocoin-cli addnode "seed3.ammocoin.org" "add"

# Check peers
ammocoin-cli getpeerinfo
```

**Signature verification failed in migration claim**
```bash
# Verify signature yourself
ammocoin-cli verifymessage "YOUR_V1.0_ADDRESS" "SIGNATURE" "I am migrating to AMMOcoin v1.1.0"
# Should return: true

# If false, re-sign:
SIGNATURE=$(ammocoin-cli signmessage "YOUR_V1.0_ADDRESS" "I am migrating to AMMOcoin v1.1.0")
```

---

## VERIFICATION CHECKLIST

After completing migration, verify:

- [ ] v1.1.0 daemon is running: `ps aux | grep ammocoind`
- [ ] Version is correct: `ammocoin-cli getinfo | grep version`
- [ ] Wallet is loaded: `ammocoin-cli getwalletinfo`
- [ ] Network is syncing: `ammocoin-cli getblockchaininfo`
- [ ] Peers connected: `ammocoin-cli getconnectioncount`
- [ ] v1.0 wallet backed up: `ls ~/ammocoin-backups/`
- [ ] Migration claim submitted
- [ ] Monitoring for claim processing

---

## EMERGENCY ROLLBACK (IF NEEDED)

If you need to go back to v1.0 temporarily:

```bash
# Stop v1.1.0
ammocoin-cli stop
sleep 10

# Restore v1.0
mv ~/.ammocoin ~/.ammocoin-v1.1.0-backup
mv ~/.ammocoin-v1.0 ~/.ammocoin

# Start old v1.0 daemon (if you still have it)
/path/to/old/ammocoind -daemon
```

**Note:** This only works during the migration period. After v1.0 network is shut down, rollback is not possible.

---

## SUPPORT

- **Email:** support@ammocoin.org
- **Documentation:** https://docs.ammocoin.org
- **GitHub Issues:** https://github.com/ammocoin/ammocoin/issues
- **Forum:** https://forum.ammocoin.org

---

## QUICK REFERENCE - COPY/PASTE FULL MIGRATION

For experienced users, here's the entire migration in one script:

```bash
#!/bin/bash
set -e

echo "=== AMMOcoin v1.1.0 Migration Script ==="
echo "Starting migration process..."

# Backup
echo "Step 1: Backing up v1.0 wallet..."
mkdir -p ~/ammocoin-backups
cp ~/.ammocoin/wallet.dat ~/ammocoin-backups/wallet-v1.0-$(date +%Y%m%d-%H%M%S).dat

# Stop v1.0
echo "Step 2: Stopping v1.0 daemon..."
ammocoin-cli stop 2>/dev/null || true
sleep 30
pkill ammocoind || true
sleep 10

# Install dependencies
echo "Step 3: Installing dependencies..."
sudo apt update
sudo apt install -y build-essential autoconf autoconf-archive automake \
    libtool pkg-config git curl wget libssl-dev libboost-all-dev \
    libdb-dev libdb++-dev libevent-dev libzmq3-dev libminiupnpc-dev \
    libnatpmp-dev libgmp-dev libsodium-dev python3 python3-pip

# Install Rust
if ! command -v cargo &> /dev/null; then
    echo "Installing Rust..."
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
    source $HOME/.cargo/env
fi

# Build v1.1.0
echo "Step 4: Building AMMOcoin v1.1.0 (this takes 20-60 minutes)..."
cd ~
git clone https://github.com/ammocoin/ammocoin.git ammocoin-v1.1.0
cd ammocoin-v1.1.0
./autogen.sh
./configure --disable-tests --disable-bench --without-gui --enable-wallet --with-incompatible-bdb
make -j$(nproc)

# Install binaries
echo "Step 5: Installing binaries..."
mkdir -p ~/ammocoin-bin
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx ~/ammocoin-bin/
echo 'export PATH="$HOME/ammocoin-bin:$PATH"' >> ~/.bashrc
source ~/.bashrc

# Prepare data directory
echo "Step 6: Setting up v1.1.0 data directory..."
mv ~/.ammocoin ~/.ammocoin-v1.0
mkdir -p ~/.ammocoin
cp ~/.ammocoin-v1.0/wallet.dat ~/.ammocoin/

# Create config
RPCPASS=$(openssl rand -base64 32)
cat > ~/.ammocoin/ammocoin.conf << EOF
rpcuser=ammocoinrpc
rpcpassword=$RPCPASS
rpcallowip=127.0.0.1
listen=1
server=1
daemon=1
EOF

# Start v1.1.0
echo "Step 7: Starting AMMOcoin v1.1.0..."
ammocoind -daemon
sleep 20

echo "=== Migration Complete ==="
echo ""
echo "Next steps:"
echo "1. Check status: ammocoin-cli getinfo"
echo "2. Generate new address: ammocoin-cli getnewaddress"
echo "3. Sign migration claim with your v1.0 address"
echo "4. Submit claim to support@ammocoin.org"
echo ""
echo "RPC Password saved to: ~/ammocoin-backups/v1.1.0-rpc-password.txt"
echo $RPCPASS > ~/ammocoin-backups/v1.1.0-rpc-password.txt
```

**Save this as `migrate_to_v1.1.0.sh` and run:**
```bash
chmod +x migrate_to_v1.1.0.sh
./migrate_to_v1.1.0.sh
```

---

**Migration Deadline:** 90 days from network launch
**Current Network:** v1.1.0
**Status:** Active

---

*Last Updated: December 22, 2025*
