# seed1.ammocoin.org - Complete Rebuild Instructions

**Target:** seed1.ammocoin.org (Vultr VPS)
**Objective:** Clean build and deployment of v1.1.0 with CORRECT genesis
**Critical:** This node will be the first peer - MUST have correct genesis!

---

## ⚠️ CRITICAL WARNING

The current node on seed1.ammocoin.org has **WRONG genesis block** and must be:
1. Completely stopped
2. All old data deleted
3. Fresh build from v1.1.0 tag
4. Genesis verification BEFORE starting

**DO NOT skip any step!**

---

## Phase 1: Pre-Build Preparation

### Step 1: SSH to Server
```bash
ssh root@seed1.ammocoin.org
```

### Step 2: Stop Old Node (If Running)
```bash
# Try to stop gracefully
ammocoin-cli stop 2>/dev/null

# Wait for shutdown
sleep 10

# Force kill if still running
pkill -9 ammocoind

# Verify stopped
ps aux | grep ammocoind | grep -v grep
# Should return nothing
```

### Step 3: Backup Old Installation (For Safety)
```bash
# Create backup directory with timestamp
BACKUP_DIR="$HOME/ammocoin-old-$(date +%Y%m%d-%H%M%S)"
mkdir -p "$BACKUP_DIR"

# Backup data directory
if [ -d "$HOME/.ammocoin" ]; then
    mv "$HOME/.ammocoin" "$BACKUP_DIR/data"
fi

# Backup old binaries
if [ -f "/usr/local/bin/ammocoind" ]; then
    cp /usr/local/bin/ammocoind "$BACKUP_DIR/ammocoind-old"
    cp /usr/local/bin/ammocoin-cli "$BACKUP_DIR/ammocoin-cli-old"
fi

echo "Backup created in: $BACKUP_DIR"
ls -lh "$BACKUP_DIR"
```

### Step 4: Clean System
```bash
# Remove old binaries
sudo rm -f /usr/local/bin/ammocoind
sudo rm -f /usr/local/bin/ammocoin-cli
sudo rm -f /usr/local/bin/ammocoin-tx

# Remove any old source directories
rm -rf /tmp/AMMOcoin* /tmp/ammocoin*

# Verify removed
which ammocoind
# Should return: ammocoind not found
```

---

## Phase 2: Install Build Dependencies

### Step 1: Update System
```bash
sudo apt-get update
sudo apt-get upgrade -y
```

### Step 2: Install Build Tools
```bash
sudo apt-get install -y \
    build-essential \
    libtool \
    autotools-dev \
    automake \
    pkg-config \
    libssl-dev \
    libevent-dev \
    bsdmainutils \
    python3 \
    libboost-all-dev \
    libminiupnpc-dev \
    libzmq3-dev \
    libgmp-dev \
    git \
    curl \
    cargo \
    rustc
```

### Step 3: Install Berkeley DB 4.8
```bash
cd /tmp

# Download
wget https://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz

# Extract
tar -xzf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix

# Configure and build
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local

# Compile (this takes 5-10 minutes)
make -j$(nproc)

# Install
sudo make install

# Verify
ls -l /usr/local/lib/libdb*
```

### Step 4: Install/Update Rust
```bash
# Check current Rust version
rustc --version

# If not installed or too old (<1.80.0):
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env

# Install specific version
rustup install 1.92.0
rustup default 1.92.0

# Verify
rustc --version
# Should show: rustc 1.92.0 or newer
```

---

## Phase 3: Clone and Build from Source

### Step 1: Clone Repository
```bash
cd /tmp
git clone https://github.com/everquin/AMMOcoin.git
cd AMMOcoin
```

### Step 2: Checkout Correct Tag
```bash
# CRITICAL: Use the exact tag
git checkout v1.1.0

# Verify you're on the right tag
git describe --tags
# Should show: v1.1.0

# Show current commit
git log -1 --oneline
```

### Step 3: Navigate to Build Directory
```bash
cd source
pwd
# Should show: /tmp/AMMOcoin/source
```

### Step 4: Generate Configure Script
```bash
./autogen.sh
```

**Expected output:**
```
libtoolize: putting auxiliary files in AC_CONFIG_AUX_DIR, 'build-aux'.
...
configure.ac:XX: installing 'build-aux/install-sh'
```

### Step 5: Configure Build
```bash
./configure \
    --prefix=/usr/local \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --with-incompatible-bdb \
    LDFLAGS="-L/usr/local/lib" \
    CPPFLAGS="-I/usr/local/include"
```

