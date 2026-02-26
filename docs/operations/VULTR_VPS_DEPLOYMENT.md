# AMMOcoin v1.1.0 Vultr VPS Masternode Deployment Guide

## Overview
This guide covers deploying AMMOcoin v1.1.0 Linux binaries on Vultr VPS for masternode operation.

## Prerequisites

### VPS Requirements
- **Provider**: Vultr VPS
- **OS**: Ubuntu 22.04 LTS (recommended) or CentOS 8+
- **RAM**: Minimum 2GB (4GB recommended for masternodes)
- **Storage**: 40GB+ SSD storage
- **CPU**: 2+ vCPU cores
- **Network**: Stable internet connection

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
   - **Server Image**: Ubuntu 22.04 x64
   - **Server Size**: $12/mo (2 vCPU, 4GB RAM, 80GB SSD)
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
mkdir -p ~/ammocoin-v1.1.0
cd ~/ammocoin-v1.1.0

# Download Linux binaries (replace with actual download link)
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Extract binaries
tar -xzf ammocoin-v1.1.0-linux-x86_64.tar.gz

# Make binaries executable
chmod +x ammocoind ammocoin-cli ammocoin-tx

# Create symlinks for system-wide access
sudo ln -sf ~/ammocoin-v1.1.0/ammocoind /usr/local/bin/ammocoind
sudo ln -sf ~/ammocoin-v1.1.0/ammocoin-cli /usr/local/bin/ammocoin-cli
sudo ln -sf ~/ammocoin-v1.1.0/ammocoin-tx /usr/local/bin/ammocoin-tx
```

### Create Configuration Directory
```bash
# Create ammocoin data directory
mkdir -p ~/.ammocoin

# Create configuration file
cat > ~/.ammocoin/ammocoin.conf << EOF
# AMMOcoin v1.1.0 Configuration for Masternode
rpcuser=ammocoinrpc
rpcpassword=$(openssl rand -base64 32)
rpcallowip=127.0.0.1
rpcport=51473
port=37020

# Masternode configuration
masternode=1
masternodeprivkey=YOUR_MASTERNODE_PRIVATE_KEY_HERE
externalip=YOUR_VPS_IP_ADDRESS_HERE

# Network settings
listen=1
server=1
daemon=1
maxconnections=256

# Logging
debug=0
printtoconsole=0

# Privacy features (Sapling)
exportdir=~/.ammocoin/sapling-output

# Performance tuning
dbcache=512
maxmempool=300
mempoolexpiry=24

# Addnodes (add known good nodes)
addnode=seed1.ammocoin.org
addnode=seed2.ammocoin.org
EOF

# Secure configuration file
chmod 600 ~/.ammocoin/ammocoin.conf
```

## Step 3: Masternode Setup

### Generate Masternode Keys
```bash
# Start daemon briefly to generate masternode key
ammocoind -daemon
sleep 10

# Generate masternode private key
ammocoin-cli masternode genkey

# Stop daemon
ammocoin-cli stop
sleep 5
```

### Update Configuration
```bash
# Edit configuration with your masternode key and VPS IP
nano ~/.ammocoin/ammocoin.conf

# Replace placeholders:
# YOUR_MASTERNODE_PRIVATE_KEY_HERE -> output from masternode genkey
# YOUR_VPS_IP_ADDRESS_HERE -> your VPS public IP address
```

## Step 4: Create System Service

### Create Systemd Service File
```bash
sudo tee /etc/systemd/system/ammocoin.service > /dev/null << EOF
[Unit]
Description=AMMOcoin daemon
After=network.target

[Service]
Type=forking
User=ammocoin
Group=ammocoin
WorkingDirectory=/home/ammocoin
ExecStart=/usr/local/bin/ammocoind -conf=/home/ammocoin/.ammocoin/ammocoin.conf -datadir=/home/ammocoin/.ammocoin
ExecStop=/usr/local/bin/ammocoin-cli -conf=/home/ammocoin/.ammocoin/ammocoin.conf -datadir=/home/ammocoin/.ammocoin stop
Restart=always
RestartSec=10
KillMode=process

# Security measures
NoNewPrivileges=yes
PrivateTmp=yes
ProtectSystem=full
ProtectHome=read-only
ReadWritePaths=/home/ammocoin/.ammocoin

[Install]
WantedBy=multi-user.target
EOF

# Reload systemd and enable service
sudo systemctl daemon-reload
sudo systemctl enable ammocoin.service
```

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

### Verify Masternode Status
```bash
# Check masternode status
ammocoin-cli masternode status

# Check block synchronization
ammocoin-cli getblockchaininfo

# Check connection count
ammocoin-cli getconnectioncount

# Check masternode list (should show your node after activation)
ammocoin-cli masternode list
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
/home/ammocoin/.ammocoin/debug.log {
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
    ~/.ammocoin/wallet.dat \
    ~/.ammocoin/ammocoin.conf \
    ~/.ammocoin/masternode.conf 2>/dev/null

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
ammocoin-cli masternode status

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

# Add more nodes manually
ammocoin-cli addnode "ip.address.here:37020" "add"

# Check firewall
sudo ufw status
```

#### Masternode Not Starting
```bash
# Check masternode configuration
ammocoin-cli masternode debug

# Verify masternode private key
grep masternodeprivkey ~/.ammocoin/ammocoin.conf

# Check collateral transaction
ammocoin-cli masternode outputs
```

#### Service Issues
```bash
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

**Network Note**: Ensure your VPS has a stable internet connection. Intermittent connectivity can affect masternode rewards.