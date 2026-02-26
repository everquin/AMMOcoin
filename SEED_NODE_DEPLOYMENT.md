# AMMOcoin v1.1.0 Seed Node Deployment Guide

**For production seed nodes running Ubuntu Linux**

---

## Quick Deploy with Claude

### Option 1: Paste Prompt to Claude (Recommended)

SSH into your seed node VM and start a Claude Code session, then paste this prompt:

```
I need to set up AMMOcoin v1.1.0 on this seed node. This is a production deployment.

IMPORTANT CONTEXT:
- This is a seed node that will help bootstrap the v1.1.0 network
- We're migrating from v1.0 to v1.1.0 (new genesis block)
- The node is running on Ubuntu (check with: lsb_release -a)
- I may have a v1.0 node running that needs to be stopped

TASK:
1. Check if any AMMOcoin v1.0 process is running and stop it gracefully
2. Backup the v1.0 wallet if it exists (to ~/ammocoin-v1.0-backup/)
3. Download AMMOcoin v1.1.0 Linux binaries from GitHub release
4. Verify the SHA256 checksum matches the official release
5. Extract binaries to /opt/ammocoin/v1.1.0/
6. Create fresh data directory at ~/.ammocoin-v1.1.0/
7. Create ammocoin.conf with seed node configuration
8. Start ammocoind daemon
9. Verify the node is running and show status

RELEASE INFORMATION:
- GitHub Release: https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0
- Binary: AMMOcoin-v1.1.0-Linux-x86_64.tar.gz (112 MB)
- Expected SHA256: 082f1eb063b3098d0deaef9a8550a9965cb341d771140c4222fd33944c0f5509
- Genesis Block Hash: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2

SEED NODE CONFIGURATION REQUIREMENTS:
- Listen on all interfaces (listen=1)
- Enable RPC server (server=1)
- Set maxconnections=125 (seed nodes need higher limits)
- Enable transaction indexing (txindex=1)
- Set RPC credentials with strong password
- Configure P2P port: 37020
- Configure RPC port: 51473

NETWORK PORTS:
- P2P: 37020
- RPC: 51473

After setup, provide me with:
1. The node's public IP address
2. Confirmation that the daemon is running
3. Output of: ./ammocoin-cli getinfo
4. Output of: ./ammocoin-cli getpeerinfo
5. Output of: ./ammocoin-cli getblockchaininfo

Make sure to use proper permissions and security practices. This is a production seed node.
```

---

## Option 2: Manual Deployment

### Prerequisites

- Ubuntu 20.04 or 22.04 (recommended) or 24.04
- Root or sudo access
- At least 10GB free disk space
- Ports 37020 and 51473 open in firewall

---

### Step 1: Stop Existing v1.0 Node (if running)

```bash
# Check if v1.0 is running
ps aux | grep ammocoin

# If running, stop it gracefully
pkill -SIGTERM ammocoind

# Wait for it to shut down (up to 60 seconds)
sleep 60

# Verify it stopped
ps aux | grep ammocoin
```

---

### Step 2: Backup v1.0 Wallet (if exists)

```bash
# Create backup directory
mkdir -p ~/ammocoin-v1.0-backup

# Backup wallet and config
if [ -d ~/.ammocoin ]; then
  cp ~/.ammocoin/wallet.dat ~/ammocoin-v1.0-backup/ 2>/dev/null || true
  cp ~/.ammocoin/ammocoin.conf ~/ammocoin-v1.0-backup/ 2>/dev/null || true
  echo "✅ v1.0 data backed up to ~/ammocoin-v1.0-backup/"
else
  echo "ℹ️  No v1.0 data directory found"
fi
```

---

### Step 3: Download v1.1.0 Binaries

```bash
# Create installation directory
sudo mkdir -p /opt/ammocoin/v1.1.0
cd /tmp

# Download binaries
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Download checksums
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt
```

---

### Step 4: Verify Checksum

