# AMMOcoin v1.1.0 - Official Release

**Release Date:** February 22, 2026
**Tag:** v1.1.0
**Status:** Production Ready - All platforms available

---

## What's New in v1.1.0

### Fresh Blockchain Start with Paper Wallet Genesis

This release introduces a **completely new blockchain** with the paper wallet private key embedded in the genesis block, providing a clean start for the AMMOcoin network.

**Genesis Block Parameters:**
```
Hash:        000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
Merkle Root: a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab
nNonce:      1299391
nTime:       1623089845 (June 7, 2021 - 23:04:05 UTC)
```

**Paper Wallet (Genesis Coinbase):**
```
Address:     AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME
Public Key:  049f0878e7c014c51fcb3f4f5571710833c0369aacba72546a6935c8c52d4dfdfee07cce4224c61904358c3e06faecbb9c2f286dccd864fd9dc3b061552084f752
```

---

## CRITICAL: This is NOT an Upgrade - It's a Restart

**THIS IS A FRESH BLOCKCHAIN** - completely incompatible with v1.0

### What This Means:
- **NO migration** from v1.0 blockchain
- **NO compatibility** with v1.0 nodes
- **MUST delete** old blockchain data (~/.ammocoin)
- **MUST download** new v1.1.0 binaries
- **ALL nodes** must upgrade simultaneously

---

## Downloads

### macOS ARM64 (Apple Silicon)

| File | Description |
|------|-------------|
| [AMMOcoin-v1.1.0-macOS-ARM64.dmg](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.dmg) | **Recommended** - Disk image with Qt wallet + CLI tools (67 MB) |
| [AMMOcoin-v1.1.0-macOS-ARM64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz) | CLI binaries only (15 MB) |
| [AMMOcoin-v1.1.0-macOS-ARM64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.zip) | CLI binaries only (19 MB) |

**Install:** Open .dmg, drag AMMOcoin-Qt to Applications. On first launch: right-click > Open, or run `xattr -cr AMMOcoin-Qt.app`

### Windows x86_64

| File | Description |
|------|-------------|
| [AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe) | **Recommended** - NSIS installer with Start Menu, uninstaller, protocol handler (78 MB) |
| [AMMOcoin-v1.1.0-Windows-x86_64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.tar.gz) | Portable binaries (41 MB) |
| [AMMOcoin-v1.1.0-Windows-x86_64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.zip) | Portable binaries (41 MB) |

**Install:** Run the .exe installer and follow the wizard. Launches from Start Menu.

### Linux x86_64 (Ubuntu/Debian)

| File | Description |
|------|-------------|
| [AMMOcoin-v1.1.0-Linux-amd64.deb](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-amd64.deb) | **Recommended** - Debian package with systemd service (7 MB) |
| [AMMOcoin-v1.1.0-Linux-x86_64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz) | Standalone binaries (11 MB) |
| [AMMOcoin-v1.1.0-Linux-x86_64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.zip) | Standalone binaries (11 MB) |

**Install:**
```bash
sudo dpkg -i AMMOcoin-v1.1.0-Linux-amd64.deb
sudo systemctl start ammocoind
```

### Linux ARM64 / Raspberry Pi

| File | Description |
|------|-------------|
| [AMMOcoin-v1.1.0-Linux-arm64.deb](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-arm64.deb) | **Recommended** - Debian package with systemd service, ARM-tuned config (6 MB) |
| [AMMOcoin-v1.1.0-Linux-ARM64.tar.gz](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-ARM64.tar.gz) | Standalone binaries (10 MB) |
| [AMMOcoin-v1.1.0-Linux-ARM64.zip](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-ARM64.zip) | Standalone binaries (10 MB) |

**Install:**
```bash
sudo dpkg -i AMMOcoin-v1.1.0-Linux-arm64.deb
sudo systemctl start ammocoind
```

### Checksums

Full checksums file: [AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt)

```
# macOS ARM64
08dfb0be819eba85c3238f916e7c2464d1333f97a71a4c1caa0d9ebcea6fd7b6  AMMOcoin-v1.1.0-macOS-ARM64.dmg
feea58d2ec34d7758eefa8d4ca04eb5a3d6e5a98a5d67d19f1d2ff69d07cdeb3  AMMOcoin-v1.1.0-macOS-ARM64.tar.gz

# Windows x86_64
e24c16299e123d5929308530d7d3c3f413a35849e88339ceca561f1f5b8f2992  AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe
3a4170a4a1f71bcac2e5d33a3b3c83e3df384f2e7fe143d201b8e4e31ee407ac  AMMOcoin-v1.1.0-Windows-x86_64.tar.gz

# Linux x86_64
801b371e41bd1d6d4a78c7883a04f6b6f300e610189a7f56e020f3d82ad81f6d  AMMOcoin-v1.1.0-Linux-amd64.deb
63f9506060cb1405846189e8e19b4950f2246c143148a9c929df639db5ebf86a  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Linux ARM64
ddc1b030968468e0349d266e6b1647850ea1412a52fe5de36a76d0f7149ca65e  AMMOcoin-v1.1.0-Linux-arm64.deb
e558220746d595a3d24f7593664d9f63ae8fcce844c967c7a7afcc070bcb043a  AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
```

