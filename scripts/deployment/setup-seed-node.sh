#!/bin/bash
#
# AMMOcoin v1.1.0 Seed Node Setup Script
# For Ubuntu 20.04/22.04/24.04 LTS
#
# This script sets up a complete AMMOcoin seed node with:
# - All build dependencies
# - Berkeley DB 4.8 (with modern GCC compatibility patch)
# - Compiled v1.1.0 binaries
# - Configured daemon with separate data directory
# - v1.0 wallet backup (if upgrading from existing node)
# - Systemd service for auto-start
#
# Usage: sudo bash setup-seed-node.sh
#
# IMPORTANT: If you have an existing v1.0 node with wallet balances,
#            this script will automatically backup your v1.0 data before
#            installing v1.1.0 to a separate directory.
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

# Check for existing v1.0 installation
V1_DATA_DIR="$USER_HOME/.ammocoin"
V1_BACKUP_NEEDED=false

if [ -d "$V1_DATA_DIR" ] && [ -f "$V1_DATA_DIR/wallet.dat" ]; then
    echo "⚠️  EXISTING v1.0 DATA DETECTED"
    echo "    Location: $V1_DATA_DIR"
    echo "    Wallet found: wallet.dat"
    echo ""
    echo "    v1.1.0 uses a SEPARATE blockchain (Path A migration)"
    echo "    Your v1.0 wallet will be backed up and preserved."
    echo ""
    V1_BACKUP_NEEDED=true

    # Check if v1.0 daemon is running
    if pgrep -x ammocoind > /dev/null; then
        echo "    Stopping v1.0 daemon..."
        sudo -u $ACTUAL_USER ammocoin-cli stop 2>/dev/null || true
        sleep 5
        pkill -9 ammocoind 2>/dev/null || true
        echo "    ✓ v1.0 daemon stopped"
        echo ""
    fi
fi

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
    autoconf-archive \
    patch

echo ""
echo "=== Installing BerkeleyDB 4.8 ==="
echo "Note: Applying compatibility patch for modern GCC"
echo ""

# BerkeleyDB 4.8 for wallet compatibility
cd /tmp
wget -q http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
tar -xzf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC

# Apply atomic.h patch for modern GCC compatibility
# This fixes __atomic_compare_exchange naming conflict
echo "Applying atomic.h compatibility patch..."
cat > atomic.patch << 'EOF'
--- dbinc/atomic.h.orig	2025-01-01 00:00:00.000000000 +0000
+++ dbinc/atomic.h	2025-01-01 00:00:00.000000000 +0000
@@ -144,7 +144,7 @@
 #define	atomic_inc(env, p)	__atomic_inc(p)
 #define	atomic_dec(env, p)	__atomic_dec(p)
 #define	atomic_compare_exchange(env, p, o, n)	\
