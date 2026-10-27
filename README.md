# AMMOcoin v1.1.1

**Privacy-Focused Cryptocurrency Platform with Multi-Platform Support**

[![Release](https://img.shields.io/badge/release-v1.1.1-brightgreen)](https://github.com/everquin/AMMOcoin/releases/tag/v1.1.1)
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-blue)](https://github.com/everquin/AMMOcoin/releases)
[![License](https://img.shields.io/badge/license-MIT-yellow)](https://opensource.org/licenses/MIT)

---

## ⚠️ **v1.1.1 - Proof-of-Stake Hard Fork - Everyone Must Upgrade**

v1.1.1 switches the network to **Proof-of-Stake from block 2,776**. There is no mining after the fork.

- **New network magic** (`c7 9a e3 b5`): v1.1.1 nodes do **not** connect to v1.0 or v1.1.0 nodes. Every wallet, staker, masternode and seed must upgrade.
- **New data folder:** Linux `~/.ammocoin11`, macOS `~/Library/Application Support/AMMOcoin11`, Windows `%APPDATA%\AMMOcoin11` (was `.ammocoin` / `AMMOcoin`).
- **Ports:** P2P **37020**, RPC **51473**.
- **Linux:** binaries need **glibc 2.34+** (Ubuntu 22.04 or newer; 24.04 tested). Ubuntu 18.04/20.04 must upgrade or reinstall the OS.
- **v1.0 holders:** balances from the block 434,881 snapshot are **airdropped to the same addresses**. Keep your v1.0 `wallet.dat` and **send nothing anywhere**. See [v1.0 Balance Airdrop](docs/migration/V1.0_BALANCE_AIRDROP.md).

v1.1.1 is released. Binaries, SHA256 checksums and the signed checksums file are on the [GitHub Releases](https://github.com/everquin/AMMOcoin/releases/tag/v1.1.1) page. Do not install binaries from any other source.

**📋 [v1.1.1 Release Notes](docs/release-notes/RELEASE_NOTES_v1.1.1.md)**

**📋 Genesis Block Hash (unchanged):** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

---

## 📢 **v1.1.0 Release - January 3, 2026** (superseded by v1.1.1)

v1.1.0 introduced the new genesis block and multi-platform support. Its PoW phase ended at block 2,775; v1.1.0 nodes cannot follow the v1.1.1 chain.

### What's New in v1.1.0
- ✅ New genesis block for clean blockchain start
- ✅ Multi-platform binaries (macOS, Linux, Windows)
- ✅ 250M AMMO distribution fund in block 1 for v1.0 user migration
- ✅ Enhanced build system with automated CI/CD
- ✅ Comprehensive documentation and migration guides

**Important:** v1.1 is a new blockchain, not compatible with v1.0. See [v1.0 Balance Airdrop](docs/migration/V1.0_BALANCE_AIRDROP.md) for how v1.0 balances move over.

---

## What is AMMOcoin?

AMMOcoin is a modern, privacy-focused cryptocurrency built on proven blockchain technology. It combines the robust foundation of Bitcoin with advanced privacy features, energy-efficient Proof-of-Stake consensus, and comprehensive multi-platform support.

### Key Features

🛡️ **Privacy Technology**
- **Sapling Protocol**: Optional shielded (zero-knowledge) transactions; AMMO is transparent by default, the transparent side of shielding/unshielding is visible, and peers can see your IP
- **Shielded Addresses**: Optional privacy for enhanced transaction confidentiality
- **Selective Disclosure**: Users control transaction visibility

⚡ **Advanced Consensus**
- **Proof-of-Stake**: Energy-efficient mining alternative
- **Masternode Network**: Tier-two infrastructure for enhanced services
- **Fast Block Times**: 3-minute block generation

🏛️ **Governance & Economics**
- **Decentralized Voting**: Community-driven development decisions
- **Treasury System**: Superblock budget paid only to proposals approved by masternode vote
- **Staking**: Stakers run the network with their crew: each block is made by a staking wallet chosen in proportion to mature coins staking

🔧 **Developer Features**
- **JSON-RPC API**: Complete programmatic blockchain access
- **Multi-signature Support**: Enterprise-grade security
- **HD Wallets**: BIP32/44 hierarchical deterministic wallets

---

## 📦 **Download Binaries**

### v1.1.1 (current)

v1.1.1 binaries are on the [GitHub Releases](https://github.com/everquin/AMMOcoin/releases/tag/v1.1.1) page with SHA256 checksums. **v1.1.0 binaries below no longer follow the network after block 2,775** and are listed for reference only.

### v1.1.0 Releases (obsolete after the fork)

| Platform | Download | Size | Checksum (SHA256) |
|----------|----------|------|-------------------|
| **macOS ARM64** | [.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz) / [.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.zip) | 4.0 MB | `71048bb009...` |
| **Linux x86_64** | [.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz) | 112 MB | `082f1eb063...` |
| **Windows x86_64** | [.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.tar.gz) / [.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.zip) | 17 MB | `66bd10254f...` |

### Each platform includes:
- `ammocoind` - Core daemon server
- `ammocoin-cli` - Command-line interface
- `ammocoin-tx` - Transaction utility

---

## 🚀 **Quick Start**

### Using Pre-Built Binaries (Recommended)

Download the v1.1.1 archive for your platform from the official GitHub release, verify its SHA256 checksum, then:

#### macOS
```bash
# Extract (file name from the v1.1.1 release page)
tar -xzf AMMOcoin-v1.1.1-<platform>.tar.gz
cd <extracted folder>/bin

# Start daemon (data folder: ~/Library/Application Support/AMMOcoin11)
./ammocoind -daemon

# Check status
./ammocoin-cli getinfo

# Verify genesis block
./ammocoin-cli getblockhash 0
# Should return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

#### Linux (glibc 2.34+, Ubuntu 22.04 or newer)
```bash
# Check glibc first - must be 2.34 or newer
ldd --version

# Extract (file name from the v1.1.1 release page)
tar -xzf AMMOcoin-v1.1.1-<platform>.tar.gz
cd <extracted folder>/bin

# Install system-wide (optional)
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx

# Start daemon (data folder: ~/.ammocoin11)
ammocoind -daemon

# Check status - block height should pass 2,775 once synced
ammocoin-cli getinfo
```

For a server, run the node under systemd and set `Environment=HOME=/root` (or the service user's home) in the unit, otherwise it exits with "Cannot find the Sapling parameters". See [Node Setup](docs/04-node-setup.md).

#### Windows
```powershell
# Extract the ZIP file
# Navigate to the bin directory

# Start daemon (data folder: %APPDATA%\AMMOcoin11)
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
git clone https://github.com/everquin/AMMOcoin.git
cd AMMOcoin/source

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
| **Linux x86_64** | ✅ Production | Ubuntu 22.04+ (24.04 tested), Debian 12+ | glibc 2.34+ (Ubuntu 18.04/20.04 not supported) |
| **Windows x86_64** | ✅ Production | Windows 10/11 64-bit | Built with MinGW |
| **ARM64/RPi** | ✅ Production | Raspberry Pi OS (64-bit) | Headless daemon + CLI |

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

# Enable staking (unlock for staking only; coins need 600 confirmations)
ammocoin-cli walletpassphrase "YOUR_PASSPHRASE" 0 true

# Check staking status
ammocoin-cli getstakingstatus
```

### Privacy Transactions
```bash
# Create shielded address (Sapling)
ammocoin-cli getnewshieldaddress

# Shield coins for privacy
ammocoin-cli shieldsendmany "from_address" '[{"address":"shielded_address","amount":10}]'

# List shielded balances
ammocoin-cli getshieldbalance
```

### Masternode Setup
```bash
# Generate masternode key
ammocoin-cli createmasternodekey

# Get collateral output (10,000 AMMO, 15 confirmations)
ammocoin-cli getmasternodeoutputs

# masternode.conf line:  mn1 VPS_PUBLIC_IP:37020 mnprivkey collateral_txid index
# Start from the controller wallet
ammocoin-cli startmasternode alias false "mn1"

# Check
ammocoin-cli getmasternodestatus
ammocoin-cli listmasternodes

# See full guide: docs/03-masternode-setup.md
```

### Cold Staking
```bash
# On the staking server
ammocoin-cli getnewstakingaddress
# ...and whitelist the owner address, or the delegated coins will not stake
ammocoin-cli delegatoradd "OWNER_ADDRESS"

# In the owner wallet
ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000
# owner address not in this wallet (e.g. offline): pass it plus ext_owner=true
ammocoin-cli delegatestake "S_STAKING_ADDRESS" 5000 "OWNER_ADDRESS" true

# Check
ammocoin-cli getcoldstakingbalance   # staking server
ammocoin-cli listcoldutxos           # staking server
ammocoin-cli getstakingstatus
```

---

## 📊 **Technical Specifications**

### Network Parameters
- **P2P Port**: 37020 (mainnet)
- **RPC Port**: 51473 (mainnet)
- **Network Magic**: `c7 9a e3 b5` (v1.1.1)
- **Block Time**: 3 minutes
- **Algorithm**: Proof-of-Stake from block 2,776 (blocks 1-2,775 were PoW; no mining after the fork)
- **Stake Maturity**: 600 confirmations
- **Issuance**: the original declining schedule in `GetBlockValue()` (`source/src/validation.cpp`), unchanged by the fork; each block pays the masternode selected by the payment queue its share (`nMNBlockReward`) and the staker the rest
- **Masternode Collateral**: 10,000 AMMO (15 confirmations)
- **Seed Nodes**: seed1.ammocoin.org (78.141.194.140), seed2.ammocoin.org (104.238.165.56), seed3.ammocoin.org (New York, Sydney and Dallas seeds)

### Genesis Block
- **Hash**: `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
- **Merkle Root**: `a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab`
- **Timestamp**: June 7, 2021 - 23:04:05 UTC
- **Nonce**: 1299391
- **Distribution Fund**: 250,000,000 AMMO (block 1, paid to `AJSpvakMXqZDrqimNP7X8R26NzyNGtmA8u`)

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
- **🔄 [v1.0 Balance Airdrop](docs/migration/V1.0_BALANCE_AIRDROP.md)** - how v1.0 balances reach v1.1 (send nothing)
- **📦 [Release Notes v1.1.1](docs/release-notes/RELEASE_NOTES_v1.1.1.md)** - PoS hard fork, upgrade checklist
- **📦 [Release Notes v1.1.0](docs/release-notes/RELEASE_NOTES_v1.1.0.md)** - What was new in v1.1.0
- **⚡ [Genesis Block Authority](V1.1.0_GENESIS_BLOCK_AUTHORITY.md)** - Official genesis parameters
- **⚖️ [Compliance record](docs/compliance/README.md)** - Proudly Worthless™: no ICO, no sale, no price; binding principles, decision log and the pre-merge review checklist

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
- [v1.0 Balance Airdrop](docs/migration/V1.0_BALANCE_AIRDROP.md) - current process
- Superseded (history only): [Side-by-Side Operation Guide](docs/migration/SIDE_BY_SIDE_OPERATION_GUIDE.md), [User Migration Guide](docs/migration/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md), [Distribution Process Guide](docs/migration/DISTRIBUTION_PROCESS_GUIDE.md)

### Technical Documentation
- [White Paper, 2nd Edition (v1.1.1)](docs/whitepapers/AMMOcoin_Whitepaper_2ndEdition_v1.1.1.md) - current
- Superseded (history only): [Comprehensive Whitepaper v1.1.0](docs/whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md), [Standard Whitepaper v1.1.0](docs/whitepapers/AMMOcoin_Whitepaper_v1.1.0.md)

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
- ✅ Never send coins to an emailed "disposal" or "migration" address - the v1.0 airdrop needs no action
- ✅ Verify checksums before installation
- ✅ Store large amounts in cold storage
- ✅ Use hardware wallets when available

### Wallet Encryption
```bash
# Encrypt wallet
ammocoin-cli encryptwallet "STRONG_PASSPHRASE"

# Unlock for staking only
ammocoin-cli walletpassphrase "PASSPHRASE" 0 true

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

- **GitHub Issues**: https://github.com/everquin/AMMOcoin/issues (public, for technical bugs only)
- **v1.0 airdrop claims** (missing balance only): email **claims@ammocoin.org**, see [what to send](docs/migration/CLAIM_TEMPLATE.md). Never in a public issue. Status: [claims log](docs/migration/CLAIMS_LOG.md)
- **Documentation**: https://github.com/everquin/AMMOcoin/tree/main/docs

---

## 📄 **License**

AMMOcoin Core is released under the terms of the MIT license. See [COPYING](source/COPYING) for more information or https://opensource.org/licenses/MIT

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
- ARM64/Raspberry Pi binaries
- Comprehensive documentation
- Migration guides and tools

- v1.1.1 Proof-of-Stake hard fork (block 2,776)

### In Progress 🔄
- Network upgrade to v1.1.1
- v1.0 balance airdrop to the same addresses
- Mobile wallet development

### Planned 📋
- Hardware wallet integration
- Enhanced privacy features
- Lightning network integration

The project runs no exchange and seeks no listing. Any exchange listing could only come from an explicit masternode governance vote (DAO Command).

---

**Current Version**: v1.1.1 (mandatory PoS hard fork at block 2,776)
**Release Date**: v1.1.1 October 21, 2026; v1.1.0 January 3, 2026
**Genesis Block**: `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
