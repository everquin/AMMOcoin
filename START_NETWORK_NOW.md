# START NETWORK NOW - Quick Reference

**Ready to launch AMMOcoin v1.1.0 network on seed1.ammocoin.org**

---

## 🚀 FASTEST METHOD (5 Minutes)

### On seed1.ammocoin.org (48.141.194.140):

**Option 1: Run Automated Deployment Script**

```bash
# SSH into seed1
ssh root@48.141.194.140

# Clone/update repository
cd ~
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git || (cd AMMOcoin-v1.1.0 && git pull)
cd AMMOcoin-v1.1.0

# Run deployment script
bash scripts/deploy-and-start-network.sh
```

This script will:
- ✅ Check for v1.0 data (preserves it safely)
- ✅ Verify v1.1.0 binaries are installed
- ✅ Create v1.1.0 data directory
- ✅ Generate secure configuration
- ✅ Install zkSNARK parameters
- ✅ Configure firewall
- ✅ Start v1.1.0 daemon
- ✅ Verify genesis block
- ✅ Generate initial supply address
- ✅ Optionally generate 100 blocks

---

## 📋 MANUAL METHOD (If You Prefer Step-by-Step)

### Step 1: Install Binaries (if not already done)

```bash
# Use already compiled binaries
sudo install -m 0755 -o root -g root -t /usr/local/bin \
    /opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind \
    /opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-cli \
    /opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-tx

# Verify
ammocoind --version
```

### Step 2: Create Configuration

```bash
# Create v1.1.0 data directory
mkdir -p /root/.ammocoin-v1.1.0

# Generate RPC password
RPC_PASS=$(openssl rand -hex 32)

# Create config
cat > /root/.ammocoin-v1.1.0/ammocoin.conf << EOF
listen=1
server=1
daemon=1
dnsseed=1
rpcuser=ammocoinrpc
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=8332
port=37020
maxconnections=250
dbcache=1000
maxmempool=500
staking=1
EOF

chmod 600 /root/.ammocoin-v1.1.0/ammocoin.conf

# Save credentials
echo "RPC Password: $RPC_PASS" > /root/ammocoin-rpc-password.txt
```

### Step 3: Install zkSNARK Parameters

```bash
mkdir -p /root/.ammocoin-params
cd /root/.ammocoin-params
wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
cd ~
```

### Step 4: Start Daemon

```bash
# Start v1.1.0
ammocoind -datadir=/root/.ammocoin-v1.1.0 -daemon

# Wait for startup
sleep 10

# Check status
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getinfo

# Verify genesis block
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockhash 0
# Should be: 000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329
```

### Step 5: Generate Initial Supply

```bash
# Get address for initial supply
SUPPLY_ADDRESS=$(ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getnewaddress "initial_supply")
echo "$SUPPLY_ADDRESS" > /root/initial-supply-address.txt

# Generate 100 blocks
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 generate 100

# Check balance
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getbalance
```

---

## ✅ VERIFICATION COMMANDS

After deployment, verify everything is working:

```bash
# 1. Check daemon is running
ps aux | grep "ammocoind.*ammocoin-v1.1.0" | grep -v grep

# 2. Verify genesis block
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockhash 0

# 3. Check blockchain status
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getblockchaininfo

# 4. Check balance
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getbalance

# 5. Check staking status
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getstakinginfo

# 6. View recent logs
tail -50 /root/.ammocoin-v1.1.0/debug.log
```

---

## 🎯 WHAT YOU NEED FOR DISTRIBUTION

Total required supply: **232.4M AMMO**

- Top 61 holders: 218.7M AMMO
- Migration fund: 13.7M AMMO

### Generate Sufficient Supply:

```bash
# Check current balance
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getbalance

# Generate more blocks if needed
# Each block rewards ~1000 AMMO initially
# Need ~232,400 blocks for full supply
# Generate in batches:

ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 generate 1000
# Repeat as needed

# Or let it stake naturally over time
```

---

## 📊 MONITORING

### Watch Network Status:

```bash
# Real-time monitoring
watch -n 5 'ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getinfo'

# Or create status script:
cat > /root/network-status.sh << 'EOF'
#!/bin/bash
echo "=== AMMOcoin v1.1.0 Status ==="
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getinfo
echo ""
echo "=== Staking Info ==="
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getstakinginfo
EOF

chmod +x /root/network-status.sh
./network-status.sh
```

---

## 🔧 USEFUL COMMANDS

```bash
# Stop daemon
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 stop

# Restart daemon
ammocoind -datadir=/root/.ammocoin-v1.1.0 -daemon

# Get new address
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 getnewaddress

# Send AMMO
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 sendtoaddress "address" amount

# List transactions
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 listtransactions

# Get transaction details
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 gettransaction "txid"

# Backup wallet
ammocoin-cli -datadir=/root/.ammocoin-v1.1.0 backupwallet "/root/wallet-backup.dat"
```

---

## 🆘 TROUBLESHOOTING

### Daemon won't start:

```bash
# Check logs
tail -100 /root/.ammocoin-v1.1.0/debug.log

# Check if port is in use
sudo netstat -tulpn | grep 37020

# Kill old processes
pkill -f ammocoind
```

### Wrong genesis block:

```bash
# Verify binary
strings /usr/local/bin/ammocoind | grep "000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329"

# If wrong, reinstall binaries from GitHub Release
```

---

## 📞 NEXT STEPS AFTER NETWORK IS RUNNING

1. **Generate sufficient supply** (~232.4M AMMO)
2. **Run distribution script** for top 61 holders
3. **Fund migration fund** for claims
4. **Announce to users** network is live
5. **Deploy seed2** (if available)
6. **Monitor network** health

---

## ⚠️ CRITICAL REMINDERS

- ✅ v1.0 data at `/root/.ammocoin` is PRESERVED (never deleted)
- ✅ v1.1.0 uses SEPARATE directory `/root/.ammocoin-v1.1.0`
- ✅ Genesis block MUST be `0x0000075a...` (Path A)
- ✅ Save RPC credentials securely
- ✅ Backup wallet regularly

---

**Ready to launch?** Run the deployment script and your network will be live in 5 minutes!

```bash
ssh root@48.141.194.140
cd ~/AMMOcoin-v1.1.0
bash scripts/deploy-and-start-network.sh
```

