# 🔧 AMMOcoin Troubleshooting Guide

Complete solutions for common AMMOcoin issues. Find quick fixes and detailed diagnostics for wallet, staking, masternode, and network problems.

> **v1.1.1:** paths below use the new default data folder - Linux `~/.ammocoin11`, macOS `~/Library/Application Support/AMMOcoin11`, Windows `%APPDATA%\AMMOcoin11` (v1.0/v1.1.0 used `.ammocoin` / `AMMOcoin`). Mainnet ports: P2P **37020**, RPC **51473**.

## 🔀 v1.1.1 Upgrade Issues

#### ❌ "No Peers" / "Stuck at Block 2,775"
**Cause**: You are running v1.0 or v1.1.0. v1.1.1 is a hard fork (Proof-of-Stake from block 2,776) with new network magic bytes, so v1.1.1 nodes do not connect to older nodes.
**Solution**: Stop the old node, install v1.1.1, and check your config:
```bash
ammocoin-cli stop
ammocoind -version          # must show v1.1.1
# Remove dead/wrong entries from ammocoin.conf:
#   addnode=147.182.245.102   (dead seed)
#   port=37019                (wrong - mainnet is 37020)
# Working seeds:
#   addnode=78.141.194.140:37020    (seed1)
#   addnode=104.238.165.56:37020    (seed2.ammocoin.org)
```

#### ❌ "Balance / Wallet Missing After Upgrade"
**Cause**: v1.1.1 uses a new data folder (`~/.ammocoin11`), so it starts with an empty wallet.
**Solution**: Stop the node, copy your backed-up `wallet.dat` (and `ammocoin.conf`, `masternode.conf`) from `~/.ammocoin` into `~/.ammocoin11`, then start again. Do not copy `blocks/` or `chainstate/`.

#### ❌ "version `GLIBC_2.34' not found"
**Cause**: v1.1.1 Linux binaries need glibc 2.34 or newer.
**Solution**: Check with `ldd --version`. Use Ubuntu 22.04 LTS or newer (24.04 tested). Ubuntu 18.04/20.04 cannot run the binaries - upgrade or reinstall the OS.

