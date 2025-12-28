#!/bin/bash
#
# AMMOcoin v1.1.0 Seed Node Deployment Script
#
# Deploys and configures an AMMOcoin v1.1.0 seed node on Ubuntu 22.04
# Suitable for Vultr VPS or similar cloud providers
#
# Usage:
#   ./deploy-seed-node.sh [node_number]
#
# Example:
#   ./deploy-seed-node.sh 1
#

set -e  # Exit on error

# Configuration
NODE_NUM=${1:-1}
AMMO_USER="ammocoin"
AMMO_HOME="/home/$AMMO_USER"
AMMO_DIR="$AMMO_HOME/.ammocoin"
INSTALL_DIR="/opt/ammocoin"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Logging functions
log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    log_error "Please run as root (use sudo)"
    exit 1
fi

log_info "=== AMMOcoin v1.1.0 Seed Node Deployment ==="
log_info "Node Number: $NODE_NUM"
echo

# Step 1: System Update
log_info "Step 1: Updating system packages..."
apt-get update
apt-get upgrade -y

# Step 2: Install Dependencies
log_info "Step 2: Installing dependencies..."
apt-get install -y \
    curl \
    wget \
    unzip \
    ufw \
    fail2ban \
    htop \
    nano \
    git

# Step 3: Create AMMOcoin User
log_info "Step 3: Creating AMMOcoin user..."
if id "$AMMO_USER" &>/dev/null; then
    log_warn "User $AMMO_USER already exists"
else
    useradd -m -s /bin/bash "$AMMO_USER"
    log_info "User $AMMO_USER created"
fi

# Step 4: Install Binaries
log_info "Step 4: Installing AMMOcoin binaries..."

# Check if binaries are provided as argument or need to be downloaded
if [ -f "./ammocoind" ] && [ -f "./ammocoin-cli" ]; then
    log_info "Using local binaries"
    mkdir -p "$INSTALL_DIR/bin"
    cp ./ammocoind "$INSTALL_DIR/bin/"
    cp ./ammocoin-cli "$INSTALL_DIR/bin/"
    cp ./ammocoin-tx "$INSTALL_DIR/bin/"
else
    log_error "Binaries not found in current directory"
    log_error "Please copy ammocoind, ammocoin-cli, and ammocoin-tx to this directory"
    exit 1
fi

chmod +x "$INSTALL_DIR/bin/ammocoind"
chmod +x "$INSTALL_DIR/bin/ammocoin-cli"
chmod +x "$INSTALL_DIR/bin/ammocoin-tx"

# Create symlinks
ln -sf "$INSTALL_DIR/bin/ammocoind" /usr/local/bin/ammocoind
ln -sf "$INSTALL_DIR/bin/ammocoin-cli" /usr/local/bin/ammocoin-cli
ln -sf "$INSTALL_DIR/bin/ammocoin-tx" /usr/local/bin/ammocoin-tx

# Verify installation
log_info "Verifying binary installation..."
if /usr/local/bin/ammocoind --version | grep -q "v1.1.0"; then
    log_info "Binary verification successful"
else
    log_error "Binary verification failed"
    exit 1
fi

# Step 5: Create Data Directory
log_info "Step 5: Creating data directory..."
mkdir -p "$AMMO_DIR"
chown -R "$AMMO_USER:$AMMO_USER" "$AMMO_DIR"

# Step 6: Generate RPC Credentials
log_info "Step 6: Generating RPC credentials..."
RPC_USER="rpc_ammocoin"
RPC_PASS=$(openssl rand -base64 32 | tr -d "=+/" | cut -c1-25)

log_info "RPC Username: $RPC_USER"
log_info "RPC Password: $RPC_PASS"

# Step 7: Create Configuration File
log_info "Step 7: Creating ammocoin.conf..."

# Get server's external IP
EXTERNAL_IP=$(curl -s ifconfig.me)
log_info "External IP: $EXTERNAL_IP"

cat > "$AMMO_DIR/ammocoin.conf" << EOF
# AMMOcoin v1.1.0 Configuration
# Seed Node #$NODE_NUM
# Generated: $(date)

# Network
listen=1
server=1
daemon=1
externalip=$EXTERNAL_IP
maxconnections=125

# RPC
rpcuser=$RPC_USER
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=37021

# Logging
debug=0
printtoconsole=0

# Performance
dbcache=300
maxmempool=300
maxorphantx=10

# Privacy
privatesendclient=0
EOF

# Add seed nodes (will be filled in after deployment)
cat >> "$AMMO_DIR/ammocoin.conf" << EOF

# Seed Nodes (add other seed node IPs here)
# addnode=SEED_NODE_1_IP:37020
# addnode=SEED_NODE_2_IP:37020
# addnode=SEED_NODE_3_IP:37020
EOF

chown "$AMMO_USER:$AMMO_USER" "$AMMO_DIR/ammocoin.conf"
chmod 600 "$AMMO_DIR/ammocoin.conf"

log_info "Configuration file created at $AMMO_DIR/ammocoin.conf"

# Step 8: Create Systemd Service
log_info "Step 8: Creating systemd service..."

