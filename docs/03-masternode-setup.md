# 🏛️ AMMOcoin Masternode Setup Guide

Set up your own AMMOcoin masternode to provide network services, vote in governance and receive the masternode payment set by the code. This comprehensive guide covers everything from requirements to maintenance.

> **v1.1.1 (upcoming):** v1.1.1 is a mandatory hard fork. The network runs Proof-of-Stake from block 2,776 and v1.1.1 nodes do not connect to v1.0 or v1.1.0 nodes, so every masternode (VPS and controller wallet) must upgrade. The default data folder is now `~/.ammocoincore` (Linux), `~/Library/Application Support/AMMOcoinCore` (macOS), `%APPDATA%\AMMOcoinCore` (Windows). See the [v1.1.1 release notes](release-notes/RELEASE_NOTES_v1.1.1.md).

## 🤔 What is a Masternode?

A **masternode** is a specially configured node that provides enhanced services to the AMMOcoin network. In return the code pays it the masternode share of a block when it reaches the front of the payment queue.

### Masternode Functions
- 🔒 **InstantSend** - Near-instant transaction confirmations
- 🛡️ **Enhanced Security** - Additional network protection layers
- 🗳️ **Governance Voting** - Participate in DAO decisions
- 💰 **Masternode Payment** - 3 AMMO per paid block (`GetMasternodePayment()`)
- 🌐 **Network Stability** - Always-on full nodes

### Benefits vs Regular Staking
| Feature | Staking | Masternode |
|---------|---------|------------|
| **Minimum Coins** | Any amount (600 confirmations to stake) | 10,000 AMMO |
| **Rewards** | 247 AMMO per staked block today (250 if no masternode is paid) | 3 AMMO per paid block |
| **Requirements** | Basic wallet | VPS + Technical setup |
| **Voting Rights** | No | Yes |
| **Network Services** | Basic | Enhanced |

## 💎 Masternode Requirements

### Financial Requirements
- **💰 Collateral**: Exactly 10,000 AMMO
- **💸 Operating Costs**: $5-20/month (VPS hosting)
- **⚡ Network Costs**: Minimal bandwidth usage

### Technical Requirements
- **🖥️ VPS/Server**: Linux-based virtual private server
- **💾 RAM**: Minimum 1GB, recommended 2GB+
- **💿 Storage**: 20GB+ SSD space
- **🌐 Network**: Static, public (routable) IPv4/IPv6 address, port **37020** open
- **🐧 OS**: Ubuntu 22.04 LTS or newer (24.04 tested) - the Linux binaries need glibc 2.34+
- **⏰ Uptime**: 99%+ availability required

### Knowledge Requirements
- Basic Linux command line skills
- Understanding of SSH and remote servers
- Ability to follow technical instructions
- Basic networking knowledge

## 🎯 Masternode Setup Process Overview

The setup involves **two main components**:

1. **🔑 Collateral Wallet** - Holds the 10,000 AMMO collateral
2. **🖥️ Remote Server** - Runs the masternode software 24/7

**Security Note**: Never store your 10,000 AMMO on the remote server!

## 📋 Step 1: Prepare Collateral Wallet

### Setup Local Wallet
1. **Download** and install latest AMMOcoin wallet
2. **Encrypt** wallet with strong password
3. **Backup** wallet.dat file securely
4. **Sync** wallet completely with network

### Acquire Collateral
```
Required: Exactly 10,000 AMMO
Method: Purchase or stake to accumulate (there is no mining after block 2,776)
Important: Must be a single 10,000 AMMO output (one transaction)
```

### Create Collateral Transaction
1. **Send** exactly 10,000 AMMO to yourself
2. **Use** a new address for collateral
3. **Wait** for 15 confirmations
4. **Record** transaction details

```bash
# Generate new address for collateral
./ammocoin-cli getnewaddress

# Send exactly 10,000 AMMO to this address
./ammocoin-cli sendtoaddress [new_address] 10000

# After 15 confirmations, list valid collateral outputs (txid + index)
./ammocoin-cli getmasternodeoutputs
```

## 🖥️ Step 2: VPS Server Setup

### Choose VPS Provider
**Recommended Providers**:
- **Vultr** - $5-10/month, good performance
- **DigitalOcean** - $5-10/month, reliable
- **Linode** - $5-10/month, excellent support
- **Contabo** - $4-8/month, budget option

### Server Specifications
```
OS: Ubuntu 24.04 LTS (tested) or 22.04 LTS - NOT 18.04/20.04 (glibc too old)
RAM: 2GB minimum, 4GB preferred
Storage: 20GB SSD minimum
Network: 1TB+ bandwidth
Location: Choose based on your timezone
```

