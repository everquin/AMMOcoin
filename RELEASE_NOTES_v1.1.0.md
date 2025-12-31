# AMMOcoin v1.1.0 - Path A Migration

**Release Date:** December 28, 2025
**Release Type:** Major Release - New Blockchain (Path A)
**Network Status:** Ready for deployment

---

## ⚠️ CRITICAL: Path A Migration - New Blockchain

**This is a completely new blockchain, NOT a fork of v1.0!**

- **v1.0 Genesis Block:** `0x000001c4271a6e733011fbb7bde9f727b67e294413e89e89c525e169bda50795`
- **v1.1.0 Genesis Block:** `0x000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329`

**Your v1.0 wallet is required to claim v1.1.0 balances.**

### What This Means:

- ❌ v1.0 and v1.1.0 are **separate, incompatible blockchains**
- ❌ Your v1.0 balances will **NOT automatically appear** in v1.1.0
- ✅ v1.0 private keys are **required** to claim v1.1.0 balances
- ✅ **NEVER delete** your v1.0 wallet before claiming v1.1.0

📖 **Complete Migration Guide:** [V1.0_TO_V1.1.0_NODE_MIGRATION.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/V1.0_TO_V1.1.0_NODE_MIGRATION.md)

---

## 📦 Download Pre-Compiled Binaries

### Linux (Ubuntu 20.04/22.04/24.04 LTS) - x86_64

**Recommended for fastest setup (saves ~30 minutes compilation time)**

#### Download tar.gz (Recommended):
```bash
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
```

#### Download zip (Alternative):
```bash
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.zip
```

#### Verify Checksum:
```bash
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Should match: 917cd4365b352ad7800ba9dd2c388408cba0341ff6da1ba8aa33f84515e73acb
```

#### Extract and Install:
```bash
# Extract
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Install system-wide
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx

# Verify installation
ammocoind --version
# Should show: AMMOcoin Core Daemon version v1.1.0.0
```

**File Sizes:**
- tar.gz: 72 MB (compressed)
- zip: 72 MB (compressed)
- Extracted: ~198 MB (with debug symbols)

---

### macOS (Apple Silicon - M1/M2/M3/M4)

**For ARM64 Macs (Apple Silicon)**

#### Download:
```bash
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/ammocoin-v1.1.0-macos-arm64.tar.gz
```

#### Extract and Install:
```bash
# Extract
tar -xzf ammocoin-v1.1.0-macos-arm64.tar.gz

# Install
sudo cp ammocoind ammocoin-cli ammocoin-tx /usr/local/bin/

# Verify
ammocoind --version
```

**Note:** Intel Mac (x86_64) users should compile from source. See build guide below.

---

### Windows

Coming soon - Windows binaries are currently in development.

For now, Windows users can compile from source using WSL2 (Windows Subsystem for Linux).

---

## 🔐 Checksums (SHA256)

**Always verify checksums before installation!**

### Linux x86_64:
```
917cd4365b352ad7800ba9dd2c388408cba0341ff6da1ba8aa33f84515e73acb  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
8cc8d9a3b96b92305cd99393f79598cf3ca3611693000d2da1f9727aadd161f7  AMMOcoin-v1.1.0-Linux-x86_64.zip
```

Download complete checksums: [CHECKSUMS-Linux.txt](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/CHECKSUMS-Linux.txt)

---

## 📋 Quick Installation Guide

### Step 1: Install Runtime Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y \
    libboost-system1.71.0 libboost-filesystem1.71.0 \
    libboost-thread1.71.0 libboost-program-options1.71.0 \
    libevent-2.1-7 libzmq5 libsodium23
```

**Note:** Ubuntu 22.04+ may have different Boost version numbers (1.74.0). Install the version available in your distribution.

---

### Step 2: Install zkSNARK Parameters

```bash
mkdir -p ~/.ammocoin-params
cd ~/.ammocoin-params
wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
```

---

### Step 3: Create Configuration

```bash
# Create data directory
mkdir -p ~/.ammocoin-v1.1.0

# Generate secure RPC password
RPC_PASS=$(openssl rand -hex 32)

# Create configuration file
cat > ~/.ammocoin-v1.1.0/ammocoin.conf << EOF
# AMMOcoin v1.1.0 Configuration
listen=1
server=1
daemon=1

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=$RPC_PASS
rpcallowip=127.0.0.1
rpcport=8332

# Network
port=37020
maxconnections=125

# Seed Nodes
addnode=seed1.ammocoin.org:37020
addnode=seed2.ammocoin.org:37020

# Performance
dbcache=450
maxmempool=300
EOF

# Secure the configuration
chmod 600 ~/.ammocoin-v1.1.0/ammocoin.conf

