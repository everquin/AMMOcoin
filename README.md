# AMMOcoin v1.1.0

**Privacy-Focused Cryptocurrency Platform with Multi-Platform Support**

[![Release](https://img.shields.io/badge/release-v1.1.0-brightgreen)](https://github.com/everquin/AMMOcoin-v1.1.0/releases/tag/v1.1.0)
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-blue)](https://github.com/everquin/AMMOcoin-v1.1.0/releases)
[![License](https://img.shields.io/badge/license-MIT-yellow)](https://opensource.org/licenses/MIT)

---

## 📢 **v1.1.0 Release - January 3, 2026**

AMMOcoin v1.1.0 is now available! This major release features a new genesis block and complete multi-platform support.

**🔗 [Download Latest Release](https://github.com/everquin/AMMOcoin-v1.1.0/releases/tag/v1.1.0)**

**📋 Genesis Block Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

### What's New
- ✅ New genesis block for clean blockchain start
- ✅ Multi-platform binaries (macOS, Linux, Windows)
- ✅ 250M AMMO distribution fund for v1.0 user migration
- ✅ Enhanced build system with automated CI/CD
- ✅ Comprehensive documentation and migration guides

**Important:** v1.1.0 is a new blockchain, not compatible with v1.0. See [Migration Guide](docs/migration/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md) for details.

---

## What is AMMOcoin?

AMMOcoin is a modern, privacy-focused cryptocurrency built on proven blockchain technology. It combines the robust foundation of Bitcoin with advanced privacy features, energy-efficient Proof-of-Stake consensus, and comprehensive multi-platform support.

### Key Features

🛡️ **Privacy Technology**
- **Sapling Protocol**: Zero-knowledge proofs for completely private transactions
- **Shielded Addresses**: Optional privacy for enhanced transaction confidentiality
- **Selective Disclosure**: Users control transaction visibility

⚡ **Advanced Consensus**
- **Proof-of-Stake**: Energy-efficient mining alternative
- **Masternode Network**: Tier-two infrastructure for enhanced services
- **Fast Block Times**: 60-second block generation

🏛️ **Governance & Economics**
- **Decentralized Voting**: Community-driven development decisions
- **Treasury System**: Sustainable funding for ecosystem growth
- **Staking Rewards**: Passive income for network participants

🔧 **Developer Features**
- **JSON-RPC API**: Complete programmatic blockchain access
- **Multi-signature Support**: Enterprise-grade security
- **HD Wallets**: BIP32/44 hierarchical deterministic wallets

---

## 📦 **Download Binaries**

### Official v1.1.0 Releases

**Download from GitHub Releases:** https://github.com/everquin/AMMOcoin-v1.1.0/releases/tag/v1.1.0

| Platform | Download | Size | Checksum (SHA256) |
|----------|----------|------|-------------------|
| **macOS ARM64** | [.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz) / [.zip](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.zip) | 4.0 MB | `2678196bbc...` |
| **Linux x86_64** | [.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz) | 112 MB | `04f0aec634...` |
| **Windows x86_64** | [.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.tar.gz) / [.zip](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.zip) | 17 MB | `372e0e9f6a...` |

**Verify Checksums:** [Download CHECKSUMS.txt](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt)

### Each platform includes:
- `ammocoind` - Core daemon server
- `ammocoin-cli` - Command-line interface
- `ammocoin-tx` - Transaction utility

---

## 🚀 **Quick Start**

### Using Pre-Built Binaries (Recommended)

#### macOS
```bash
# Download and extract
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
cd AMMOcoin-v1.1.0-macOS-ARM64/bin

# Start daemon
./ammocoind -daemon

# Check status
./ammocoin-cli getinfo

# Verify genesis block
./ammocoin-cli getblockhash 0
# Should return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

#### Linux
```bash
# Download and extract
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
cd bin

# Install system-wide (optional)
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx

# Start daemon
ammocoind -daemon

# Check status
ammocoin-cli getinfo
```

#### Windows
```powershell
# Extract the ZIP file
# Navigate to the bin directory

# Start daemon
.\ammocoind.exe -daemon

# Check status (in new command prompt)
.\ammocoin-cli.exe getinfo
```

See [Installation Guide](docs/installation/) for detailed platform-specific instructions.

---

## 🔧 **Build from Source**

### Prerequisites

#### macOS
```bash
brew install boost berkeley-db@4 libevent openssl@3 qt@5
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install build-essential libtool autotools-dev automake \
  pkg-config libssl-dev libevent-dev bsdmainutils libboost-all-dev \
  libdb++-dev libzmq3-dev libminiupnpc-dev libsodium-dev
```

### Build Steps
```bash
# Clone repository
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0/source

# Configure
./configure --with-incompatible-bdb --disable-tests --disable-bench

# Build
make -j$(nproc)

# Binaries will be in src/
ls -lh src/ammocoind src/ammocoin-cli src/ammocoin-tx
```

For detailed build instructions, see:
- [Linux Build Guide](docs/installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md)
- [macOS Build Guide](docs/installation/INSTALL_MACOS.md)
- [Cross-Compilation Guide](docs/installation/CROSS_COMPILATION_GUIDE.md)

---

## 💻 **Platform Support**

| Platform | Status | Minimum OS | Notes |
|----------|--------|------------|-------|
| **macOS ARM64** | ✅ Production | macOS 11 Big Sur | Native Apple Silicon (M1/M2/M3) |
| **macOS Intel** | ✅ Production | macOS 10.15 | Via Rosetta 2 on ARM64 |
| **Linux x86_64** | ✅ Production | Ubuntu 20.04, Debian 11, RHEL 8 | glibc 2.31+ |
| **Windows x86_64** | ✅ Production | Windows 10/11 64-bit | Built with MinGW |
| **ARM64/RPi** | 🔄 Planned | Raspberry Pi OS | Future release |

---

## 🔧 **Usage Examples**

### Basic Operations
```bash
# Start daemon
ammocoind -daemon

# Check node status
ammocoin-cli getinfo

# Get blockchain info
ammocoin-cli getblockchaininfo

# Create new address
ammocoin-cli getnewaddress

# Send transaction
ammocoin-cli sendtoaddress "ADDRESS" 10.0

# Enable staking
ammocoin-cli walletpassphrase "YOUR_PASSPHRASE" 999999 true

# Check staking status
ammocoin-cli getstakingstatus
```

### Privacy Transactions
```bash
# Create shielded address (Sapling)
ammocoin-cli getnewshieldedaddress

# Shield coins for privacy
ammocoin-cli shieldsendmany "from_address" '[{"address":"shielded_address","amount":10}]'

# List shielded balances
ammocoin-cli z_gettotalbalance
```

### Masternode Setup
```bash
# Generate masternode key
ammocoin-cli createmasternodekey

# Get collateral output
ammocoin-cli getmasternodeoutputs

# See full guide: docs/03-masternode-setup.md
```

---

## 📊 **Technical Specifications**

### Network Parameters
- **P2P Port**: 37020 (mainnet)
- **RPC Port**: 51473 (mainnet)
- **Block Time**: 60 seconds
- **Algorithm**: Proof-of-Stake
- **Masternode Collateral**: 10,000 AMMO
- **Staking Minimum**: Variable by tier

### Genesis Block
- **Hash**: `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
- **Merkle Root**: `a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab`
- **Timestamp**: June 7, 2021 - 23:04:05 UTC
- **Nonce**: 1299391
- **Distribution Fund**: 250,000,000 AMMO

See [V1.1.0_GENESIS_BLOCK_AUTHORITY.md](V1.1.0_GENESIS_BLOCK_AUTHORITY.md) for complete genesis block details.

### Privacy Features
- **Protocol**: Sapling (zk-SNARKs)
- **Address Format**: Base58 (0x17 version byte)
- **Private Keys**: WIF format (0x97 version)
- **Cryptography**: SHA256, RIPEMD160, secp256k1

---

## 📝 **Documentation**

### Quick Links
- **📖 [Full Documentation](docs/README.md)** - Complete documentation index
- **🔄 [Migration Guide](docs/migration/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)** - v1.0 → v1.1.0 migration
- **📦 [Release Notes](docs/release-notes/RELEASE_NOTES_v1.1.0.md)** - What's new in v1.1.0
- **⚡ [Genesis Block Authority](V1.1.0_GENESIS_BLOCK_AUTHORITY.md)** - Official genesis parameters

### Installation & Setup
- [macOS Installation](docs/installation/INSTALL_MACOS.md)
- [Linux Build Instructions](docs/installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md)
- [Cross-Compilation Guide](docs/installation/CROSS_COMPILATION_GUIDE.md)
- [Ubuntu Upgrade Guide](docs/installation/UBUNTU_UPGRADE_GUIDE.md)

### Operations & Deployment
- [Seed Node Operations](docs/operations/SEED_NODE_QUICK_START.md)
- [Vultr VPS Deployment](docs/operations/VULTR_VPS_DEPLOYMENT.md)
- [Testing Guide](docs/operations/TEST_LOCAL_NODE_MACOS.md)

### Migration & Distribution
- [User Migration Guide](docs/migration/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)
- [Distribution Process Guide](docs/migration/DISTRIBUTION_PROCESS_GUIDE.md)
- [Migration Options Comparison](docs/migration/MIGRATION_OPTION_COMPARISON.md)

### Technical Documentation
- [Comprehensive Whitepaper](docs/whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md)
- [Standard Whitepaper](docs/whitepapers/AMMOcoin_Whitepaper_v1.1.0.md)

### User Guides (in docs/)
- [Wallet Setup](docs/01-wallet-setup.md)
- [Staking Guide](docs/02-staking-guide.md)
- [Masternode Setup](docs/03-masternode-setup.md)
- [Node Setup](docs/04-node-setup.md)
- [Terminal Commands](docs/05-terminal-commands.md)
- [DAO Participation](docs/06-dao-participation.md)
- [Security Guide](docs/08-security-guide.md)
- [Troubleshooting](docs/09-troubleshooting.md)
- [FAQ](docs/10-faq.md)

---

## 🛠️ **Additional Tools**

### Paper Wallet Generator
Secure offline wallet generation with QR code support.

```bash
# Open the paper wallet generator
open paper-wallet-generator/index.html
# Generate secure offline wallets with QR codes
```

See [Paper Wallet Guide](paper-wallet-generator/README.md)

### Blockchain Explorer
Modern web-based blockchain explorer with real-time data.

```bash
cd blockchain-explorer
npm install
cp .env.example .env.local
npm run dev
# Opens at http://localhost:3000
```

See [Explorer Documentation](blockchain-explorer/README.md)

---

## 🔒 **Security**

### Reporting Vulnerabilities
For security concerns, please email: **security@ammocoin.org**

**Do not create public issues for security vulnerabilities.**

### Best Practices
- ✅ Always encrypt your wallet with a strong passphrase
- ✅ Regular backup of wallet.dat file
- ✅ Keep software updated to latest version
- ✅ Use official releases only from GitHub
- ✅ Verify checksums before installation
- ✅ Store large amounts in cold storage
- ✅ Use hardware wallets when available

### Wallet Encryption
```bash
# Encrypt wallet
ammocoin-cli encryptwallet "STRONG_PASSPHRASE"

# Unlock for staking
ammocoin-cli walletpassphrase "PASSPHRASE" 999999 true

# Unlock for sending (60 seconds)
ammocoin-cli walletpassphrase "PASSPHRASE" 60
```

---

## 🤝 **Contributing**

We welcome contributions! Here's how to get started:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines
- Follow existing code style
- Add tests for new features
- Update documentation as needed
- Ensure all tests pass before submitting

---

## 📞 **Community & Support**

- **GitHub Issues**: https://github.com/everquin/AMMOcoin-v1.1.0/issues
- **GitHub Discussions**: https://github.com/everquin/AMMOcoin-v1.1.0/discussions
- **Documentation**: https://github.com/everquin/AMMOcoin-v1.1.0/tree/main/docs

---

## 📄 **License**

AMMOcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more information or https://opensource.org/licenses/MIT

---

## 🌟 **Acknowledgments**

AMMOcoin is built upon the foundational work of:
- **Bitcoin Core** - Original blockchain implementation
- **PIVX** - Proof-of-Stake consensus and masternode framework
- **Zcash** - Sapling privacy protocol (zk-SNARKs)
- **Dash** - InstantSend and governance features

We acknowledge and thank the broader cryptocurrency development community for their contributions to open-source blockchain technology.

---

## 📈 **Roadmap**

### Completed ✅
- v1.1.0 Multi-platform release
- New genesis block implementation
- macOS ARM64 native support
- Linux x86_64 binaries
- Windows x86_64 binaries
- Comprehensive documentation
- Migration guides and tools

### In Progress 🔄
- Network bootstrap and seed nodes
- User distribution processing
- Mobile wallet development
- Additional exchange listings

### Planned 📋
- ARM64/Raspberry Pi support
- Hardware wallet integration
- Enhanced privacy features
- Lightning network integration
- Decentralized exchange (DEX)

---

**Current Version**: v1.1.0
**Release Date**: January 3, 2026
**Status**: Production Ready ✅
**Genesis Block**: `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