**Watch for errors!** Configuration should complete with:
```
Options used to compile and link:
  with wallet   = yes
  with gui / qt = no
  ...
```

### Step 6: Build (This Takes 15-30 Minutes)
```bash
# Use all CPU cores
make -j$(nproc)
```

**Watch for:**
- Rust compilation progress
- C++ compilation progress
- No errors in output

**When complete, you should see:**
```
make[1]: Leaving directory '.../source'
```

### Step 7: Verify Build Success
```bash
ls -lh src/ammocoind src/ammocoin-cli src/ammocoin-tx
```

**Expected output:**
```
-rwxr-xr-x 1 root root 15M Dec 30 XX:XX src/ammocoind
-rwxr-xr-x 1 root root 2.1M Dec 30 XX:XX src/ammocoin-cli
-rwxr-xr-x 1 root root 1.9M Dec 30 XX:XX src/ammocoin-tx
```

---

## Phase 4: CRITICAL - Genesis Verification

### Step 1: Verify Genesis in Binary (Static Check)
```bash
strings src/ammocoind | grep "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
```

**MUST return 2-3 matches showing:**
```
000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
assert(consensus.hashGenesisBlock == uint256S("0x000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"));
```

**❌ If NO matches found:** DO NOT PROCEED! Source code is wrong!

### Step 2: Check for Old Genesis (Should Find NOTHING)
```bash
strings src/ammocoind | grep -E "000001c4|0000075a"
```

**MUST return NOTHING!**

**❌ If old genesis found:** DO NOT PROCEED! You're building from wrong source!

### Step 3: Runtime Genesis Test
```bash
# Create test directory
mkdir -p /tmp/ammocoin-test
cat > /tmp/ammocoin-test/ammocoin.conf <<EOF
rpcuser=test
rpcpassword=test123
rpcport=51473
server=1
daemon=1
EOF

# Start daemon
./src/ammocoind -datadir=/tmp/ammocoin-test -daemon

# Wait for startup
sleep 10

# Get genesis hash
GENESIS=$(./src/ammocoin-cli -datadir=/tmp/ammocoin-test getblockhash 0)

# Stop daemon
./src/ammocoin-cli -datadir=/tmp/ammocoin-test stop
sleep 5

# Clean up test data
rm -rf /tmp/ammocoin-test

# Verify genesis
echo "Genesis hash from node: $GENESIS"
echo "Expected genesis hash:  000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"

if [ "$GENESIS" = "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2" ]; then
    echo "✅ SUCCESS: Genesis verification PASSED!"
    echo "Safe to proceed with installation."
else
    echo "❌ CRITICAL ERROR: Genesis verification FAILED!"
    echo "DO NOT INSTALL these binaries!"
    exit 1
fi
```

**ONLY proceed if verification passed!**

---

## Phase 5: Install Verified Binaries

### Step 1: Strip Debug Symbols (Reduce Size)
```bash
strip src/ammocoind src/ammocoin-cli src/ammocoin-tx

# Check new sizes
ls -lh src/ammocoind src/ammocoin-cli src/ammocoin-tx
```

### Step 2: Install to System
```bash
sudo cp src/ammocoind src/ammocoin-cli src/ammocoin-tx /usr/local/bin/
sudo chmod +x /usr/local/bin/ammocoin*

# Verify installation
which ammocoind
# Should show: /usr/local/bin/ammocoind

ammocoind --version
```

### Step 3: Final Binary Verification
```bash
# Verify installed binary has correct genesis
strings /usr/local/bin/ammocoind | grep "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
# MUST return matches!
```

---

## Phase 6: Configure Production Node

### Step 1: Create Fresh Data Directory
```bash
mkdir -p ~/.ammocoin
chmod 700 ~/.ammocoin
```

### Step 2: Create Configuration File
```bash
cat > ~/.ammocoin/ammocoin.conf <<'EOF'
# AMMOcoin v1.1.0 Production Configuration
# seed1.ammocoin.org

# Server Settings
server=1
daemon=1
listen=1

# RPC Settings (CHANGE THESE!)
rpcuser=ammouser
rpcpassword=CHANGE_THIS_PASSWORD_NOW
rpcport=51473
rpcallowip=127.0.0.1
rpcbind=127.0.0.1

# Network Settings
port=37020
maxconnections=125

# This is a seed node
dnsseed=1

# Logging
debug=0
shrinkdebugfile=1
printtoconsole=0

# Genesis Block (reference - embedded in binary)
# Hash: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
EOF

# Secure the config file
chmod 600 ~/.ammocoin/ammocoin.conf
```