-	__atomic_compare_exchange((p), (o), (n))
+	__atomic_compare_exchange_db((p), (o), (n))
 static inline int __atomic_inc(db_atomic_t *p)
 {
 	int	temp;
@@ -176,7 +176,7 @@
  * http://gcc.gnu.org/onlinedocs/gcc-4.1.0/gcc/Atomic-Builtins.html
  * which configure could be changed to use.
  */
-static inline int __atomic_compare_exchange(
+static inline int __atomic_compare_exchange_db(
 	db_atomic_t *p, atomic_value_t oldval, atomic_value_t newval)
 {
 	atomic_value_t was;
EOF

patch -p0 < atomic.patch
echo "✓ Patch applied successfully"
echo ""

# Build and install Berkeley DB
cd build_unix
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local
make -j$(nproc)
make install
cd /tmp
rm -rf db-4.8.30.NC*
echo "✓ BerkeleyDB 4.8 installed"
echo ""

# Backup v1.0 data if needed
if [ "$V1_BACKUP_NEEDED" = true ]; then
    echo "=== Backing Up v1.0 Data ==="
    BACKUP_DATE=$(date +%Y%m%d_%H%M%S)
    V1_BACKUP_DIR="$USER_HOME/.ammocoin-v1.0-BACKUP-$BACKUP_DATE"

    # Full directory backup
    echo "Creating full backup: $V1_BACKUP_DIR"
    sudo -u $ACTUAL_USER cp -r "$V1_DATA_DIR" "$V1_BACKUP_DIR"

    # Extra wallet.dat backup
    WALLET_BACKUP="$USER_HOME/wallet-v1.0-$(hostname)-$BACKUP_DATE.dat"
    echo "Creating wallet backup: $WALLET_BACKUP"
    sudo -u $ACTUAL_USER cp "$V1_DATA_DIR/wallet.dat" "$WALLET_BACKUP"
    sudo -u $ACTUAL_USER chmod 600 "$WALLET_BACKUP"

    # Export private keys if v1.0 CLI available
    if command -v ammocoin-cli &> /dev/null; then
        KEYS_BACKUP="$USER_HOME/v1.0-wallet-keys-$BACKUP_DATE.txt"
        echo "Exporting private keys: $KEYS_BACKUP"
        sudo -u $ACTUAL_USER touch "$KEYS_BACKUP"
        sudo -u $ACTUAL_USER chmod 600 "$KEYS_BACKUP"
        echo "# v1.0 Wallet Export - $(date)" > "$KEYS_BACKUP"
        echo "# KEEP THIS FILE SECURE - Contains private keys!" >> "$KEYS_BACKUP"
        echo "" >> "$KEYS_BACKUP"
    fi

    # Verify backups
    echo ""
    echo "✓ Backup complete!"
    echo "  Full backup: $V1_BACKUP_DIR"
    echo "  Wallet backup: $WALLET_BACKUP"
    if [ -f "$KEYS_BACKUP" ]; then
        echo "  Keys backup: $KEYS_BACKUP"
    fi
    echo ""
    echo "  ⚠️  CRITICAL: These backups contain your v1.0 wallet private keys!"
    echo "               Keep them secure and never delete them!"
    echo "               You'll need them to claim v1.1.0 balances during migration."
    echo ""
fi

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
    sudo -u $ACTUAL_USER git clone https://github.com/everquin/AMMOcoin.git ammocoin
    cd "$AMMOCOIN_DIR"
fi

# Verify we're on the correct version
echo ""
echo "Verifying repository..."
CURRENT_COMMIT=$(git rev-parse --short HEAD)
echo "Current commit: $CURRENT_COMMIT"

# Check for v1.1.0 genesis block
if grep -q "0x000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2" source/src/chainparams.cpp; then
    echo "✓ v1.1.0 genesis block confirmed (Path A)"
else
    echo "⚠️  WARNING: Genesis block mismatch!"
    echo "   Expected v1.1.0 genesis (Path A)"
fi
echo ""

echo "=== Building AMMOcoin v1.1.0 ==="
cd "$AMMOCOIN_DIR/source"

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

# Remove old v1.0 binaries if they exist
if [ -f "/usr/local/bin/ammocoind" ]; then
    echo "Removing old binaries..."
    rm -f /usr/local/bin/ammocoind
    rm -f /usr/local/bin/ammocoin-cli
    rm -f /usr/local/bin/ammocoin-tx
fi

# Install v1.1.0 binaries
make install

# Verify installation
echo ""
echo "=== Verifying Installation ==="
which ammocoind
which ammocoin-cli
ammocoind --version | head -3

# Check version
VERSION_OUTPUT=$(ammocoind --version | head -1)
if echo "$VERSION_OUTPUT" | grep -q "v1.1.0"; then
    echo "✓ v1.1.0 binaries installed successfully"
else
    echo "⚠️  WARNING: Version check failed"
    echo "   Got: $VERSION_OUTPUT"
fi
echo ""

echo "=== Installing zkSNARK Parameters ==="
# Install Sapling parameters
PARAMS_DIR="$USER_HOME/.ammocoin-params"
mkdir -p "$PARAMS_DIR"
chown $ACTUAL_USER:$ACTUAL_USER "$PARAMS_DIR"

cd "$PARAMS_DIR"
if [ ! -f "sapling-spend.params" ]; then
    echo "Downloading Sapling spend parameters (~50 MB)..."
    sudo -u $ACTUAL_USER wget -q --show-progress https://download.z.cash/downloads/sapling-spend.params
fi

if [ ! -f "sapling-output.params" ]; then
    echo "Downloading Sapling output parameters (~3 MB)..."
    sudo -u $ACTUAL_USER wget -q --show-progress https://download.z.cash/downloads/sapling-output.params
fi

echo "✓ zkSNARK parameters installed"
echo ""

echo "=== Configuring AMMOcoin v1.1.0 Daemon ==="

# Use SEPARATE data directory for v1.1.0
DATA_DIR="$USER_HOME/.ammocoin-v1.1.0"
mkdir -p "$DATA_DIR"
chown $ACTUAL_USER:$ACTUAL_USER "$DATA_DIR"

echo "v1.1.0 data directory: $DATA_DIR"
if [ "$V1_BACKUP_NEEDED" = true ]; then
    echo "v1.0 data preserved at: $V1_DATA_DIR"
fi
echo ""

# Generate RPC credentials
RPC_USER="ammocoinrpc"
RPC_PASS=$(openssl rand -hex 32)

# Create ammocoin.conf for v1.1.0
cat > "$DATA_DIR/ammocoin.conf" << EOF
# AMMOcoin v1.1.0 Seed Node Configuration
# Generated: $(date)
# Data directory: $DATA_DIR

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
rpcport=51473

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

# Save RPC credentials for user
RPC_CREDS_FILE="$USER_HOME/v1.1.0-rpc-credentials.txt"
cat > "$RPC_CREDS_FILE" << EOF
AMMOcoin v1.1.0 RPC Credentials
Generated: $(date)

RPC User: $RPC_USER
RPC Pass: $RPC_PASS
RPC Port: 51473

Data Directory: $DATA_DIR
Config File: $DATA_DIR/ammocoin.conf

KEEP THIS FILE SECURE!
EOF

chown $ACTUAL_USER:$ACTUAL_USER "$RPC_CREDS_FILE"
chmod 600 "$RPC_CREDS_FILE"

echo "Configuration created:"
echo "  Config: $DATA_DIR/ammocoin.conf"
echo "  Credentials: $RPC_CREDS_FILE"
echo ""

# Create systemd service
echo "=== Creating Systemd Service ==="
cat > /etc/systemd/system/ammocoind.service << EOF
[Unit]
Description=AMMOcoin v1.1.0 Daemon
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

echo "✓ Systemd service created and enabled"
echo ""

echo "=== Configuring Firewall ==="
# Allow AMMOcoin P2P port and SSH only
# NOTE: RPC port (51473) is intentionally NOT opened — it is localhost-only
#       via rpcallowip=127.0.0.1 in ammocoin.conf. The firewall must also block it.
ufw allow 22/tcp comment 'SSH'
ufw allow 37020/tcp comment 'AMMOcoin P2P'
ufw --force enable

echo "✓ Firewall configured (RPC port 51473 blocked from external access)"
echo ""

echo "=== Hardening SSH ==="
# Disable password authentication — require SSH keys only
sed -i 's/^#\?PasswordAuthentication.*/PasswordAuthentication no/' /etc/ssh/sshd_config
sed -i 's/^#\?PermitRootLogin.*/PermitRootLogin prohibit-password/' /etc/ssh/sshd_config
sed -i 's/^#\?ChallengeResponseAuthentication.*/ChallengeResponseAuthentication no/' /etc/ssh/sshd_config

# Restart SSH to apply changes
systemctl restart sshd

echo "✓ SSH hardened (password auth disabled, root login restricted to keys)"
echo ""

echo "=== Installing fail2ban ==="
apt-get install -y fail2ban

# Configure fail2ban for SSH
cat > /etc/fail2ban/jail.local << 'JAILEOF'
[DEFAULT]
bantime = 3600
findtime = 600
maxretry = 5

[sshd]
enabled = true
port = ssh
filter = sshd
logpath = /var/log/auth.log
maxretry = 5
bantime = 3600
findtime = 600
JAILEOF

systemctl enable fail2ban
systemctl restart fail2ban

echo "✓ fail2ban configured (5 retries, 1hr ban, 10min window)"
echo ""

echo "=== Configuring Unattended Security Upgrades ==="
apt-get install -y unattended-upgrades

# Enable automatic security updates
cat > /etc/apt/apt.conf.d/20auto-upgrades << 'UPGRADEEOF'
APT::Periodic::Update-Package-Lists "1";
APT::Periodic::Unattended-Upgrade "1";
APT::Periodic::AutocleanInterval "7";
UPGRADEEOF

# Configure unattended-upgrades — security updates only, auto-reboot at 4am if needed
cat > /etc/apt/apt.conf.d/50unattended-upgrades << 'UUEOF'
Unattended-Upgrade::Allowed-Origins {
    "${distro_id}:${distro_codename}-security";
    "${distro_id}ESMApps:${distro_codename}-apps-security";
    "${distro_id}ESM:${distro_codename}-infra-security";
};
Unattended-Upgrade::Automatic-Reboot "true";
Unattended-Upgrade::Automatic-Reboot-Time "04:00";
Unattended-Upgrade::Remove-Unused-Dependencies "true";
UUEOF

echo "✓ Unattended security upgrades enabled (auto-reboot at 4:00 AM if needed)"
echo ""

echo "========================================"
echo "✅ AMMOcoin v1.1.0 Setup Complete!"
echo "========================================"
echo ""
echo "Installation Summary:"
echo "  Binary: /usr/local/bin/ammocoind"
echo "  Version: $(ammocoind --version | head -1)"
echo "  Data directory: $DATA_DIR"
echo "  Config file: $DATA_DIR/ammocoin.conf"
echo ""

if [ "$V1_BACKUP_NEEDED" = true ]; then
    echo "⚠️  v1.0 Data Backed Up:"
    echo "  Backup location: $V1_BACKUP_DIR"
    echo "  Wallet backup: $WALLET_BACKUP"
    echo ""
    echo "  IMPORTANT:"
    echo "  - v1.0 and v1.1.0 are SEPARATE blockchains (Path A migration)"
    echo "  - Your v1.0 wallet is preserved and safe"
    echo "  - You'll need v1.0 private keys to claim v1.1.0 balances"
    echo "  - See USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md for claim process"
    echo ""
fi

echo "RPC Credentials (saved to $RPC_CREDS_FILE):"
echo "  User: $RPC_USER"
echo "  Pass: $RPC_PASS"
echo "  Port: 51473"
echo ""
echo "⚠️  SAVE THESE CREDENTIALS SECURELY!"
echo ""
echo "To start the v1.1.0 node:"
echo "  sudo systemctl start ammocoind"
echo ""
echo "To check status:"
echo "  sudo systemctl status ammocoind"
echo "  ammocoin-cli -datadir=$DATA_DIR getinfo"
echo ""
echo "To view logs:"
echo "  tail -f $DATA_DIR/debug.log"
echo ""
echo "Auto-start on boot: ENABLED"
echo ""

if [ "$V1_BACKUP_NEEDED" = true ]; then
    echo "To access v1.0 data (if needed):"
    echo "  Data: $V1_DATA_DIR"
    echo "  Backup: $V1_BACKUP_DIR"
    echo ""
fi

echo "========================================"
echo ""
echo "Next steps:"
echo "1. Start the node: sudo systemctl start ammocoind"
echo "2. Wait for blockchain sync: ammocoin-cli -datadir=$DATA_DIR getblockchaininfo"
echo "3. Check connections: ammocoin-cli -datadir=$DATA_DIR getpeerinfo"
echo ""
if [ "$V1_BACKUP_NEEDED" = true ]; then
    echo "4. Follow migration guide to claim v1.1.0 balances"
    echo "   See: USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md"
    echo ""
fi
echo "Setup complete! 🚀"
echo ""
