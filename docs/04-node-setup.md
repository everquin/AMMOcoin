# 🌐 AMMOcoin Node Setup Guide

Set up your own AMMOcoin full node to contribute to network decentralization, improve privacy, and gain complete control over your transactions.

> **v1.1.1 (upcoming):** mandatory hard fork. Proof-of-Stake from block 2,776 (no mining after), new network magic so v1.1.1 nodes do not connect to v1.0 or v1.1.0 nodes, and a new default data folder (`~/.ammocoin11`, `~/Library/Application Support/AMMOcoin11`, `%APPDATA%\AMMOcoin11`). Linux binaries need glibc 2.34+ (Ubuntu 22.04 or newer). See the [v1.1.1 release notes](release-notes/RELEASE_NOTES_v1.1.1_DRAFT.md).

## 🤔 What is a Full Node?

A **full node** is a program that validates transactions and blocks on the AMMOcoin network. Unlike lightweight wallets, full nodes:

- 📋 **Download** the complete blockchain
- ✅ **Validate** all transactions and blocks
- 🌐 **Relay** transactions and blocks to peers
- 🔒 **Enforce** network consensus rules
- 🛡️ **Strengthen** network security and decentralization

### Node vs Wallet vs Masternode
| Feature | Light Wallet | Full Node | Masternode |
|---------|-------------|-----------|------------|
| **Blockchain** | Headers only | Full download | Full download |
| **Validation** | SPV | Complete | Complete |
| **Requirements** | Low | Medium | High |
| **Collateral** | None | None | 10,000 AMMO |
| **Rewards** | Staking only | Staking only | MN + Staking |
| **Voting** | No | No | Yes |

## 🎯 Why Run a Full Node?

### Benefits for You
- 🔐 **Maximum Privacy** - No third-party dependency
- ⚡ **Fastest Sync** - Instant transaction validation
- 🛡️ **Security** - Validate all rules yourself
- 🎛️ **Control** - Complete autonomy over transactions
- 📊 **Data Access** - Full blockchain analytics

### Benefits for Network
- 🌍 **Decentralization** - Reduces single points of failure
- 🔗 **Redundancy** - More copies of the blockchain
- 🚀 **Performance** - More nodes = better network speed
- 🛡️ **Security** - Harder to attack distributed network

## 💻 System Requirements

### Minimum Requirements
- **CPU**: 1 core, 1GHz processor
- **RAM**: 2GB (4GB recommended)
- **Storage**: 50GB available space
- **Network**: Broadband internet connection
- **OS**: Windows 10, macOS 10.14, Ubuntu 22.04+ (24.04 tested)

> **Linux:** the v1.1.1 binaries need **glibc 2.34 or newer** (`ldd --version`). Ubuntu 18.04 and 20.04 cannot run them - upgrade or reinstall the OS first.

### Recommended Specifications
- **CPU**: 2+ cores, 2GHz+ processor
- **RAM**: 8GB for optimal performance
- **Storage**: 100GB+ SSD (much faster sync)
- **Network**: Unlimited or high-cap data plan
- **Uptime**: 24/7 for maximum network contribution

### Hardware Recommendations
- **Desktop**: Any modern computer
- **VPS**: $10-20/month cloud server
- **Raspberry Pi**: Pi 4 with 4GB+ RAM
- **Mini PC**: Intel NUC or similar

## 📥 Installation Methods

### Method 1: Pre-compiled Binaries (Recommended)

#### Windows Installation
```powershell
# Download from GitHub releases
# Extract to C:\AMMOcoin\
# Add to PATH environment variable

# Create data directory (v1.1.1 default)
mkdir %APPDATA%\AMMOcoin11

# Create shortcut with parameters
"C:\AMMOcoin\ammocoind.exe" -daemon
```

#### macOS Installation
```bash
# Download the macOS release from GitHub releases
# Install AMMOcoin.app to Applications (or extract ammocoind/ammocoin-cli)

# Create data directory (v1.1.1 default)
mkdir ~/Library/Application\ Support/AMMOcoin11
```

#### Linux Installation (Ubuntu/Debian)
```bash
# Check glibc (must be 2.34+)
ldd --version

# Download the v1.1.1 Linux release from https://github.com/everquin/AMMOcoin/releases
# (v1.1.1 is upcoming - verify the published SHA256 checksum)

# Extract and install (file name depends on the release)
tar -xzf AMMOcoin-v1.1.1-Linux-x86_64.tar.gz
sudo install -m 0755 -t /usr/local/bin bin/ammocoind bin/ammocoin-cli

# Create data directory (v1.1.1 default)
mkdir ~/.ammocoin11

# Verify installation
ammocoind --version
```