# Save credentials
echo "RPC Password: $RPC_PASS" > ~/ammocoin-rpc-password.txt
chmod 600 ~/ammocoin-rpc-password.txt
```

---

### Step 4: Start the Node

```bash
# Start daemon
ammocoind -datadir=~/.ammocoin-v1.1.0 -daemon

# Wait a few seconds for startup
sleep 5

# Check status
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getinfo

# Verify correct genesis block
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockhash 0
# Should show: 000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329
```

---

### Step 5: Monitor Synchronization

```bash
# Watch the log
tail -f ~/.ammocoin-v1.1.0/debug.log

# Check blockchain info
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockchaininfo

# Check peer connections
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getpeerinfo
```

---

## 🔧 Compile from Source (Alternative)

If you prefer to compile from source or need a different platform:

### Automated Setup Script (Ubuntu/Debian):

```bash
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0
sudo bash scripts/setup-seed-node.sh
```

### Manual Compilation:

See detailed guides:
- **Linux:** [SEED_NODE_QUICK_START.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/SEED_NODE_QUICK_START.md)
- **Ubuntu Commands:** [VULTR_VM_SETUP_COMMANDS.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/VULTR_VM_SETUP_COMMANDS.md)
- **Binary Guide:** [LINUX_BINARY_DISTRIBUTION_GUIDE.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/LINUX_BINARY_DISTRIBUTION_GUIDE.md)

---

## 💰 Migration & Distribution

### For v1.0 Holders:

**Top 61 Holders (94.11% of supply):**
- 218.7M AMMO distributed automatically
- Distribution will occur after network launch
- Check your v1.1.0 balance after distribution

**All Other Holders (5.89% of supply):**
- 13.7M AMMO available via migration fund
- Claim using signature verification with v1.0 private keys
- 90-day claim window after network launch

### Migration Process:

📖 **User Migration Guide:** [USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)

📖 **Node Operator Migration:** [V1.0_TO_V1.1.0_NODE_MIGRATION.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/V1.0_TO_V1.1.0_NODE_MIGRATION.md)

**CRITICAL:** Your v1.0 `wallet.dat` contains the private keys needed to claim v1.1.0 balances. NEVER delete it!

---

## 🔧 Technical Details

### Binary Information:

**Linux x86_64:**
- **Platform:** Ubuntu 20.04 LTS
- **Compiler:** GCC 9.4.0
- **Architecture:** x86_64 (64-bit ELF)
- **Linking:** Dynamically linked
- **Debug Symbols:** Included (not stripped)
- **Berkeley DB:** 4.8 (with atomic.h patch for modern GCC)

**macOS ARM64:**
- **Platform:** macOS 14+ (Sonoma)
- **Architecture:** ARM64 (Apple Silicon)
- **Minimum:** M1/M2/M3/M4 processors

### Compatibility:

**Linux (tested):**
- ✅ Ubuntu 20.04 LTS (Focal Fossa)
- ✅ Ubuntu 22.04 LTS (Jammy Jellyfish)
- ✅ Ubuntu 24.04 LTS (Noble Numbat)

**Linux (should work):**
- Debian 10+ (Buster or later)
- Linux Mint 20+
- Pop!_OS 20.04+
- Other Ubuntu-based distributions with glibc 2.31+

**macOS (tested):**
- ✅ macOS 14+ on Apple Silicon (M1/M2/M3/M4)

---

## ✨ Features

### Core Features:
- ✅ **Full Node Support** - Complete blockchain validation
- ✅ **Staking** - Proof of Stake consensus
- ✅ **Masternodes** - Tiered masternode system
- ✅ **zkSNARK Privacy** - Sapling-based private transactions
- ✅ **P2P Network** - Port 37020 (mainnet)
- ✅ **RPC API** - Port 8332 (JSON-RPC)

### Network Parameters:
- **Block Time:** 60 seconds
- **Staking Minimum:** Varies by tier
- **P2P Port:** 37020
- **RPC Port:** 8332
- **Genesis Block:** `0x000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329`
- **Genesis Nonce:** 1299334

### Privacy Features:
- **Sapling zkSNARK** - Zero-knowledge proofs for private transactions
- **Shielded Addresses** - Optional privacy-preserving addresses
- **Transparent/Shielded** - Both modes supported

---

## 🛡️ Security

### Binary Verification:

**Always verify checksums before installing:**

```bash
# Download checksum file
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/CHECKSUMS-Linux.txt