### Step 3: CHANGE RPC PASSWORD!
```bash
nano ~/.ammocoin/ammocoin.conf
# Change rpcpassword to a strong random password
# Save: Ctrl+O, Enter, Ctrl+X
```

### Step 4: Verify Configuration
```bash
cat ~/.ammocoin/ammocoin.conf | grep -E "rpcuser|rpcpassword|port"
# Ensure password is NOT "CHANGE_THIS_PASSWORD_NOW"
```

---

## Phase 7: Start Production Node

### Step 1: Open Firewall Port
```bash
# Allow P2P port
sudo ufw allow 37020/tcp

# Verify
sudo ufw status | grep 37020
```

### Step 2: Start Node
```bash
ammocoind -daemon
```

**Expected output:**
```
AMMOcoin server starting
```

### Step 3: Wait for Startup
```bash
sleep 15
```

### Step 4: Verify Genesis (CRITICAL!)
```bash
ammocoin-cli getblockhash 0
```

**MUST return:**
```
000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

**❌ If different:** STOP IMMEDIATELY! Investigate!

### Step 5: Check Blockchain Info
```bash
ammocoin-cli getblockchaininfo
```

**Expected output:**
```json
{
  "chain": "main",
  "blocks": 0,
  "headers": 0,
  "bestblockhash": "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2",
  "difficulty": 0.000244140625,
  ...
}
```

### Step 6: Check Network Status
```bash
ammocoin-cli getnetworkinfo
```

**Verify:**
- `"connections"` shows network is active
- `"localservices"` shows correct services
- `"version"` shows v1.1.0

### Step 7: Monitor Logs
```bash
tail -50 ~/.ammocoin/debug.log
```

**Look for:**
- No errors
- No genesis assertion failures
- Clean startup messages
- Listening on port 37020

---

## Phase 8: Ongoing Monitoring

### Step 1: Create Monitoring Script
```bash
cat > ~/monitor-node.sh <<'MONITOR_SCRIPT'
#!/bin/bash

echo "========================================="
echo "AMMOcoin v1.1.0 Node Status"
echo "Date: $(date)"
echo "========================================="
echo ""

echo "1. GENESIS VERIFICATION:"
GENESIS=$(ammocoin-cli getblockhash 0 2>/dev/null)
EXPECTED="000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"

if [ "$GENESIS" = "$EXPECTED" ]; then
    echo "   ✅ Genesis: $GENESIS (CORRECT)"
else
    echo "   ❌ Genesis: $GENESIS (WRONG!)"
    echo "   Expected:  $EXPECTED"
fi
echo ""

echo "2. BLOCKCHAIN INFO:"
ammocoin-cli getblockchaininfo 2>/dev/null | grep -E "blocks|bestblockhash|difficulty|verificationprogress"
echo ""

echo "3. NETWORK INFO:"
ammocoin-cli getnetworkinfo 2>/dev/null | grep -E "version|subversion|connections|localservices"
echo ""

echo "4. PEER INFO:"
PEERS=$(ammocoin-cli getpeerinfo 2>/dev/null | grep -c "addr")
echo "   Connected Peers: $PEERS"
if [ "$PEERS" -gt 0 ]; then
    ammocoin-cli getpeerinfo 2>/dev/null | grep -E "addr|version" | head -10
fi
echo ""

echo "5. RECENT LOG ENTRIES:"
tail -10 ~/.ammocoin/debug.log | grep -v "UpdateTip"
echo ""

echo "========================================="
MONITOR_SCRIPT

chmod +x ~/monitor-node.sh
```

### Step 2: Run Monitoring
```bash
# Run once
~/monitor-node.sh

# Or run continuously (Ctrl+C to stop)
watch -n 60 ~/monitor-node.sh
```

### Step 3: Set Up Systemd Service (Optional but Recommended)
```bash
sudo cat > /etc/systemd/system/ammocoind.service <<'SYSTEMD_SERVICE'
[Unit]
Description=AMMOcoin Daemon
After=network.target

[Service]
Type=forking
User=root
ExecStart=/usr/local/bin/ammocoind -daemon -conf=/root/.ammocoin/ammocoin.conf -datadir=/root/.ammocoin
ExecStop=/usr/local/bin/ammocoin-cli stop
Restart=on-failure
RestartSec=10