### Initial Server Setup
```bash
# Connect to your VPS via SSH
ssh root@your_server_ip

# Update system packages
apt update && apt upgrade -y

# Create non-root user for security
adduser ammocoin
usermod -aG sudo ammocoin

# Switch to new user
su - ammocoin
```

## 🔧 Step 3: Install AMMOcoin Daemon

### Download and Install
```bash
# Create working directory
mkdir ~/ammocoin && cd ~/ammocoin

# Check glibc (must be 2.34 or newer)
ldd --version

# Download the v1.1.1 Linux release from the official GitHub release page
# (https://github.com/everquin/AMMOcoin/releases - v1.1.1 is upcoming; verify the SHA256 checksum)

# Extract files (file name depends on the release)
tar -xzf AMMOcoin-v1.1.1-Linux-x86_64.tar.gz

# Move to system path
sudo install -m 0755 -t /usr/local/bin bin/ammocoind bin/ammocoin-cli

# Verify installation
ammocoind --version
```

### Create Configuration
```bash
# Create data directory (v1.1.1 default)
mkdir ~/.ammocoincore

# Create configuration file
nano ~/.ammocoincore/ammocoin.conf
```

**Configuration File**:
```conf
# Basic settings
rpcuser=ammocoin_user
rpcpassword=your_strong_random_password
rpcallowip=127.0.0.1
daemon=1
server=1
listen=1

# Masternode settings
masternode=1
masternodeprivkey=YOUR_MASTERNODE_PRIVATE_KEY
masternodeaddr=YOUR_SERVER_IP:37020
externalip=YOUR_SERVER_IP

# Network settings
port=37020
rpcport=51473

# Performance settings
maxconnections=256

# Seed nodes
addnode=78.141.194.140:37020
addnode=104.238.165.56:37020
```

> **Important:** `YOUR_SERVER_IP` must be the VPS's **public, routable** IP and the port must be **37020**. `127.0.0.1` or private addresses (10.x, 172.16-31.x, 192.168.x) are rejected with `Invalid IP address`.

## 🔑 Step 4: Generate Masternode Key

### On Local Wallet
```bash
# Generate masternode private key
./ammocoin-cli createmasternodekey

# Get collateral output info (txid and index)
./ammocoin-cli getmasternodeoutputs
```

**Example Output**:
```
Masternode Private Key: 7X4j9K2m8P5n1Q3r6T8uV9wY2z5A7b4C8d6F3g9H1k4M7n
[ { "txhash": "a1b2c3d4e5f6...transaction_hash", "outputidx": 0 } ]
```

> There is no `masternode genkey` command in AMMOcoin - use `createmasternodekey`.

### Update Server Configuration
```bash
# Edit server config with your key
nano ~/.ammocoincore/ammocoin.conf

# Replace YOUR_MASTERNODE_PRIVATE_KEY with generated key
# Replace YOUR_SERVER_IP with your VPS IP address
```

## 🚀 Step 5: Configure Local Wallet

### Create Masternode Configuration
```bash
# Create masternode config file in the controller wallet's data folder
# Linux: ~/.ammocoincore/masternode.conf
# macOS: ~/Library/Application Support/AMMOcoinCore/masternode.conf
# Windows: %APPDATA%\AMMOcoinCore\masternode.conf
nano ~/.ammocoincore/masternode.conf
```

**Masternode Configuration Format**:
```
# Format: alias IP:port masternodeprivkey collateral_output_txid collateral_output_index
mn1 203.0.113.10:37020 7X4j9K2m8P5n1Q3r6T8uV9wY2z5A7b4C8d6F3g9H1k4M7n a1b2c3d4e5f6...transaction_hash 0
```

