# AMMOcoin v1.1.1 (upcoming) Seed Node Deployment Guide

**For production seed nodes running Ubuntu Linux**

> **v1.1.1 is a mandatory hard fork.** Proof-of-Stake starts at block 2,776 and there is no mining after it. v1.1.1 uses new network magic bytes (`c7 9a e3 b5`), so it does **not** connect to v1.0 or v1.1.0 nodes. Every seed node must run v1.1.1.
> v1.1.1 is not released yet. Download links and checksums will be published on the official GitHub release page; do not use binaries from any other source.

**Current seed nodes:**
- seed1.ammocoin.org - `78.141.194.140:37020`
- seed2.ammocoin.org - `104.238.165.56:37020`
- `147.182.245.102` is **dead** - remove it from any config or firewall rule.

---

## Quick Deploy with Claude

### Option 1: Paste Prompt to Claude (Recommended)

SSH into your seed node VM and start a Claude Code session, then paste this prompt:

```
I need to set up AMMOcoin v1.1.1 on this seed node. This is a production deployment.

IMPORTANT CONTEXT:
- This is a seed node for the AMMOcoin v1.1 network
- v1.1.1 is a hard fork: Proof-of-Stake from block 2776, no mining. New network
  magic, so it will not peer with v1.0 or v1.1.0 nodes.
- The node must run Ubuntu 22.04 or newer (24.04 tested). The binaries need
  glibc >= 2.34 (check with: ldd --version). Ubuntu 18.04/20.04 cannot run them.
- There may be an old v1.0 or v1.1.0 node running that needs to be stopped

TASK:
1. Check if any old AMMOcoin process is running and stop it gracefully
2. Back up any old wallet.dat and ammocoin.conf (~/.ammocoin, ~/.ammocoin-v1.1.0)
   to ~/ammocoin-backup/
3. Download the AMMOcoin v1.1.1 Linux binaries from the official GitHub release
4. Verify the SHA256 checksum against the official release checksums
5. Install the binaries to /opt/ammocoin-v1.1.1/bin/
6. Create the data directory ~/.ammocoin11/ (new v1.1.1 default)
7. Create ammocoin.conf with seed node configuration
8. Install a systemd unit (must include Environment=HOME=...) and start it
9. Verify the node is running, has peers and is past block 2775

RELEASE INFORMATION:
- GitHub Release: <v1.1.1 release URL - not published yet>
- Genesis Block Hash: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2

SEED NODE CONFIGURATION REQUIREMENTS:
- Listen on all interfaces (listen=1)
- Enable RPC server (server=1), localhost only
- Set maxconnections=125 (seed nodes need higher limits)
- Enable transaction indexing (txindex=1)
- Set RPC credentials with strong password
- P2P port: 37020, RPC port: 51473
- addnode=78.141.194.140:37020 and addnode=104.238.165.56:37020

After setup, provide me with:
1. The node's public IP address
2. Confirmation that the service is running
3. Output of: ammocoin-cli getinfo
4. Output of: ammocoin-cli getpeerinfo
5. Output of: ammocoin-cli getblockchaininfo

Make sure to use proper permissions and security practices. This is a production seed node.
```

---

## Option 2: Manual Deployment

### Prerequisites

- **Ubuntu 22.04 or 24.04** (24.04 tested). The v1.1.1 binaries require **glibc 2.34+**; check with `ldd --version`. Ubuntu 18.04 and 20.04 cannot run them - upgrade or reinstall the OS first.
- Root or sudo access
- At least 10GB free disk space
- Port 37020 open in firewall (RPC port 51473 stays closed to the internet)

---

### Step 1: Stop Existing Node (if running)

```bash
# Check if an old v1.0 / v1.1.0 node is running
ps aux | grep ammocoin

# If running as a service
sudo systemctl stop ammocoind 2>/dev/null || true

# Otherwise stop it gracefully
pkill -SIGTERM ammocoind

# Wait for it to shut down (up to 60 seconds)
sleep 60

# Verify it stopped
ps aux | grep ammocoin
```

---

### Step 2: Backup Old Wallets (if they exist)

```bash
# Create backup directory
mkdir -p ~/ammocoin-backup

# Backup wallet and config from the old data folders
for d in ~/.ammocoin ~/.ammocoin-v1.1.0; do
  if [ -d "$d" ]; then
    mkdir -p ~/ammocoin-backup/$(basename "$d")
    cp "$d"/wallet.dat ~/ammocoin-backup/$(basename "$d")/ 2>/dev/null || true
    cp "$d"/ammocoin.conf ~/ammocoin-backup/$(basename "$d")/ 2>/dev/null || true
    echo "✅ $d backed up to ~/ammocoin-backup/$(basename "$d")/"
  fi
done
```

