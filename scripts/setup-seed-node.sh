#!/bin/bash
#
# AMMOcoin v1.1.0 Seed Node Setup Script
# For Ubuntu 20.04/22.04/24.04 LTS
#
# This script sets up a complete AMMOcoin seed node with:
# - All build dependencies
# - Compiled binaries
# - Configured daemon
# - Systemd service for auto-start
#
# Usage: sudo bash setup-seed-node.sh
#

set -e  # Exit on error

echo "========================================"
echo "AMMOcoin v1.1.0 Seed Node Setup"
echo "========================================"
echo ""

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    echo "ERROR: Please run as root (use sudo)"
    exit 1
fi

# Get actual user (not root)
ACTUAL_USER="${SUDO_USER:-$USER}"
USER_HOME=$(eval echo ~$ACTUAL_USER)

echo "Installing for user: $ACTUAL_USER"
echo "Home directory: $USER_HOME"
echo ""

# System info
echo "=== System Information ==="
cat /etc/os-release | grep PRETTY_NAME
uname -a
echo "CPU Cores: $(nproc)"
echo "RAM: $(free -h | grep Mem: | awk '{print $2}')"
echo "Disk: $(df -h / | tail -1 | awk '{print $4}') available"
echo ""

# Update system
echo "=== Updating System ==="
apt-get update
apt-get upgrade -y
echo ""

# Install build dependencies
echo "=== Installing Build Dependencies ==="
apt-get install -y \
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
    libqrencode-dev \
    libgmp-dev \
    libsodium-dev \
    cargo \
    rustc \
    git \
    wget \
    curl \
    unzip \
    autoconf-archive

echo ""
echo "=== Installing BerkeleyDB 4.8 ==="
# BerkeleyDB 4.8 for wallet compatibility
cd /tmp
wget http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
tar -xzf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local
make -j$(nproc)
make install
cd /tmp
rm -rf db-4.8.30.NC*
echo ""

# Clone or update repository
echo "=== Setting up AMMOcoin Repository ==="
AMMOCOIN_DIR="$USER_HOME/ammocoin"

if [ -d "$AMMOCOIN_DIR" ]; then
    echo "Repository exists, updating..."
    cd "$AMMOCOIN_DIR"
    sudo -u $ACTUAL_USER git pull
else
    echo "Cloning repository..."
    cd "$USER_HOME"
    sudo -u $ACTUAL_USER git clone https://github.com/everquin/AMMOcoin-v1.1.0.git ammocoin
    cd "$AMMOCOIN_DIR"
fi

echo ""
echo "=== Building AMMOcoin ==="
cd "$AMMOCOIN_DIR/ammocoin-apps-from-ammocoin"

# Clean previous build
make clean 2>/dev/null || true

# Run autogen
sudo -u $ACTUAL_USER ./autogen.sh

# Configure
sudo -u $ACTUAL_USER ./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --with-incompatible-bdb \
    LDFLAGS="-L/usr/local/lib/" \
    CPPFLAGS="-I/usr/local/include/"

# Build (use all cores)
echo "Building with $(nproc) cores (this may take 10-20 minutes)..."
sudo -u $ACTUAL_USER make -j$(nproc)

echo ""
echo "=== Installing Binaries ==="
make install

# Verify installation
echo ""
echo "=== Verifying Installation ==="
which ammocoind
which ammocoin-cli
ammocoind --version

echo ""
echo "=== Installing zkSNARK Parameters ==="
# Install Sapling parameters
PARAMS_DIR="$USER_HOME/.ammocoin-params"
mkdir -p "$PARAMS_DIR"
chown $ACTUAL_USER:$ACTUAL_USER "$PARAMS_DIR"

cd "$PARAMS_DIR"
if [ ! -f "sapling-spend.params" ]; then
    echo "Downloading Sapling spend parameters..."
    sudo -u $ACTUAL_USER wget -q --show-progress https://download.z.cash/downloads/sapling-spend.params
fi

if [ ! -f "sapling-output.params" ]; then
    echo "Downloading Sapling output parameters..."
    sudo -u $ACTUAL_USER wget -q --show-progress https://download.z.cash/downloads/sapling-output.params
fi

echo ""
echo "=== Configuring AMMOcoin Daemon ==="
DATA_DIR="$USER_HOME/.ammocoin"
mkdir -p "$DATA_DIR"
chown $ACTUAL_USER:$ACTUAL_USER "$DATA_DIR"

# Generate RPC credentials
RPC_USER="ammocoinrpc"
RPC_PASS=$(openssl rand -hex 32)

# Create ammocoin.conf
cat > "$DATA_DIR/ammocoin.conf" << EOF
# AMMOcoin Seed Node Configuration
# Generated: $(date)

# Network
listen=1
server=1
daemon=1

# This is a seed node
dnsseed=1

# RPC Settings
rpcuser=$RPC_USER
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=8332

# Network Settings
port=37020
maxconnections=125

# Performance
dbcache=450
maxmempool=300

# Logging
debug=0
shrinkdebugfile=1

# Staking (enable if you want this node to stake)
# staking=1
EOF

chown $ACTUAL_USER:$ACTUAL_USER "$DATA_DIR/ammocoin.conf"
chmod 600 "$DATA_DIR/ammocoin.conf"

echo "Configuration created at: $DATA_DIR/ammocoin.conf"
echo "RPC User: $RPC_USER"
echo "RPC Pass: $RPC_PASS"
echo ""

# Create systemd service
echo "=== Creating Systemd Service ==="
cat > /etc/systemd/system/ammocoind.service << EOF
[Unit]
Description=AMMOcoin Daemon
After=network.target

[Service]
Type=forking
User=$ACTUAL_USER
Group=$ACTUAL_USER
ExecStart=/usr/local/bin/ammocoind -daemon -conf=$DATA_DIR/ammocoin.conf -datadir=$DATA_DIR
ExecStop=/usr/local/bin/ammocoin-cli -conf=$DATA_DIR/ammocoin.conf -datadir=$DATA_DIR stop
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
systemctl daemon-reload
systemctl enable ammocoind.service

echo ""
echo "=== Configuring Firewall ==="
# Allow AMMOcoin port
ufw allow 37020/tcp comment 'AMMOcoin P2P'
ufw allow 8332/tcp comment 'AMMOcoin RPC'
ufw --force enable

echo ""
echo "========================================"
echo "✅ AMMOcoin Seed Node Setup Complete!"
echo "========================================"
echo ""
echo "Binary location: /usr/local/bin/ammocoind"
echo "Data directory: $DATA_DIR"
echo "Config file: $DATA_DIR/ammocoin.conf"
echo ""
echo "RPC Credentials:"
echo "  User: $RPC_USER"
echo "  Pass: $RPC_PASS"
echo "  Port: 8332"
echo ""
echo "Save these credentials securely!"
echo ""
echo "To start the node:"
echo "  sudo systemctl start ammocoind"
echo ""
echo "To check status:"
echo "  sudo systemctl status ammocoind"
echo "  ammocoin-cli getinfo"
echo ""
echo "To view logs:"
echo "  tail -f $DATA_DIR/debug.log"
echo ""
echo "To enable auto-start on boot (already done):"
echo "  sudo systemctl enable ammocoind"
echo ""
echo "========================================"