### Method 2: Build from Source
```bash
# Install dependencies (Ubuntu/Debian)
sudo apt update
sudo apt install build-essential libtool autotools-dev automake pkg-config
sudo apt install libssl-dev libevent-dev bsdmainutils python3
sudo apt install libboost-all-dev libdb4.8-dev libdb4.8++-dev

# Clone repository
git clone https://github.com/everquin/AMMOcoin.git
cd ammocoin

# Build
./autogen.sh
./configure
make -j$(nproc)
sudo make install
```

## ⚙️ Node Configuration

### Basic Configuration File

Create `~/.ammocoin11/ammocoin.conf` (Linux), `~/Library/Application Support/AMMOcoin11/ammocoin.conf` (macOS) or `%APPDATA%\AMMOcoin11\ammocoin.conf` (Windows):

```conf
# Basic node configuration
daemon=1
server=1
listen=1

# Network settings
port=37020
rpcport=51473
maxconnections=50

# Performance settings
dbcache=450
maxmempool=300

# Logging
debug=0
logtimestamps=1

# RPC security (if needed)
rpcuser=your_username
rpcpassword=your_secure_password
rpcallowip=127.0.0.1

# Seed nodes
addnode=78.141.194.140:37020
addnode=104.238.165.56:37020

# Optional: Enable staking
staking=1

# Optional: Prune old blocks (saves space)
# prune=2000
```

### Advanced Configuration Options

#### High-Performance Node
```conf
# Optimized for fast, powerful hardware
daemon=1
server=1
listen=1

# Network optimization
port=37020
maxconnections=125
timeout=30000

# Performance tuning
dbcache=2048
maxmempool=1024
par=4

# Bandwidth optimization
maxreceivebuffer=5000
maxsendbuffer=1000

# Connection management
# seed1 and seed2.ammocoin.org
addnode=78.141.194.140:37020
addnode=104.238.165.56:37020
```

#### Low-Resource Node
```conf
# Optimized for limited hardware (Raspberry Pi)
daemon=1
server=1
listen=1

# Conservative resource usage
maxconnections=20
dbcache=100
maxmempool=50

# Pruning to save space
prune=2000

# Limit bandwidth
maxreceivebuffer=1000
maxsendbuffer=1000
```

#### Privacy-Focused Node
```conf
# Enhanced privacy configuration
daemon=1
server=1
listen=1

# Tor integration
proxy=127.0.0.1:9050
onion=127.0.0.1:9050
onlynet=onion

# Disable unnecessary services
upnp=0
natpmp=0
discover=0

# Randomize outbound connections
seednode=0
```

## 🚀 Starting Your Node

### First-Time Startup

#### Linux/macOS
```bash
# Start daemon
ammocoind -daemon

# Check if running
ammocoin-cli getinfo

# View sync progress
ammocoin-cli getblockchaininfo
```

#### Windows
```powershell
# Start daemon
ammocoind.exe

# Or run as service
# Use NSSM or similar service wrapper
```

### Monitoring Initial Sync

The first sync downloads the entire blockchain:

```bash
# Check sync progress
ammocoin-cli getblockchaininfo | grep -E "(blocks|headers|verificationprogress)"

# Monitor in real-time
watch -n 30 'ammocoin-cli getblockchaininfo | grep verificationprogress'

# Expected sync time:
# HDD: 4-12 hours
# SSD: 1-4 hours
# VPS: 1-2 hours
```

### Sync Progress Indicators
```json
{
  "blocks": 3500,             // Current blocks downloaded (past 2,775 = on the v1.1.1 PoS chain)
  "headers": 3500,            // Headers downloaded
  "verificationprogress": 0.95 // 95% complete
}
```

## 🔧 Node Management

### System Service Setup

#### Linux (systemd)
```bash
# Create service file
sudo nano /etc/systemd/system/ammocoind.service
```

```ini
[Unit]
Description=AMMOcoin daemon
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
User=root
Environment=HOME=/root
ExecStart=/opt/ammocoin-v1.1.1/bin/ammocoind -datadir=/root/.ammocoin11 -daemon=0
ExecStop=/opt/ammocoin-v1.1.1/bin/ammocoin-cli -datadir=/root/.ammocoin11 stop
Restart=on-failure
TimeoutStopSec=120

[Install]
WantedBy=multi-user.target
```

> **`Environment=HOME=...` is required.** Without it the node exits with `Cannot find the Sapling parameters` (they are looked up in `$HOME/.ammocoin-params`). For a non-root user set `User=ammocoin`, `Environment=HOME=/home/ammocoin` and `-datadir=/home/ammocoin/.ammocoin11`. Remove `daemon=1` from `ammocoin.conf` when using this unit, and adjust the binary path if you installed to `/usr/local/bin`.

