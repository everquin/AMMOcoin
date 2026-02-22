# 💻 AMMOcoin Terminal Commands Reference

Complete reference guide for AMMOcoin CLI (Command Line Interface) commands. Master the terminal for advanced wallet management and network operations.

## 🚀 Getting Started with CLI

### Installation & Setup
```bash
# Linux/macOS - Add to PATH
export PATH=$PATH:/path/to/ammocoin

# Windows - Add to system PATH or use full path
C:\AMMOcoin\ammocoin-cli.exe

# Verify installation
ammocoin-cli --version
```

### Basic CLI Structure
```bash
# Standard format
ammocoin-cli [options] <command> [params]

# With configuration
ammocoin-cli -rpcuser=user -rpcpassword=pass <command>

# Help for any command
ammocoin-cli help <command>
```

### Common Options
```bash
-conf=<file>       # Specify config file location
-rpcuser=<user>    # RPC username
-rpcpassword=<pw>  # RPC password
-rpcport=<port>    # RPC port (default: 51473)
-rpcconnect=<ip>   # RPC server IP
-testnet           # Use testnet
```

## 💰 Wallet Commands

### Balance & Account Management
```bash
# Get wallet balance
ammocoin-cli getbalance

# Get unconfirmed balance
ammocoin-cli getunconfirmedbalance

# Get wallet info
ammocoin-cli getwalletinfo

# List account balances
ammocoin-cli listaccounts

# Get account balance
ammocoin-cli getbalance "account_name"

# Create new account
ammocoin-cli getaccountaddress "new_account"
```

### Address Management
```bash
# Generate new receiving address
ammocoin-cli getnewaddress

# Generate new address with label
ammocoin-cli getnewaddress "payment_label"

# List all addresses
ammocoin-cli listaddressgroupings

# Get address info
ammocoin-cli getaddressinfo "address"

# Validate address
ammocoin-cli validateaddress "address"

# Get account for address
ammocoin-cli getaccount "address"

# Set account for address
ammocoin-cli setaccount "address" "account_name"
```

### Sending Transactions
```bash
# Send to address
ammocoin-cli sendtoaddress "address" amount

# Send with comment
ammocoin-cli sendtoaddress "address" amount "comment" "to_comment"

# Send from specific account
ammocoin-cli sendfrom "account" "address" amount

# Send to multiple addresses
ammocoin-cli sendmany "account" '{"addr1":amount1,"addr2":amount2}'

# Create raw transaction
ammocoin-cli createrawtransaction '[{"txid":"id","vout":n}]' '{"address":amount}'

# Sign raw transaction
ammocoin-cli signrawtransaction "hex_string"

# Send raw transaction
ammocoin-cli sendrawtransaction "hex_string"
```

### Transaction History
```bash
# List recent transactions
ammocoin-cli listtransactions

# List specific number of transactions
ammocoin-cli listtransactions "*" 50

# List transactions for account
ammocoin-cli listtransactions "account_name" 10

# Get transaction details
ammocoin-cli gettransaction "txid"

# List unspent outputs
ammocoin-cli listunspent

# List unspent with minimum confirmations
ammocoin-cli listunspent 6

# Get received by address
ammocoin-cli getreceivedbyaddress "address"

# List received by address
ammocoin-cli listreceivedbyaddress
```

## 🔐 Wallet Security Commands

### Encryption & Backup
```bash
# Encrypt wallet
ammocoin-cli encryptwallet "passphrase"

# Change wallet passphrase
ammocoin-cli walletpassphrasechange "old" "new"

# Unlock wallet temporarily
ammocoin-cli walletpassphrase "passphrase" timeout

# Unlock for staking only
ammocoin-cli walletpassphrase "passphrase" timeout true

# Lock wallet
ammocoin-cli walletlock

# Dump wallet to file
ammocoin-cli dumpwallet "filename.txt"

# Import wallet from file
ammocoin-cli importwallet "filename.txt"

# Backup wallet
ammocoin-cli backupwallet "backup_filename.dat"
```