# Verify your download
sha256sum -c CHECKSUMS-Linux.txt --ignore-missing
```

### Future Enhancements:
- GPG signatures for binaries (planned for v1.1.1)
- Reproducible builds (planned)
- Code signing for macOS/Windows (planned)

### Reporting Security Issues:

If you discover a security vulnerability, please email: security@ammocoin.org (or create a private security advisory on GitHub)

---

## 📚 Documentation

### User Guides:
- [User Migration Guide](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)
- [Node Operator Migration](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/V1.0_TO_V1.1.0_NODE_MIGRATION.md)
- [Network Bootstrap Guide](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/NETWORK_BOOTSTRAP_GUIDE.md)

### Technical Guides:
- [Linux Binary Distribution](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/LINUX_BINARY_DISTRIBUTION_GUIDE.md)
- [Seed Node Quick Start](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/SEED_NODE_QUICK_START.md)
- [Vultr VM Setup Commands](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/VULTR_VM_SETUP_COMMANDS.md)
- [GitHub Release Strategy](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/GITHUB_BINARY_RELEASE_STRATEGY.md)

### Development Docs:
- [Repository Audit](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/docs/20251228_COMPREHENSIVE_REPOSITORY_AUDIT.md)
- [Implementation Plan](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/docs/20251228_NEXT_STEPS_IMPLEMENTATION_PLAN.md)
- [Distribution Scripts](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/DISTRIBUTION_SCRIPTS_README.md)

---

## 🐛 Known Issues

**None currently reported.**

### Reporting Issues:

- **GitHub Issues:** https://github.com/everquin/AMMOcoin-v1.1.0/issues
- **Security Issues:** Create private security advisory or email security@ammocoin.org

When reporting issues, please include:
- Operating system and version
- Binary version (`ammocoind --version`)
- Relevant log entries from `~/.ammocoin-v1.1.0/debug.log`
- Steps to reproduce

---

## 🔄 Upgrade Path

### From v1.0 to v1.1.0:

**IMPORTANT:** This is NOT a simple upgrade! Path A is a complete blockchain restart.

**Required Steps:**
1. ✅ Backup v1.0 wallet (CRITICAL - contains claim keys!)
2. ✅ Stop v1.0 daemon
3. ✅ Install v1.1.0 binaries (see above)
4. ✅ Create separate v1.1.0 data directory
5. ✅ Configure and start v1.1.0 node
6. ✅ Wait for distribution or claim from migration fund

📖 **Complete Guide:** [V1.0_TO_V1.1.0_NODE_MIGRATION.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/V1.0_TO_V1.1.0_NODE_MIGRATION.md)

**DO NOT:**
- ❌ Delete v1.0 wallet before claiming v1.1.0 balances
- ❌ Overwrite v1.0 data directory
- ❌ Expect v1.0 balances to appear automatically

---

## 📞 Support

### Community:
- **GitHub Discussions:** https://github.com/everquin/AMMOcoin-v1.1.0/discussions
- **Issues:** https://github.com/everquin/AMMOcoin-v1.1.0/issues

### Resources:
- **Website:** https://www.ammocoin.org
- **Documentation:** https://github.com/everquin/AMMOcoin-v1.1.0
- **Seed Nodes:** seed1.ammocoin.org, seed2.ammocoin.org

---

## 📅 Release Timeline

| Phase | Status | Date |
|-------|--------|------|
| v1.0 snapshot captured | ✅ Complete | December 2025 |
| v1.1.0 binaries compiled | ✅ Complete | December 28, 2025 |
| GitHub Release published | ✅ Complete | December 28, 2025 |
| Seed nodes deployed | ⏸️ Pending | TBD |
| Network launch | ⏸️ Pending | TBD |
| Top 61 distribution | ⏸️ Pending | After network launch |
| Migration fund claims open | ⏸️ Pending | After network launch |
| Claim window closes | ⏸️ Pending | 90 days after opening |

---

## 💡 Key Takeaways

1. ⚠️ **v1.1.0 is a NEW blockchain**, not an upgrade of v1.0
2. 🔑 **Your v1.0 private keys** are required to claim v1.1.0 balances
3. 🚫 **NEVER delete v1.0 wallet** before claiming
4. 📦 **Pre-compiled binaries** available for quick setup
5. 🌐 **Separate data directories** for v1.0 and v1.1.0
6. ✅ **Verify checksums** before installation
7. 📖 **Read migration guides** before upgrading nodes

---

## 🎉 Thank You

Thank you to all AMMOcoin v1.0 holders for your continued support. This Path A migration represents a fresh start for the AMMOcoin network with improved features and enhanced privacy capabilities.

**Happy Staking!**

---

**Release Created:** December 28, 2025
**Binary Compilation:** Ubuntu 20.04 LTS (Vultr VM)
**Version:** v1.1.0.0
**Commit:** [See tagged commit](https://github.com/everquin/AMMOcoin-v1.1.0/tree/v1.1.0)

🤖 Generated with [Claude Code](https://claude.com/claude-code)