[Install]
WantedBy=multi-user.target
SYSTEMD_SERVICE

# Enable and start
sudo systemctl daemon-reload
sudo systemctl enable ammocoind.service
sudo systemctl start ammocoind.service

# Check status
sudo systemctl status ammocoind.service
```

---

## Phase 9: Final Verification Checklist

Run through this checklist before announcing node is ready:

```bash
# 1. Genesis hash correct?
ammocoin-cli getblockhash 0
# Expected: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2

# 2. Node is running?
ps aux | grep ammocoind | grep -v grep

# 3. Port is listening?
sudo netstat -tulpn | grep 37020

# 4. RPC is working?
ammocoin-cli getblockchaininfo | grep blocks

# 5. No errors in log?
tail -100 ~/.ammocoin/debug.log | grep -i error

# 6. DNS resolves correctly?
dig seed1.ammocoin.org
# Should return server's public IP

# 7. External connectivity?
# From another machine:
# telnet seed1.ammocoin.org 37020
# Should connect
```

### Checklist:
- [ ] Genesis hash is 000000593...
- [ ] Node is running without errors
- [ ] Port 37020 is listening
- [ ] RPC responds to commands
- [ ] No errors in debug.log
- [ ] DNS resolves correctly
- [ ] External connections work
- [ ] Monitoring script runs
- [ ] Systemd service enabled (if configured)

---

## Troubleshooting

### Build Failed During Configuration
```bash
# Check config.log for details
cat config.log | tail -100

# Common fix: Install missing dependencies
sudo apt-get install -y libboost-all-dev libssl-dev libevent-dev
```

### Build Failed During Make
```bash
# Check for specific error
# Usually Rust or C++ compilation issues

# For Rust errors:
rustup update
rustup default 1.92.0
make clean
make -j$(nproc)
```

### Node Won't Start
```bash
# Check debug log
cat ~/.ammocoin/debug.log

# Check if port is already in use
sudo netstat -tulpn | grep 37020

# Try starting in foreground for debugging
ammocoind -printtoconsole
```

### Wrong Genesis After All
```bash
# This is CRITICAL - do not proceed
# Verify source:
cd /tmp/AMMOcoin
git log -1 --oneline
git describe --tags

# Should show v1.1.0
# If not, you checked out wrong tag!
```

---

## Emergency Rollback (If Needed)

If something goes wrong and you need to go back:

```bash
# Stop new node
ammocoin-cli stop
sleep 5

# Restore old binaries
sudo cp "$BACKUP_DIR/ammocoind-old" /usr/local/bin/ammocoind
sudo cp "$BACKUP_DIR/ammocoin-cli-old" /usr/local/bin/ammocoin-cli
sudo chmod +x /usr/local/bin/ammocoin*

# Restore old data
rm -rf ~/.ammocoin
cp -r "$BACKUP_DIR/data" ~/.ammocoin

# Start old node
ammocoind -daemon
```

**Note:** Only use if new build fails completely!

---

## After Successful Deployment

### 1. Announce to Community
```
✅ seed1.ammocoin.org is now live with v1.1.0!

Genesis: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
P2P Port: 37020

Connect your v1.1.0 nodes:
- Download: https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0
- Add seed node: ammocoin-cli addnode "seed1.ammocoin.org:37020" "add"

Remember to delete old blockchain data before connecting!
```

### 2. Monitor Continuously
- Check every hour for first 24 hours
- Watch for peer connections
- Monitor for any errors
- Verify all connecting nodes have correct genesis

### 3. Update Documentation
- Mark seed node as "LIVE" in documentation
- Update network status
- Provide connection instructions to users

---

## Critical Commands Reference

### Genesis Verification
```bash
ammocoin-cli getblockhash 0
# MUST return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

### Check Node Status
```bash
ammocoin-cli getblockchaininfo
ammocoin-cli getnetworkinfo
ammocoin-cli getpeerinfo
```

### View Logs
```bash
tail -f ~/.ammocoin/debug.log
```

### Restart Node
```bash
ammocoin-cli stop
sleep 5
ammocoind -daemon
```

---

## Contact for Issues

If you encounter problems:
1. Check troubleshooting section above
2. Review debug.log for errors
3. Verify genesis hash multiple times
4. Check repository documentation

**DO NOT start the node publicly if genesis verification fails!**

---

**Last Updated:** December 30, 2025
**Status:** Ready for Execution on seed1.ammocoin.org
**Estimated Time:** 45-90 minutes total
