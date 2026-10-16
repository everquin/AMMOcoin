# Commands to Run on Vultr Ubuntu VM

**Copy and paste these in order on your seed1.ammocoin.org VM**

---

## ⚠️ CRITICAL: v1.1.1 (upcoming) Hard Fork

- **v1.1.1 is mandatory.** Proof-of-Stake from block 2,776, no mining. New network magic (`a3 4d b1 e7`): v1.1.1 does not connect to v1.0 or v1.1.0 nodes.
- **OS:** Ubuntu 22.04 or 24.04 (24.04 tested). v1.1.1 needs glibc 2.34+; on Ubuntu 18.04/20.04 upgrade or reinstall the OS first (`ldd --version`).
- **Data dir:** `~/.ammocoincore` (v1.0/v1.1.0 used `~/.ammocoincore`). Sapling params: `~/.ammocoin-params`.
- **Seeds:** seed1 `78.141.194.140:37020`, seed2.ammocoin.org `104.238.165.56:37020`. `147.182.245.102` is dead.
- **Existing installs:** stop the old node and back up every `wallet.dat` before continuing. Keep v1.0 `wallet.dat` files - v1.0 balances are airdropped to the same addresses on v1.1 ([v1.0 Balance Airdrop](../migration/V1.0_BALANCE_AIRDROP.md)).

**Then continue below.**

---

## Step 1: Update System (2 minutes)

```bash
sudo apt-get update && sudo apt-get upgrade -y
```

---

## Step 2: Install Dependencies (5 minutes)

```bash
sudo apt-get install -y \
    build-essential libtool autotools-dev automake \
    pkg-config libssl-dev libevent-dev bsdmainutils \
    python3 libboost-all-dev libminiupnpc-dev libzmq3-dev \
    libqrencode-dev libgmp-dev libsodium-dev cargo rustc \
    git wget curl unzip autoconf-archive
```

---

## Step 3: Install BerkeleyDB 4.8 (5 minutes)

```bash
cd /tmp
wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
tar -xzf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local
make -j$(nproc)
sudo make install
cd ~
```

**⚠️ Important:** On Ubuntu 22.04+ with GCC 9+, you may encounter:
```
error: '__atomic_compare_exchange' was not declared in this scope
```

**Fix:** Apply the atomic.h patch before `make`:
```bash
cd /tmp/db-4.8.30.NC
sed -i 's/__atomic_compare_exchange((p), (o), (n))/__atomic_compare_exchange_db((p), (o), (n))/' dbinc/atomic.h
cd build_unix
make -j$(nproc)
sudo make install
```

See `V1.0_TO_V1.1.0_NODE_MIGRATION.md` for detailed explanation. This patch is standard for modern GCC compatibility.

---

## Step 4: Clone Repository (1 minute)

```bash
git clone https://github.com/everquin/AMMOcoin.git ~/ammocoin
cd ~/ammocoin
git checkout v1.1.1    # until the tag exists: git checkout v1.1.1-pos-fork
cd source
```

---

## Step 5: Build AMMOcoin (10-15 minutes)

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

---

## Step 6: Verify Build (30 seconds)

```bash
ammocoind --version
```

Should show: `AMMOcoin Core Daemon version v1.1.1.0`

---

## Step 7: Install zkSNARK Parameters (2 minutes)

```bash
mkdir -p ~/.ammocoin-params
cd ~/.ammocoin-params
wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
cd ~
```

---

## Step 8: Create Configuration (1 minute)

```bash
mkdir -p ~/.ammocoincore

# Generate strong RPC password
RPC_PASS=$(openssl rand -hex 32)

cat > ~/.ammocoincore/ammocoin.conf << EOF
# AMMOcoin Seed Node Configuration
listen=1
server=1
dnsseed=1

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=51473

# Network
port=37020
maxconnections=125

# Seed nodes (omit this node's own IP)
addnode=78.141.194.140:37020
addnode=104.238.165.56:37020

# Performance
dbcache=450
maxmempool=300

# Logging
debug=0
shrinkdebugfile=1
EOF

chmod 600 ~/.ammocoincore/ammocoin.conf

# Save RPC credentials
echo "RPC Password: $RPC_PASS" > ~/rpc-credentials.txt
chmod 600 ~/rpc-credentials.txt

echo "Configuration created!"
echo "RPC Password saved to: ~/rpc-credentials.txt"
cat ~/rpc-credentials.txt
```

---

## Step 9: Configure Firewall (30 seconds)

```bash
sudo ufw allow 37020/tcp comment 'AMMOcoin P2P'
sudo ufw allow ssh
sudo ufw --force enable
sudo ufw status
```

---

## Step 10: Start the Node (1 minute)

```bash
ammocoind -daemon

# Wait a few seconds
sleep 5

# Check status
ammocoin-cli getinfo
```

---

## Step 11: Monitor Initial Startup (2 minutes)

```bash
# Watch the log file
tail -f ~/.ammocoincore/debug.log

# Press Ctrl+C to stop watching when you see connections forming
```

---

## Step 12: Set Up Systemd Service (2 minutes)

`Environment=HOME=` is required - without it the node exits with "Cannot find the Sapling parameters". Stop the manually started node first (`ammocoin-cli stop`).

```bash
sudo tee /etc/systemd/system/ammocoind.service > /dev/null << EOF
[Unit]
Description=AMMOcoin Daemon
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
User=$USER
Group=$USER
Environment=HOME=$HOME
ExecStart=/usr/local/bin/ammocoind -datadir=$HOME/.ammocoincore -daemon=0
ExecStop=/usr/local/bin/ammocoin-cli -datadir=$HOME/.ammocoincore stop
Restart=on-failure
RestartSec=10
TimeoutStartSec=120
TimeoutStopSec=120

# Hardening
PrivateTmp=true
ProtectSystem=full
NoNewPrivileges=true
PrivateDevices=true

[Install]
WantedBy=multi-user.target
EOF

# Enable the service
sudo systemctl daemon-reload
sudo systemctl enable --now ammocoind

echo "Systemd service created, enabled and started!"
```

---

## Verification Commands

After setup, verify everything is working:

```bash
# Check if daemon is running
ammocoin-cli getinfo

# Check blockchain info
ammocoin-cli getblockchaininfo

# Check peer connections
ammocoin-cli getpeerinfo

# Check connection count
ammocoin-cli getconnectioncount

# View recent log entries
tail -50 ~/.ammocoincore/debug.log
```

---

## Useful Management Commands

```bash
# Start node (if stopped)
ammocoind -daemon
# OR with systemd:
sudo systemctl start ammocoind

# Stop node
ammocoin-cli stop
# OR with systemd:
sudo systemctl stop ammocoind

# Restart node
sudo systemctl restart ammocoind

# Check service status
sudo systemctl status ammocoind

# View logs
tail -f ~/.ammocoincore/debug.log

# Check RPC credentials
cat ~/rpc-credentials.txt
```

---

## Next Steps

Once this node is running:

1. **Connect to the other seed** (seed2.ammocoin.org is `104.238.165.56`):
   ```bash
   ammocoin-cli addnode "104.238.165.56:37020" "add"
   ```
2. **Check the height** is past 2,775 once synced (`ammocoin-cli getblockcount`). There is no mining in v1.1.1; blocks come from staking wallets.

---

**Total Setup Time:** ~30 minutes
**Node Name:** seed1.ammocoin.org
**Network Port:** 37020
**RPC Port:** 51473 (localhost only)

