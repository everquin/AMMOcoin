# AMMOcoin Documentation

Welcome to the AMMOcoin documentation. This directory contains all official documentation for the project.

> **⚠️ v1.1.1 is a mandatory hard fork.** Proof-of-Stake starts at block 2,776 and there is no mining after it. v1.1.1 uses new network magic, so it does not connect to v1.0 or v1.1.0 nodes - everyone must upgrade. New data folder (`~/.ammocoin11`, `~/Library/Application Support/AMMOcoin11`, `%APPDATA%\AMMOcoin11`), ports 37020 (P2P) / 51473 (RPC), Linux binaries need glibc 2.34+ (Ubuntu 22.04 or newer). See the [v1.1.1 Release Notes](release-notes/RELEASE_NOTES_v1.1.1.md).

## Quick Links

### For Users
- [v1.0 Balance Airdrop](migration/V1.0_BALANCE_AIRDROP.md) - v1.0 balances are airdropped to the same addresses; send nothing
- [Wallet Setup](01-wallet-setup.md) - Install and configure your wallet
- [Staking Guide](02-staking-guide.md) - Staking and cold staking
- [Masternode Setup](03-masternode-setup.md) - Run a masternode
- [Node Setup](04-node-setup.md) - Full node and systemd service
- [Terminal Commands](05-terminal-commands.md) - CLI reference
- [DAO Participation](06-dao-participation.md) - Proposals and voting
- [Security Guide](08-security-guide.md) - Protect your wallet
- [Troubleshooting](09-troubleshooting.md) - Common problems
- [FAQ](10-faq.md) - Frequently asked questions

### Superseded (history only)
- [User Migration Guide](migration/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md) and [Distribution Process Guide](migration/DISTRIBUTION_PROCESS_GUIDE.md) - old disposal-address process, replaced by the airdrop
- [Quick Download Guide v1.1.0](release-notes/QUICK_DOWNLOAD_GUIDE_v1.1.0.md) - v1.1.0 binaries no longer follow the network after block 2,775

### For Node Operators
- [Seed Node Operations](operations/SEED_NODE_QUICK_START.md) - Running a seed node
- [Vultr VPS Deployment](operations/VULTR_VPS_DEPLOYMENT.md) - Deploy on Vultr VPS
- [Testing Guide](operations/TEST_LOCAL_NODE_MACOS.md) - Test your node locally

### For Developers
- [Linux Build Instructions](installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md) - Build from source on Linux
- [Cross-Compilation Guide](installation/CROSS_COMPILATION_GUIDE.md) - Multi-platform builds
- [macOS Installation](installation/INSTALL_MACOS.md) - Build on macOS

### Technical Documentation
- [Comprehensive Whitepaper](whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md) - Complete technical specification
- [Standard Whitepaper](whitepapers/AMMOcoin_Whitepaper_v1.1.0.md) - Concise whitepaper

### Release Information
- [Release Notes v1.1.1](release-notes/RELEASE_NOTES_v1.1.1.md) - PoS hard fork at block 2,776
- [Release Notes v1.1.0](release-notes/RELEASE_NOTES_v1.1.0.md) - What's new in v1.1.0
- [GitHub Release Notes](release-notes/RELEASE_NOTES_GITHUB.md) - GitHub-formatted notes

## Directory Structure

```
docs/
├── installation/     # Build and installation guides
├── guides/          # General guides and tutorials
├── operations/      # Node operations and deployment
├── whitepapers/     # Technical whitepapers
├── migration/       # v1.0 → v1.1 migration docs (airdrop)
└── release-notes/   # Release notes and changelogs
```

## Genesis Block Authority

The definitive genesis block parameters are documented in the root directory:
[V1.1.0_GENESIS_BLOCK_AUTHORITY.md](../V1.1.0_GENESIS_BLOCK_AUTHORITY.md)

**Genesis Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

## Getting Help

- **GitHub Issues:** https://github.com/everquin/AMMOcoin/issues
- **GitHub Discussions:** https://github.com/everquin/AMMOcoin/discussions

## Contributing

Documentation improvements are welcome! Please submit pull requests with clear descriptions of changes.
