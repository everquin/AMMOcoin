# AMMOcoin v1.1.0 Network Launch Deployment

**Date:** December 28, 2025
**Status:** Ready for deployment
**Networks:** seed1.ammocoin.org, seed2.ammocoin.org (if available)

---

## 🎯 Deployment Overview

### Goals:
1. Deploy v1.1.0 to seed nodes
2. Start v1.1.0 network with fresh genesis block
3. Generate initial supply for distribution
4. Verify network is operational
5. Prepare for user connections

### Seed Nodes:
- **seed1.ammocoin.org** - IP: 48.141.194.140 (Vultr VM)
- **seed2.ammocoin.org** - IP: TBD (if available)

---

## ⚠️ PRE-DEPLOYMENT CHECKLIST

### ✅ Before You Begin:

1. **v1.0 Data Safety** (CRITICAL!)
   - [ ] Verify v1.0 wallets are backed up
   - [ ] Confirm v1.0 data is in `~/.ammocoin` or `/root/.ammocoin`
   - [ ] Never delete v1.0 data (needed for claims!)

2. **Binary Verification**
   - [ ] Confirm v1.1.0 binaries are compiled on seed1
   - [ ] Location: `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/`
   - [ ] OR: Download from GitHub Release

3. **Network Readiness**
   - [ ] DNS configured (seed1.ammocoin.org, seed2.ammocoin.org)
   - [ ] Firewall rules ready (port 37020 open)
   - [ ] SSH access verified

---

## 📋 DEPLOYMENT STEPS

### Option A: Use Pre-Compiled Binaries (Faster - 5 minutes)

**On seed1.ammocoin.org:**

```bash
# SSH into seed1
ssh root@48.141.194.140

# Download binaries from GitHub Release
cd /tmp
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Verify checksum
echo "917cd4365b352ad7800ba9dd2c388408cba0341ff6da1ba8aa33f84515e73acb  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz" | sha256sum -c

# Extract
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Install to /usr/local/bin (system-wide)
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx

# Verify installation
which ammocoind
ammocoind --version
# Should show: AMMOcoin Core Daemon version v1.1.0.0
```

---

### Option B: Use Already Compiled Binaries (If still on VM)

**If binaries are still at `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/`:**

```bash
# SSH into seed1
ssh root@48.141.194.140

# Install binaries system-wide
sudo install -m 0755 -o root -g root -t /usr/local/bin \
    /opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind \
    /opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-cli \
    /opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-tx

# Verify
which ammocoind
ammocoind --version
```

---

## 🔧 CONFIGURATION SETUP

### Step 1: Create v1.1.0 Data Directory

**CRITICAL: Use separate directory from v1.0!**

```bash
# Create v1.1.0 data directory
mkdir -p /root/.ammocoin-v1.1.0

# Verify v1.0 is still intact (if it exists)
ls -la /root/.ammocoin/wallet.dat 2>/dev/null && echo "✓ v1.0 wallet preserved"
```

---

### Step 2: Create Configuration File

```bash
# Generate secure RPC password
RPC_PASS=$(openssl rand -hex 32)

# Create v1.1.0 configuration
cat > /root/.ammocoin-v1.1.0/ammocoin.conf << EOF
# AMMOcoin v1.1.0 Seed Node Configuration
listen=1
server=1
daemon=1
dnsseed=1

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=8332

# Network
port=37020
maxconnections=250

# Seed Nodes (connect to other seed if available)
# addnode=seed2.ammocoin.org:37020

# Performance (adjust based on VM resources)
dbcache=1000
maxmempool=500

# Logging
debug=0
shrinkdebugfile=1

# Staking (enable for initial supply generation)
staking=1
EOF

# Secure the configuration
chmod 600 /root/.ammocoin-v1.1.0/ammocoin.conf

# Save RPC credentials
echo "Seed Node: seed1.ammocoin.org" > /root/ammocoin-v1.1.0-credentials.txt
echo "RPC Password: $RPC_PASS" >> /root/ammocoin-v1.1.0-credentials.txt
chmod 600 /root/ammocoin-v1.1.0-credentials.txt

echo "✓ Configuration created"
cat /root/ammocoin-v1.1.0-credentials.txt
```

---

### Step 3: Install zkSNARK Parameters

```bash
# Install Sapling parameters
mkdir -p /root/.ammocoin-params
cd /root/.ammocoin-params
wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
cd ~

echo "✓ zkSNARK parameters installed"
```

---

### Step 4: Configure Firewall

```bash
# Open P2P port
sudo ufw allow 37020/tcp comment 'AMMOcoin v1.1.0 P2P'

# Verify firewall status
sudo ufw status | grep 37020

echo "✓ Firewall configured"
```

---

## 🚀 START THE NETWORK

### Step 1: Start v1.1.0 Daemon

