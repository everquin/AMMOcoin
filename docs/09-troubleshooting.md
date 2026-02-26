# 🔧 AMMOcoin Troubleshooting Guide

Complete solutions for common AMMOcoin issues. Find quick fixes and detailed diagnostics for wallet, staking, masternode, and network problems.

## 🚨 Emergency Quick Fixes

### Wallet Won't Start
```bash
# Quick diagnosis
ps aux | grep ammocoin    # Check if already running
pkill ammocoind          # Force close if stuck
rm ~/.ammocoin/ammocoin.conf.lock  # Remove lock file
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
ammocoin-cli addnode "node.ammocoin.org:37020" "add"
```

### Staking Stopped
```bash
# Quick staking restart
ammocoin-cli walletpassphrase "your_password" 999999 true
ammocoin-cli getstakinginfo  # Verify enabled: true
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
cp wallet_backup.dat ~/.ammocoin/wallet.dat
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
rm ~/.ammocoin/.lock
rm ~/.ammocoin/ammocoin.conf.lock

# Restart
ammocoind
```

#### ❌ "Insufficient Disk Space"
**Symptoms**: Wallet crashes, sync stops
**Solutions**:
```bash
# Check disk space
df -h ~/.ammocoin/

# Clean up log files
truncate -s 0 ~/.ammocoin/debug.log

# Enable pruning (if acceptable)
echo "prune=2000" >> ~/.ammocoin/ammocoin.conf
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

# If still stuck, restart sync
ammocoin-cli stop
rm -rf ~/.ammocoin/peers.dat
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
ammocoin-cli getstakinginfo

# Look for:
# "enabled": false
# "staking": false
# "errors": "Wallet is locked"
```

**Solutions**:
```bash
# Unlock wallet for staking
ammocoin-cli walletpassphrase "password" 999999 true

# Enable staking in config
echo "staking=1" >> ~/.ammocoin/ammocoin.conf

# Restart wallet
ammocoin-cli stop && ammocoind
```

#### ❌ "No Staking Rewards"
**Symptoms**: Staking active but no rewards
**Diagnosis**:
```bash
# Check staking weight
ammocoin-cli getstakinginfo | grep weight

# Check coin age
ammocoin-cli listunspent | grep confirmations

# Check network weight
ammocoin-cli getstakinginfo | grep netstakeweight
```

**Solutions**:
```bash
# Ensure coins are mature (>8 hours)
# Small amounts may take weeks to stake

# Split large UTXOs
ammocoin-cli splitstakingutxos 5000

# Improve uptime
# Keep wallet online 24/7

# Check for errors
tail -f ~/.ammocoin/debug.log | grep -i stake
```

#### ❌ "Very Low Staking Weight"
**Symptoms**: expectedtime showing years
**Solutions**:
```bash
# Combine dust UTXOs
ammocoin-cli combineutxos 100

# Increase coin amount
# Buy more AMMO

# Check network conditions
ammocoin-cli getstakinginfo | grep difficulty
```

### Staking Performance Issues

#### ❌ "Inconsistent Staking"
**Symptoms**: Staking turns on/off randomly
**Diagnosis**:
```bash
# Monitor staking status
watch -n 30 'ammocoin-cli getstakinginfo | grep enabled'

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
grep -i "disconnect" ~/.ammocoin/debug.log
```

## 🏛️ Masternode Issues

### Masternode Setup Problems

#### ❌ "Masternode Not Starting"
**Symptoms**: Status shows "MISSING" or won't start
**Diagnosis**:
```bash
# Check collateral
ammocoin-cli masternode outputs

# Verify 15+ confirmations
ammocoin-cli gettransaction "collateral_txid"

# Check masternode.conf syntax
cat ~/.ammocoin/masternode.conf
```

**Solutions**:
```bash
# Verify masternode.conf format
# alias IP:port masternodeprivkey collateral_txid output_index

# Example correct format:
# mn1 192.168.1.100:37020 7abc...xyz a1b2c3...890 0

# Restart both local and remote
ammocoin-cli stop       # Local
ssh user@vps ammocoind stop  # Remote
# Start remote first, then local
```

#### ❌ "PRE_ENABLED Status Stuck"
**Symptoms**: Never reaches ENABLED status
**Diagnosis**:
```bash
# Check remote server
ssh user@vps ammocoin-cli masternode status

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
ammocoin-cli masternode start-alias "mn1"

# Wait for network propagation (up to 30 minutes)
```

### Masternode Monitoring Issues

#### ❌ "Masternode Expired"
**Symptoms**: Status changes to EXPIRED
**Diagnosis**:
```bash
# Check last seen time
ammocoin-cli masternode list | grep "your_ip"

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
ammocoin-cli masternode start-alias "mn1"

# Monitor server stability
ssh user@vps tail -f ~/.ammocoin/debug.log
```

