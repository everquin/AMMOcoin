# AMMOcoin v1.1.0 - Option 2.5: Team Distribution Premine

**Release Date:** December 31, 2025
**Release Type:** Major Release - New Blockchain with 250M AMMO Team Distribution
**Network Status:** Ready for deployment

---

## ⚠️ CRITICAL: New Blockchain with Team Distribution

**This is a completely new blockchain, NOT a fork of v1.0!**

- **v1.0 Genesis Block:** `0x000001c4271a6e733011fbb7bde9f727b67e294413e89e89c525e169bda50795`
- **v1.1.0 Genesis Block:** `0x000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

### What This Means:

- ❌ v1.0 and v1.1.0 are **separate, incompatible blockchains**
- ❌ Your v1.0 balances will **NOT automatically appear** in v1.1.0
- ✅ **Team-controlled distribution:** 250,000,000 AMMO in genesis will be manually distributed to verified v1.0 users
- ✅ **NEVER delete** your v1.0 wallet - required to send coins to the disposal wallet for migration
- ✅ **Secure genesis:** New wallet generated with no private key exposure

📖 **Distribution Details:** [Distribution Process Guide](https://github.com/everquin/AMMOcoin/blob/main/docs/migration/DISTRIBUTION_PROCESS_GUIDE.md)

---

## 📦 Download Pre-Compiled Binaries

### Linux (Ubuntu 20.04/22.04/24.04 LTS) - x86_64

**Recommended for fastest setup (saves ~30 minutes compilation time)**

#### Download .deb package (Recommended for Ubuntu/Debian):
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-amd64.deb
sha256sum AMMOcoin-v1.1.0-Linux-amd64.deb
# Should match: ae32a07effe874cf925e9e7c8dc604189f38113c54264ac47564a4e88fb53259
sudo dpkg -i AMMOcoin-v1.1.0-Linux-amd64.deb
```

#### Download tar.gz (Alternative):
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Should match: 41111899895744cf945079c544766199cc9e30398d2e239d76adf742a37f0b40
```

#### Extract and Install (tar.gz):
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
- .deb: 7.8 MB
- tar.gz: 11.3 MB (compressed)
- zip: 11.3 MB (compressed)

---

### macOS (Apple Silicon - M1/M2/M3/M4)

**For ARM64 Macs (Apple Silicon)**

#### Download tar.gz (Recommended):
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
```

#### Download zip (Alternative):
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.zip
```

#### Verify Checksum:
```bash
shasum -a 256 AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
# Should match: f314ff670ad1088cc64516be4b2f7667974f9937a3c2e1683844e5500cb709dd
```

#### Extract and Install:
```bash
# Extract
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
cd AMMOcoin-v1.1.0-macOS-ARM64

# Install
sudo cp ammocoind ammocoin-cli ammocoin-tx /usr/local/bin/
sudo chmod +x /usr/local/bin/ammocoin*

# Verify
ammocoind --version
```

**File Sizes:**
- .dmg: 80 MB (installer with Qt wallet)
- tar.gz: 4.5 MB (compressed, CLI only)
- zip: 15.3 MB (compressed)

**Note:** Intel Mac (x86_64) users should compile from source. See build guide below.

---

### Windows

Download **AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe** from the [GitHub Release](https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0). The NSIS installer includes the Qt wallet, daemon, CLI tools, Sapling parameters, and Start Menu shortcuts.

---

## 🔐 Checksums (SHA256)

**Always verify checksums before installation!**

### macOS ARM64:
```
08dfb0be819eba85c3238f916e7c2464d1333f97a71a4c1caa0d9ebcea6fd7b6  AMMOcoin-v1.1.0-macOS-ARM64.dmg
f314ff670ad1088cc64516be4b2f7667974f9937a3c2e1683844e5500cb709dd  AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
2724fcd9aeff0896b1785fb935c95dc228d8ea9856b29041e4cb931b70bd367b  AMMOcoin-v1.1.0-macOS-ARM64.zip
```

### Linux x86_64:
```
41111899895744cf945079c544766199cc9e30398d2e239d76adf742a37f0b40  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
582ab59221ba97046492e0d54fe76fbc62ac38a0acb99d72b9e51db4e788297a  AMMOcoin-v1.1.0-Linux-x86_64.zip
ae32a07effe874cf925e9e7c8dc604189f38113c54264ac47564a4e88fb53259  AMMOcoin-v1.1.0-Linux-amd64.deb
```

### Linux ARM64:
```
42678ae20253b9acaa35732835a2a2a0ee552bb9a6b809ee683b5377d3f45014  AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
106eb73d750161ef1cc63cb846b79a7a88f99d8b37e4745b9b912c96fffd4c6f  AMMOcoin-v1.1.0-Linux-ARM64.zip
d4ded3c4d368ce1fe7f40d998c924a61419c481242e7420fcdf2ac7925b073f3  AMMOcoin-v1.1.0-Linux-arm64.deb
```

### Windows x86_64:
```
82f7a652b0c388e69f1a03be8eff11a514195c02f5f91357cf588f7a698a31c8  AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe
34253f343617d116ffe5441f7517dc63a864747160c2f591140f227e7c81a0b8  AMMOcoin-v1.1.0-Windows-x86_64.tar.gz
d3a0478c82a2437197ccff4b8d6e49a6278fdffa446da7b68469818ec66ba440  AMMOcoin-v1.1.0-Windows-x86_64.zip
```

Download complete checksums: [AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt)

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
rpcport=51473

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
# Should show: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
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
git clone https://github.com/everquin/AMMOcoin.git
cd AMMOcoin
sudo bash scripts/setup-seed-node.sh
```

