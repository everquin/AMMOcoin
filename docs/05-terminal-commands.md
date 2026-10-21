# 💻 AMMOcoin Terminal Commands Reference

Complete reference guide for AMMOcoin CLI (Command Line Interface) commands. Master the terminal for advanced wallet management and network operations.

> ℹ️ Written for **v1.1.1 (upcoming)**: Proof-of-Stake from block 2,776, no mining. Mainnet ports: **P2P 37020**, **RPC 51473**. Default data folder: Linux `~/.ammocoin11`, macOS `~/Library/Application Support/AMMOcoin11`, Windows `%APPDATA%\AMMOcoin11`. Run `ammocoin-cli help` on your node for the authoritative command list.

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
-datadir=<dir>     # Data directory (default: ~/.ammocoin11 on Linux)
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

# List labels
ammocoin-cli listlabels

# Addresses for a label
ammocoin-cli getaddressesbylabel "label_name"

# Shielded (Sapling) balance
ammocoin-cli getshieldbalance
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

# Set label for address
ammocoin-cli setlabel "address" "label_name"

# New shielded (Sapling) address
ammocoin-cli getnewshieldaddress
```

### Sending Transactions
```bash
# Send to address
ammocoin-cli sendtoaddress "address" amount

# Send with comment
ammocoin-cli sendtoaddress "address" amount "comment" "to_comment"

# Send to multiple addresses (first argument is a dummy, use "")
ammocoin-cli sendmany "" '{"addr1":amount1,"addr2":amount2}'

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
# Check if wallet is staking (staking_status, mature UTXOs, wallet unlocked, etc.)
ammocoin-cli getstakingstatus

# Get stake split threshold
ammocoin-cli getstakesplitthreshold

# Set stake split threshold
ammocoin-cli setstakesplitthreshold amount
```

### Staking Optimization
```bash
# Auto-combine small UTXOs (threshold in AMMO)
ammocoin-cli setautocombinethreshold true 500
ammocoin-cli getautocombinethreshold

# List stakeable coins (600 confirmations needed to stake)
ammocoin-cli listunspent 600

# Check coin maturity
ammocoin-cli listunspent | grep -A5 -B5 "confirmations"
```

### Cold Staking
```bash
# Staking server: create a staking (S...) address
ammocoin-cli getnewstakingaddress
ammocoin-cli liststakingaddresses

# Owner wallet: delegate coins to the staking address
ammocoin-cli delegatestake "S_STAKING_ADDRESS" amount
ammocoin-cli delegatestake "S_STAKING_ADDRESS" amount "A_OWNER_ADDRESS"
# Owner address not in this wallet (e.g. offline): ext_owner=true
ammocoin-cli delegatestake "S_STAKING_ADDRESS" amount "A_OWNER_ADDRESS" true

# Staking server: whitelist the owner so its delegations are staked
ammocoin-cli delegatoradd "A_OWNER_ADDRESS"
ammocoin-cli listdelegators
ammocoin-cli delegatorremove "A_OWNER_ADDRESS"

# Balances and UTXOs
ammocoin-cli getcoldstakingbalance    # server: coins delegated to it
ammocoin-cli getdelegatedbalance      # owner: coins it has delegated
ammocoin-cli listcoldutxos            # server: delegated UTXOs
```

## 🏛️ Masternode Commands

There is no `masternode` command group (no `masternode genkey`, `masternode start-alias`, etc.). Use these commands:

### Masternode Management
```bash
# Generate masternode private key
ammocoin-cli createmasternodekey

# Get masternode outputs (10,000 AMMO collateral txid + index)
ammocoin-cli getmasternodeoutputs

# Start one masternode from the controller wallet (alias from masternode.conf)
ammocoin-cli startmasternode alias false "alias_name"

# Start all masternodes in masternode.conf
ammocoin-cli startmasternode all false

# Get masternode status (run on the masternode itself)
ammocoin-cli getmasternodestatus

# List masternode configuration (masternode.conf entries)
ammocoin-cli listmasternodeconf
```

### Masternode Network Information
```bash
# List all masternodes
ammocoin-cli listmasternodes