---

## Quick Start

### 1. Delete Old Blockchain Data (REQUIRED!)
```bash
# WARNING: This deletes ALL old blockchain data
# Backup wallet.dat first if it has balances
rm -rf ~/.ammocoin
```

### 2. Install and Configure
```bash
mkdir -p ~/.ammocoin
cat > ~/.ammocoin/ammocoin.conf <<EOF
rpcuser=yourusername
rpcpassword=$(openssl rand -hex 32)
rpcport=51473
port=37020
server=1
daemon=1
listen=1

# Seed nodes
addnode=seed1.ammocoin.org:37020
addnode=seed2.ammocoin.org:37020
EOF
chmod 600 ~/.ammocoin/ammocoin.conf
```

### 3. Start Node
```bash
ammocoind -daemon
```

### 4. Verify Genesis Block
```bash
sleep 10
ammocoin-cli getblockhash 0
# MUST return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

---

## Network Information

### Seed Nodes
- **seed1.ammocoin.org** (78.141.194.140)
- **seed2.ammocoin.org** (147.182.245.102)

### Network Ports
- **P2P Port:** 37020 (mainnet), 37022 (testnet)
- **RPC Port:** 51473 (mainnet), 51475 (testnet)

### Genesis Block
```
Hash: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

**ALL nodes MUST have this genesis hash or they cannot connect!**

---

## Verification

### Verify Downloaded Binaries
```bash
# macOS/Linux
shasum -a 256 <downloaded-file>

# Windows (PowerShell)
Get-FileHash <downloaded-file> -Algorithm SHA256
```

Compare output with the checksums above.

### Verify Running Node
```bash
ammocoin-cli getblockhash 0
ammocoin-cli getblockchaininfo

# Should show:
# "blocks": 0
# "bestblockhash": "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
```

---

## Building from Source

### Prerequisites
- Git, C++ compiler (GCC 9+ / Clang)
- Rust toolchain (1.80.0+)
- Boost, Berkeley DB 4.8, OpenSSL, libevent

### Build
```bash
git clone https://github.com/everquin/AMMOcoin.git
cd AMMOcoin/source

# Install depends
cd depends && make -j$(nproc) && cd ..

# Configure and build
./autogen.sh
./configure --prefix=$(pwd)/depends/$(depends/config.guess)
make -j$(nproc)
```

See platform-specific build guides in `docs/installation/`.

---

## Known Issues

### macOS Gatekeeper ("damaged" warning)
```bash
# Remove quarantine attribute
xattr -cr /Applications/AMMOcoin-Qt.app
# Or for CLI binaries:
sudo xattr -dr com.apple.quarantine ammocoind ammocoin-cli ammocoin-tx
```

### No Peers Connecting
- Ensure port **37020** is open in firewall
- Add seed nodes manually:
  ```bash
  ammocoin-cli addnode "seed1.ammocoin.org:37020" "add"
  ammocoin-cli addnode "seed2.ammocoin.org:37020" "add"
  ```

---

## Documentation

- **[Whitepaper v1.1.0](https://github.com/everquin/AMMOcoin/blob/main/docs/whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md)**
- **[Genesis Block Authority](https://github.com/everquin/AMMOcoin/blob/main/V1.1.0_GENESIS_BLOCK_AUTHORITY.md)** - Single source of truth for genesis parameters
- **[Linux Build Instructions](https://github.com/everquin/AMMOcoin/blob/main/docs/installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md)**
- **[Seed Node Quick Start](https://github.com/everquin/AMMOcoin/blob/main/docs/operations/SEED_NODE_QUICK_START.md)**

---

## Changelog

### v1.1.0 (February 22, 2026)

#### Added
- Pre-built installers for all platforms (.dmg, .exe, .deb)
- New genesis block with paper wallet key integration
- Sapling shielded transaction support
- Complete documentation suite
- Paper wallet generator and blockchain explorer

#### Changed
- **BREAKING:** Fresh blockchain start - incompatible with v1.0
- Upgraded from PIVX 3.x to PIVX 5.x codebase
- P2P port: 37020, RPC port: 51473
- Correct genesis nNonce: 1299391

#### Fixed
- All PIVX legacy branding replaced with AMMOcoin
- Correct port configuration across all documentation
- macOS Gatekeeper compatibility (ad-hoc codesigning)

---

## Security Notes

### Paper Wallet Private Key
The genesis block contains the paper wallet private key. This key:
- Holds the genesis 250M AMMO reward
- Is documented in V1.1.0_GENESIS_BLOCK_AUTHORITY.md
- Is intentionally public for this fresh start

### Verify Everything
- Always verify SHA256 checksums after download
- Always verify genesis hash in running node
- Never run unverified binaries
- Build from source if unsure

---

## License

Distributed under the MIT License. See `COPYING` file in repository.

---

## Credits

**Development:** AMMOcoin Core Development Team
**Website:** [ammocoin.org](https://ammocoin.org)
**Repository:** [github.com/everquin/AMMOcoin](https://github.com/everquin/AMMOcoin)

---

**Genesis Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

If your node shows a different genesis hash, STOP and investigate!
