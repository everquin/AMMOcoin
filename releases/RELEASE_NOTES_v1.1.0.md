# AMMOcoin v1.1.0 - Official Release

**Release Date:** January 3, 2026
**Genesis Block Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
**Merkle Root:** `a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab`
**Nonce:** `1299391`

## Overview

AMMOcoin v1.1.0 is a major release featuring a new genesis block and multi-platform support. This release includes production-ready binaries for macOS ARM64, Linux x86_64, and Windows x86_64.

## What's New in v1.1.0

### Core Changes
- **New Genesis Block** - Fresh blockchain start with genesis block mined on January 1, 2026
- **Updated Dependencies** - All dependencies updated to latest stable versions
- **Improved Build System** - Enhanced cross-platform compilation support

### Platform Support
- **macOS ARM64** - Native support for Apple Silicon (M1/M2/M3 chips)
- **Linux x86_64** - Compatible with Ubuntu 20.04+, Debian 11+, RHEL 8+
- **Windows x86_64** - Full support for Windows 10/11 64-bit

### Technical Improvements
- Rust 1.80+ integration for enhanced cryptographic operations
- MinGW POSIX threading model for Windows builds
- Optimized dependency builds with Qt 5.9.7 support
- BerkeleyDB 4.8 wallet compatibility

## Download

### macOS ARM64 (Apple Silicon)
- **Size:** 4.0 MB (tar.gz), 4.0 MB (zip)
- **Binaries:** ammocoind, ammocoin-cli, ammocoin-tx
- **Minimum OS:** macOS 11 (Big Sur) or later
- **Download:**
  - [AMMOcoin-macOS-ARM64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-macOS-ARM64.tar.gz)
  - [AMMOcoin-macOS-ARM64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-macOS-ARM64.zip)

### Linux x86_64
- **Size:** 112 MB (tar.gz)
- **Binaries:** ammocoind, ammocoin-cli, ammocoin-tx
- **Minimum OS:** Ubuntu 20.04, Debian 11, RHEL 8, or equivalent
- **Download:**
  - [AMMOcoin-Linux-x86_64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-Linux-x86_64.tar.gz)

### Windows x86_64
- **Size:** 17 MB (tar.gz), 17 MB (zip)
- **Binaries:** ammocoind.exe, ammocoin-cli.exe, ammocoin-tx.exe
- **Minimum OS:** Windows 10 64-bit or Windows 11
- **Download:**
  - [AMMOcoin-Windows-x86_64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-Windows-x86_64.tar.gz)
  - [AMMOcoin-Windows-x86_64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-Windows-x86_64.zip)

## Installation

### macOS ARM64
```bash
# Extract the archive
tar -xzf AMMOcoin-macOS-ARM64.tar.gz
cd AMMOcoin-macOS-ARM64/bin

# Run the daemon
./ammocoind -daemon

# Check status
./ammocoin-cli getinfo
```

### Linux x86_64
```bash
# Extract the archive
tar -xzf AMMOcoin-Linux-x86_64.tar.gz
cd bin

# Run the daemon
./ammocoind -daemon

# Check status
./ammocoin-cli getinfo
```

### Windows x86_64
```powershell
# Extract the zip file
# Navigate to the bin directory in File Explorer or Command Prompt

# Run the daemon
ammocoind.exe -daemon

# Check status (in a new command prompt)
ammocoin-cli.exe getinfo
```

## Verification

To verify the integrity of your download:

### macOS/Linux
```bash
sha256sum AMMOcoin-<platform>.tar.gz
```

### Windows
```powershell
certutil -hashfile AMMOcoin-Windows-x86_64.zip SHA256
```

Compare the output with the checksums in [AMMOcoin-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-ALL-PLATFORMS-CHECKSUMS.txt)

## Configuration

### First Run
On first run, AMMOcoin will create a data directory:
- **macOS:** `~/Library/Application Support/AMMOcoin/`
- **Linux:** `~/.ammocoin/`
- **Windows:** `%APPDATA%\AMMOcoin\`

### Basic Configuration
Create a file named `ammocoin.conf` in your data directory:

```conf
# RPC Settings
rpcuser=yourusername
rpcpassword=yourpassword
rpcallowip=127.0.0.1

# Network Settings
listen=1
server=1

# Optional: Enable transaction indexing
txindex=1
```

## Upgrading from v1.0

**IMPORTANT:** v1.1.0 uses a new genesis block and is NOT compatible with v1.0 blockchain data.

This is a fresh start. You will need to:
1. Backup your v1.0 wallet (if you have funds)
2. Stop v1.0 daemon
3. Install v1.1.0 binaries
4. Start with a fresh blockchain

## Network Information

- **P2P Port:** 44444
- **RPC Port:** 44445
- **Testnet P2P Port:** 54444
- **Testnet RPC Port:** 54445

## Troubleshooting

### macOS: "Cannot be opened because the developer cannot be verified"
```bash
sudo xattr -r -d com.apple.quarantine /path/to/AMMOcoin-macOS-ARM64
```

### Linux: "Permission denied"
```bash
chmod +x ammocoind ammocoin-cli ammocoin-tx
```

### Windows: "VCRUNTIME140.dll was not found"
Install Visual C++ Redistributable from Microsoft.

## Build Information

### macOS ARM64
- Built natively on macOS 14 (Sonoma) with Apple Silicon
- Compiler: Apple clang 15.0.0
- Rust: 1.85.0
- Dependencies: Boost 1.85, OpenSSL 3.4, BerkeleyDB 4.8

### Linux x86_64
- Built via GitHub Actions on Ubuntu 22.04
- Compiler: GCC 11.4.0
- Rust: 1.80.0
- Cross-platform dependency builds

### Windows x86_64
- Cross-compiled via GitHub Actions using MinGW-w64
- Compiler: MinGW-w64 GCC 11.4 (POSIX threads)
- Rust: 1.80.0
- Windows target: x86_64-pc-windows-gnu

## SHA256 Checksums

```
# macOS ARM64
71048bb0096c421bdbe331705a2cb9b00b46b0642e2cbf81ed6bfb025076e881  AMMOcoin-macOS-ARM64.tar.gz
c2359866e4738e9f0230b2f4dada18acb4b45afae645630ce576244bc3093ec6  AMMOcoin-macOS-ARM64.zip

# Linux x86_64
082f1eb063b3098d0deaef9a8550a9965cb341d771140c4222fd33944c0f5509  AMMOcoin-Linux-x86_64.tar.gz

# Windows x86_64
66bd10254f2a43cf48b27e8a14699cf44e12ce4fdc3eb7bbfc3d6a2d9e1603ae  AMMOcoin-Windows-x86_64.tar.gz
533e5160cdf5c59e8a61e20628f25c67fc5f74a260928ab9faa02f4464861f0d  AMMOcoin-Windows-x86_64.zip
```

## Support

- **GitHub Issues:** https://github.com/everquin/AMMOcoin/issues
- **Documentation:** See the `docs/` directory in the repository

## Contributors

Special thanks to all contributors who made this release possible.

## License

AMMOcoin is released under the MIT License. See LICENSE file for details.

---

**Note:** This is a major release with a new genesis block. Always verify the genesis block hash before mining or running a node to ensure you're on the correct network.