### Private Key Management
```bash
# Dump private key for address
ammocoin-cli dumpprivkey "address"

# Import private key
ammocoin-cli importprivkey "privatekey"

# Import private key with label
ammocoin-cli importprivkey "privatekey" "label"

# Import private key without rescan
ammocoin-cli importprivkey "privatekey" "label" false

# Generate new key pair
ammocoin-cli getnewaddress
```

## 🎯 Staking Commands

### Staking Information
```bash
# Get staking information
ammocoin-cli getstakinginfo

# Check if wallet is staking
ammocoin-cli getstakingstatus

# Get stake split threshold
ammocoin-cli getstakesplitthreshold

# Set stake split threshold
ammocoin-cli setstakesplitthreshold amount

# Get reserve balance
ammocoin-cli getreservebalance

# Set reserve balance (coins not used for staking)
ammocoin-cli setreservebalance amount
```

### Staking Optimization
```bash
# Split staking UTXOs for optimal staking
ammocoin-cli splitstakingutxos target_size

# Combine small UTXOs
ammocoin-cli combineutxos [amount]

# List stakeable coins
ammocoin-cli listunspent 1 999999 [] true

# Check coin age
ammocoin-cli listunspent | grep -A5 -B5 "confirmations"
```

## 🏛️ Masternode Commands

### Masternode Management
```bash
# Generate masternode private key
ammocoin-cli masternode genkey

# Get masternode outputs (collateral)
ammocoin-cli masternode outputs

# Start masternode
ammocoin-cli masternode start-alias "alias_name"

# Start all masternodes
ammocoin-cli masternode start-all

# Get masternode status
ammocoin-cli masternode status

# List masternode configuration
ammocoin-cli masternode list-conf

# Debug masternode
ammocoin-cli masternode debug
```

### Masternode Network Information
```bash
# List all masternodes
ammocoin-cli masternode list

# List active masternodes
ammocoin-cli masternode list active

# List masternode protocol versions
ammocoin-cli masternode list protocol

# Get masternode count
ammocoin-cli masternode count

# Get masternode winners
ammocoin-cli masternode winners

# Current masternode winner
ammocoin-cli masternode current
```

## 🌐 Network Commands

### Network Information
```bash
# Get network info
ammocoin-cli getnetworkinfo

# Get blockchain info
ammocoin-cli getblockchaininfo

# Get peer info
ammocoin-cli getpeerinfo

# Get connection count
ammocoin-cli getconnectioncount

# Get network hash rate
ammocoin-cli getnetworkhashps

# Get difficulty
ammocoin-cli getdifficulty
```

### Peer Management
```bash
# Add peer node
ammocoin-cli addnode "ip:port" "add"

# Remove peer node
ammocoin-cli addnode "ip:port" "remove"

# Try connection to peer
ammocoin-cli addnode "ip:port" "onetry"

# List added nodes
ammocoin-cli getaddednodeinfo

# Disconnect peer
ammocoin-cli disconnectnode "ip:port"

# Ban peer
ammocoin-cli setban "ip" "add" bantime

# List banned peers
ammocoin-cli listbanned
```

### Blockchain Commands
```bash
# Get best block hash
ammocoin-cli getbestblockhash

# Get block count
ammocoin-cli getblockcount

# Get block hash by height
ammocoin-cli getblockhash height

# Get block info
ammocoin-cli getblock "blockhash"

# Get block header
ammocoin-cli getblockheader "blockhash"

# Get chain tips
ammocoin-cli getchaintips

# Get mempool info
ammocoin-cli getmempoolinfo

# Get raw mempool
ammocoin-cli getrawmempool
```

## 🗳️ Governance Commands

### Budget/Proposal System
```bash
# List budget proposals
ammocoin-cli getbudgetinfo

# Get budget info for specific proposal
ammocoin-cli getbudgetinfo "proposal_name"

# Prepare budget proposal
ammocoin-cli preparebudget "proposal_name" "url" payment_count block_start "address" monthly_payment

# Submit budget proposal
ammocoin-cli submitbudget "proposal_name" "url" payment_count block_start "address" monthly_payment "fee_txid"

# Vote on proposal
ammocoin-cli mnbudgetvote "local|many|alias" "proposal_hash" "yes|no" "alias_name"

# Get budget votes
ammocoin-cli getbudgetvotes "proposal_name"

# List budget proposals with votes
ammocoin-cli getbudgetprojection

# Get next superblock
ammocoin-cli getnextsuperblock
```

