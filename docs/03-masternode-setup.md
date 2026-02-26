# 🏛️ AMMOcoin Masternode Setup Guide

Set up your own AMMOcoin masternode to earn higher rewards and contribute to network stability. This comprehensive guide covers everything from requirements to maintenance.

## 🤔 What is a Masternode?

A **masternode** is a specially configured node that provides enhanced services to the AMMOcoin network and earns premium rewards in return.

### Masternode Functions
- 🔒 **InstantSend** - Near-instant transaction confirmations
- 🛡️ **Enhanced Security** - Additional network protection layers
- 🗳️ **Governance Voting** - Participate in DAO decisions
- 💰 **Premium Rewards** - Higher returns than regular staking
- 🌐 **Network Stability** - Always-on full nodes

### Benefits vs Regular Staking
| Feature | Staking | Masternode |
|---------|---------|------------|
| **Minimum Coins** | 1 AMMO | 10,000 AMMO |
| **Annual Returns** | 8-12% | 15-25% |
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
- **🌐 Network**: Static IP address
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
Method: Purchase, mine, or stake to accumulate
Important: Must be in single transaction/address
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

# Get transaction output info
./ammocoin-cli gettransaction [txid]
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
OS: Ubuntu 20.04 LTS (recommended)
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

# Download latest release (replace with current version)
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Extract files
tar -xzf ammocoind-linux.tar.gz

# Make executable
chmod +x ammocoind ammocoin-cli

# Move to system path
sudo cp ammocoind ammocoin-cli /usr/local/bin/

# Verify installation
ammocoind --version
```

### Create Configuration
```bash
# Create data directory
mkdir ~/.ammocoin

# Create configuration file
nano ~/.ammocoin/ammocoin.conf
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
externalip=YOUR_SERVER_IP

# Network settings
port=37020
rpcport=51473

# Performance settings
maxconnections=256
```

## 🔑 Step 4: Generate Masternode Key

### On Local Wallet
```bash
# Generate masternode private key
./ammocoin-cli masternode genkey

# Get collateral output info
./ammocoin-cli masternode outputs
```

**Example Output**:
```
Masternode Private Key: 7X4j9K2m8P5n1Q3r6T8uV9wY2z5A7b4C8d6F3g9H1k4M7n
Collateral Output: "a1b2c3d4e5f6...transaction_hash" : "0"
```

### Update Server Configuration
```bash
# Edit server config with your key
nano ~/.ammocoin/ammocoin.conf

# Replace YOUR_MASTERNODE_PRIVATE_KEY with generated key
# Replace YOUR_SERVER_IP with your VPS IP address
```

## 🚀 Step 5: Configure Local Wallet

### Create Masternode Configuration
```bash
# Create masternode config file
nano ~/.ammocoin/masternode.conf
```

**Masternode Configuration Format**:
```
# Format: alias IP:port masternodeprivkey collateral_output_txid collateral_output_index
mn1 123.456.789.10:37020 7X4j9K2m8P5n1Q3r6T8uV9wY2z5A7b4C8d6F3g9H1k4M7n a1b2c3d4e5f6...transaction_hash 0
```

**Real Example**:
```
mynode01 192.168.1.100:37020 7rVTLnLh8WKG1JzVzjNJTurBNp8TKbwpEj9nDjHjbhvK2L a1b2c3d4e5f67890abcdef1234567890abcdef1234567890abcdef1234567890 0
```

## ⚡ Step 6: Start Masternode

### Start Remote Server
```bash
# SSH into your VPS
ssh ammocoin@your_server_ip

# Start daemon
ammocoind

# Wait for sync (check progress)
ammocoin-cli getblockchaininfo

# Check masternode status
ammocoin-cli masternode status
```

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
./ammocoin-cli masternode start-alias mn1

# Or start all masternodes
./ammocoin-cli masternode start-all

# Check status
./ammocoin-cli masternode list-conf
```

## 📊 Step 7: Monitor Masternode

### Check Masternode Status
```bash
# On remote server
ammocoin-cli masternode status

# Expected output for successful start:
{
  "outpoint": "a1b2c3d4e5f6...transaction_hash-0",
  "service": "192.168.1.100:37020",
  "status": "Masternode successfully started"
}
```

### Monitor from Local Wallet
```bash
# List all masternodes and their status
./ammocoin-cli masternode list

# Check specific masternode
./ammocoin-cli masternode list full | grep your_server_ip

# View masternode count
./ammocoin-cli masternode count
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
- **Block Reward**: ~5 AMMO per block (3-minute blocks)
- **Masternode Share**: 45% of block reward (~2.25 AMMO)
- **Selection**: Deterministic based on queue order
- **Frequency**: Approximately every 12-24 hours per masternode

### Expected Returns
```
Network Masternodes: 1,000 active
Your Position: Average
Rewards per Day: ~2.25 AMMO
Monthly Rewards: ~67.5 AMMO
Annual Rewards: ~821 AMMO
Annual Return: ~0.8% (on 10,000 AMMO)
```

### Reward Calculation
**Formula**: Daily Rewards = (Daily Blocks × MN Reward) / Active Masternodes
- Daily Blocks: 480 (1 block/3 minutes)
- MN Reward per Block: ~2.25 AMMO
- Daily Pool: 480 × 2.25 = 1,080 AMMO
- Your Share: 1,080 / Active MNs

## 🔧 Maintenance & Management

### Regular Maintenance Tasks

#### Daily Checks
```bash
# Check masternode status
ammocoin-cli masternode status

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
tail -f ~/.ammocoin/debug.log
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
3. **Confirm** server IP and port accessibility
4. **Restart** both local wallet and remote daemon

#### ❌ Sync Issues
**Symptoms**: getblockchaininfo shows wrong block height
**Solutions**:
```bash
# Stop daemon
ammocoin-cli stop

# Remove blockchain data (keep wallet.dat!)
rm -rf ~/.ammocoin/blocks ~/.ammocoin/chainstate

# Restart daemon
ammocoind

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

# Add peers manually
ammocoin-cli addnode "peer_ip:37020" "add"
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

STATUS=$(ammocoin-cli masternode status | jq -r '.status')

if [ "$STATUS" != "Masternode successfully started" ]; then
    echo "Masternode issue detected, restarting..."
    ammocoin-cli stop
    sleep 10
    ammocoind
fi
```

### Performance Optimization
- **SSD Storage** - Faster blockchain sync
- **More RAM** - Better performance under load
- **Better Network** - Reduced latency
- **Geographic Distribution** - Spread risk

## 💡 Economics & ROI Analysis

### Investment Breakdown
```
Initial Investment: 10,000 AMMO
VPS Costs: $10/month × 12 = $120/year
Annual Rewards: ~821 AMMO
Break-even: ~2.5 years (excluding AMMO price appreciation)
```

### Risk Factors
- **Price Volatility** - AMMO value fluctuation
- **Network Changes** - Reward structure updates
- **Technical Risk** - Server downtime, technical issues
- **Competition** - Increasing masternode count reduces rewards

### ROI Optimization
1. **Minimize** VPS costs through annual plans
2. **Maximize** uptime through monitoring
3. **Compound** rewards by reinvesting
4. **Scale** with additional masternodes

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