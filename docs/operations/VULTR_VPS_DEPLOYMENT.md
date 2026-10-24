# AMMOcoin v1.1.1 Vultr VPS Masternode Deployment Guide

## Overview
This guide covers deploying AMMOcoin v1.1.1 Linux binaries on Vultr VPS for masternode operation.

> **v1.1.1 is a mandatory hard fork.** Proof-of-Stake from block 2,776, no mining, new network magic (`c7 9a e3 b5`): v1.1.1 does not connect to v1.0 or v1.1.0 nodes. Default data dir is now `~/.ammocoin11` (was `~/.ammocoin`). Use only the official GitHub release (https://github.com/everquin/AMMOcoin/releases/tag/v1.1.1).

**Key facts:**
- Collateral: **10,000 AMMO** (15 confirmations)
- Masternode payment: 3 AMMO per paid block, 6 AMMO only after block 3,715,200 (see the [v1.1.1 release notes](../release-notes/RELEASE_NOTES_v1.1.1.md))
- The VPS needs a **public, routable IPv4 address** and must use port **37020**. 127.0.0.1 or private IPs (10.x, 172.16-31.x, 192.168.x) are rejected with `Invalid IP address`.
- RPC port 51473 stays localhost-only.

## Prerequisites

### VPS Requirements
- **Provider**: Vultr VPS
- **OS**: Ubuntu 22.04 or 24.04 LTS (24.04 tested). v1.1.1 binaries need **glibc 2.34+**; Ubuntu 18.04/20.04 (and CentOS 8) cannot run them
- **RAM**: Minimum 2GB (4GB recommended for masternodes)
- **Storage**: 40GB+ SSD storage
- **CPU**: 2+ vCPU cores
- **Network**: Stable internet connection and a public IPv4 address

### Security Requirements
- SSH key authentication (disable password auth)
- UFW firewall configuration
- Non-root user with sudo privileges
- Regular security updates

## Step 1: VPS Initial Setup

### Create Vultr VPS Instance
1. Log into Vultr dashboard
2. Deploy new server:
   - **Server Type**: Regular Performance
   - **Server Location**: Choose closest to your location
   - **Server Image**: Ubuntu 24.04 x64
   - **Server Size**: 2 vCPU, 4GB RAM, 80GB SSD
   - **SSH Keys**: Add your public key

### Initial Server Configuration
```bash
# Update system packages
sudo apt update && sudo apt upgrade -y

# Install essential packages
sudo apt install -y curl wget git htop unzip fail2ban ufw

# Configure firewall
sudo ufw default deny incoming
sudo ufw default allow outgoing
sudo ufw allow ssh
sudo ufw allow 37020/tcp  # AMMOcoin P2P port
sudo ufw --force enable

# Create ammocoin user
sudo useradd -m -s /bin/bash ammocoin
sudo usermod -aG sudo ammocoin
sudo passwd ammocoin  # Set strong password
```

## Step 2: AMMOcoin Installation

### Download Linux Binaries
```bash
# Switch to ammocoin user
sudo su - ammocoin

# Create directories
mkdir -p ~/ammocoin-v1.1.1
cd ~/ammocoin-v1.1.1

# Download the v1.1.1 Linux x86_64 archive and checksums from the official
# GitHub release: https://github.com/everquin/AMMOcoin/releases/tag/v1.1.1
# Verify: sha256sum <archive> must match the published checksum

# Extract binaries
tar -xzf AMMOcoin-v1.1.1-*.tar.gz

# Make binaries executable (adjust path if the archive has a bin/ folder)
chmod +x ammocoind ammocoin-cli ammocoin-tx

# Create symlinks for system-wide access
sudo ln -sf ~/ammocoin-v1.1.1/ammocoind /usr/local/bin/ammocoind
sudo ln -sf ~/ammocoin-v1.1.1/ammocoin-cli /usr/local/bin/ammocoin-cli
sudo ln -sf ~/ammocoin-v1.1.1/ammocoin-tx /usr/local/bin/ammocoin-tx

# Check (fails with "GLIBC_2.34 not found" on Ubuntu 18.04/20.04)
ammocoind --version
```

## Step 3: Masternode Setup

A masternode uses two wallets: the **controller wallet** (your local wallet holding the 10,000 AMMO collateral) and the **VPS** (runs the masternode, holds no coins).

### On the Controller Wallet (local)
```bash
# 1. Create a collateral address and send exactly 10,000 AMMO to it
ammocoin-cli getnewaddress "mn1"
ammocoin-cli sendtoaddress "ADDRESS_FROM_ABOVE" 10000

# 2. Wait for 15 confirmations, then generate the masternode key
ammocoin-cli createmasternodekey
# -> MASTERNODE_PRIVKEY (save it)

# 3. Find the collateral txid and output index
ammocoin-cli getmasternodeoutputs
# -> COLLATERAL_TXID and COLLATERAL_INDEX
```

Add one line to `masternode.conf` in the controller's data folder (Linux `~/.ammocoin11/`, macOS `~/Library/Application Support/AMMOcoin11/`, Windows `%APPDATA%\AMMOcoin11\`):

```
mn1 YOUR_VPS_IP:37020 MASTERNODE_PRIVKEY COLLATERAL_TXID COLLATERAL_INDEX
```

Restart the controller wallet so it reads `masternode.conf`.

### On the VPS: Create Configuration
```bash
# Create ammocoin data directory (v1.1.1 default)
mkdir -p ~/.ammocoin11

# Create configuration file
cat > ~/.ammocoin11/ammocoin.conf << EOF
# AMMOcoin v1.1.1 Configuration for Masternode
rpcuser=ammocoinrpc
rpcpassword=$(openssl rand -base64 32)
rpcallowip=127.0.0.1
rpcport=51473
port=37020

# Masternode configuration (public IP, port 37020)
masternode=1
masternodeprivkey=MASTERNODE_PRIVKEY
masternodeaddr=YOUR_VPS_IP:37020
externalip=YOUR_VPS_IP

# Network settings
listen=1
server=1
maxconnections=256

# Logging
debug=0
printtoconsole=0

# Performance tuning
dbcache=512
maxmempool=300
mempoolexpiry=24

# Seed nodes
addnode=78.141.194.140:37020
addnode=104.238.165.56:37020
EOF

# Secure configuration file
chmod 600 ~/.ammocoin11/ammocoin.conf
```

Replace `MASTERNODE_PRIVKEY` (from `createmasternodekey`) and `YOUR_VPS_IP` (the VPS public IPv4, e.g. from `curl -4 ifconfig.me`).

## Step 4: Create System Service

### Create Systemd Service File
`Environment=HOME=` is **required**: without it the node exits with `Cannot find the Sapling parameters` (they live in `~/.ammocoin-params`).

```bash
sudo tee /etc/systemd/system/ammocoin.service > /dev/null << EOF
[Unit]
Description=AMMOcoin daemon
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
User=ammocoin
Group=ammocoin
Environment=HOME=/home/ammocoin
WorkingDirectory=/home/ammocoin
ExecStart=/usr/local/bin/ammocoind -datadir=/home/ammocoin/.ammocoin11 -daemon=0
ExecStop=/usr/local/bin/ammocoin-cli -datadir=/home/ammocoin/.ammocoin11 stop
Restart=on-failure
TimeoutStopSec=120

# Security measures
NoNewPrivileges=yes
PrivateTmp=yes
ProtectSystem=full
ProtectHome=read-only
ReadWritePaths=/home/ammocoin/.ammocoin11 /home/ammocoin/.ammocoin-params

[Install]
WantedBy=multi-user.target
EOF

# Reload systemd and enable service
sudo systemctl daemon-reload
sudo systemctl enable ammocoin.service
```

Running as root instead (the tested v1.1.1 unit): `User=root`, `Environment=HOME=/root`, `ExecStart=/opt/ammocoin-v1.1.1/bin/ammocoind -datadir=/root/.ammocoin11 -daemon=0`, `ExecStop=/opt/ammocoin-v1.1.1/bin/ammocoin-cli -datadir=/root/.ammocoin11 stop`, `Restart=on-failure`, `TimeoutStopSec=120` (and drop the `ProtectHome`/`ReadWritePaths` lines).

## Step 5: Start and Monitor

### Start AMMOcoin Service
```bash
# Start the service
sudo systemctl start ammocoin.service

# Check service status
sudo systemctl status ammocoin.service

# Monitor logs
sudo journalctl -f -u ammocoin.service

# Check if daemon is running
ammocoin-cli getinfo
```

### Start the Masternode (from the Controller Wallet)
Wait until the VPS is fully synced (height past 2,775), then on the **controller wallet**:
```bash
ammocoin-cli startmasternode alias false mn1
```

### Verify Masternode Status
```bash
# Check masternode status (on the VPS)
ammocoin-cli getmasternodestatus

# Check block synchronization
ammocoin-cli getblockchaininfo

# Check connection count
ammocoin-cli getconnectioncount

# Check masternode list (should show your node after activation)
ammocoin-cli listmasternodes
```

## Step 6: Security Hardening

### Additional Security Measures
```bash
# Install additional security tools
sudo apt install -y chkrootkit rkhunter logwatch

# Configure automatic security updates
sudo apt install -y unattended-upgrades
sudo dpkg-reconfigure -plow unattended-upgrades

# Set up log rotation for AMMOcoin
sudo tee /etc/logrotate.d/ammocoin > /dev/null << EOF
/home/ammocoin/.ammocoin11/debug.log {
    daily
    rotate 7
    compress
    delaycompress
    missingok
    notifempty
    copytruncate
}
EOF

# Disable unused services
sudo systemctl disable bluetooth
sudo systemctl disable cups
sudo systemctl disable avahi-daemon
```

## Step 7: Backup and Recovery

### Create Backup Scripts
```bash
# Create backup script
cat > ~/backup-ammocoin.sh << 'EOF'
#!/bin/bash
BACKUP_DIR="/home/ammocoin/backups"
DATE=$(date +%Y%m%d_%H%M%S)

mkdir -p $BACKUP_DIR

# Stop service
sudo systemctl stop ammocoin.service

# Backup wallet and configuration
tar -czf $BACKUP_DIR/ammocoin-backup-$DATE.tar.gz \
    ~/.ammocoin11/wallet.dat \
    ~/.ammocoin11/ammocoin.conf \
    ~/.ammocoin11/masternode.conf 2>/dev/null

# Start service
sudo systemctl start ammocoin.service

# Keep only last 7 backups
find $BACKUP_DIR -name "ammocoin-backup-*.tar.gz" -mtime +7 -delete

echo "Backup completed: $BACKUP_DIR/ammocoin-backup-$DATE.tar.gz"
EOF

chmod +x ~/backup-ammocoin.sh

# Add to crontab for daily backups
(crontab -l 2>/dev/null; echo "0 2 * * * /home/ammocoin/backup-ammocoin.sh") | crontab -
```

## Step 8: Monitoring and Maintenance

### Health Check Commands
```bash
# Node status check
ammocoin-cli getinfo | jq '.'

# Masternode status
ammocoin-cli getmasternodestatus

# Network health
ammocoin-cli getpeerinfo | jq 'length'

# Check if fully synced
ammocoin-cli getblockchaininfo | jq '.verificationprogress'

# Memory usage
free -h
df -h
```

### Performance Monitoring
```bash
# Install monitoring tools
sudo apt install -y htop iotop nethogs

# Check system resources
htop
iotop
nethogs

# Monitor AMMOcoin process
ps aux | grep ammocoind
```

## Troubleshooting

### Common Issues

#### Node Not Syncing
```bash
# Check peer connections
ammocoin-cli getpeerinfo

# Add the seed nodes manually
ammocoin-cli addnode "78.141.194.140:37020" "add"
ammocoin-cli addnode "104.238.165.56:37020" "add"

# Stuck at block 2,775? The node or its peers are not on v1.1.1

# Check firewall
sudo ufw status
```

#### Masternode Not Starting
```bash
# Check masternode status on the VPS
ammocoin-cli getmasternodestatus

# Verify masternode private key and address
grep -E "masternodeprivkey|masternodeaddr|externalip" ~/.ammocoin11/ammocoin.conf

# Check collateral transaction (on the controller wallet)
ammocoin-cli getmasternodeoutputs
```

- `Invalid IP address`: `masternodeaddr` / `masternode.conf` uses 127.0.0.1 or a private IP. Use the VPS public IPv4 with port 37020.
- Wrong port: masternodes must use **37020** (not 37019).
- Collateral must be exactly 10,000 AMMO with at least 15 confirmations.

#### Service Issues
```bash
# "Cannot find the Sapling parameters" -> add Environment=HOME=/home/ammocoin
#   to the unit, then: sudo systemctl daemon-reload

# Check service logs
sudo journalctl -u ammocoin.service -f

# Restart service
sudo systemctl restart ammocoin.service

# Check service status
sudo systemctl status ammocoin.service
```

### Getting Help
- **AMMOcoin Discord**: [Link to Discord]
- **GitHub Issues**: [Link to GitHub]
- **Community Forum**: [Link to Forum]

## Maintenance Schedule

### Daily
- Monitor masternode status
- Check system resources
- Review logs for errors

### Weekly
- Update system packages
- Check backup integrity
- Monitor disk space

### Monthly
- Security audit
- Performance review
- Update documentation

---

**Security Note**: Always keep your masternode private keys secure and create regular backups. Never share your private keys or wallet files.

**Performance Note**: Monitor your VPS resources regularly. If you experience performance issues, consider upgrading to a higher tier VPS.

**Network Note**: Ensure your VPS has a stable internet connection. Intermittent connectivity can drop the masternode out of the payment queue.