```bash
# Calculate SHA256
echo "Verifying checksum..."
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Expected: 082f1eb063b3098d0deaef9a8550a9965cb341d771140c4222fd33944c0f5509
# Compare with checksums file
grep "Linux-x86_64" AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt

# If they match, proceed. If not, STOP and investigate!
```

---

### Step 5: Extract and Install

```bash
# Extract
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Move binaries
sudo mv bin/* /opt/ammocoin/v1.1.0/

# Make executable
sudo chmod +x /opt/ammocoin/v1.1.0/*

# Create symlinks for easy access
sudo ln -sf /opt/ammocoin/v1.1.0/ammocoind /usr/local/bin/ammocoind
sudo ln -sf /opt/ammocoin/v1.1.0/ammocoin-cli /usr/local/bin/ammocoin-cli
sudo ln -sf /opt/ammocoin/v1.1.0/ammocoin-tx /usr/local/bin/ammocoin-tx

# Verify installation
ammocoind --version
```

---

### Step 6: Create Data Directory and Configuration

```bash
# Create fresh v1.1.0 data directory
mkdir -p ~/.ammocoin-v1.1.0

# Generate strong RPC password
RPC_PASSWORD=$(openssl rand -base64 32)

# Create ammocoin.conf
cat > ~/.ammocoin-v1.1.0/ammocoin.conf <<EOF
# AMMOcoin v1.1.0 Seed Node Configuration
# Generated: $(date)

# Network Settings
listen=1
server=1
daemon=1
maxconnections=125

# RPC Settings
rpcuser=ammocoin_rpc
rpcpassword=${RPC_PASSWORD}
rpcallowip=127.0.0.1
rpcport=51473

# P2P Settings
port=37020

# Performance
dbcache=512
maxmempool=300

# Indexing (required for seed nodes)
txindex=1
addressindex=1
timestampindex=1
spentindex=1

# Logging
debug=0
printtoconsole=0
EOF

echo "✅ Configuration created at ~/.ammocoin-v1.1.0/ammocoin.conf"
echo "⚠️  RPC Password: ${RPC_PASSWORD}"
echo "    Save this password securely!"
```

---

### Step 7: Configure Firewall

```bash
# Allow P2P port
sudo ufw allow 37020/tcp comment 'AMMOcoin P2P'

# RPC port should NOT be exposed to internet
# Only allow from localhost (already configured in ammocoin.conf)

# Verify firewall rules
sudo ufw status
```

---

### Step 8: Start the Daemon

```bash
# Start ammocoind
ammocoind -datadir=~/.ammocoin-v1.1.0

# Wait for startup (5-10 seconds)
sleep 10

# Check if it's running
ps aux | grep ammocoind

# Should see: ammocoind -datadir=/home/[user]/.ammocoin-v1.1.0
```

---

### Step 9: Verify Node is Running

```bash
# Check blockchain info
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockchaininfo

# Expected output should show:
# - "chain": "main"
# - "blocks": 0 (or higher if syncing)
# - "bestblockhash": "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2" (genesis)

# Get node info
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getinfo

# Check peer connections
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getpeerinfo

# Get network info
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getnetworkinfo
```

---

### Step 10: Verify Genesis Block

```bash
# Get block hash for block 0
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockhash 0

# Should return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2

# Get block details
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblock $(ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockhash 0)

# Verify:
# - "hash": "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
# - "merkleroot": "a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab"
# - "nonce": 1299391
```

---

### Step 11: Set Up Auto-Start (Optional but Recommended)

```bash
# Create systemd service
sudo tee /etc/systemd/system/ammocoind.service > /dev/null <<EOF
[Unit]
Description=AMMOcoin v1.1.0 Daemon
After=network.target

[Service]
Type=forking
User=$(whoami)
Group=$(whoami)
WorkingDirectory=/opt/ammocoin/v1.1.0
ExecStart=/opt/ammocoin/v1.1.0/ammocoind -datadir=/home/$(whoami)/.ammocoin-v1.1.0 -daemon
ExecStop=/opt/ammocoin/v1.1.0/ammocoin-cli -datadir=/home/$(whoami)/.ammocoin-v1.1.0 stop
Restart=on-failure
RestartSec=30

[Install]
WantedBy=multi-user.target
EOF

# Reload systemd
sudo systemctl daemon-reload

# Enable auto-start
sudo systemctl enable ammocoind

# Check status
sudo systemctl status ammocoind
```