# Filter by text (e.g. your IP or address)
ammocoin-cli listmasternodes "YOUR_VPS_IP"

# Get masternode count
ammocoin-cli getmasternodecount

# Get masternode winners
ammocoin-cli getmasternodewinners

# Current masternode winner
ammocoin-cli masternodecurrent

# Masternode sync status
ammocoin-cli mnsync status
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

# Get difficulty
ammocoin-cli getdifficulty
```

> Mining/hashrate commands are not used on mainnet: there is no mining after block 2,775.

### Peer Management
```bash
# Add peer node (seeds: 78.141.194.140:37020, 104.238.165.56:37020)
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
# Finalized budgets
ammocoin-cli mnfinalbudget show

# Check budgets
ammocoin-cli checkbudgets
```

## 🔧 System & Debug Commands

### Node Management
```bash
# Stop daemon
ammocoin-cli stop

# Get info
ammocoin-cli getinfo

# Get memory info
ammocoin-cli getmemoryinfo

# Get supply info
ammocoin-cli getsupplyinfo
```

### Debug & Monitoring
```bash
# Set log level
ammocoin-cli logging '["net","tor"]' '["http"]'

# Generate blocks (regtest only - not available on mainnet, which is PoS)
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

### Configuration
Configuration is read from `ammocoin.conf` in the data folder at startup; restart the node after changes. There are no config RPC commands.
- Linux: `~/.ammocoin11/ammocoin.conf`
- macOS: `~/Library/Application Support/AMMOcoin11/ammocoin.conf`
- Windows: `%APPDATA%\AMMOcoin11\ammocoin.conf`

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

# Get new exchange address (EXM...)
ammocoin-cli getnewexchangeaddress
```

## 🛡️ Security Commands

### Wallet Security
```bash
# Rescan blockchain
ammocoin-cli rescanblockchain start_height

# Abandon transaction
ammocoin-cli abandontransaction "txid"
```

### Network Security
```bash
# Get banned peers
ammocoin-cli listbanned

# Clear banned peers
ammocoin-cli clearbanned

# Set network active
ammocoin-cli setnetworkactive true|false
```

## 📝 Batch Operations & Scripting

### Batch Commands
```bash
# Run several commands in a loop
for cmd in getbalance getblockcount getstakingstatus getnetworkinfo; do
  ammocoin-cli $cmd
done
```

### Useful Scripts

#### Monitor Staking Status
```bash
#!/bin/bash
# monitor_staking.sh
while true; do
  echo "=== $(date) ==="
  ammocoin-cli getstakingstatus | grep -E "(staking_status|mnsync|walletunlocked|stakeablecoins)"
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

# Recovery from corrupted blockchain (keep wallet.dat!)
rm -rf ~/.ammocoin11/blocks ~/.ammocoin11/chainstate
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
alias stake='ammocoin-cli getstakingstatus'
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

# Monitor staking status
watch -n 30 'ammocoin-cli getstakingstatus'
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
ammocoin-cli getstakingstatus | jq .staking_status

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
- [ ] `getstakingstatus` - Monitor staking
- [ ] `getnetworkinfo` - Check network status
- [ ] `walletpassphrase` - Unlock wallet
- [ ] `backupwallet` - Create backups
- [ ] `listtransactions` - View transaction history

### Advanced Commands for Power Users
- [ ] Masternode commands (`createmasternodekey`, `getmasternodeoutputs`, `startmasternode`, `getmasternodestatus`, `listmasternodes`)
- [ ] Cold staking commands (`getnewstakingaddress`, `delegatestake`, `delegatoradd`, `listcoldutxos`)
- [ ] Budget commands (`getbudgetinfo`, `mnbudgetvote`) - Governance voting
- [ ] Raw transaction commands
- [ ] Debug and monitoring commands
- [ ] Batch operation scripts

**💻 You now have complete command-line control over your AMMOcoin node and wallet!**

---

*Next: Learn about [DAO Participation](./06-dao-participation.md) to vote on network governance.*