```bash
# Start the daemon with v1.1.0 data directory
ammocoind -datadir=/root/.ammocoin-v1.1.0 -daemon

# Wait for startup
sleep 10

# Check if it's running
ps aux | grep ammocoind | grep -v grep
```

---

### Step 2: Verify Daemon is Running

```bash
# Get node info
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getinfo

# Check blockchain info
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockchaininfo

# Verify genesis block (CRITICAL!)
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockhash 0
# Should show: 00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570
```

**Expected Output:**
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
  "keypoololdest": 1735430000,
  "keypoolsize": 1000,
  "paytxfee": 0.00000000,
  "relayfee": 0.00010000,
  "staking status": "Staking Active"
}
```

---

### Step 3: Monitor Initial Startup

```bash
# Watch the log file
tail -f /root/.ammocoin-v1.1.0/debug.log

# Press Ctrl+C to exit when you see successful startup
```

**Look for:**
```
AMMOcoin version v1.1.0.0 starting
Using data directory /root/.ammocoin-v1.1.0
Using config file /root/.ammocoin-v1.1.0/ammocoin.conf
init message: Loading block index...
init message: Verifying blocks...
genesis block hash: 00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570
init message: Loading wallet...
init message: Activating best chain...
init message: Done loading
```

---

## 💰 GENERATE INITIAL SUPPLY

### Step 1: Get a Wallet Address

```bash
# Generate new address for initial supply
SUPPLY_ADDRESS=$(ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getnewaddress "initial_supply")

echo "Initial Supply Address: $SUPPLY_ADDRESS"

# Save for distribution script
echo "$SUPPLY_ADDRESS" > /root/initial-supply-address.txt
```

---

### Step 2: Generate Blocks (Mine/Stake Initial Supply)

**Option A: Generate blocks manually (fast for initial launch)**

```bash
# Generate 100 blocks to create initial supply
# This will create ~100,000 AMMO (1000 AMMO per block initially)
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 generate 100

# Check balance
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getbalance

# Check blockchain height
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockcount
```

**Option B: Let staking generate blocks (slower, more realistic)**

```bash
# Enable staking and wait for natural block generation
# Staking is already enabled in config
# Monitor with:
watch -n 5 'ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getinfo | grep -E "blocks|balance|staking"'
```

---

### Step 3: Verify Initial Supply

```bash
# Check total supply
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getinfo | grep balance

# Check block height
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockcount

# List transactions
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 listtransactions

# Get detailed balance breakdown
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getwalletinfo
```

---

## 🌐 SET UP SYSTEMD SERVICE (Auto-Start)

### Create Service File

```bash
# Create systemd service for auto-start on reboot
sudo tee /etc/systemd/system/ammocoind-v1.1.0.service > /dev/null << EOF
[Unit]
Description=AMMOcoin v1.1.0 Daemon
After=network.target

[Service]
Type=forking
User=root
Group=root
ExecStart=/usr/local/bin/ammocoind -datadir=/root/.ammocoin-v1.1.0 -daemon
ExecStop=/usr/local/bin/ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 stop
Restart=on-failure
RestartSec=10
TimeoutStartSec=120
TimeoutStopSec=60

# Hardening
PrivateTmp=true
ProtectSystem=full
NoNewPrivileges=true
PrivateDevices=true

[Install]
WantedBy=multi-user.target
EOF

# Reload systemd
sudo systemctl daemon-reload

# Enable service
sudo systemctl enable ammocoind-v1.1.0

# Check status
sudo systemctl status ammocoind-v1.1.0
```

**Note:** The daemon is already running manually, so we don't start it via systemd yet. This is for auto-start on reboot.

---

## 🔍 VERIFICATION CHECKLIST

### Essential Checks:

```bash
# 1. Verify correct binary version
ammocoind --version | grep "v1.1.0"

# 2. Verify correct genesis block
GENESIS=$(ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockhash 0)
if [ "$GENESIS" = "00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570" ]; then
    echo "✓ Correct genesis block (Path A)"
else
    echo "✗ ERROR: Wrong genesis block!"
    echo "Got: $GENESIS"
fi

# 3. Verify daemon is running
ps aux | grep "ammocoind.*ammocoin-v1.1.0" | grep -v grep && echo "✓ Daemon running"

# 4. Verify data directory is separate
ls -la /root/.ammocoin/ 2>/dev/null && echo "✓ v1.0 data preserved"
ls -la /root/.ammocoin-v1.1.0/ && echo "✓ v1.1.0 data exists"

# 5. Verify network port is listening
sudo netstat -tulpn | grep 37020 && echo "✓ P2P port listening"

# 6. Check blockchain sync status
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockchaininfo | grep -E "blocks|headers"

# 7. Check peer connections (will be 0 initially)
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getconnectioncount
```

---

## 🔗 CONNECT SEED2 (If Available)

### On seed2.ammocoin.org:

```bash
# SSH to seed2
ssh root@<seed2-ip>