---

### Step 12: Monitor the Node

```bash
# Watch the log file
tail -f ~/.ammocoin-v1.1.0/debug.log

# Check sync status every 10 seconds
watch -n 10 'ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockchaininfo | grep -E "(blocks|verificationprogress)"'

# Monitor connections
watch -n 5 'ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getconnectioncount'
```

---

## Useful Commands

### Start/Stop Node

```bash
# Start
ammocoind -datadir=~/.ammocoin-v1.1.0

# Stop (graceful)
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 stop

# Stop (force, only if graceful fails)
pkill -SIGTERM ammocoind
```

### Get Node Status

```bash
# Quick status
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getinfo

# Blockchain info
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockchaininfo

# Network info
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getnetworkinfo

# Peer info
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getpeerinfo

# Connection count
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getconnectioncount
```

### Create Alias (Optional)

```bash
# Add to ~/.bashrc
echo 'alias ammocoin-cli="ammocoin-cli -datadir=~/.ammocoin-v1.1.0"' >> ~/.bashrc
source ~/.bashrc

# Now you can just use:
ammocoin-cli getinfo
```

---

## Troubleshooting

### Node won't start

```bash
# Check if port is already in use
sudo netstat -tulpn | grep 37020

# Check log file for errors
tail -100 ~/.ammocoin-v1.1.0/debug.log

# Verify binaries are executable
ls -lh /opt/ammocoin/v1.1.0/
```

### No connections

```bash
# Verify firewall allows P2P port
sudo ufw status | grep 37020

# Test if port is reachable
curl -v telnet://YOUR_PUBLIC_IP:37020

# Check if node is listening
sudo netstat -tulpn | grep ammocoind
```

### Wrong genesis block

```bash
# If you see a different genesis hash, you're on the wrong network
# Stop the node
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 stop

# Delete blockchain data (keeps wallet)
rm -rf ~/.ammocoin-v1.1.0/blocks
rm -rf ~/.ammocoin-v1.1.0/chainstate
rm -rf ~/.ammocoin-v1.1.0/database

# Restart and it will re-sync
ammocoind -datadir=~/.ammocoin-v1.1.0
```

---

## Security Checklist

- [ ] Firewall configured (P2P port open, RPC port blocked)
- [ ] Strong RPC password set (saved securely)
- [ ] RPC only accessible from localhost
- [ ] SSH key authentication enabled (password auth disabled)
- [ ] System updates applied: `sudo apt update && sudo apt upgrade -y`
- [ ] Only necessary ports exposed
- [ ] Fail2ban installed: `sudo apt install fail2ban`

---

## Expected Node Information

After successful setup, your seed node should show:

```json
{
  "chain": "main",
  "blocks": 0,
  "bestblockhash": "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2",
  "version": 1010000,
  "protocolversion": 70915,
  "connections": 0
}
```

**Genesis block hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
**Merkle root:** `a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab`
**Nonce:** `1299391`

---

## Next Steps After Seed Node is Running

1. **Add seed node to DNS:** Update DNS seeders to point to this node
2. **Add to hardcoded seeds:** Update source code with seed node IP
3. **Monitor:** Watch for incoming connections
4. **Launch additional nodes:** Point them to this seed node

---

## Support

- **GitHub Issues:** https://github.com/everquin/AMMOcoin/issues
- **Documentation:** https://github.com/everquin/AMMOcoin/tree/main/docs

---

**Last Updated:** January 5, 2026
**Version:** v1.1.0
**Target OS:** Ubuntu 20.04/22.04/24.04