#### ❌ "Low Masternode Rewards"
**Symptoms**: Infrequent or no masternode payments
**Diagnosis**:
```bash
# Check payment queue position
ammocoin-cli masternode winners

# Verify masternode is active
ammocoin-cli masternode list active | grep "your_ip"

# Check network masternode count
ammocoin-cli masternode count
```

**Solutions**:
```bash
# Ensure consistent uptime
# Monitor server with external service

# Check for network issues
ssh user@vps ammocoin-cli getpeerinfo

# Verify correct payment address
grep -i "masternode" ~/.ammocoin/ammocoin.conf
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
ammocoin-cli addnode "seed.ammocoin.org:37020" "add"

# Check ISP blocking
# Try different port in config
port=47020

# Use VPN if needed
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
grep -i "error\|corrupt" ~/.ammocoin/debug.log
```

**Solutions**:
```bash
# Reindex blockchain
ammocoin-cli stop
ammocoind -reindex

# If reindex fails, resync
ammocoin-cli stop
rm -rf ~/.ammocoin/blocks ~/.ammocoin/chainstate
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
grep -v testnet ~/.ammocoin/ammocoin.conf > temp.conf
mv temp.conf ~/.ammocoin/ammocoin.conf

# Clear testnet data
rm -rf ~/.ammocoin/testnet3/

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
df -h ~/.ammocoin/

# Check file permissions
ls -la ~/.ammocoin/wallet.dat
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
sudo chown -R $USER:$USER ~/.ammocoin/

# Fix permissions
chmod 700 ~/.ammocoin/
chmod 600 ~/.ammocoin/wallet.dat
chmod 600 ~/.ammocoin/ammocoin.conf
```

#### ❌ "RPC Connection Failed"
**Symptoms**: CLI commands don't work
**Diagnosis**:
```bash
# Check if daemon is running
ps aux | grep ammocoind

# Check RPC configuration
grep -E "rpc" ~/.ammocoin/ammocoin.conf

# Test RPC connection
curl --user user:pass --data-binary '{"jsonrpc": "1.0", "id":"test", "method": "getinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:51473/
```

**Solutions**:
```bash
# Start daemon if not running
ammocoind

# Configure RPC access
echo "server=1" >> ~/.ammocoin/ammocoin.conf
echo "rpcuser=user" >> ~/.ammocoin/ammocoin.conf
echo "rpcpassword=pass" >> ~/.ammocoin/ammocoin.conf

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
echo "dbcache=1024" >> ~/.ammocoin/ammocoin.conf

# Use SSD instead of HDD
# Move data directory to SSD

# Reduce startup verification
echo "checkblocks=50" >> ~/.ammocoin/ammocoin.conf
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
echo "maxmempool=50" >> ~/.ammocoin/ammocoin.conf
echo "dbcache=200" >> ~/.ammocoin/ammocoin.conf

# Enable pruning to save disk space
echo "prune=2000" >> ~/.ammocoin/ammocoin.conf
```

### Network Performance

#### ❌ "Slow Transaction Propagation"
**Symptoms**: Sent transactions take long to appear in network
**Solutions**:
```bash
# Increase connections
echo "maxconnections=50" >> ~/.ammocoin/ammocoin.conf

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
echo "maxreceivebuffer=1000" >> ~/.ammocoin/ammocoin.conf
echo "maxsendbuffer=1000" >> ~/.ammocoin/ammocoin.conf

# Reduce connections
echo "maxconnections=10" >> ~/.ammocoin/ammocoin.conf

# Use pruning
echo "prune=1000" >> ~/.ammocoin/ammocoin.conf
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
tail -f ~/.ammocoin/debug.log

# Search for errors
grep -i error ~/.ammocoin/debug.log

# Find staking messages
grep -i stake ~/.ammocoin/debug.log

# Network connection logs
grep -i "connection" ~/.ammocoin/debug.log
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
STAKING=$(ammocoin-cli getstakinginfo 2>/dev/null | jq -r .enabled)
echo "4. Staking:"
if [ "$STAKING" = "true" ]; then
    echo "   ✅ Staking enabled"
else
    echo "   ❌ Staking disabled"
fi

# Disk space
SPACE=$(df ~/.ammocoin/ | awk 'NR==2{print $5}' | sed 's/%//')
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
cp -r ~/.ammocoin ~/.ammocoin_backup_$(date +%Y%m%d)

# 3. Restore from clean backup
rm -rf ~/.ammocoin
cp -r ~/wallet_backup ~/.ammocoin

# 4. Restart and rescan
ammocoind -rescan

# 5. Verify restore
ammocoin-cli getbalance
```

#### Emergency Data Reset
```bash
# DANGER: Only if wallet.dat is safely backed up
ammocoin-cli stop
cd ~/.ammocoin
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