Keep any v1.0 `wallet.dat`: v1.0 balances are airdropped to the same addresses on v1.1.

---

### Step 3: Download v1.1.1 Binaries

```bash
# Create installation directory
sudo mkdir -p /opt/ammocoin-v1.1.1/bin
cd /tmp

# Download the Linux x86_64 archive and the checksums file from the
# official v1.1.1 GitHub release (not published yet):
#   <v1.1.1 release URL>
```

---

### Step 4: Verify Checksum

```bash
# Calculate SHA256 of the downloaded archive
sha256sum AMMOcoin-v1.1.1-*.tar.gz

# Compare with the checksums file from the official release
# If they match, proceed. If not, STOP and investigate!
```

---

### Step 5: Extract and Install

```bash
# Extract
tar -xzf AMMOcoin-v1.1.1-*.tar.gz

# Move binaries (adjust the path if the archive layout differs)
sudo mv bin/* /opt/ammocoin-v1.1.1/bin/

# Make executable
sudo chmod +x /opt/ammocoin-v1.1.1/bin/*

# Create symlinks for easy access
sudo ln -sf /opt/ammocoin-v1.1.1/bin/ammocoind /usr/local/bin/ammocoind
sudo ln -sf /opt/ammocoin-v1.1.1/bin/ammocoin-cli /usr/local/bin/ammocoin-cli
sudo ln -sf /opt/ammocoin-v1.1.1/bin/ammocoin-tx /usr/local/bin/ammocoin-tx

# Verify installation (fails with "GLIBC_2.34 not found" on Ubuntu 18.04/20.04)
ammocoind --version
```

---

### Step 6: Create Data Directory and Configuration

v1.1.1 uses the new default data folder `~/.ammocoin11` (v1.0/v1.1.0 used `~/.ammocoin`). Sapling parameters live in `~/.ammocoin-params`.

```bash
# Create the v1.1.1 data directory
mkdir -p ~/.ammocoin11

# Generate strong RPC password
RPC_PASSWORD=$(openssl rand -base64 32)

# Create ammocoin.conf
cat > ~/.ammocoin11/ammocoin.conf <<EOF
# AMMOcoin v1.1.1 Seed Node Configuration
# Generated: $(date)

# Network Settings
listen=1
server=1
maxconnections=125

# RPC Settings
rpcuser=ammocoin_rpc
rpcpassword=${RPC_PASSWORD}
rpcallowip=127.0.0.1
rpcport=51473

# P2P Settings
port=37020

# Seed nodes (omit this node's own IP)
addnode=78.141.194.140:37020
addnode=104.238.165.56:37020

# Performance
dbcache=512
maxmempool=300

# Indexing (required for seed nodes)
txindex=1

# Logging
debug=0
printtoconsole=0
EOF

chmod 600 ~/.ammocoin11/ammocoin.conf
echo "✅ Configuration created at ~/.ammocoin11/ammocoin.conf"
echo "⚠️  RPC Password: ${RPC_PASSWORD}"
echo "    Save this password securely!"
```

Do not copy `blocks/` or `chainstate/` from an old v1.0/v1.1.0 folder; let v1.1.1 sync from the seeds.

---

### Step 7: Configure Firewall

```bash
# Allow P2P port
sudo ufw allow 37020/tcp comment 'AMMOcoin P2P'

# RPC port 51473 should NOT be exposed to internet
# Only allow from localhost (already configured in ammocoin.conf)

# Remove any old rules for 37019 or the dead seed 147.182.245.102
sudo ufw status numbered

# Verify firewall rules
sudo ufw status
```

---

### Step 8: Install the systemd Service and Start

The unit **must** set `HOME`. Without it the node exits with `Cannot find the Sapling parameters`. Tested unit (running as root):

```bash
sudo tee /etc/systemd/system/ammocoind.service > /dev/null <<'EOF'
[Unit]
Description=AMMOcoin v1.1.1 Daemon
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
EOF

# Reload systemd, enable and start
sudo systemctl daemon-reload
sudo systemctl enable --now ammocoind

# Check status
sudo systemctl status ammocoind
```

If the service runs as another user, set `User=`, `Environment=HOME=/home/<user>` and `-datadir=/home/<user>/.ammocoin11` to match. The commands below assume the default data folder of the user running `ammocoin-cli`; as root, `ammocoin-cli` reads `/root/.ammocoin11` automatically.

