AMMOcoin Core v1.1.0
====================

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/everquin/AMMOcoin-v1.1.0)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/everquin/AMMOcoin-v1.1.0?color=%23FFD700&cacheSeconds=3600)](https://github.com/everquin/AMMOcoin-v1.1.0/releases)
[![Platform](https://img.shields.io/badge/platform-macOS%20ARM64-blue)](https://github.com/everquin/AMMOcoin-v1.1.0)

## What is AMMOcoin?

AMMOcoin is a modern, privacy-focused cryptocurrency built on advanced blockchain technology, emphasizing five core principles:

**(1) Advanced Privacy Protection**: Through Sapling zero-knowledge proof technology, enabling completely private transactions while maintaining network transparency and auditability.

**(2) Energy-Efficient Consensus**: Utilizing an advanced Proof-of-Stake protocol that dramatically reduces environmental impact while ensuring network security and broad participation.

**(3) Decentralized Governance**: A sophisticated DAO (Decentralized Autonomous Organization) built on our masternode network, enabling community-driven decision making, proposal submission, and democratic voting.

**(4) High-Performance Transactions**: Featuring optimized block times and masternode infrastructure for fast, reliable transaction processing with ongoing research into instant settlement mechanisms.

**(5) User-Centric Design**: Committed to delivering intuitive interfaces and comprehensive tooling for both newcomers and experienced cryptocurrency users.

For detailed specifications and community resources, visit [AMMOcoin.org](https://www.ammocoin.org/).

## Key Features

### 🛡️ **Privacy Technology**
- **Sapling Protocol**: Zero-knowledge proofs for completely private transactions
- **Shielded Addresses**: Optional privacy for enhanced transaction confidentiality
- **Selective Disclosure**: Users control transaction visibility

### ⚡ **Advanced Consensus**
- **Proof-of-Stake**: Energy-efficient mining alternative
- **Masternode Network**: Tier-two infrastructure for enhanced services
- **Fast Block Times**: Quick transaction confirmation

### 🏛️ **Governance & Economics**
- **Decentralized Voting**: Community-driven development decisions
- **Treasury System**: Sustainable funding for ecosystem growth
- **Staking Rewards**: Passive income for network participants

### 🔧 **Developer Features**
- **JSON-RPC API**: Complete programmatic blockchain access
- **ZeroMQ Integration**: Real-time event notifications
- **Multi-signature Support**: Enterprise-grade security
- **HD Wallets**: BIP32/44 hierarchical deterministic wallets

## Installation

### Quick Start (macOS)

```bash
# Clone the repository
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0

# Install dependencies
brew install boost berkeley-db@4 libevent libsodium zeromq gmp openssl

# Build AMMOcoin
./autogen.sh
./configure --disable-tests --disable-bench --enable-wallet --without-gui
make -j4

# Install binaries
sudo make install
```

### Detailed Instructions

For comprehensive build instructions, see our [Installation Guide](deployment/docs/INSTALLATION.md).

## Usage

### Starting AMMOcoin Node

```bash
# Start the daemon
ammocoind -daemon

# Check node status
ammocoin-cli getinfo

# View blockchain information
ammocoin-cli getblockchaininfo
```

### Basic Wallet Operations

```bash
# Create new address
ammocoin-cli getnewaddress

# Send coins
ammocoin-cli sendtoaddress "address" amount

# Check balance
ammocoin-cli getbalance

# Enable staking
ammocoin-cli walletpassphrase "passphrase" 999999 true
```

### Privacy Transactions (Sapling)

```bash
# Create shielded address
ammocoin-cli getnewshieldedaddress

# Shield coins for privacy
ammocoin-cli shieldsendmany "transparent_address" '[{"address":"shielded_address","amount":10}]'

# Private transaction between shielded addresses
ammocoin-cli sendmany "" '{"shielded_address":10}' 1 "" [] true
```

## Configuration

AMMOcoin uses `ammocoin.conf` for configuration. See our [configuration template](deployment/docs/ammocoin.conf.template) for detailed options.

Example basic configuration:
```ini
# Basic node configuration
server=1
daemon=1
rpcuser=ammouser
rpcpassword=secure_password_here

# Enable staking
staking=1

# Privacy features
experimentalfeatures=1
zindex=1
```

## Development

### Building from Source

**Prerequisites:**
- macOS 10.14+ (preferably macOS 13+ with Apple Silicon)
- Xcode Command Line Tools
- Homebrew package manager
- Git version control

**Dependencies:**
```bash
brew install autoconf automake libtool pkg-config
brew install boost berkeley-db@4 libevent libsodium zeromq gmp
brew install openssl rust
```

**Build Process:**
```bash
./autogen.sh
./configure --with-incompatible-bdb --disable-tests --disable-bench
make -j$(sysctl -n hw.ncpu)
```

### Contributing

We welcome contributions! Please see our [contribution guidelines](CONTRIBUTING.md) for details on:
- Code standards and review process
- Testing requirements
- Documentation standards
- Community guidelines

### Testing

AMMOcoin includes comprehensive test suites:

```bash
# Unit tests
make check

# Functional tests
test/functional/test_runner.py

# Manual testing
ammocoin-cli help  # View all available commands
```

## Network Information

### Mainnet
- **Port**: 55881
- **RPC Port**: 55882
- **Genesis Block**: [Block Hash]
- **Block Time**: 60 seconds
- **Algorithm**: Proof-of-Stake

### Testnet
- **Port**: 51474
- **RPC Port**: 51475
- **Block Time**: 60 seconds

## Technical Specifications

### Blockchain
- **Consensus**: Proof-of-Stake with Masternode network
- **Block Size**: 2MB
- **Block Time**: 60 seconds
- **Difficulty Adjustment**: Every block

### Privacy
- **Protocol**: Sapling (zk-SNARKs)
- **Shielded Pool**: Separate privacy-preserving transaction pool
- **Viewing Keys**: Optional transaction disclosure

### Economics
- **Total Supply**: [To be specified]
- **Staking Rewards**: [Percentage/Amount]
- **Masternode Collateral**: 10,000 AMMO
- **Masternode Rewards**: [Percentage]

## Security

### Reporting Vulnerabilities

For security concerns, please email: security@ammocoin.org

**Do not create public issues for security vulnerabilities.**

### Best Practices
- Always encrypt your wallet with a strong passphrase
- Regular backup of wallet.dat
- Keep software updated
- Use official releases only
- Verify checksums before installation

## License

AMMOcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more information or visit https://opensource.org/licenses/MIT.

## Community & Support

- **Website**: https://www.ammocoin.org/
- **GitHub**: https://github.com/everquin/AMMOcoin-v1.1.0
- **Documentation**: [deployment/docs/](deployment/docs/)
- **Issues**: https://github.com/everquin/AMMOcoin-v1.1.0/issues

## Acknowledgments

AMMOcoin is built upon the foundational work of the Bitcoin, Zcash, and cryptocurrency development communities. We acknowledge their contributions to open-source blockchain technology.

---

**Current Version**: v1.1.0
**Release Date**: October 2024
**Platform**: macOS (ARM64/Intel)
**Status**: Production Ready ✅