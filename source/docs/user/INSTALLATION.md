# AMMOcoin v1.1.0 Installation Guide

## System Requirements

### Minimum Requirements:
- **OS**: macOS 11.0+ (Intel) or macOS 12.0+ (Apple Silicon)
- **RAM**: 4GB minimum, 8GB recommended
- **Storage**: 20GB available space for blockchain data
- **Network**: Broadband internet connection

### Recommended Requirements:
- **OS**: macOS 13.0+ (Apple Silicon preferred)
- **RAM**: 16GB for optimal performance
- **Storage**: 50GB+ SSD storage
- **CPU**: Multi-core processor for staking/masternode operations

## Pre-Installation Dependencies

### Required System Libraries:
```bash
# Install Homebrew (if not already installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install required dependencies
brew install boost berkeley-db@4 libevent libsodium zeromq gmp openssl
```

## Installation Steps

### 1. Create AMMOcoin Directory
```bash
mkdir -p ~/.ammocoin
cd ~/.ammocoin
```

### 2. Copy Configuration File
```bash
# Copy and customize the configuration template
cp /path/to/deployment/docs/ammocoin.conf.template ~/.ammocoin/ammocoin.conf
nano ~/.ammocoin/ammocoin.conf  # Edit with your preferred editor
```

### 3. Generate RPC Credentials
```bash
# Generate a secure RPC password
openssl rand -hex 32
# Update rpcpassword in ammocoin.conf with this value
```

### 4. Set File Permissions
```bash
chmod 600 ~/.ammocoin/ammocoin.conf
chmod 700 ~/.ammocoin
```

## Running AMMOcoin

### Starting the Daemon
```bash
# Start AMMOcoin daemon
./ammocoind -daemon

# Check if it's running
./ammocoin-cli getinfo
```

### Common Commands
```bash
# Get blockchain information
./ammocoin-cli getblockchaininfo

# Get wallet information
./ammocoin-cli getwalletinfo

# Create new address
./ammocoin-cli getnewaddress

# Send transaction
./ammocoin-cli sendtoaddress ADDRESS AMOUNT

# Stop the daemon
./ammocoin-cli stop
```

## Staking Setup

### Enable Staking
1. Ensure wallet is encrypted with a passphrase
2. Unlock wallet for staking:
```bash
./ammocoin-cli walletpassphrase "your_passphrase" 9999999 true
```
3. Verify staking is active:
```bash
./ammocoin-cli getstakinginfo
```

## Masternode Setup

### Prerequisites:
- 10,000 AMMO collateral
- Static IP address
- Port 55881 open

### Setup Steps:
1. Generate masternode private key:
```bash
./ammocoin-cli createmasternodekey
```

2. Add to ammocoin.conf:
```
masternode=1
masternodeprivkey=YOUR_PRIVATE_KEY
```

3. Restart daemon and verify:
```bash
./ammocoin-cli getmasternodestatus
```

## Privacy Transactions (Sapling)

### Shield Coins
```bash
# Create shielded address
./ammocoin-cli getnewshieldedaddress

# Shield transparent coins
./ammocoin-cli shieldsendmany "transparent_address" '[{"address":"shielded_address","amount":AMOUNT}]'
```

## Troubleshooting

### Common Issues:

1. **Daemon won't start**:
   - Check configuration file syntax
   - Verify file permissions
   - Check available disk space

2. **Connection issues**:
   - Verify firewall settings
   - Check network connectivity
   - Confirm port 55881 is accessible

3. **Sync problems**:
   - Delete peers.dat and restart
   - Add more addnode entries
   - Check system clock accuracy

### Log Files:
- Main log: `~/.ammocoin/debug.log`
- Configuration: `~/.ammocoin/ammocoin.conf`

### Support:
- GitHub Issues: https://github.com/ammocoin-project/ammocoin/issues
- Community: [AMMOcoin Official Channels]

## Security Recommendations

1. **Backup Wallet**:
   ```bash
   ./ammocoin-cli backupwallet backup.dat
   ```

2. **Encrypt Wallet**:
   ```bash
   ./ammocoin-cli encryptwallet "secure_passphrase"
   ```

3. **Regular Updates**:
   - Keep AMMOcoin software updated
   - Monitor security announcements

4. **Network Security**:
   - Use firewall protection
   - Regular system updates
   - Monitor unusual activity

---

**Note**: This is AMMOcoin v1.1.0 with full Sapling privacy support and masternode functionality. Always backup your wallet before performing major operations.