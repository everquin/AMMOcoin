# AMMOcoin Seed Node Quick Start Guide

**For:** seed1.ammocoin.org
**Date:** December 28, 2025
**Platform:** Ubuntu 20.04/22.04/24.04 LTS on Vultr

---

## ⚠️ CRITICAL: Existing v1.0 Node Operators

**If you have an existing AMMOcoin v1.0 installation with wallet balances:**

🔴 **STOP! Read this first:** `V1.0_TO_V1.1.0_NODE_MIGRATION.md`

v1.1.0 is a **completely new blockchain**. Your v1.0 wallet contains private keys needed to claim v1.1.0 balances. The automated setup script will:
- ✅ Detect existing v1.0 installation
- ✅ Automatically backup v1.0 wallet and data
- ✅ Create separate v1.1.0 data directory
- ✅ Preserve v1.0 data untouched

**For fresh installs (no existing v1.0):** Continue below.

---

## Method 1: Automated Setup (Recommended)

### On your Vultr Ubuntu VM:

```bash
# 1. Clone the repository
git clone https://github.com/everquin/AMMOcoin.git
cd AMMOcoin

# 2. Run the setup script
sudo bash scripts/setup-seed-node.sh
```

**Time:** 15-25 minutes (automated)

**What it does:**
- Updates system
- Installs all dependencies
- Compiles AMMOcoin binaries
- Installs zkSNARK parameters
- Creates configuration
- Sets up systemd service
- Configures firewall

---

## Method 2: Manual Step-by-Step

### Step 1: Update System
```bash
sudo apt-get update
sudo apt-get upgrade -y
```

### Step 2: Install Dependencies
```bash
sudo apt-get install -y \
    build-essential libtool autotools-dev automake \
    pkg-config libssl-dev libevent-dev bsdmainutils \
    python3 libboost-all-dev libminiupnpc-dev libzmq3-dev \
    libqrencode-dev libgmp-dev libsodium-dev cargo rustc \
    git wget curl unzip autoconf-archive
```

### Step 3: Install BerkeleyDB 4.8
```bash
cd /tmp
wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
tar -xzf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local
make -j$(nproc)
sudo make install
```

**Note:** If you encounter `__atomic_compare_exchange` errors on modern Ubuntu with GCC 9+, you need to apply the atomic.h patch. See `V1.0_TO_V1.1.0_NODE_MIGRATION.md` for details. The automated setup script (Method 1) includes this patch automatically.

### Step 4: Clone Repository
```bash
cd ~
git clone https://github.com/everquin/AMMOcoin.git ammocoin
cd ammocoin/source
```

### Step 5: Build AMMOcoin
```bash
./autogen.sh

./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --with-incompatible-bdb \
    LDFLAGS="-L/usr/local/lib/" \
    CPPFLAGS="-I/usr/local/include/"

make -j$(nproc)
sudo make install
```

### Step 6: Verify Installation
```bash
which ammocoind
ammocoind --version
```

Should show: `AMMOcoin Core Daemon version v1.1.0.0`

### Step 7: Install zkSNARK Parameters
```bash
mkdir -p ~/.ammocoin-params
cd ~/.ammocoin-params

wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
```

### Step 8: Create Configuration
```bash
mkdir -p ~/.ammocoin

cat > ~/.ammocoin/ammocoin.conf << 'EOF'
# AMMOcoin Seed Node Configuration
listen=1
server=1
daemon=1
dnsseed=1

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=CHANGE_THIS_TO_SECURE_PASSWORD
rpcallowip=127.0.0.1
rpcport=51473

# Network
port=37020
maxconnections=125

# Performance
dbcache=450
maxmempool=300
EOF

chmod 600 ~/.ammocoin/ammocoin.conf
```

**IMPORTANT:** Change the `rpcpassword` to a strong random password!

### Step 9: Configure Firewall
```bash
sudo ufw allow 37020/tcp comment 'AMMOcoin P2P'
sudo ufw enable
```

### Step 10: Start the Node
```bash
ammocoind -daemon
```

### Step 11: Verify Node is Running
```bash
ammocoin-cli getinfo
tail -f ~/.ammocoin/debug.log
```

---

## Setting Up Systemd Service (Auto-start)

Create service file:
```bash
sudo nano /etc/systemd/system/ammocoind.service
```

Paste this content:
```ini
[Unit]
Description=AMMOcoin Daemon
After=network.target

[Service]
Type=forking
User=YOUR_USERNAME
Group=YOUR_USERNAME
ExecStart=/usr/local/bin/ammocoind -daemon
ExecStop=/usr/local/bin/ammocoin-cli stop
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
```