**Real Example** (use your VPS's public IP; private IPs like 192.168.x.x are rejected):
```
mynode01 203.0.113.10:37020 7rVTLnLh8WKG1JzVzjNJTurBNp8TKbwpEj9nDjHjbhvK2L a1b2c3d4e5f67890abcdef1234567890abcdef1234567890abcdef1234567890 0
```

## ⚡ Step 6: Start Masternode

### Start Remote Server
```bash
# SSH into your VPS
ssh ammocoin@your_server_ip

# Start daemon (or use the systemd service below)
ammocoind -daemon

# Wait for sync (check progress)
ammocoin-cli getblockchaininfo

# Check masternode status
ammocoin-cli getmasternodestatus
```

### Run as a systemd Service (recommended)
The unit **must** set `HOME`, otherwise the node exits with `Cannot find the Sapling parameters` (they live in `~/.ammocoin-params`). Tested unit, `/etc/systemd/system/ammocoind.service`:

```ini
[Unit]
Description=AMMOcoin daemon
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
User=root
Environment=HOME=/root
ExecStart=/opt/ammocoin-v1.1.1/bin/ammocoind -datadir=/root/.ammocoincore -daemon=0
ExecStop=/opt/ammocoin-v1.1.1/bin/ammocoin-cli -datadir=/root/.ammocoincore stop
Restart=on-failure
TimeoutStopSec=120

[Install]
WantedBy=multi-user.target
```

```bash
sudo systemctl daemon-reload
sudo systemctl enable --now ammocoind
```

If you run as a non-root user (e.g. `ammocoin`), set `User=ammocoin`, `Environment=HOME=/home/ammocoin`, and `-datadir=/home/ammocoin/.ammocoincore`, with the binaries path adjusted to where you installed them. Remove `daemon=1` from `ammocoin.conf` when using this unit.

### Start from Local Wallet

#### GUI Method
1. **Restart** local wallet
2. **Go to** Masternodes tab
3. **Find** your masternode
4. **Right-click** → "Start alias"
5. **Enter** wallet password
6. **Wait** for confirmation

#### Command Line Method
```bash
# Start specific masternode
./ammocoin-cli startmasternode alias false mn1

# Or start all masternodes in masternode.conf
./ammocoin-cli startmasternode all false

# Check status
./ammocoin-cli listmasternodeconf
```

## 📊 Step 7: Monitor Masternode

### Check Masternode Status
```bash
# On remote server
ammocoin-cli getmasternodestatus

# Expected output for successful start (abridged):
{
  "txhash": "a1b2c3d4e5f6...transaction_hash",
  "outputidx": 0,
  "netaddr": "203.0.113.10:37020",
  "message": "Masternode successfully started"
}
```

### Monitor from Local Wallet
```bash
# List all masternodes and their status
./ammocoin-cli listmasternodes

# Check specific masternode
./ammocoin-cli listmasternodes your_server_ip

# View masternode count
./ammocoin-cli getmasternodecount
```

### GUI Monitoring
- **Masternodes Tab** - Shows status and earnings
- **Status Indicators**:
  - 🟢 **ENABLED** - Active and earning
  - 🟡 **PRE_ENABLED** - Starting up
  - 🔴 **EXPIRED** - Needs restart
  - ⚫ **MISSING** - Connection issues

## 💰 Masternode Rewards

### Reward Distribution
- **Block Reward**: 250 AMMO per block today (3-minute blocks); the v1.1.1 fork keeps the original schedule (225 AMMO from block 86,401, 45 AMMO from 151,201, lower later)
- **Masternode Payment**: Fixed 3 AMMO per paid block (the staker keeps the rest, 247 AMMO today); it becomes 6 AMMO only after block 3,715,200
- **Selection**: Deterministic based on queue order
- **Frequency**: Depends on how many masternodes are active

### Reward Calculation
**Formula**: Daily Rewards ≈ (Daily Blocks × MN Payment) / Active Masternodes
- Daily Blocks: 480 (1 block/3 minutes)
- MN Payment per Block: 3 AMMO
- Daily Pool: 480 × 3 = 1,440 AMMO
- Your Share: 1,440 / Active MNs

Example: with 100 active masternodes, each is paid about 14.4 AMMO/day on average (one 3 AMMO payment roughly every 100 blocks, about every 5 hours). Actual results vary with the active count and your uptime.

## 🔧 Maintenance & Management

### Regular Maintenance Tasks

#### Daily Checks
```bash
# Check masternode status
ammocoin-cli getmasternodestatus

# Verify blockchain sync
ammocoin-cli getblockchaininfo

# Check peer connections
ammocoin-cli getconnectioncount
```

#### Weekly Maintenance
```bash
# Update system packages
sudo apt update && sudo apt upgrade -y

# Check disk space
df -h

# Monitor logs
tail -f ~/.ammocoincore/debug.log
```

#### Monthly Tasks
- **Update** AMMOcoin software if new version available
- **Review** earnings and performance
- **Check** VPS billing and renewal dates
- **Backup** configuration files

### Troubleshooting Common Issues

#### ❌ Masternode Not Starting
**Symptoms**: Status shows "MISSING" or "EXPIRED"
**Solutions**:
1. **Verify** collateral has 15+ confirmations
2. **Check** masternode.conf syntax
3. **Confirm** server IP is public and the port is 37020 (`Invalid IP address` means 127.0.0.1 or a private IP was used)
4. **Restart** both local wallet and remote daemon

#### ❌ Sync Issues
**Symptoms**: getblockchaininfo shows wrong block height
**Solutions**:
```bash
# Stop daemon
ammocoin-cli stop

# Remove blockchain data (keep wallet.dat!)
rm -rf ~/.ammocoincore/blocks ~/.ammocoincore/chainstate

# Restart daemon
ammocoind -daemon

# Wait for resync
```

#### ❌ Network Connectivity
**Symptoms**: Low peer count, connection issues
**Solutions**:
```bash
# Check firewall
sudo ufw status

# Allow AMMOcoin port
sudo ufw allow 37020

# Add seed nodes manually
ammocoin-cli addnode "78.141.194.140:37020" "add"
ammocoin-cli addnode "104.238.165.56:37020" "add"
```

### Security Hardening

#### Server Security
```bash
# Change SSH port
sudo nano /etc/ssh/sshd_config
# Change Port 22 to custom port

# Disable root login
# Set PermitRootLogin no

# Setup fail2ban
sudo apt install fail2ban
sudo systemctl enable fail2ban
```

#### Firewall Configuration
```bash
# Setup basic firewall
sudo ufw default deny incoming
sudo ufw default allow outgoing
sudo ufw allow your_ssh_port
sudo ufw allow 37020
sudo ufw enable
```

## 📈 Advanced Masternode Strategies

### Multiple Masternodes
- **Scale** with additional 10,000 AMMO collaterals
- **Distribute** across different VPS providers
- **Stagger** start times for better queue position
- **Monitor** performance across all nodes

### Automation Scripts
```bash
#!/bin/bash
# masternode_monitor.sh
# Check masternode status and restart if needed

STATUS=$(ammocoin-cli getmasternodestatus | jq -r '.message')

if [ "$STATUS" != "Masternode successfully started" ]; then
    echo "Masternode issue detected, restarting..."
    sudo systemctl restart ammocoind
fi
```

### Performance Optimization
- **SSD Storage** - Faster blockchain sync
- **More RAM** - Better performance under load
- **Better Network** - Reduced latency
- **Geographic Distribution** - Spread risk

## 💡 How Masternode Payments Work

### What the code does
```
Collateral:        10,000 AMMO, locked in your own wallet (it is not spent or sent to anyone)
Payment per block: 3 AMMO to the masternode at the front of the queue (GetMasternodePayment())
Payment frequency: about once every N blocks, where N = number of enabled masternodes
Running costs:     your own server (VPS) costs, paid by you to your hosting provider
```

What one masternode receives depends on how many others are enabled and on keeping the node online; the code sets the per-block amount, not what any operator will receive over time. The AMMOcoin project publishes no price for AMMO and makes no claim about what AMMO is or will be worth.

### Things that change payments
- **Masternode Count** - More enabled masternodes means each one is paid less often
- **Network Changes** - Consensus changes to the reward schedule (announced as such)
- **Downtime** - A masternode that drops off the list stops being paid until it is enabled again

### Keeping a Masternode Paid
1. **Maximize** uptime through monitoring
2. **Keep** the node on the current release
3. **Do not move** the collateral UTXO (moving it disables the masternode)

## 🆘 Support & Resources

### Documentation Links
- [Node Setup Guide](./04-node-setup.md)
- [Terminal Commands](./05-terminal-commands.md)
- [Troubleshooting](./09-troubleshooting.md)

### Community Support
- **Discord**: #masternode-support
- **Telegram**: @AMMOcoinMasternodes
- **Forum**: forum.ammocoin.org/masternodes

### Emergency Contacts
- **Technical Issues**: support@ammocoin.org
- **Security Issues**: security@ammocoin.org

---

## ✅ Masternode Setup Checklist

### Preparation
- [ ] 10,000 AMMO acquired and confirmed
- [ ] VPS purchased and configured
- [ ] Local wallet encrypted and backed up
- [ ] SSH access to server confirmed

### Configuration
- [ ] Collateral transaction created (exactly 10,000 AMMO)
- [ ] 15+ confirmations on collateral
- [ ] Masternode private key generated
- [ ] Server daemon installed and configured
- [ ] masternode.conf file created locally

### Activation
- [ ] Remote daemon started and synced
- [ ] Masternode started from local wallet
- [ ] Status shows "ENABLED"
- [ ] Listed in active masternode list
- [ ] Monitoring setup configured

### Ongoing
- [ ] Daily status checks scheduled
- [ ] Weekly maintenance routine established
- [ ] Backup procedures documented
- [ ] Emergency contacts saved

**🎉 Congratulations! Your AMMOcoin masternode is now active and earning rewards.**

---

*Next: Learn about [Node Setup](./04-node-setup.md) for advanced network participation.*