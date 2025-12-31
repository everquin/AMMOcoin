# AMMOcoin v1.1.0 - Seed Node Update Guide

**Date:** December 30, 2025
**Target Node:** seed1.ammocoin.org
**Critical Action:** Complete blockchain wipe and fresh start
**Authority:** V1.1.0_GENESIS_BLOCK_AUTHORITY.md

---

## ⚠️ CRITICAL WARNING

This is a **COMPLETE BLOCKCHAIN RESTART** with a new genesis block.

- **ALL blockchain data will be deleted**
- **ALL wallets in old data directory will be lost**
- **NO migration from v1.0 is possible**
- **This creates an incompatible network**

**Before proceeding:**
1. Backup any wallets with balances (there shouldn't be any on test network)
2. Coordinate with all node operators for simultaneous upgrade
3. Announce network restart to community

---

## Pre-Update Checklist

- [ ] Confirm no wallets with real balances exist
- [ ] Backup current data directory (for audit trail)
- [ ] Download and verify new v1.1.0 binaries
- [ ] Schedule maintenance window
- [ ] Notify other node operators

---

## Part 1: Backup and Preparation

### 1. SSH to Seed Node
```bash
ssh root@seed1.ammocoin.org
```

### 2. Check Current Status
```bash
ammocoin-cli getblockchaininfo 2>/dev/null || echo "Node not running"
```

**Record the output for reference** (shows what genesis you're currently on)

### 3. Stop Current Node
```bash
ammocoin-cli stop
sleep 10

# Verify stopped
ps aux | grep ammocoind | grep -v grep || echo "Node stopped successfully"
```

### 4. Backup Old Data Directory
```bash
# Create backup with timestamp
BACKUP_DIR="$HOME/ammocoin-v1.0-backup-$(date +%Y%m%d-%H%M%S)"
mv ~/.ammocoin "$BACKUP_DIR"

echo "Backup created at: $BACKUP_DIR"
ls -lh "$BACKUP_DIR"
```

**Note:** This backup is for audit trail only - it CANNOT be used with v1.1.0

### 5. Backup Old Binaries
```bash
mkdir -p ~/old-binaries
cp $(which ammocoind) ~/old-binaries/ammocoind-v1.0 2>/dev/null || echo "ammocoind not found in PATH"
cp $(which ammocoin-cli) ~/old-binaries/ammocoin-cli-v1.0 2>/dev/null || echo "ammocoin-cli not found in PATH"
```

---

## Part 2: Install New Binaries

### Option A: Download from GitHub Release (Recommended)

```bash
cd /tmp

# Download Linux binaries (when available)
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0-genesis-final/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Download checksums
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0-genesis-final/CHECKSUMS-Linux.txt

# Verify integrity
sha256sum -c CHECKSUMS-Linux.txt --ignore-missing

# If checksum passes:
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
cd AMMOcoin-v1.1.0-Linux-x86_64/

# Install binaries
sudo cp ammocoind ammocoin-cli ammocoin-tx /usr/local/bin/
sudo chmod +x /usr/local/bin/ammocoin*
```

### Option B: Build from Source (If binaries not yet available)

```bash
# Clone repository
cd /tmp
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0

# Checkout exact tag
git checkout v1.1.0-genesis-final

# Follow Linux build instructions
cat LINUX_BUILD_INSTRUCTIONS_v1.1.0.md
# (Complete the build process as documented)

# After successful build:
cd ammocoin-apps-from-ammocoin
sudo cp src/ammocoind src/ammocoin-cli src/ammocoin-tx /usr/local/bin/
sudo chmod +x /usr/local/bin/ammocoin*
```

---

## Part 3: Verify New Binaries

### 1. Check Version
```bash
ammocoind --version
# Should show version information
```

### 2. Verify Genesis Hash (CRITICAL)
```bash
strings /usr/local/bin/ammocoind | grep "00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570"
```

**MUST return matches!** Example:
```
00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570
assert(consensus.hashGenesisBlock == uint256S("0x00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570"));
```

**If no matches:** DO NOT START NODE - binaries are incorrect!

### 3. Check for Old Genesis (Should Find Nothing)
```bash
strings /usr/local/bin/ammocoind | grep -E "000001c4|0000075a"
# Should return NOTHING
```

---

## Part 4: Configure New Node

### 1. Create Fresh Data Directory
```bash
mkdir -p ~/.ammocoin
chmod 700 ~/.ammocoin
```

### 2. Create Configuration File
```bash
cat > ~/.ammocoin/ammocoin.conf <<EOF
# AMMOcoin v1.1.0 Configuration
# Seed Node: seed1.ammocoin.org

# Server mode
server=1
daemon=1
listen=1

# RPC Configuration
rpcuser=your_rpc_user_here
rpcpassword=your_secure_password_here
rpcport=8332
rpcallowip=127.0.0.1
rpcbind=127.0.0.1

# Network
maxconnections=125
port=8338

# Logging
debug=0
shrinkdebugfile=1

# This is a seed node
dnsseed=1

# Genesis block (for reference - embedded in binary)
# Genesis: 00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570
EOF

chmod 600 ~/.ammocoin/ammocoin.conf
```

**IMPORTANT:** Replace `your_rpc_user_here` and `your_secure_password_here` with secure credentials!

---

## Part 5: Start New Node

### 1. Start Daemon
```bash
ammocoind -daemon
```

**Expected output:**
```
AMMOcoin server starting
```

### 2. Wait for Startup
```bash
sleep 10
```

### 3. Check Initial Status
```bash
ammocoin-cli getblockchaininfo
```

**Expected output:**
```json
{
  "chain": "main",
  "blocks": 0,
  "headers": 0,
  "bestblockhash": "00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570",
  "difficulty": 0.000244140625,
  ...
}
```

### 4. Verify Genesis Hash (CRITICAL)
```bash
GENESIS=$(ammocoin-cli getblockhash 0)
echo "Genesis hash: $GENESIS"

if [ "$GENESIS" = "00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570" ]; then
    echo "✅ SUCCESS: Correct v1.1.0 genesis!"
else
    echo "❌ CRITICAL ERROR: Wrong genesis hash!"
    echo "Expected: 00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570"
    echo "Got: $GENESIS"
    echo "STOP: Do not allow connections - investigate immediately!"
    exit 1
fi
```

---

## Part 6: Network Verification

### 1. Check Peer Connections
```bash
ammocoin-cli getpeerinfo
```

**Initially should return:** `[]` (no peers yet)

### 2. Check Network Info
```bash
ammocoin-cli getnetworkinfo
```

**Verify:**
- `"version"` matches v1.1.0
- `"subversion"` shows correct version string
- `"localservices"` shows node is ready

### 3. Monitor Debug Log
```bash
tail -f ~/.ammocoin/debug.log
```

**Look for:**
- No assertion failures
- No genesis block errors
- Clean startup

Press Ctrl+C to exit

---

## Part 7: Firewall and Network Configuration

### 1. Ensure Port 8338 is Open
```bash
sudo ufw allow 8338/tcp
sudo ufw status
```

### 2. Test External Connectivity
```bash
# From a different machine:
telnet seed1.ammocoin.org 8338
# Should connect (Ctrl+] then 'quit' to exit)
```

### 3. Add to DNS Seeds (if not already)
```bash
# Verify DNS entry exists
dig seed1.ammocoin.org
# Should return your server's IP
```

---

## Part 8: Post-Update Monitoring

### 1. Monitor Logs Continuously
```bash
tail -f ~/.ammocoin/debug.log | grep -E "ERROR|WARNING|block|peer"
```

### 2. Check Status Every Hour (first 24 hours)
```bash
# Create monitoring script
cat > ~/monitor-ammocoin.sh <<'EOF'
#!/bin/bash
while true; do
    clear
    echo "=== AMMOcoin v1.1.0 Status ==="
    date
    echo ""

    echo "Genesis:"
    ammocoin-cli getblockhash 0
    echo ""

    echo "Chain info:"
    ammocoin-cli getblockchaininfo | grep -E "blocks|bestblockhash|difficulty"
    echo ""

    echo "Peers:"
    ammocoin-cli getpeerinfo | grep -E "addr|version" | head -20
    echo ""

    echo "Network:"
    ammocoin-cli getnetworkinfo | grep -E "version|connections"

    sleep 300  # Check every 5 minutes
done
EOF

chmod +x ~/monitor-ammocoin.sh
```

### 3. Run Monitor
```bash
# In a screen or tmux session:
screen -S ammocoin-monitor
~/monitor-ammocoin.sh
# Detach with Ctrl+A then D
```

---

## Emergency Rollback Procedure

**IF SOMETHING GOES WRONG and you need to rollback to v1.0:**

```bash
# Stop v1.1.0 node
ammocoin-cli stop
sleep 5

# Restore old binaries
sudo cp ~/old-binaries/ammocoind-v1.0 /usr/local/bin/ammocoind
sudo cp ~/old-binaries/ammocoin-cli-v1.0 /usr/local/bin/ammocoin-cli
sudo chmod +x /usr/local/bin/ammocoin*

# Restore old data directory
rm -rf ~/.ammocoin
cp -r $BACKUP_DIR ~/.ammocoin

# Start old node
ammocoind -daemon

# Verify
sleep 10
ammocoin-cli getblockchaininfo
```

**Note:** Rollback only works if you kept the backup and no other nodes upgraded

---

## Troubleshooting

### Node Won't Start
```bash
# Check error log
tail -100 ~/.ammocoin/debug.log

# Check if port is in use
sudo netstat -tulpn | grep 8338

# Try starting in foreground for debugging
ammocoind -printtoconsole
```

### Wrong Genesis Hash
```bash
# Verify binary
strings /usr/local/bin/ammocoind | grep -E "00000f14|000001c4|0000075a"

# If wrong, re-download or rebuild
# DO NOT proceed with network launch
```

### No Peer Connections
```bash
# Check firewall
sudo ufw status | grep 8338

# Check if listening
sudo netstat -tulpn | grep 8338

# Manually add peer (for testing)
ammocoin-cli addnode "other-node-ip:8338" "add"
```

### Assertion Failed on Startup
```bash
# This means genesis mismatch - CRITICAL
# Check debug.log for exact assertion
cat ~/.ammocoin/debug.log | grep -i "assert"

# Verify you're running correct binaries
strings /usr/local/bin/ammocoind | grep genesis
```

---

## Final Verification Checklist

Before announcing seed node is ready:

- [ ] Node starts without errors
- [ ] Genesis hash is `00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570`
- [ ] No old genesis hashes found in binaries
- [ ] Port 8338 is open and listening
- [ ] DNS entry for seed1.ammocoin.org is correct
- [ ] RPC is responding to local requests
- [ ] Debug log shows no errors
- [ ] Can connect to node from external machine
- [ ] Backup of old data is safe
- [ ] Monitoring is in place

---

## Communication Template

**When seed node is ready, announce to community:**

```
🎉 AMMOcoin v1.1.0 Network Launch

The seed node (seed1.ammocoin.org) has been successfully updated to v1.1.0!

Genesis Block: 00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570
Network Port: 8338
RPC Port: 8332

⚠️ IMPORTANT: This is a fresh blockchain start
- You MUST delete your old blockchain data (~/.ammocoin)
- Download new v1.1.0 binaries from GitHub
- All nodes must upgrade simultaneously
- No migration from v1.0 is possible

Download: https://github.com/everquin/AMMOcoin-v1.1.0/releases/tag/v1.1.0-genesis-final
Authority: V1.1.0_GENESIS_BLOCK_AUTHORITY.md

The network is now live. Connect your nodes!
```

---

## Support

For seed node issues:
- Check AUDIT_RESULTS_AND_NEXT_STEPS.md for status
- Review V1.1.0_GENESIS_BLOCK_AUTHORITY.md for genesis parameters
- Contact node operators channel for coordination

**Genesis Hash (MUST match):**
`00000cd103e27df3a1c4ab850754c16b4923f075a82eb8aecb4c0e288c4f9570`

---

**Last Updated:** December 30, 2025
**Status:** Ready for Execution