---

### Step 9: Verify Node is Running

```bash
# Check blockchain info
ammocoin-cli getblockchaininfo

# Expected output should show:
# - "chain": "main"
# - "blocks": past 2775 once synced (PoS blocks from 2776)

# Get node info
ammocoin-cli getinfo

# Check peer connections (should include 78.141.194.140 / 104.238.165.56)
ammocoin-cli getpeerinfo

# Get network info
ammocoin-cli getnetworkinfo
```

---

### Step 10: Verify Genesis Block

```bash
# Get block hash for block 0
ammocoin-cli getblockhash 0

# Should return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2

# Get block details
ammocoin-cli getblock $(ammocoin-cli getblockhash 0)

# Verify:
# - "hash": "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
# - "merkleroot": "a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab"
# - "nonce": 1299391
```

---

### Step 11: Monitor the Node

```bash
# Watch the log file
tail -f ~/.ammocoin11/debug.log

# Or the service journal
journalctl -u ammocoind -f

# Check sync status every 10 seconds
watch -n 10 'ammocoin-cli getblockchaininfo | grep -E "(blocks|verificationprogress)"'

# Monitor connections
watch -n 5 'ammocoin-cli getconnectioncount'
```

---

## Useful Commands

### Start/Stop Node

```bash
# Start / stop / restart via systemd
sudo systemctl start ammocoind
sudo systemctl stop ammocoind
sudo systemctl restart ammocoind

# Stop directly (graceful)
ammocoin-cli stop
```

### Get Node Status

```bash
# Quick status
ammocoin-cli getinfo

# Blockchain info
ammocoin-cli getblockchaininfo

# Network info
ammocoin-cli getnetworkinfo

# Peer info
ammocoin-cli getpeerinfo

# Connection count
ammocoin-cli getconnectioncount
```

---

## Troubleshooting

### Node won't start

```bash
# Check the service log
journalctl -u ammocoind -n 100

# "Cannot find the Sapling parameters" -> add Environment=HOME=/root
#   (or the service user's HOME) to the unit, then:
sudo systemctl daemon-reload && sudo systemctl restart ammocoind

# "GLIBC_2.34 not found" -> OS too old; use Ubuntu 22.04+ (24.04 tested)

# Check if port is already in use
sudo ss -tulpn | grep 37020

# Check log file for errors
tail -100 ~/.ammocoin11/debug.log

# Verify binaries are executable
ls -lh /opt/ammocoin-v1.1.1/bin/
```

### No connections

```bash
# Verify firewall allows P2P port
sudo ufw status | grep 37020

# Test if the seeds are reachable
nc -zv 78.141.194.140 37020
nc -zv 104.238.165.56 37020

# Check if node is listening
sudo ss -tulpn | grep ammocoind
```

Remember that v1.1.1 does not connect to v1.0 or v1.1.0 nodes. Peers still running old versions will never show up.

### Stuck at block 2,775

The node is running v1.1.0 (or connected only to v1.1.0 peers). Check `ammocoind --version`, install v1.1.1 and restart.

### Wrong genesis block

```bash
# If you see a different genesis hash, you're on the wrong network
sudo systemctl stop ammocoind

# Delete blockchain data (keeps wallet)
rm -rf ~/.ammocoin11/blocks
rm -rf ~/.ammocoin11/chainstate
rm -rf ~/.ammocoin11/database

# Restart and it will re-sync
sudo systemctl start ammocoind
```

---

## Security Checklist

- [ ] Firewall configured (P2P port 37020 open, RPC port 51473 blocked)
- [ ] Strong RPC password set (saved securely)
- [ ] RPC only accessible from localhost
- [ ] SSH key authentication enabled (password auth disabled)
- [ ] System updates applied: `sudo apt update && sudo apt upgrade -y`
- [ ] Only necessary ports exposed
- [ ] Fail2ban installed: `sudo apt install fail2ban`

---

## Expected Node Information

After successful setup, your seed node should show something like:

```json
{
  "chain": "main",
  "blocks": 2776,
  "version": 1010100,
  "protocolversion": 70927,
  "connections": 1
}
```

(`blocks` keeps rising as PoS blocks are staked; `connections` depends on the network.)

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
- **Release notes:** [docs/release-notes/RELEASE_NOTES_v1.1.1.md](docs/release-notes/RELEASE_NOTES_v1.1.1.md)

---

**Last Updated:** October 16, 2026
**Version:** v1.1.1 (upcoming)
**Target OS:** Ubuntu 22.04/24.04 (glibc 2.34+)
