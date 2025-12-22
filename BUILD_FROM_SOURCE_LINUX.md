# AMMOcoin v1.1.0 - Build from Source on Linux

**Platform:** Ubuntu 20.04/22.04, Debian 11+, or similar
**Build Time:** 20-40 minutes
**Difficulty:** Intermediate

---

## Prerequisites

Update your system:

```bash
sudo apt update
sudo apt upgrade -y
```

---

## Install Build Dependencies

```bash
# Install base build tools
sudo apt install -y build-essential autoconf autoconf-archive automake \
    libtool pkg-config git curl wget

# Install required libraries
sudo apt install -y libssl-dev libboost-all-dev libdb-dev libdb++-dev \
    libevent-dev libzmq3-dev libminiupnpc-dev libnatpmp-dev \
    libgmp-dev libsodium-dev python3 python3-pip

# Install Rust (required for Sapling support)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env

# Verify installation
rustc --version
cargo --version
```

---

## Download and Build AMMOcoin v1.1.0

### Step 1: Clone the Repository

```bash
cd ~
git clone https://github.com/ammocoin/ammocoin.git ammocoin-v1.1.0
cd ammocoin-v1.1.0
```

**Or if you have a source archive:**

```bash
cd ~
tar -xzf ammocoin-v1.1.0-source.tar.gz
cd ammocoin-v1.1.0
```

### Step 2: Build AMMOcoin

```bash
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

# Compile (adjust -j based on CPU cores)
make -j$(nproc)
```

**Build takes approximately:**
- 2-core CPU: 40-60 minutes
- 4-core CPU: 20-30 minutes
- 8-core CPU: 10-15 minutes

**If you encounter errors during build**, try:
```bash
make clean
make -j1  # Single-threaded build (slower but more stable)
```

### Step 3: Install Binaries

**Option A: System-wide installation**
```bash
sudo make install
```

**Option B: Local installation** (Recommended)
```bash
mkdir -p ~/ammocoin-bin
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx ~/ammocoin-bin/

# Add to PATH
echo 'export PATH="$HOME/ammocoin-bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

---

## Verify Installation

```bash
ammocoind --version
```

Expected output:
```
AMMOcoin Core Daemon version v1.1.0.0-xxxxxxx
```

---

## Migration from v1.0 to v1.1.0

### IMPORTANT: Backup First!

**Before starting migration:**

```bash
# Locate your v1.0 data directory
ls -la ~/.ammocoin/

# Backup your wallet
cp ~/.ammocoin/wallet.dat ~/ammocoin-v1.0-wallet-backup.dat

# Also backup configuration
cp ~/.ammocoin/ammocoin.conf ~/ammocoin-v1.0-config-backup.conf 2>/dev/null || true
cp ~/.ammocoin/masternode.conf ~/ammocoin-v1.0-masternode-backup.conf 2>/dev/null || true

