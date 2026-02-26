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
  - [AMMOcoin-v1.1.0-macOS-ARM64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz)
  - [AMMOcoin-v1.1.0-macOS-ARM64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.zip)

### Linux x86_64
- **Size:** 112 MB (tar.gz)
- **Binaries:** ammocoind, ammocoin-cli, ammocoin-tx
- **Minimum OS:** Ubuntu 20.04, Debian 11, RHEL 8, or equivalent
- **Download:**
  - [AMMOcoin-v1.1.0-Linux-x86_64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz)

### Windows x86_64
- **Size:** 17 MB (tar.gz), 17 MB (zip)
- **Binaries:** ammocoind.exe, ammocoin-cli.exe, ammocoin-tx.exe
- **Minimum OS:** Windows 10 64-bit or Windows 11
- **Download:**
  - [AMMOcoin-v1.1.0-Windows-x86_64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.tar.gz)
  - [AMMOcoin-v1.1.0-Windows-x86_64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.zip)

## Installation

### macOS ARM64
```bash
# Extract the archive
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
cd AMMOcoin-v1.1.0-macOS-ARM64/bin

# Run the daemon
./ammocoind -daemon

# Check status
./ammocoin-cli getinfo
```

### Linux x86_64
```bash
# Extract the archive
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
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
certutil -hashfile AMMOcoin-v1.1.0-Windows-x86_64.zip SHA256
```

Compare the output with the checksums in [AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt)

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

- **P2P Port:** 37020 (mainnet), 37022 (testnet)
- **RPC Port:** 51473 (mainnet), 51475 (testnet)

## Troubleshooting

### macOS: "Cannot be opened because the developer cannot be verified"
```bash
sudo xattr -r -d com.apple.quarantine /path/to/AMMOcoin-v1.1.0-macOS-ARM64
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
feea58d2ec34d7758eefa8d4ca04eb5a3d6e5a98a5d67d19f1d2ff69d07cdeb3  AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
08dfb0be819eba85c3238f916e7c2464d1333f97a71a4c1caa0d9ebcea6fd7b6  AMMOcoin-v1.1.0-macOS-ARM64.dmg
682e51a856c026bcf2a9bd2df3dcb234a67af5c130af0a1294855575bc0e3d50  AMMOcoin-v1.1.0-macOS-ARM64.zip

# Linux x86_64
63f9506060cb1405846189e8e19b4950f2246c143148a9c929df639db5ebf86a  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
cc93add92c198039d17be6ddad3f0c0f9d463c1e14e7ddd5566fcef48bfd0548  AMMOcoin-v1.1.0-Linux-x86_64.zip
801b371e41bd1d6d4a78c7883a04f6b6f300e610189a7f56e020f3d82ad81f6d  AMMOcoin-v1.1.0-Linux-amd64.deb

# Windows x86_64
3a4170a4a1f71bcac2e5d33a3b3c83e3df384f2e7fe143d201b8e4e31ee407ac  AMMOcoin-v1.1.0-Windows-x86_64.tar.gz
c3c4fe99f544adb7409aa6938447ad51038cbde19aa8982bb11ee5d45ad5aa26  AMMOcoin-v1.1.0-Windows-x86_64.zip
e24c16299e123d5929308530d7d3c3f413a35849e88339ceca561f1f5b8f2992  AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe

# Linux ARM64
e558220746d595a3d24f7593664d9f63ae8fcce844c967c7a7afcc070bcb043a  AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
afadc0762283b9b4db0f31d7bf4d289a699cd5c97b8900391602fa98e619cc88  AMMOcoin-v1.1.0-Linux-ARM64.zip
ddc1b030968468e0349d266e6b1647850ea1412a52fe5de36a76d0f7149ca65e  AMMOcoin-v1.1.0-Linux-arm64.deb
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
