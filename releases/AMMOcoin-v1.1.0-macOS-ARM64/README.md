# AMMOcoin v1.1.0 - macOS ARM64 (Apple Silicon)

**Release Date:** December 31, 2025
**Platform:** macOS ARM64 (Apple Silicon M1/M2/M3/M4)
**Version:** 1.1.0

---

## ✅ Verified Genesis Block

This release contains binaries built with the correct v1.1.0 genesis block:

```
Genesis Hash:  00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162
Merkle Root:   58f0e4c39f4d2dce2c51cc1de1e2cd37ab4c1b41b7a2288805f683444ac63bd8
Genesis Time:  1623089845 (June 7, 2021 19:30:45 UTC)
Genesis Nonce: 284486
Genesis Reward: 250,000,000 AMMO
```

---

## Package Contents

```
bin/
├── ammocoind      - AMMOcoin daemon (11 MB)
├── ammocoin-cli   - Command-line interface (382 KB)
└── ammocoin-tx    - Transaction utility (1.4 MB)
```

---

## System Requirements

- **OS:** macOS 11.0 (Big Sur) or later
- **Architecture:** ARM64 (Apple Silicon)
- **RAM:** 2 GB minimum, 4 GB recommended
- **Disk Space:** 20 GB for blockchain data
- **Network:** Broadband internet connection

---

## Installation

### 1. Extract the Archive

```bash
# For .tar.gz
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz

# For .zip
unzip AMMOcoin-v1.1.0-macOS-ARM64.zip
```

### 2. Move Binaries to System Path (Optional)

```bash
sudo cp AMMOcoin-v1.1.0-macOS-ARM64/bin/* /usr/local/bin/
```

Or add to your PATH:

```bash
export PATH="/path/to/AMMOcoin-v1.1.0-macOS-ARM64/bin:$PATH"
```

### 3. Remove macOS Quarantine Attribute

```bash
sudo xattr -rd com.apple.quarantine AMMOcoin-v1.1.0-macOS-ARM64/bin/*
```

---

## Quick Start

### Start the Daemon

```bash
./bin/ammocoind -daemon
```

### Check Status

```bash
./bin/ammocoin-cli getinfo
```

### View Blockchain Info

```bash
./bin/ammocoin-cli getblockchaininfo
```

### Get a New Address

```bash
./bin/ammocoin-cli getnewaddress
```

### Stop the Daemon

```bash
./bin/ammocoin-cli stop
```

---

## Configuration

Create `~/.ammocoin/ammocoin.conf`:

```
# Network
listen=1
server=1
daemon=1

# RPC
rpcuser=your_rpc_username
rpcpassword=your_secure_rpc_password
rpcallowip=127.0.0.1
rpcport=37020

# Staking
staking=1

# Performance
dbcache=100
maxconnections=125
```

---

## Verification

### Verify Genesis Block

```bash
./bin/ammocoin-cli getblockhash 0
# Expected: 00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162

./bin/ammocoin-cli getblock $(./bin/ammocoin-cli getblockhash 0) 2
# Check for "value": 250000000.00 in genesis transaction
```

### Verify Binary Checksum

```bash
shasum -a 256 bin/ammocoind
# Compare with CHECKSUMS-macOS-ARM64.txt
```

---

## Network Parameters

- **Max Supply:** 9,999,999,999 AMMO
- **Genesis Premine:** 250,000,000 AMMO
- **Block Time:** 3 minutes
- **Masternode Collateral:** 10,000 AMMO
- **RPC Port:** 37020
- **P2P Port:** 37019

---

## Support

- **Documentation:** https://github.com/ammocoin/ammocoin
- **Issues:** https://github.com/ammocoin/ammocoin/issues
- **Discord:** TBD
- **Website:** https://www.ammocoin.org

---

## License

MIT License - See LICENSE file for details

---

**Built:** December 31, 2025
**Git Commit:** cfea301
**Tested:** ✅ Verified on macOS 15.6.1 (Apple Silicon)