#### ❌ "Cannot find the Sapling parameters" (systemd)
**Cause**: systemd services start without `HOME`, so the node cannot find `~/.ammocoin-params`.
**Solution**: Add `Environment=HOME=/root` (or the service user's home) to the `[Service]` section, then:
```bash
sudo systemctl daemon-reload && sudo systemctl restart ammocoind
```
Sapling params locations: Linux `~/.ammocoin-params`, macOS `~/Library/Application Support/AMMOcoinParams`, Windows `%APPDATA%\AMMOcoinParams`.

#### ❌ "Invalid IP address" (masternode)
**Cause**: The masternode address is 127.0.0.1, a private IP (10.x, 172.16-31.x, 192.168.x) or not on port 37020.
**Solution**: Use the VPS's public, routable IP with port **37020** in both `masternode.conf` (controller) and `masternodeaddr=` / `externalip=` (VPS).

## 🚨 Emergency Quick Fixes

### Wallet Won't Start
```bash
# Quick diagnosis
ps aux | grep ammocoin    # Check if already running
pkill ammocoind          # Force close if stuck
rm ~/.ammocoin11/.lock  # Remove stale lock file
ammocoind                # Restart

# If still failing
ammocoind -reindex       # Rebuild database
```

### Lost Connection
```bash
# Immediate reconnection
ammocoin-cli stop
sleep 5
ammocoind
ammocoin-cli addnode "seed1.ammocoin.org:37020" "add"
```

### Staking Stopped
```bash
# Quick staking restart
ammocoin-cli walletpassphrase "your_password" 999999 true
ammocoin-cli getstakingstatus  # Verify staking_status: true
```

## 💰 Wallet Issues

### Wallet Startup Problems

#### ❌ "Wallet.dat Corrupt"
**Symptoms**: Error on startup, can't load wallet
**Solutions**:
```bash
# Stop wallet completely
ammocoin-cli stop
pkill ammocoind

# Try repair
ammocoind -salvagewallet

# If repair fails, restore from backup
cp wallet_backup.dat ~/.ammocoin11/wallet.dat
ammocoind
```

#### ❌ "Another Instance Running"
**Symptoms**: "Cannot obtain a lock on data directory"
**Solutions**:
```bash
# Find and kill existing process
ps aux | grep ammocoin
kill -9 [process_id]

# Remove lock files
rm ~/.ammocoin11/.lock

# Restart
ammocoind
```

#### ❌ "Insufficient Disk Space"
**Symptoms**: Wallet crashes, sync stops
**Solutions**:
```bash
# Check disk space
df -h ~/.ammocoin11/

# Clean up log files
truncate -s 0 ~/.ammocoin11/debug.log

# Move the data folder to a larger disk and start with -datadir=/path/to/data
# (pruning is not supported)
```

### Sync & Connection Issues

#### ❌ "Not Syncing"
**Symptoms**: Block count not increasing
**Diagnosis**:
```bash
# Check current status
ammocoin-cli getblockchaininfo

# Check peers
ammocoin-cli getpeerinfo

# Expected: Multiple peers, increasing blocks
```

**Solutions**:
```bash
# Add reliable peers
ammocoin-cli addnode "seed1.ammocoin.org:37020" "add"
ammocoin-cli addnode "seed2.ammocoin.org:37020" "add"
ammocoin-cli addnode "78.141.194.140:37020" "add"
ammocoin-cli addnode "104.238.165.56:37020" "add"

# Stuck at 2,775? You are not on v1.1.1 - see "v1.1.1 Upgrade Issues" above

# If still stuck, restart sync
ammocoin-cli stop
rm -rf ~/.ammocoin11/peers.dat
ammocoind

# Nuclear option: reindex
ammocoind -reindex
```

#### ❌ "Fork Detected"
**Symptoms**: Warning about being on wrong chain
**Solutions**:
```bash
# Check if on correct chain
ammocoin-cli getblockhash $(ammocoin-cli getblockcount)

# If wrong, invalidate bad blocks
ammocoin-cli invalidateblock "bad_block_hash"

# Resync from checkpoint
ammocoind -checkpoints
```

### Transaction Issues

#### ❌ "Transaction Not Confirming"
**Symptoms**: Transaction stuck in mempool
**Diagnosis**:
```bash
# Check transaction status
ammocoin-cli gettransaction "txid"

# Check mempool
ammocoin-cli getmempoolinfo

# Check if transaction is in mempool
ammocoin-cli getrawmempool | grep "txid"
```

**Solutions**:
```bash
# If low fee, abandon and resend
ammocoin-cli abandontransaction "txid"

# Create new transaction with higher fee
ammocoin-cli sendtoaddress "address" amount "" "" true

# If confirmed but not showing
ammocoin-cli rescanblockchain
```

#### ❌ "Insufficient Funds"
**Symptoms**: Can't send despite showing balance
**Diagnosis**:
```bash
# Check confirmed vs unconfirmed
ammocoin-cli getbalance        # Confirmed
ammocoin-cli getunconfirmedbalance

# Check if coins are locked
ammocoin-cli listlockunspent

# Check UTXOs
ammocoin-cli listunspent
```

**Solutions**:
```bash
# Wait for confirmations
ammocoin-cli getbalance "*" 6  # 6 confirmations

# Unlock locked coins
ammocoin-cli lockunspent true []

# Send with coin control
ammocoin-cli createrawtransaction [...] {...}
```

## 🎯 Staking Problems

### Staking Not Working

#### ❌ "Staking: Off"
**Symptoms**: Green arrow missing, no staking
**Diagnosis**:
```bash
# Check staking status
ammocoin-cli getstakingstatus

# Look for:
# "staking_status": false
# "walletunlocked": false
# "stakeablecoins": 0   (coins need 600 confirmations)
# "mnsync": false
```

**Solutions**:
```bash
# Unlock wallet for staking
ammocoin-cli walletpassphrase "password" 999999 true

# Make sure staking is not disabled in config (staking=1 is the default)
grep staking ~/.ammocoin11/ammocoin.conf

# Restart wallet
ammocoin-cli stop && ammocoind
```

#### ❌ "No Stakes"
**Symptoms**: Staking active but no blocks staked
**Diagnosis**:
```bash
# Check stakeable coins and staking balance
ammocoin-cli getstakingstatus | grep -E "stakeablecoins|stakingbalance"

# Check coin maturity (600 confirmations needed)
ammocoin-cli listunspent | grep confirmations
```

**Solutions**:
```bash
# Ensure coins are mature (600 confirmations, about 30 hours at 3-minute blocks)
# Small amounts may take weeks to stake

# Set how large stake outputs are split
ammocoin-cli setstakesplitthreshold 5000

# Improve uptime
# Keep wallet online 24/7

# Check for errors
tail -f ~/.ammocoin11/debug.log | grep -i stake
```

#### ❌ "Very Low Staking Weight"
**Symptoms**: expectedtime showing years
**Solutions**:
```bash
# Consolidate dust UTXOs by sending them to yourself
ammocoin-cli sendtoaddress "YOUR_OWN_ADDRESS" AMOUNT
# (the new UTXO must reach 600 confirmations again before staking)

# Stake more of the coins you already hold

# Check network conditions
ammocoin-cli getdifficulty
```

### Staking Performance Issues

#### ❌ "Inconsistent Staking"
**Symptoms**: Staking turns on/off randomly
**Diagnosis**:
```bash
# Monitor staking status
watch -n 30 'ammocoin-cli getstakingstatus | grep staking_status'

# Check for network disconnections
ammocoin-cli getpeerinfo | wc -l
```

**Solutions**:
```bash
# Improve network stability
# Use wired connection instead of WiFi

# Add reliable peers
ammocoin-cli addnode "reliable_peer:37020" "add"

# Monitor logs for disconnections
grep -i "disconnect" ~/.ammocoin11/debug.log
```

## 🏛️ Masternode Issues

### Masternode Setup Problems

#### ❌ "Masternode Not Starting"
**Symptoms**: Status shows "MISSING" or won't start
**Diagnosis**:
```bash
# Check collateral
ammocoin-cli getmasternodeoutputs

# Verify 15+ confirmations
ammocoin-cli gettransaction "collateral_txid"

# Check masternode.conf syntax
cat ~/.ammocoin11/masternode.conf
```

**Solutions**:
```bash
# Verify masternode.conf format
# alias IP:port masternodeprivkey collateral_txid output_index

# Example correct format:
# mn1 203.0.113.10:37020 7abc...xyz a1b2c3...890 0
# The IP must be the VPS's public IP on port 37020 - 127.0.0.1 or private
# IPs (192.168.x, 10.x) fail with "Invalid IP address"

# Restart both local and remote
ammocoin-cli stop       # Local
ssh user@vps ammocoind stop  # Remote
# Start remote first, then from the local wallet:
ammocoin-cli startmasternode alias false mn1
```

#### ❌ "PRE_ENABLED Status Stuck"
**Symptoms**: Never reaches ENABLED status
**Diagnosis**:
```bash
# Check remote server
ssh user@vps ammocoin-cli getmasternodestatus

# Check if receiving connections
ssh user@vps ammocoin-cli getpeerinfo | wc -l

# Verify protocol version
ssh user@vps ammocoin-cli getnetworkinfo | grep protocolversion
```

**Solutions**:
```bash
# Open firewall port
ssh user@vps sudo ufw allow 37020

# Restart masternode sequence
ammocoin-cli startmasternode alias false mn1

# Wait for network propagation (up to 30 minutes)
```

### Masternode Monitoring Issues

#### ❌ "Masternode Expired"
**Symptoms**: Status changes to EXPIRED
**Diagnosis**:
```bash
# Check last seen time
ammocoin-cli listmasternodes | grep "your_ip"

# Check server uptime
ssh user@vps uptime

# Check daemon status
ssh user@vps ammocoin-cli getinfo
```

**Solutions**:
```bash
# Restart remote daemon if down
ssh user@vps ammocoind

# Restart masternode from local wallet
ammocoin-cli startmasternode alias false mn1

# Monitor server stability
ssh user@vps tail -f ~/.ammocoin11/debug.log
```

#### ❌ "Masternode Rarely Paid"
**Symptoms**: Infrequent or no masternode payments
**Diagnosis**:
```bash
# Check payment queue position
ammocoin-cli getmasternodewinners

# Verify masternode is active
ammocoin-cli listmasternodes | grep "your_ip"

# Check network masternode count
ammocoin-cli getmasternodecount

# Expected: one turn about every N blocks, where N = enabled masternodes
```

**Solutions**:
```bash
# Ensure consistent uptime
# Monitor server with external service

# Check for network issues
ssh user@vps ammocoin-cli getpeerinfo

# Verify correct payment address
grep -i "masternode" ~/.ammocoin11/ammocoin.conf
```

## 🌐 Network & Connection Issues

### Peer Connection Problems

#### ❌ "No Connections"
**Symptoms**: getconnectioncount returns 0
**Diagnosis**:
```bash
# Check network settings
ammocoin-cli getnetworkinfo

# Check if port is blocked
netstat -tlnp | grep 37020

# Test external connectivity
telnet peer_ip 37020
```

**Solutions**:
```bash
# Configure firewall
sudo ufw allow 37020/tcp

# Add manual peers
ammocoin-cli addnode "seed1.ammocoin.org:37020" "add"

# Remove dead seed 147.182.245.102 and any port=37019 from ammocoin.conf
# Mainnet P2P port is 37020 (masternodes must use 37020)

# Check ISP blocking - use VPN if needed
```

#### ❌ "High Latency Connections"
**Symptoms**: Slow sync, delayed transactions
**Diagnosis**:
```bash
# Check peer latencies
ammocoin-cli getpeerinfo | grep -E "(addr|pingtime)"

# Test network speed
speedtest-cli
```

**Solutions**:
```bash
# Disconnect slow peers
ammocoin-cli disconnectnode "slow_peer_ip:37020"

# Connect to geographically closer nodes
ammocoin-cli addnode "local_node_ip:37020" "add"

# Limit connections to reduce bandwidth
maxconnections=20
```

### Blockchain Data Issues

#### ❌ "Corrupted Blockchain"
**Symptoms**: Validation errors, crashes during sync
**Diagnosis**:
```bash
# Verify blockchain integrity
ammocoin-cli verifychain

# Check for error messages
grep -i "error\|corrupt" ~/.ammocoin11/debug.log
```

**Solutions**:
```bash
# Reindex blockchain
ammocoin-cli stop
ammocoind -reindex

# If reindex fails, resync
ammocoin-cli stop
rm -rf ~/.ammocoin11/blocks ~/.ammocoin11/chainstate
ammocoind
```

#### ❌ "Wrong Network"
**Symptoms**: Connecting to testnet instead of mainnet
**Diagnosis**:
```bash
# Check network
ammocoin-cli getblockchaininfo | grep chain

# Should show "main" not "test"
```

**Solutions**:
```bash
# Remove testnet config
grep -v testnet ~/.ammocoin11/ammocoin.conf > temp.conf
mv temp.conf ~/.ammocoin11/ammocoin.conf

# Clear testnet data
rm -rf ~/.ammocoin11/testnet5/

# Restart on mainnet
ammocoind
```

## 🔐 Security & Access Issues

### Password & Encryption Problems

#### ❌ "Wrong Passphrase"
**Symptoms**: Can't unlock wallet despite correct password
**Diagnosis**:
```bash
# Verify wallet is encrypted
ammocoin-cli getwalletinfo | grep unlocked_until

# Check for special characters
# Some characters may cause issues
```

**Solutions**:
```bash
# Try different character encodings
# Avoid special characters in passwords

# If truly forgotten - no recovery possible
# Restore from backup with known password

# Prevention: Test password immediately after setting
ammocoin-cli walletpassphrase "new_password" 30
```

#### ❌ "Wallet Won't Encrypt"
**Symptoms**: encryptwallet command fails
**Diagnosis**:
```bash
# Check if already encrypted
ammocoin-cli getwalletinfo

# Check available disk space
df -h ~/.ammocoin11/

# Check file permissions
ls -la ~/.ammocoin11/wallet.dat
```

**Solutions**:
```bash
# Ensure wallet not already encrypted
# Stop all other operations

# Free up disk space if needed
# Ensure write permissions

# Backup before encrypting
ammocoin-cli backupwallet "pre_encrypt_backup.dat"
```

### Permission & Access Issues

#### ❌ "Permission Denied"
**Symptoms**: Can't read/write wallet files
**Solutions**:
```bash
# Fix file ownership
sudo chown -R $USER:$USER ~/.ammocoin11/

# Fix permissions
chmod 700 ~/.ammocoin11/
chmod 600 ~/.ammocoin11/wallet.dat
chmod 600 ~/.ammocoin11/ammocoin.conf
```

#### ❌ "RPC Connection Failed"
**Symptoms**: CLI commands don't work
**Diagnosis**:
```bash
# Check if daemon is running
ps aux | grep ammocoind

# Check RPC configuration
grep -E "rpc" ~/.ammocoin11/ammocoin.conf

# Test RPC connection
curl --user user:pass --data-binary '{"jsonrpc": "1.0", "id":"test", "method": "getinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:51473/
```

**Solutions**:
```bash
# Start daemon if not running
ammocoind

# Configure RPC access
echo "server=1" >> ~/.ammocoin11/ammocoin.conf
echo "rpcuser=user" >> ~/.ammocoin11/ammocoin.conf
echo "rpcpassword=pass" >> ~/.ammocoin11/ammocoin.conf

# Restart daemon
ammocoin-cli stop && ammocoind
```

## 🔧 Performance Issues

### Slow Wallet Performance

#### ❌ "Slow Startup"
**Symptoms**: Wallet takes long time to start
**Solutions**:
```bash
# Increase database cache
echo "dbcache=1024" >> ~/.ammocoin11/ammocoin.conf

# Use SSD instead of HDD
# Move data directory to SSD

# Reduce startup verification
echo "checkblocks=50" >> ~/.ammocoin11/ammocoin.conf
```

#### ❌ "High Memory Usage"
**Symptoms**: System becomes slow, high RAM usage
**Diagnosis**:
```bash
# Check memory usage
ammocoin-cli getmemoryinfo

# Monitor system resources
top -p $(pgrep ammocoind)
```

**Solutions**:
```bash
# Reduce memory usage
echo "maxmempool=50" >> ~/.ammocoin11/ammocoin.conf
echo "dbcache=200" >> ~/.ammocoin11/ammocoin.conf
```

### Network Performance

#### ❌ "Slow Transaction Propagation"
**Symptoms**: Sent transactions take long to appear in network
**Solutions**:
```bash
# Increase connections
echo "maxconnections=50" >> ~/.ammocoin11/ammocoin.conf

# Connect to well-connected nodes
ammocoin-cli addnode "fast_node_ip:37020" "add"

# Increase transaction fee
# Higher fees get priority
```

#### ❌ "Bandwidth Issues"
**Symptoms**: High data usage, slow internet
**Solutions**:
```bash
# Limit bandwidth
echo "maxreceivebuffer=1000" >> ~/.ammocoin11/ammocoin.conf
echo "maxsendbuffer=1000" >> ~/.ammocoin11/ammocoin.conf

# Reduce connections
echo "maxconnections=10" >> ~/.ammocoin11/ammocoin.conf
```

## 🛠️ Advanced Diagnostics

### Debug Logging

#### Enable Detailed Logging
```bash
# Add to ammocoin.conf
debug=1
debuglogfile=debug.log
logtimestamps=1

# Specific categories
debug=net
debug=mempool
debug=stakeweight
```

#### Log Analysis
```bash
# Monitor live logs
tail -f ~/.ammocoin11/debug.log

# Search for errors
grep -i error ~/.ammocoin11/debug.log

# Find staking messages
grep -i stake ~/.ammocoin11/debug.log

# Network connection logs
grep -i "connection" ~/.ammocoin11/debug.log
```

### System Health Check Script
```bash
#!/bin/bash
# ammocoin_health_check.sh

echo "=== AMMOcoin Health Check ==="
echo "Date: $(date)"
echo ""

# Basic connectivity
echo "1. Daemon Status:"
if pgrep ammocoind > /dev/null; then
    echo "   ✅ Daemon running"
else
    echo "   ❌ Daemon not running"
    exit 1
fi

# Network connectivity
PEERS=$(ammocoin-cli getconnectioncount 2>/dev/null)
echo "2. Network:"
if [ "$PEERS" -gt 3 ]; then
    echo "   ✅ Connected peers: $PEERS"
else
    echo "   ⚠️  Low peer count: $PEERS"
fi

# Sync status
BLOCKS=$(ammocoin-cli getblockcount 2>/dev/null)
HEADERS=$(ammocoin-cli getblockchaininfo 2>/dev/null | jq -r .headers)
echo "3. Sync Status:"
if [ "$BLOCKS" = "$HEADERS" ]; then
    echo "   ✅ Fully synced: $BLOCKS blocks"
else
    echo "   ⚠️  Syncing: $BLOCKS/$HEADERS blocks"
fi

# Staking status
STAKING=$(ammocoin-cli getstakingstatus 2>/dev/null | jq -r .staking_status)
echo "4. Staking:"
if [ "$STAKING" = "true" ]; then
    echo "   ✅ Staking active"
else
    echo "   ❌ Not staking"
fi

# Disk space
SPACE=$(df ~/.ammocoin11/ | awk 'NR==2{print $5}' | sed 's/%//')
echo "5. Disk Space:"
if [ "$SPACE" -lt 85 ]; then
    echo "   ✅ Disk usage: ${SPACE}%"
else
    echo "   ⚠️  High disk usage: ${SPACE}%"
fi

echo ""
echo "Health check complete."
```

### Recovery Procedures

#### Complete Wallet Recovery
```bash
# 1. Stop wallet
ammocoin-cli stop

# 2. Backup current state
cp -r ~/.ammocoin11 ~/.ammocoin11_backup_$(date +%Y%m%d)

# 3. Restore from clean backup
rm -rf ~/.ammocoin11
cp -r ~/wallet_backup ~/.ammocoin11

# 4. Restart and rescan
ammocoind -rescan

# 5. Verify restore
ammocoin-cli getbalance
```

#### Emergency Data Reset
```bash
# DANGER: Only if wallet.dat is safely backed up
ammocoin-cli stop
cd ~/.ammocoin11
rm -rf blocks chainstate peers.dat banlist.dat
# Keep: wallet.dat, ammocoin.conf, masternode.conf
ammocoind
```

## 📞 Getting Help

### Self-Help Resources
1. **Check Logs**: Always start with debug.log
2. **Search Documentation**: Use this guide's search function
3. **Community Forums**: Search existing threads
4. **GitHub Issues**: Check for known bugs

### When to Seek Help
- **After trying** documented solutions
- **With specific** error messages
- **Including** relevant log excerpts
- **With details** about your setup

### Support Channels
- **Discord**: #technical-support
- **Telegram**: @AMMOcoinSupport
- **Forum**: forum.ammocoin.org/support
- **GitHub**: github.com/everquin/AMMOcoin/issues

### Emergency Situations
- **Wallet won't start**: Try emergency fixes first
- **Lost access**: Focus on backup restoration
- **Network attacks**: Contact security team immediately
- **Critical bugs**: Report on GitHub with "critical" label

---

## ✅ Troubleshooting Checklist

### Before Seeking Help
- [ ] Tried basic restart (stop/start wallet)
- [ ] Checked debug.log for error messages
- [ ] Verified system requirements met
- [ ] Confirmed latest software version
- [ ] Reviewed relevant documentation section

### Information to Gather
- [ ] Operating system and version
- [ ] AMMOcoin version (--version output)
- [ ] Error messages (exact text)
- [ ] Log file excerpts (relevant portions)
- [ ] Steps to reproduce issue

### Prevention Measures
- [ ] Regular wallet backups scheduled
- [ ] Configuration files documented
- [ ] Monitoring scripts deployed
- [ ] Update procedures established
- [ ] Emergency contacts saved

**🔧 Most AMMOcoin issues can be resolved with the solutions in this guide. When in doubt, start with the basics: restart, check logs, verify configuration.**

---

*Next: Check the [FAQ](./10-faq.md) for quick answers to common questions.*