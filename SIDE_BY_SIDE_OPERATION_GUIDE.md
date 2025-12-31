# Running v1.0 and v1.1.0 Side-by-Side

**Purpose:** Extract private keys from v1.0 wallet for use in v1.1.0
**Important:** This does NOT automatically transfer balances!

---

## Why Run Side-by-Side?

v1.1.0 is a **fresh blockchain** - it does not continue v1.0's chain. To use your v1.0 addresses in v1.1.0:

1. Extract private keys from v1.0 wallet
2. Import those keys into v1.1.0 wallet
3. **Your v1.0 balance does NOT transfer automatically**

**Note:** Whether you receive v1.1.0 coins depends on the migration mechanism (snapshot, airdrop, etc.)

---

## Configuration for Side-by-Side

### v1.0 Configuration

Keep v1.0 in default location with different ports:

**~/.ammocoin-v1.0/ammocoin.conf:**
```ini
# v1.0 Configuration
datadir=/home/user/.ammocoin-v1.0
port=8339           # Different from v1.1.0
rpcport=8333        # Different from v1.1.0
rpcuser=ammo_v10
rpcpassword=your_password_here
server=1
```

### v1.1.0 Configuration

Use default location for v1.1.0:

**~/.ammocoin/ammocoin.conf:**
```ini
# v1.1.0 Configuration
port=8338           # Default v1.1.0 port
rpcport=8332        # Default v1.1.0 RPC port
rpcuser=ammo_v11
rpcpassword=different_password_here
server=1
daemon=1
```

---

## Starting Both Daemons

### Start v1.0
```bash
# Start v1.0 with specific data directory
/path/to/v1.0/ammocoind -datadir=$HOME/.ammocoin-v1.0 -daemon

# Verify v1.0 is running
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 getinfo
```

### Start v1.1.0
```bash
# Start v1.1.0 (uses default ~/.ammocoin)
ammocoind -daemon

# Verify v1.1.0 is running
ammocoin-cli getblockchaininfo
```

### Verify Both Running
```bash
# Check ports
netstat -tulpn | grep ammocoin

# Should see:
# 8339 - v1.0 P2P
# 8333 - v1.0 RPC
# 8338 - v1.1.0 P2P
# 8332 - v1.1.0 RPC
```

---

## Extracting Private Keys from v1.0

### Method 1: Dump All Private Keys
```bash
# Using v1.0 CLI with datadir specified
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 dumpwallet ~/v10-wallet-dump.txt

# This creates a text file with all your private keys
cat ~/v10-wallet-dump.txt
```

**Format of dump file:**
```
# Extended private key
# addr=AeLWWVfT293noSbYpRJBN6xMsKk5ksgggC hdkeypath=m/0'/0'/0' 2021-06-07T23:04:05Z label= # addr=AeLWWVfT293noSbYpRJBN6xMsKk5ksgggC
Kz3fQ8... 2021-06-07T23:04:05Z label= # addr=AeLWWVfT293noSbYpRJBN6xMsKk5ksgggC
...
```

### Method 2: Dump Specific Address
```bash
# Get private key for specific address
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 dumpprivkey AeLWWVfT293noSbYpRJBN6xMsKk5ksgggC

# Returns: PPewqGBHgSnxRsYMRMgG4B2YHcJratTszSMBehfjSayqjjRgVnGB
```

### Method 3: List All Addresses First
```bash
# See all addresses in v1.0 wallet
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 listaddressgroupings

# Then dump each address you want
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 dumpprivkey ADDRESS_HERE
```

---

## Importing Keys into v1.1.0

### Import Individual Keys
```bash
# Import a specific private key
ammocoin-cli importprivkey "PPewqGBHgSnxRsYMRMgG4B2YHcJratTszSMBehfjSayqjjRgVnGB" "my_label" false

# The 'false' means don't rescan blockchain (faster if you know address has no history)
```

### Import from Dump File
```bash
# Import entire wallet dump
ammocoin-cli importwallet ~/v10-wallet-dump.txt

# This imports all keys from the dump file
# Takes longer because it rescans blockchain
```

### Verify Import
```bash
# List all addresses in v1.1.0 wallet
ammocoin-cli listaddressgroupings

# Check if specific address exists
ammocoin-cli validateaddress AeLWWVfT293noSbYpRJBN6xMsKk5ksgggC
```

---

## Important Notes

### Your Addresses Work, But Balances Don't Transfer

After importing keys:
- ✅ Same addresses in v1.1.0
- ✅ You control same private keys
- ❌ **Your v1.0 balance is NOT automatically there**

**Why?** v1.1.0 is a fresh blockchain. Your balance depends on:
- Snapshot/airdrop mechanism (if implemented)
- Team manual distribution (if planned)
- Mining/receiving new coins on v1.1.0 chain

### Wallet.dat Is NOT Compatible

Do NOT copy v1.0 wallet.dat to v1.1.0 directory:
- Different blockchain = wallet will be confused
- Could cause errors or crashes
- Use key export/import instead

### Keep v1.0 Wallet Safe

Until you're certain you have all keys:
- Keep v1.0 wallet.dat backup
- Keep v1.0 daemon accessible
- Don't delete v1.0 data directory

---

## Example: Complete Migration

```bash
# 1. Start v1.0 (if not running)
/path/to/v1.0/ammocoind -datadir=$HOME/.ammocoin-v1.0 -daemon

# 2. Export all keys from v1.0
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 dumpwallet ~/v10-keys.txt

# 3. Start v1.1.0 (if not running)
ammocoind -daemon
sleep 10

# 4. Import keys to v1.1.0
ammocoin-cli importwallet ~/v10-keys.txt

# 5. Verify addresses imported
ammocoin-cli listaddressgroupings

# 6. Secure delete the key dump
shred -u ~/v10-keys.txt

# 7. Stop v1.0 (if you're done with it)
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 stop
```

---

## Stopping Daemons

### Stop v1.0
```bash
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 stop
```

### Stop v1.1.0
```bash
ammocoin-cli stop
```

### Force Stop (if needed)
```bash
pkill -9 ammocoind
```

---

## Troubleshooting

### Port Already in Use
```bash
# If ports conflict:
# Edit config files to use different ports
# Or stop one daemon before starting the other
```

### RPC Connection Failed
```bash
# Specify datadir when using v1.0 CLI
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 -rpcport=8333 getinfo
```

### Wrong Balance Showing
```bash
# v1.1.0 is fresh blockchain - check for:
# 1. Snapshot distribution (if implemented)
# 2. Team-issued coins (if planned)
# 3. Mining rewards (if you're mining)

# Your v1.0 balance does NOT automatically appear
```

---

## Security Warnings

### Private Key Dump File

The wallet dump contains **all your private keys in plain text**:
- ⚠️ Anyone with this file can steal your coins
- ⚠️ Delete securely after importing: `shred -u filename`
- ⚠️ Never email or upload to cloud
- ⚠️ Don't leave on shared computer

### RPC Credentials

- Use different passwords for v1.0 and v1.1.0
- Never share RPC credentials
- Restrict rpcallowip to localhost only

---

## When to Use This Guide

**Use side-by-side operation if:**
- You have v1.0 wallet with addresses you want to reuse
- You need to extract private keys
- Migration mechanism will credit your keys (ask team)

**Don't use if:**
- You're starting fresh with new addresses
- You have no v1.0 balance to migrate
- Team provides automatic migration tool

---

**Questions about balance migration?**

Contact AMMOcoin team to understand:
- Is there a snapshot/airdrop?
- How will v1.0 balances be credited?
- Do you need to register for migration?

This guide only covers **key extraction**, not balance transfer!