```bash
# Enable and start service
sudo systemctl daemon-reload
sudo systemctl enable ammocoind
sudo systemctl start ammocoind

# Check status
sudo systemctl status ammocoind

# View logs
sudo journalctl -u ammocoind -f
```

#### macOS (launchd)
```bash
# Create plist file
sudo nano /Library/LaunchDaemons/org.ammocoin.ammocoind.plist
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>org.ammocoin.ammocoind</string>
    <key>ProgramArguments</key>
    <array>
        <string>/usr/local/bin/ammocoind</string>
    </array>
    <key>RunAtLoad</key>
    <true/>
    <key>KeepAlive</key>
    <true/>
</dict>
</plist>
```

```bash
# Load service
sudo launchctl load /Library/LaunchDaemons/org.ammocoin.ammocoind.plist

# Start service
sudo launchctl start org.ammocoin.ammocoind
```

### Daily Operations

#### Health Checks
```bash
# Node status
ammocoin-cli getinfo

# Network connectivity
ammocoin-cli getpeerinfo | grep addr

# Blockchain sync
ammocoin-cli getblockchaininfo

# Memory usage
ammocoin-cli getmemoryinfo

# Uptime
ammocoin-cli uptime
```

#### Maintenance Commands
```bash
# Graceful shutdown
ammocoin-cli stop

# Force restart (if needed)
pkill ammocoind && sleep 5 && ammocoind -daemon

# Check log files
tail -f ~/.ammocoin11/debug.log

# Disk space check
df -h ~/.ammocoin11/
```

## 🔒 Security Hardening

### Network Security

#### Firewall Configuration
```bash
# Ubuntu/Debian UFW
sudo ufw allow 37020/tcp comment "AMMOcoin P2P"
sudo ufw allow ssh
sudo ufw enable

# CentOS/RHEL firewalld
sudo firewall-cmd --permanent --add-port=37020/tcp
sudo firewall-cmd --reload
```

#### Port Configuration
```conf
# Default ports
port=37020        # P2P network port
rpcport=51473     # RPC port (localhost only)

# Custom ports (if needed)
port=47020
rpcport=47021
```

### Access Control

#### RPC Security
```conf
# Secure RPC configuration
rpcuser=unique_username_$(openssl rand -hex 4)
rpcpassword=$(openssl rand -base64 32)
rpcallowip=127.0.0.1

# Disable RPC if not needed
server=0
```

#### File Permissions
```bash
# Secure configuration files
chmod 600 ~/.ammocoin11/ammocoin.conf
chmod 700 ~/.ammocoin11/

# Secure wallet file
chmod 600 ~/.ammocoin11/wallet.dat
```

### Monitoring & Alerts

#### Log Monitoring
```bash
# Monitor for errors
tail -f ~/.ammocoin11/debug.log | grep -i error

# Check for warnings
grep -i warning ~/.ammocoin11/debug.log

# Monitor connections
grep -i "connection" ~/.ammocoin11/debug.log | tail -20
```

#### Automated Monitoring Script
```bash
#!/bin/bash
# node_monitor.sh

# Check if node is running
if ! pgrep ammocoind > /dev/null; then
    echo "ERROR: AMMOcoin daemon not running!"
    # Restart or alert
fi

# Check sync status
BLOCKS=$(ammocoin-cli getblockcount 2>/dev/null)
CONNECTIONS=$(ammocoin-cli getconnectioncount 2>/dev/null)

if [ "$CONNECTIONS" -lt 3 ]; then
    echo "WARNING: Low peer connections: $CONNECTIONS"
fi

echo "Node Status: $BLOCKS blocks, $CONNECTIONS peers"
```

## 🔧 Troubleshooting

### Common Issues & Solutions

#### Sync Problems
```bash
# Node not syncing
# Check peers
ammocoin-cli getpeerinfo

# Add seed nodes manually
ammocoin-cli addnode "78.141.194.140:37020" "add"
ammocoin-cli addnode "104.238.165.56:37020" "add"

# Restart with fresh peer connections
ammocoin-cli stop
rm ~/.ammocoin11/peers.dat
ammocoind -daemon
```

#### Performance Issues
```bash
# Slow performance
# Increase database cache
echo "dbcache=1024" >> ~/.ammocoin11/ammocoin.conf

# Check disk space
df -h ~/.ammocoin11/

# Monitor resource usage
top -p $(pgrep ammocoind)
```

#### Network Connectivity
```bash
# Port not accessible
# Check firewall
sudo ufw status

# Test port connectivity
telnet your_ip 37020

# Check network binding
netstat -tlnp | grep 37020
```