# Verify backup
ls -lh ~/*backup*
```

**Store backup on external media or encrypted location!**

---

### Migration Process

#### Step 1: Stop v1.0 Daemon (if running)

```bash
# If you have v1.0 installed
ammocoin-cli stop

# Or kill the process
pkill ammocoind

# Wait for shutdown
sleep 5
```

#### Step 2: Prepare v1.1.0 Data Directory

```bash
# Rename old directory (keeps v1.0 data safe)
mv ~/.ammocoin ~/.ammocoin-v1.0

# Create new v1.1.0 directory
mkdir -p ~/.ammocoin

# Copy wallet from v1.0
cp ~/.ammocoin-v1.0/wallet.dat ~/.ammocoin/

# Copy configuration (optional)
cp ~/.ammocoin-v1.0/ammocoin.conf ~/.ammocoin/ 2>/dev/null || true
```

#### Step 3: Create Configuration File

```bash
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

# Add seed nodes (will be provided at launch)
# addnode=seed1.ammocoin.org
# addnode=seed2.ammocoin.org
# addnode=seed3.ammocoin.org
EOF

# Generate random RPC password
RPCPASS=$(openssl rand -base64 32)
sed -i "s/CHANGE_THIS_TO_RANDOM_PASSWORD/$RPCPASS/" ~/.ammocoin/ammocoin.conf
```

#### Step 4: Start AMMOcoin v1.1.0

```bash
# Start the daemon
ammocoind -daemon

# Wait for startup
sleep 10

# Check status
ammocoin-cli getinfo
```

#### Step 5: Verify Your v1.0 Balance

```bash
# Check balance from v1.0 wallet
ammocoin-cli getbalance

# List all addresses with balances
ammocoin-cli listaddressgroupings
```

**IMPORTANT:** This shows your v1.0 balance. On the v1.1.0 network, you need to claim it from the migration fund.

#### Step 6: Generate v1.1.0 Address

```bash
# Create new receiving address for v1.1.0
NEW_ADDRESS=$(ammocoin-cli getnewaddress "Migrated Wallet")
echo "Your new v1.1.0 address: $NEW_ADDRESS"

# Save it
echo $NEW_ADDRESS > ~/v1.1.0-address.txt
```

#### Step 7: Prove Ownership of v1.0 Address

```bash
# Get your v1.0 address (replace with your actual address)
V10_ADDRESS="YOUR_V1.0_ADDRESS_HERE"

# Sign a message proving ownership
SIGNATURE=$(ammocoin-cli signmessage "$V10_ADDRESS" "I am migrating to AMMOcoin v1.1.0")

echo "v1.0 Address: $V10_ADDRESS"
echo "Signature: $SIGNATURE"
echo "v1.1.0 Address: $NEW_ADDRESS"

# Save claim information
cat > ~/migration-claim.txt << EOF
v1.0 Address: $V10_ADDRESS
Message: I am migrating to AMMOcoin v1.1.0
Signature: $SIGNATURE
v1.1.0 Address: $NEW_ADDRESS
Date: $(date)
EOF

cat ~/migration-claim.txt
```

#### Step 8: Submit Migration Claim

**Option A: Via Web Form** (Easiest)

1. Go to: https://ammocoin.org/migrate
2. Enter your v1.0 address
3. Enter the message: `I am migrating to AMMOcoin v1.1.0`
4. Enter your signature (from above)
5. Enter your NEW v1.1.0 address
6. Submit

**Option B: Via Email**

```bash
# Email the claim file
cat ~/migration-claim.txt | mail -s "Migration Claim - $V10_ADDRESS" support@ammocoin.org
```

Or manually send email to: support@ammocoin.org

Subject: `Migration Claim - [YOUR_V1.0_ADDRESS]`

Attach or paste contents of `~/migration-claim.txt`

#### Step 9: Wait for Confirmation

Migration claims are processed within 24-48 hours. Check your balance:

```bash
# Check balance periodically
watch -n 30 'ammocoin-cli getbalance'
```

---

## Running AMMOcoin v1.1.0 Daily

### Start the Daemon

```bash
ammocoind -daemon
```

### Common Commands

```bash
# Check status
ammocoin-cli getinfo

# Check balance
ammocoin-cli getbalance

# Get blockchain info
ammocoin-cli getblockchaininfo

# Send AMMO
ammocoin-cli sendtoaddress "RECIPIENT_ADDRESS" AMOUNT

# Get new receiving address
ammocoin-cli getnewaddress

# List transactions
ammocoin-cli listtransactions

# Backup wallet
ammocoin-cli backupwallet "$HOME/wallet-backup-$(date +%Y%m%d).dat"

# Stop daemon
ammocoin-cli stop
```

### Auto-start on Boot (Optional)

Create a systemd service:

```bash
sudo tee /etc/systemd/system/ammocoind.service > /dev/null << EOF
[Unit]
Description=AMMOcoin v1.1.0 Daemon
After=network.target

[Service]
Type=forking
User=$USER
Group=$USER
ExecStart=$(which ammocoind) -daemon -conf=$HOME/.ammocoin/ammocoin.conf -datadir=$HOME/.ammocoin
ExecStop=$(which ammocoin-cli) -conf=$HOME/.ammocoin/ammocoin.conf -datadir=$HOME/.ammocoin stop
Restart=on-failure
RestartSec=30

[Install]
WantedBy=multi-user.target
EOF

# Enable and start
sudo systemctl daemon-reload
sudo systemctl enable ammocoind
sudo systemctl start ammocoind

# Check status
sudo systemctl status ammocoind

# View logs
journalctl -u ammocoind -f
```

---

## Building a GUI Wallet (Optional)

If you want a graphical interface:

```bash
# Install Qt5 dependencies
sudo apt install -y qtbase5-dev qttools5-dev qttools5-dev-tools \
    libqrencode-dev libprotobuf-dev protobuf-compiler

# Rebuild with GUI
cd ~/ammocoin-v1.1.0
make clean
./configure --enable-wallet --with-gui
make -j$(nproc)

# Install
sudo make install

# Or copy locally
cp src/qt/ammocoin-qt ~/ammocoin-bin/
```

Run the GUI wallet:
```bash
ammocoin-qt &
```

---

## Troubleshooting

### Build Errors

**Error: "configure: error: libdb_cxx headers missing"**
```bash
sudo apt install -y libdb++-dev
```

**Error: "Rust compiler not found"**
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env
./configure ...  # Re-run configure
make
```

**Error: "Berkeley DB version 4.8 not found"**

This is normal. The build will use the system's DB version:
```bash
./configure --with-incompatible-bdb ...
```

**Error: "cargo build failed" or Rust compilation errors**

The Sapling/Rust components may have compatibility issues. Try:
```bash
make clean
./configure --disable-tests --disable-bench --without-gui --enable-wallet
make -j1  # Single-threaded
```

### Runtime Errors

**Error: "Cannot obtain a lock on data directory"**

Another instance is running:
```bash
ammocoin-cli stop
# Wait 10 seconds
sleep 10
ammocoind -daemon
```

**Error: "Error loading wallet.dat"**

Restore from backup:
```bash
ammocoin-cli stop
cp ~/ammocoin-v1.0-wallet-backup.dat ~/.ammocoin/wallet.dat
ammocoind -daemon
```

**Error: "Connection refused" when using ammocoin-cli**

Daemon not running or wrong RPC credentials:
```bash
# Check if running
ps aux | grep ammocoind

# Check config
cat ~/.ammocoin/ammocoin.conf

# Restart daemon
ammocoin-cli stop
ammocoind -daemon
```

### Network Issues

**No connections to peers:**

```bash
# Check peer count
ammocoin-cli getconnectioncount

# Add seed nodes manually
ammocoin-cli addnode "seed1.ammocoin.org" "add"
ammocoin-cli addnode "seed2.ammocoin.org" "add"
ammocoin-cli addnode "seed3.ammocoin.org" "add"

# Check peers
ammocoin-cli getpeerinfo
```

---

## Performance Tuning

### Increase Database Cache

Add to `~/.ammocoin/ammocoin.conf`:
```
dbcache=2048  # MB of RAM for database cache
maxmempool=300  # MB for transaction mempool
```

### Optimize for VPS/Server

```
# Reduce memory usage
dbcache=512
maxconnections=40

# Disable wallet if running as network node only
disablewallet=1
```

---

## Masternode Setup

If you're running a masternode, additional configuration is needed:

```bash
# Generate masternode key
ammocoin-cli masternode genkey

# Add to ammocoin.conf
cat >> ~/.ammocoin/ammocoin.conf << EOF

# Masternode Configuration
masternode=1
masternodeprivkey=YOUR_MASTERNODE_KEY_HERE
externalip=YOUR_SERVER_IP:37020
EOF

# Restart
ammocoin-cli stop
sleep 5
ammocoind -daemon
```

See full masternode guide: https://docs.ammocoin.org/masternodes

---

## Support

- Email: support@ammocoin.org
- Documentation: https://docs.ammocoin.org
- GitHub Issues: https://github.com/ammocoin/ammocoin/issues
- Community Forum: https://forum.ammocoin.org

---

**Migration Deadline:** 90 days from network launch
**Current Network:** v1.1.0
**Status:** Active

---

## Quick Reference

```bash
# Daily Commands
ammocoind -daemon                              # Start
ammocoin-cli getinfo                          # Status
ammocoin-cli getbalance                       # Balance
ammocoin-cli sendtoaddress "addr" amount      # Send
ammocoin-cli stop                             # Stop

# Maintenance
ammocoin-cli backupwallet ~/backup.dat        # Backup
journalctl -u ammocoind -f                    # Logs (if systemd)
tail -f ~/.ammocoin/debug.log                 # Logs (manual)

# Troubleshooting
ps aux | grep ammocoind                        # Check if running
ammocoin-cli getpeerinfo | grep addr           # Check connections
ammocoin-cli getblockchaininfo                # Sync status
```