### Voting & Governance
```bash
# Vote on governance proposal
ammocoin-cli gobject vote-conf "governance_hash" funding yes "alias_name"

# List governance objects
ammocoin-cli gobject list

# Get governance info
ammocoin-cli getgovernanceinfo

# Prepare governance object
ammocoin-cli gobject prepare parent_hash revision_number time data_hex

# Submit governance object
ammocoin-cli gobject submit parent_hash revision_number time data_hex "fee_txid"
```

## 🔧 System & Debug Commands

### Node Management
```bash
# Stop daemon
ammocoin-cli stop

# Get info
ammocoin-cli getinfo

# Get uptime
ammocoin-cli uptime

# Get memory info
ammocoin-cli getmemoryinfo

# Get RPC info
ammocoin-cli getrpcinfo
```

### Debug & Monitoring
```bash
# Get debug info
ammocoin-cli getdebuginfo

# Set log level
ammocoin-cli logging '["net","tor"]' '["http"]'

# Generate blocks (regtest only)
ammocoin-cli generate numblocks

# Invalidate block
ammocoin-cli invalidateblock "blockhash"

# Reconsider block
ammocoin-cli reconsiderblock "blockhash"

# Ping peers
ammocoin-cli ping

# Get network totals
ammocoin-cli getnettotals
```

### Configuration Commands
```bash
# Get configuration setting
ammocoin-cli getconfig setting_name

# List configuration
ammocoin-cli listconfig

# Reload configuration
ammocoin-cli reloadconfig

# Get data directory
ammocoin-cli getdatadir
```

## 📊 Advanced Commands

### Raw Transactions
```bash
# Decode raw transaction
ammocoin-cli decoderawtransaction "hex_string"

# Get raw transaction
ammocoin-cli getrawtransaction "txid"

# Get raw transaction with details
ammocoin-cli getrawtransaction "txid" 1

# Fund raw transaction
ammocoin-cli fundrawtransaction "hex_string"

# Create multisig address
ammocoin-cli createmultisig num_required '["pubkey1","pubkey2"]'

# Add multisig address
ammocoin-cli addmultisigaddress num_required '["address1","address2"]'
```

### Script & Address Utilities
```bash
# Decode script
ammocoin-cli decodescript "hex_script"

# Create script signature
ammocoin-cli signmessage "address" "message"

# Verify message signature
ammocoin-cli verifymessage "address" "signature" "message"

# Estimate fee
ammocoin-cli estimatefee num_blocks

# Estimate smart fee
ammocoin-cli estimatesmartfee num_blocks

# Get new address for specific type
ammocoin-cli getnewaddress "label" "legacy|p2sh-segwit|bech32"
```

## 🛡️ Security Commands

### Wallet Security
```bash
# Check wallet integrity
ammocoin-cli checkwallet

# Repair wallet
ammocoin-cli repairwallet

# Rescan blockchain
ammocoin-cli rescanblockchain start_height

# Abandon transaction
ammocoin-cli abandontransaction "txid"

# Bump transaction fee
ammocoin-cli bumpfee "txid"
```

### Network Security
```bash
# Get banned peers
ammocoin-cli listbanned

# Clear banned peers
ammocoin-cli clearbanned

# Set network active
ammocoin-cli setnetworkactive true|false

# Get warnings
ammocoin-cli getwarnings

# Get chainwork
ammocoin-cli getchainwork
```

## 📝 Batch Operations & Scripting

### Batch Commands
```bash
# Execute multiple commands from file
ammocoin-cli batch commands.txt

# Example batch file (commands.txt):
getbalance
getblockcount
getstakinginfo
getnetworkinfo
```

### Useful Scripts

#### Monitor Staking Status
```bash
#!/bin/bash
# monitor_staking.sh
while true; do
  echo "=== $(date) ==="
  ammocoin-cli getstakinginfo | grep -E "(enabled|staking|weight)"
  echo ""
  sleep 300  # Check every 5 minutes
done
```