cat > /etc/systemd/system/ammocoind.service << EOF
[Unit]
Description=AMMOcoin v1.1.0 Daemon
After=network.target

[Service]
Type=forking
User=$AMMO_USER
Group=$AMMO_USER
WorkingDirectory=$AMMO_HOME
ExecStart=/usr/local/bin/ammocoind -daemon -conf=$AMMO_DIR/ammocoin.conf -datadir=$AMMO_DIR
ExecStop=/usr/local/bin/ammocoin-cli -conf=$AMMO_DIR/ammocoin.conf -datadir=$AMMO_DIR stop
Restart=on-failure
RestartSec=30
TimeoutStopSec=60
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

log_info "Systemd service created and enabled"

# Step 9: Configure Firewall
log_info "Step 9: Configuring firewall..."

# Reset UFW to defaults
ufw --force reset

# Default policies
ufw default deny incoming
ufw default allow outgoing

# Allow SSH (important!)
ufw allow 22/tcp

# Allow AMMOcoin P2P port
ufw allow 37020/tcp

# Enable firewall
ufw --force enable

log_info "Firewall configured"

# Step 10: Configure Fail2Ban
log_info "Step 10: Configuring fail2ban..."
systemctl enable fail2ban
systemctl start fail2ban

# Step 11: Create Management Scripts
log_info "Step 11: Creating management scripts..."

# Start script
cat > "$AMMO_HOME/start-node.sh" << 'EOF'
#!/bin/bash
sudo systemctl start ammocoind
echo "AMMOcoin node starting..."
sleep 3
ammocoin-cli getinfo
EOF

# Stop script
cat > "$AMMO_HOME/stop-node.sh" << 'EOF'
#!/bin/bash
sudo systemctl stop ammocoind
echo "AMMOcoin node stopped"
EOF

# Status script
cat > "$AMMO_HOME/status-node.sh" << 'EOF'
#!/bin/bash
echo "=== AMMOcoin Node Status ==="
sudo systemctl status ammocoind --no-pager
echo
echo "=== Network Info ==="
ammocoin-cli getinfo
echo
echo "=== Peer Connections ==="
ammocoin-cli getpeerinfo | grep -E "addr|version" | head -20
EOF

# Restart script
cat > "$AMMO_HOME/restart-node.sh" << 'EOF'
#!/bin/bash
sudo systemctl restart ammocoind
echo "AMMOcoin node restarting..."
sleep 3
ammocoin-cli getinfo
EOF

chmod +x "$AMMO_HOME"/*.sh
chown "$AMMO_USER:$AMMO_USER" "$AMMO_HOME"/*.sh

log_info "Management scripts created in $AMMO_HOME"

# Step 12: Display Summary
echo
echo "================================================================"
log_info "AMMOcoin v1.1.0 Seed Node Deployment Complete!"
echo "================================================================"
echo
echo "Node Details:"
echo "  Node Number:    $NODE_NUM"
echo "  External IP:    $EXTERNAL_IP"
echo "  P2P Port:       37020"
echo "  RPC Port:       37021"
echo "  Data Directory: $AMMO_DIR"
echo
echo "RPC Credentials:"
echo "  Username: $RPC_USER"
echo "  Password: $RPC_PASS"
echo
echo "Management Commands:"
echo "  Start:   sudo systemctl start ammocoind"
echo "  Stop:    sudo systemctl stop ammocoind"
echo "  Status:  sudo systemctl status ammocoind"
echo "  Logs:    journalctl -u ammocoind -f"
echo
echo "Helper Scripts (run as $AMMO_USER):"
echo "  $AMMO_HOME/start-node.sh"
echo "  $AMMO_HOME/stop-node.sh"
echo "  $AMMO_HOME/status-node.sh"
echo "  $AMMO_HOME/restart-node.sh"
echo
echo "Next Steps:"
echo "  1. Update $AMMO_DIR/ammocoin.conf with other seed node IPs"
echo "  2. Start the node: sudo systemctl start ammocoind"
echo "  3. Check status: sudo systemctl status ammocoind"
echo "  4. View logs: journalctl -u ammocoind -f"
echo "  5. Check connectivity: ammocoin-cli getpeerinfo"
echo
echo "================================================================"
echo

# Save credentials to file
cat > "$AMMO_HOME/node-credentials.txt" << EOF
AMMOcoin v1.1.0 Seed Node #$NODE_NUM
Deployed: $(date)

External IP: $EXTERNAL_IP
P2P Port: 37020
RPC Port: 37021

RPC Username: $RPC_USER
RPC Password: $RPC_PASS

Management:
  Start:   sudo systemctl start ammocoind
  Stop:    sudo systemctl stop ammocoind
  Status:  sudo systemctl status ammocoind
  Logs:    journalctl -u ammocoind -f
EOF

chown "$AMMO_USER:$AMMO_USER" "$AMMO_HOME/node-credentials.txt"
chmod 600 "$AMMO_HOME/node-credentials.txt"

log_info "Credentials saved to $AMMO_HOME/node-credentials.txt"
echo

exit 0