**Replace `YOUR_USERNAME` with your actual username!**

Enable and start:
```bash
sudo systemctl daemon-reload
sudo systemctl enable ammocoind
sudo systemctl start ammocoind
sudo systemctl status ammocoind
```

---

## Useful Commands

### Check Node Status
```bash
ammocoin-cli getinfo
ammocoin-cli getblockchaininfo
ammocoin-cli getpeerinfo
ammocoin-cli getnetworkinfo
```

### Monitor Logs
```bash
tail -f ~/.ammocoin/debug.log
```

### Check Connections
```bash
ammocoin-cli getconnectioncount
```

### Stop Node
```bash
ammocoin-cli stop
# OR
sudo systemctl stop ammocoind
```

### Restart Node
```bash
sudo systemctl restart ammocoind
```

---

## Troubleshooting

### Node won't start?
```bash
# Check logs
tail -100 ~/.ammocoin/debug.log

# Check if port is already in use
sudo netstat -tulpn | grep 37020

# Check permissions
ls -la ~/.ammocoin/
```

### Can't connect to RPC?
```bash
# Verify RPC credentials in config
cat ~/.ammocoin/ammocoin.conf | grep rpc

# Test RPC connection
curl --user ammocoinrpc:YOUR_PASSWORD \
     --data-binary '{"jsonrpc":"1.0","id":"test","method":"getinfo","params":[]}' \
     -H 'content-type: text/plain;' \
     http://127.0.0.1:51473/
```

### No incoming connections?
```bash
# Check firewall
sudo ufw status

# Check if port is open
sudo ss -tulpn | grep 37020

# Check external connectivity
curl ifconfig.me  # Get your public IP
# Then test from external: telnet YOUR_IP 37020
```

---

## Network Configuration

### DNS Records (Already Configured)
- **seed1.ammocoin.org** → This Vultr VM IP
- **seed1.ammocoin.org** → This Vultr VM IP

### Firewall Ports
- **37020/tcp** - AMMOcoin P2P (must be open)
- **51473/tcp** - RPC (can be localhost only for security)

### Performance Tuning

For VPS with 2GB RAM:
```ini
dbcache=450
maxmempool=300
maxconnections=125
```

For VPS with 4GB+ RAM:
```ini
dbcache=1000
maxmempool=500
maxconnections=250
```

---

## Security Best Practices

1. **Strong RPC Password**
   - Use: `openssl rand -hex 32`
   - Never use default passwords

2. **Firewall**
   - Only open port 37020 (P2P)
   - Keep RPC (51473) localhost only
   - Use `ufw` to manage rules

3. **Regular Updates**
   ```bash
   sudo apt-get update
   sudo apt-get upgrade
   ```

4. **Backup wallet.dat**
   ```bash
   ammocoin-cli stop
   cp ~/.ammocoin/wallet.dat ~/wallet-backup-$(date +%Y%m%d).dat
   ammocoind -daemon
   ```

5. **Monitor Logs**
   - Check debug.log regularly
   - Look for connection issues
   - Watch for errors

---

## Next Steps After Node is Running

1. **Verify Network Connectivity**
   ```bash
   ammocoin-cli getpeerinfo | grep addr
   ```

2. **Check Blockchain Sync**
   ```bash
   ammocoin-cli getblockchaininfo
   ```
   Look for `"blocks"` field increasing

3. **Generate Initial Supply** (if this is the genesis node)
   - Wait for staking rewards

4. **Set Up Second Seed Node**
   - Repeat this process on another Vultr VM
   - Configure seed2.ammocoin.org

5. **Connect Nodes**
   ```bash
   ammocoin-cli addnode "seed2.ammocoin.org:37020" "add"
   ```

---

## Support

- **Documentation:** `/docs` folder in repository
- **Implementation Plan:** `docs/20251228_NEXT_STEPS_IMPLEMENTATION_PLAN.md`
- **Network Guide:** See `docs/operations/` for deployment guides

---

## Quick Reference Card

```bash
# Start node
sudo systemctl start ammocoind

# Stop node
sudo systemctl stop ammocoind

# Restart node
sudo systemctl restart ammocoind

# Check status
sudo systemctl status ammocoind
ammocoin-cli getinfo

# View logs
tail -f ~/.ammocoin/debug.log

# Get peer count
ammocoin-cli getconnectioncount

# Get blockchain info
ammocoin-cli getblockchaininfo

# Add peer manually
ammocoin-cli addnode "IP:37020" "add"
```

---

**Last Updated:** December 28, 2025
**Node:** seed1.ammocoin.org
**Network:** AMMOcoin v1.1.0 Mainnet