#### Backup Automation
```bash
#!/bin/bash
# backup_wallet.sh
DATE=$(date +%Y%m%d_%H%M%S)
ammocoin-cli backupwallet "backup_$DATE.dat"
echo "Wallet backed up to backup_$DATE.dat"
```

#### Balance Monitor
```bash
#!/bin/bash
# balance_monitor.sh
BALANCE=$(ammocoin-cli getbalance)
echo "Current balance: $BALANCE AMMO"
echo "Last checked: $(date)"
```

## 🚨 Emergency Commands

### Recovery Operations
```bash
# Emergency stop
ammocoin-cli stop

# Force stop (if regular stop fails)
pkill ammocoind

# Start with reindex
ammocoind -reindex

# Start with rescan
ammocoind -rescan

# Start in safe mode
ammocoind -safemode

# Recovery from corrupted blockchain
rm -rf ~/.ammocoin/blocks ~/.ammocoin/chainstate
ammocoind
```

### Diagnostic Commands
```bash
# Check database
ammocoin-cli verifychain

# Verify database completely
ammocoin-cli verifychain 4 0

# Get block chain info
ammocoin-cli getblockchaininfo

# Check if daemon is running
ammocoin-cli ping

# Test RPC connection
ammocoin-cli getconnectioncount
```

## 💡 Pro Tips & Shortcuts

### Command Aliases
```bash
# Add to ~/.bashrc or ~/.zshrc
alias ac='ammocoin-cli'
alias balance='ammocoin-cli getbalance'
alias stake='ammocoin-cli getstakinginfo'
alias peers='ammocoin-cli getconnectioncount'
alias sync='ammocoin-cli getblockchaininfo | grep blocks'
```

### Useful One-Liners
```bash
# Check sync progress
ammocoin-cli getblockchaininfo | grep -E "(blocks|headers|verificationprogress)"

# Monitor mempool
watch -n 5 'ammocoin-cli getmempoolinfo'

# List recent staking rewards
ammocoin-cli listtransactions "*" 50 | grep -A5 -B5 "stake"

# Check all address balances
ammocoin-cli listaddressgroupings | grep -E "\s+[0-9]+\."

# Monitor network weight
watch -n 30 'ammocoin-cli getstakinginfo | grep netstakeweight'
```

### JSON Processing with jq
```bash
# Install jq for JSON processing
sudo apt install jq  # Linux
brew install jq      # macOS

# Pretty print JSON output
ammocoin-cli getinfo | jq .

# Extract specific values
ammocoin-cli getblockchaininfo | jq .blocks
ammocoin-cli getstakinginfo | jq .enabled

# Complex filtering
ammocoin-cli listunspent | jq '.[] | select(.amount > 100)'
```

## 📚 Help & Documentation

### Built-in Help
```bash
# List all commands
ammocoin-cli help

# Get help for specific command
ammocoin-cli help getbalance

# Get RPC command list
ammocoin-cli help | grep -E "^[a-z]"

# Search for commands
ammocoin-cli help | grep stake
```

### Error Codes & Troubleshooting
```bash
# Common error codes:
# -28: Loading block index
# -4: Insufficient funds
# -5: Invalid address
# -6: Account has insufficient funds
# -13: Error parsing JSON
# -32601: Method not found
```

---

## ✅ Command Reference Checklist

### Essential Commands to Master
- [ ] `getbalance` - Check wallet balance
- [ ] `getnewaddress` - Generate receiving address
- [ ] `sendtoaddress` - Send transactions
- [ ] `getstakinginfo` - Monitor staking
- [ ] `getnetworkinfo` - Check network status
- [ ] `walletpassphrase` - Unlock wallet
- [ ] `backupwallet` - Create backups
- [ ] `listtransactions` - View transaction history

### Advanced Commands for Power Users
- [ ] `masternode` commands - Manage masternodes
- [ ] `gobject` commands - Governance voting
- [ ] Raw transaction commands
- [ ] Debug and monitoring commands
- [ ] Batch operation scripts

**💻 You now have complete command-line control over your AMMOcoin node and wallet!**

---

*Next: Learn about [DAO Participation](./06-dao-participation.md) to vote on network governance.*