### Manual Compilation:

See detailed guides:
- **Linux:** [Seed Node Quick Start](https://github.com/everquin/AMMOcoin/blob/main/docs/operations/SEED_NODE_QUICK_START.md)
- **Ubuntu Commands:** [Vultr VM Setup Commands](https://github.com/everquin/AMMOcoin/blob/main/docs/operations/VULTR_VM_SETUP_COMMANDS.md)
- **Linux Build:** [Linux Build Instructions](https://github.com/everquin/AMMOcoin/blob/main/docs/installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md)

---

## 💰 Distribution: Option 2.5 - Team Distribution Premine

### Genesis Distribution:

**250,000,000 AMMO in Genesis Block:**
- Controlled by team wallet: `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`
- Private key secured offline (never exposed in code or GitHub)
- Will be manually distributed to verified v1.0 users

### Distribution Process:

**For v1.0 Holders:**
1. Email transfermy@ammocoin.org with amount and v1.1.0 receiving address(es)
2. Send v1.0 AMMO to team-provided disposal wallet address
3. Team verifies on-chain receipt, sends equivalent v1.1.0 AMMO
4. Migration window: 90 days from network launch (closes April 3, 2026)

**Advantages:**
- ✅ On-chain proof on both blockchains — immutable and independently verifiable
- ✅ Amount is self-verifying from the v1.0 transaction itself
- ✅ Simple for users — just send coins, no CLI signing commands
- ✅ Flexible — send any amount, split across multiple v1.1.0 addresses
- ✅ Clean audit trail: every v1.0 disposal tx maps to a v1.1.0 distribution tx

📖 **Distribution Process Guide:** [DISTRIBUTION_PROCESS_GUIDE.md](https://github.com/everquin/AMMOcoin/blob/main/docs/migration/DISTRIBUTION_PROCESS_GUIDE.md)

**CRITICAL:** Your v1.0 `wallet.dat` is needed to send coins to the disposal wallet for migration. NEVER delete it!

---

## 🔧 Technical Details

### Binary Information:

**macOS ARM64:**
- **Platform:** macOS 14+ (Sonoma)
- **Architecture:** ARM64 (Apple Silicon)
- **Minimum:** M1/M2/M3/M4 processors
- **Compiler:** Apple Clang (Xcode Command Line Tools)
- **Boost Version:** 1.85
- **Berkeley DB:** 4.8
- **Build Date:** December 31, 2025

**Linux x86_64:**
- **Status:** Released, February 22, 2026
- **Platform:** Ubuntu 20.04 LTS
- **Architecture:** x86_64 (64-bit ELF)
- **Build Date:** February 22, 2026

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
- ✅ **RPC API** - Port 51473 (JSON-RPC)

### Network Parameters:
- **Block Time:** 3 minutes
- **Staking Minimum:** Varies by tier
- **P2P Port:** 37020
- **RPC Port:** 51473
- **Genesis Block:** `0x000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
- **Genesis Nonce:** 1299391

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
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt

# Verify your download
sha256sum -c AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt --ignore-missing
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
- [User Migration Guide](https://github.com/everquin/AMMOcoin/blob/main/docs/migration/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)
- [Manual Migration Plan](https://github.com/everquin/AMMOcoin/blob/main/docs/migration/MANUAL_MIGRATION_PLAN_v1.0_to_v1.1.0.md)
- [Distribution Process Guide](https://github.com/everquin/AMMOcoin/blob/main/docs/migration/DISTRIBUTION_PROCESS_GUIDE.md)
- [Side-by-Side Operation Guide](https://github.com/everquin/AMMOcoin/blob/main/docs/migration/SIDE_BY_SIDE_OPERATION_GUIDE.md)

### Technical Guides:
- [Linux Build Instructions](https://github.com/everquin/AMMOcoin/blob/main/docs/installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md)
- [macOS Installation](https://github.com/everquin/AMMOcoin/blob/main/docs/installation/INSTALL_MACOS.md)
- [Seed Node Quick Start](https://github.com/everquin/AMMOcoin/blob/main/docs/operations/SEED_NODE_QUICK_START.md)
- [Vultr VM Setup Commands](https://github.com/everquin/AMMOcoin/blob/main/docs/operations/VULTR_VM_SETUP_COMMANDS.md)
- [Vultr VPS Deployment](https://github.com/everquin/AMMOcoin/blob/main/docs/operations/VULTR_VPS_DEPLOYMENT.md)

---

## 🐛 Known Issues

**None currently reported.**

### Reporting Issues:

- **GitHub Issues:** https://github.com/everquin/AMMOcoin/issues
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
1. ✅ Backup v1.0 wallet (CRITICAL - needed to send to disposal wallet!)
2. ✅ Install v1.1.0 binaries (see above)
3. ✅ Generate v1.1.0 receiving address(es)
4. ✅ Email transfermy@ammocoin.org with amount and v1.1.0 address(es)
5. ✅ Send v1.0 AMMO to the disposal wallet
6. ✅ Receive equivalent v1.1.0 AMMO from distribution fund

📖 **Complete Guide:** [User Migration Guide](https://github.com/everquin/AMMOcoin/blob/main/docs/migration/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)

**DO NOT:**
- ❌ Delete v1.0 wallet before transferring to disposal wallet
- ❌ Overwrite v1.0 data directory
- ❌ Expect v1.0 balances to appear automatically

---

## 📞 Support

### Community:
- **GitHub Discussions:** https://github.com/everquin/AMMOcoin/discussions
- **Issues:** https://github.com/everquin/AMMOcoin/issues

### Resources:
- **Website:** https://www.ammocoin.org
- **Documentation:** https://github.com/everquin/AMMOcoin
- **Seed Nodes:** seed1.ammocoin.org, seed2.ammocoin.org

---

## 📅 Release Timeline

| Phase | Status | Date |
|-------|--------|------|
| Option 2.5 implementation | ✅ Complete | December 31, 2025 |
| New secure genesis mined | ✅ Complete | December 31, 2025 |
| macOS ARM64 binaries | ✅ Complete | December 31, 2025 |
| Security remediation (private key removal) | ✅ Complete | December 31, 2025 |
| Linux x86_64 binaries | ✅ Complete | February 22, 2026 |
| GitHub Release v1.1.0 | ✅ Complete | February 22, 2026 |
| Seed nodes deployed | ✅ Complete | January 3, 2026 |
| Network launch | ✅ Complete | January 3, 2026 |
| Migration transfers open | ✅ Complete | January 3, 2026 |
| Migration window closes | ⏸️ Pending | April 3, 2026 |

---

## 💡 Key Takeaways

1. ⚠️ **v1.1.0 is a NEW blockchain**, not an upgrade of v1.0
2. 💰 **250M AMMO team distribution** - manually distributed to verified v1.0 users
3. 🔑 **Your v1.0 wallet** is needed to send coins to the disposal wallet
4. 🚫 **NEVER delete v1.0 wallet** before completing your transfer
5. 🔒 **Secure genesis** - no private keys exposed in code
6. 📦 **All platform binaries** available (macOS, Windows, Linux x86_64, ARM64)
7. ✅ **Verify checksums** before installation
8. 📖 **Read migration guide** for transfer process

---

## 🎉 Thank You

Thank you to all AMMOcoin v1.0 holders for your continued support. This Option 2.5 implementation provides a secure, team-controlled distribution of 250M AMMO to verified v1.0 users, ensuring a fair and flexible migration process.

**Happy Staking!**

---

**Release Created:** December 31, 2025
**Binary Compilation:** macOS ARM64 (Apple Silicon)
**Version:** v1.1.0.0
**Genesis Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
**Security:** Private keys never exposed in repository

🤖 Generated with [Claude Code](https://claude.com/claude-code)
