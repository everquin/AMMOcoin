# AMMOcoin User Guide

## 🚀 **Getting Started**

This guide covers all essential operations for AMMOcoin users, from basic wallet functions to advanced privacy features.

## 📱 **Basic Wallet Operations**

### Starting AMMOcoin
```bash
# Start daemon
ammocoind -daemon

# Check if running
ammocoin-cli getinfo
```

### Creating Addresses
```bash
# Create new transparent address
ammocoin-cli getnewaddress

# Create new address with label
ammocoin-cli getnewaddress "My Address"

# List all addresses
ammocoin-cli listaddressgroupings
```

### Sending Transactions
```bash
# Send to address
ammocoin-cli sendtoaddress "address" amount

# Send with specific fee
ammocoin-cli sendtoaddress "address" amount "" "" true

# Send to multiple addresses
ammocoin-cli sendmany "" '{"address1":10,"address2":5}'
```

### Checking Balances
```bash
# Total balance
ammocoin-cli getbalance

# Unconfirmed balance
ammocoin-cli getunconfirmedbalance

# Balance by account
ammocoin-cli getbalance "account_name"
```

## 🛡️ **Privacy Features (Sapling)**

### Shielded Addresses
```bash
# Create shielded address
ammocoin-cli getnewshieldedaddress

# List shielded addresses
ammocoin-cli listshieldedaddresses
```

### Shield Transactions
```bash
# Shield transparent coins
ammocoin-cli shieldsendmany "from_address" '[{"address":"shielded_address","amount":10}]'

# Private transfer between shielded addresses
ammocoin-cli sendmany "" '{"shielded_address":amount}' 1 "" [] true
```

### Privacy Operations
```bash
# View shielded balance
ammocoin-cli getshieldedbalance

# List shielded transactions
ammocoin-cli listshieldedtransactions

# Get payment disclosure
ammocoin-cli getpaymentdisclosure "txid" "js_index" "output_index"
```

## 💰 **Staking Operations**

### Enable Staking
```bash
# Unlock wallet for staking
ammocoin-cli walletpassphrase "your_passphrase" 999999 true

# Check staking status
ammocoin-cli getstakinginfo
```

### Staking Information
```bash
# View staking stats
ammocoin-cli getstakinginfo

# Check network weight
ammocoin-cli getnetworkinfo

# View recent stakes
ammocoin-cli liststakerecords
```

## 🏛️ **Masternode Operations**

### Masternode Setup
```bash
# Generate masternode key
ammocoin-cli createmasternodekey

# Start masternode
ammocoin-cli startmasternode "local" false

# Check masternode status
ammocoin-cli getmasternodestatus
```

### Masternode Information
```bash
# List masternodes
ammocoin-cli listmasternodes

# Get masternode count
ammocoin-cli getmasternodecount

# View masternode scores
ammocoin-cli listmasternodescores
```

## 🔐 **Security Operations**

### Wallet Encryption
```bash
# Encrypt wallet
ammocoin-cli encryptwallet "secure_passphrase"

# Change passphrase
ammocoin-cli walletpassphrasechange "old_passphrase" "new_passphrase"

# Lock wallet
ammocoin-cli walletlock
```

### Backup & Recovery
```bash
# Backup wallet
ammocoin-cli backupwallet "backup_filename.dat"

# Dump private key
ammocoin-cli dumpprivkey "address"

# Import private key
ammocoin-cli importprivkey "private_key"
```

## 📊 **Information Commands**

### Blockchain Information
```bash
# Blockchain info
ammocoin-cli getblockchaininfo

# Network info
ammocoin-cli getnetworkinfo

# Memory pool info
ammocoin-cli getmempoolinfo
```

### Transaction Information
```bash
# Get transaction details
ammocoin-cli gettransaction "txid"

# List transactions
ammocoin-cli listtransactions

# Get transaction history
ammocoin-cli listsinceblock
```

## 🔧 **Advanced Features**

### Multi-signature Transactions
```bash
# Create multisig address
ammocoin-cli createmultisig 2 '["pubkey1","pubkey2","pubkey3"]'

# Sign transaction
ammocoin-cli signrawtransaction "hex_string"

# Send raw transaction
ammocoin-cli sendrawtransaction "signed_hex"
```

### Raw Transactions
```bash
# Create raw transaction
ammocoin-cli createrawtransaction '[{"txid":"id","vout":0}]' '{"address":amount}'

# Sign raw transaction
ammocoin-cli signrawtransaction "hex"

# Decode transaction
ammocoin-cli decoderawtransaction "hex"
```

## 🚨 **Emergency Procedures**

### Wallet Recovery
```bash
# Rescan blockchain
ammocoin-cli rescanblockchain

# Repair wallet
ammocoind -salvagewallet

# Reindex blockchain
ammocoind -reindex
```

### Network Issues
```bash
# Add nodes manually
ammocoin-cli addnode "ip:port" "add"

# Get peer info
ammocoin-cli getpeerinfo

# Ban/unban nodes
ammocoin-cli setban "ip" "add"
```

## ⚙️ **Configuration Tips**

### Performance Optimization
```ini
# In ammocoin.conf
dbcache=1024
maxmempool=512
maxconnections=64
```

### Security Settings
```ini
# Enhanced security
rpcbind=127.0.0.1
rpcallowip=127.0.0.1
disablewallet=0
```

## 🆘 **Getting Help**

### Command Help
```bash
# List all commands
ammocoin-cli help

# Get command details
ammocoin-cli help "command_name"

# Get wallet help
ammocoin-cli help | grep wallet
```

### Common Issues
- **Sync Problems**: Check connections and restart with `-reindex`
- **Staking Not Working**: Verify wallet unlock and balance
- **Transaction Stuck**: Check mempool and fees
- **Connection Issues**: Add seed nodes manually

---

**Need More Help?**
- Check our [FAQ](FAQ.md)
- Review [Security Guide](SECURITY.md)
- Visit [Community Resources](../README.md#community--support)