# Repeat all deployment steps above

# Then connect to seed1
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 addnode "seed1.ammocoin.org:37020" "add"

# Verify connection
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getpeerinfo
```

### On seed1, connect to seed2:

```bash
# Add seed2 as peer
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 addnode "seed2.ammocoin.org:37020" "add"

# Verify connection
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getconnectioncount
# Should show: 1 (if seed2 is online)
```

---

## 📊 NETWORK STATUS DASHBOARD

### Create monitoring script:

```bash
cat > /root/network-status.sh << 'EOF'
#!/bin/bash
echo "========================================"
echo "AMMOcoin v1.1.0 Network Status"
echo "========================================"
echo ""
echo "Node: seed1.ammocoin.org"
echo "Time: $(date)"
echo ""
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getinfo
echo ""
echo "Blockchain Info:"
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockchaininfo | grep -E "chain|blocks|headers|difficulty|moneysupply"
echo ""
echo "Network Info:"
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getnetworkinfo | grep -E "version|subversion|connections"
echo ""
echo "Peer Count:"
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getconnectioncount
echo ""
echo "Staking Info:"
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getstakinginfo
echo ""
echo "========================================"
EOF

chmod +x /root/network-status.sh

# Run it
./network-status.sh
```

---

## 🎯 POST-DEPLOYMENT TASKS

### 1. Document Network Status

```bash
# Save initial network state
./network-status.sh > /root/network-launch-$(date +%Y%m%d-%H%M%S).txt

# Save initial supply address
echo "Initial Supply Address: $(cat /root/initial-supply-address.txt)" >> /root/network-launch-info.txt
echo "Genesis Block: $(ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockhash 0)" >> /root/network-launch-info.txt
echo "Launch Time: $(date)" >> /root/network-launch-info.txt
```

---

### 2. Prepare for Distribution

```bash
# Check balance available for distribution
BALANCE=$(ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getbalance)
echo "Balance available: $BALANCE AMMO"

# Ensure enough supply for distribution
# Need: 232.4M AMMO total
# Top 61: 218.7M AMMO
# Migration fund: 13.7M AMMO

# If balance is sufficient, proceed to distribution
# If not, generate more blocks
```

---

### 3. Test RPC Access

```bash
# Test RPC is working
curl --user ammocoinrpc:$(grep rpcpassword /root/.ammocoin-v1.1.0/ammocoin.conf | cut -d= -f2) \
     --data-binary '{"jsonrpc":"1.0","id":"test","method":"getinfo","params":[]}' \
     -H 'content-type: text/plain;' \
     http://127.0.0.1:8332/

# Should return JSON with node info
```

---

## 🆘 TROUBLESHOOTING

### Daemon won't start:

```bash
# Check logs
tail -100 /root/.ammocoin-v1.1.0/debug.log

# Check permissions
ls -la /root/.ammocoin-v1.1.0/

# Check if another daemon is running
ps aux | grep ammocoind

# Check if port is available
sudo netstat -tulpn | grep 37020
```

---

### Wrong genesis block:

```bash
# Stop daemon
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 stop

# Check binary version
ammocoind --version

# Verify chainparams.cpp has correct genesis
strings /usr/local/bin/ammocoind | grep "00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570"

# If wrong, redownload or recompile binaries
```

---

### Can't generate blocks:

```bash
# Check if wallet is encrypted
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getwalletinfo | grep unlocked

# If encrypted, unlock wallet
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 walletpassphrase "yourpassword" 9999999

# Check staking status
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getstakinginfo
```

---

## ✅ SUCCESS CRITERIA

Network launch is successful when:

- [x] v1.1.0 daemon running on seed1
- [x] Correct genesis block verified (0x0000075a...)
- [x] v1.0 data preserved and untouched
- [x] P2P port 37020 listening
- [x] Initial blocks generated
- [x] Wallet has balance > 0
- [ ] seed2 connected (if available)
- [ ] Sufficient supply generated for distribution
- [ ] RPC accessible for distribution scripts
- [ ] Network stable for 30+ minutes

---

## 📞 NEXT STEPS AFTER LAUNCH

Once network is running:

1. **Generate sufficient supply**
   - Target: 232.4M AMMO minimum
   - Generate enough blocks to reach this amount

2. **Execute distribution**
   - Run `distribute-to-top-holders.py` for top 61
   - Fund migration fund address for claims

3. **Announce to users**
   - Share GitHub release links
   - Provide seed node addresses
   - Open migration claims window

4. **Monitor network**
   - Watch for user connections
   - Monitor block production
   - Track distribution progress

---

**Deployment Guide Version:** 1.0
**Last Updated:** December 28, 2025
**Network:** AMMOcoin v1.1.0 Mainnet (Path A)