### Debug Commands
```bash
# Verbose logging
ammocoin-cli setdebug net true

# Check database integrity
ammocoin-cli verifychain

# Restart with reindex
ammocoind -reindex

# Check for corrupted blocks
ammocoin-cli getchaintips
```

## 📊 Node Optimization

### Performance Tuning

#### SSD Optimization
```conf
# Optimize for SSD storage
dbcache=2048
checkblocks=50
checklevel=1
```

#### RAM Optimization
```bash
# Calculate optimal dbcache
RAM_GB=$(free -g | awk '/^Mem:/{print $2}')
DBCACHE=$((RAM_GB * 256))
echo "Recommended dbcache: $DBCACHE"
```

#### CPU Optimization
```conf
# Multi-core systems
par=4                    # Parallel script verification
checkblocks=0           # Skip startup verification
assumevalid=latest_hash # Skip signature verification
```

### Bandwidth Management

#### Connection Limits
```conf
# Conservative bandwidth
maxconnections=20
maxreceivebuffer=1000
maxsendbuffer=1000

# High bandwidth
maxconnections=125
maxreceivebuffer=5000
maxsendbuffer=5000
```

#### Data Usage Monitoring
```bash
# Monitor network usage
ammocoin-cli getnettotals

# Bandwidth per peer
ammocoin-cli getpeerinfo | grep -E "(addr|bytessent|bytesrecv)"
```

## 🌍 Contributing to Network Health

### Best Practices

#### Stable Operation
- ✅ **24/7 Uptime** - Keep node running continuously
- ✅ **Stable Connection** - Reliable internet required
- ✅ **Updated Software** - Install updates promptly
- ✅ **Resource Monitoring** - Prevent resource exhaustion

#### Network Support
- 🌐 **Allow Incoming** - Configure firewall for port 37020
- 🔗 **Seed New Nodes** - Help new users sync faster
- 📡 **Geographic Distribution** - Run nodes in different regions
- 🔄 **Relay Transactions** - Process and forward network traffic

### Advanced Configurations

#### Seed Node Setup
```conf
# Configure as seed node
daemon=1
server=1
listen=1
discover=1

# Accept many connections
maxconnections=500

# Optimize for relaying
blocksonly=0
peerbloomfilters=1
```

#### Archive Node
```conf
# Keep full blockchain history
prune=0
txindex=1

# Enable advanced RPC
server=1
rest=1

# Performance for queries
dbcache=4096
```

## 📈 Monitoring & Analytics

### Node Statistics
```bash
# Network statistics
ammocoin-cli getnetworkinfo

# Blockchain statistics
ammocoin-cli getblockchaininfo

# Memory usage
ammocoin-cli getmemoryinfo

# Peer analysis
ammocoin-cli getpeerinfo | jq '.[] | {addr, version, subver, bytessent, bytesrecv}'
```

### Performance Metrics
```bash
# Blocks processed per hour
START_BLOCK=$(ammocoin-cli getblockcount)
sleep 3600
END_BLOCK=$(ammocoin-cli getblockcount)
echo "Processed: $((END_BLOCK - START_BLOCK)) blocks/hour"

# Average block size
ammocoin-cli getblockstats | jq .avgblocksize

# Transaction throughput
ammocoin-cli getmempoolinfo | jq .size
```

## 💡 Use Cases & Applications

### Personal Use
- **Wallet Backend** - Use as backend for personal wallet
- **Transaction Privacy** - Validate transactions privately
- **Educational** - Learn about blockchain technology
- **Development** - Test applications against full node

### Business Applications
- **Exchange Integration** - Validate deposits/withdrawals
- **Merchant Services** - Accept payments with confidence
- **Analytics** - Analyze blockchain data
- **Service Providers** - Build services on reliable infrastructure

### Network Services
- **Explorer Backend** - Power blockchain explorer
- **API Services** - Provide blockchain APIs
- **Research** - Academic blockchain research
- **Archive Services** - Preserve blockchain history

---

## ✅ Node Setup Checklist

### Initial Setup
- [ ] System requirements verified
- [ ] AMMOcoin software downloaded and installed
- [ ] Configuration file created
- [ ] Initial blockchain sync completed
- [ ] Network connectivity confirmed

### Security & Optimization
- [ ] Firewall configured (port 37020 open)
- [ ] RPC access secured
- [ ] File permissions set correctly
- [ ] Performance tuning applied
- [ ] Monitoring scripts deployed

### Ongoing Maintenance
- [ ] Regular health checks scheduled
- [ ] Update notifications configured
- [ ] Backup procedures established
- [ ] Log rotation configured
- [ ] Resource monitoring active

**🌐 Congratulations! Your AMMOcoin full node is now contributing to network security and decentralization.**

---

*Next: Master [Terminal Commands](./05-terminal-commands.md) for advanced node management.*