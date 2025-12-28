# Commands to Run on Vultr Ubuntu VM

**Copy and paste these in order on your seed1.ammocoin.org VM**

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

---

## Step 4: Clone Repository (1 minute)

```bash
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git ~/ammocoin
cd ~/ammocoin/ammocoin-apps-from-ammocoin
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

Should show: `AMMOcoin Core Daemon version v1.1.0.0`

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
mkdir -p ~/.ammocoin

# Generate strong RPC password
RPC_PASS=$(openssl rand -hex 32)

cat > ~/.ammocoin/ammocoin.conf << EOF
# AMMOcoin Seed Node Configuration
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
maxconnections=125

# Performance
dbcache=450
maxmempool=300

# Logging
debug=0
shrinkdebugfile=1
EOF

chmod 600 ~/.ammocoin/ammocoin.conf

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
tail -f ~/.ammocoin/debug.log

# Press Ctrl+C to stop watching when you see connections forming
```

---

## Step 12: Set Up Systemd Service (2 minutes)

```bash
sudo tee /etc/systemd/system/ammocoind.service > /dev/null << EOF
[Unit]
Description=AMMOcoin Daemon
After=network.target

[Service]
Type=forking
User=$USER
Group=$USER
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
EOF

# Enable the service
sudo systemctl daemon-reload
sudo systemctl enable ammocoind

echo "Systemd service created and enabled!"
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
tail -50 ~/.ammocoin/debug.log
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
tail -f ~/.ammocoin/debug.log

# Check RPC credentials
cat ~/rpc-credentials.txt
```

---

## Next Steps

Once this node is running:

1. **Set up seed2.ammocoin.org** (repeat on another Vultr VM)
2. **Connect the nodes:**
   ```bash
   ammocoin-cli addnode "seed2.ammocoin.org:37020" "add"
   ```
3. **Generate initial supply** (see NETWORK_BOOTSTRAP_GUIDE.md)
4. **Execute distribution** to top 61 holders

---

**Total Setup Time:** ~30 minutes
**Node Name:** seed1.ammocoin.org / node1.ammocoin.org
**Network Port:** 37020
**RPC Port:** 8332 (localhost only)

