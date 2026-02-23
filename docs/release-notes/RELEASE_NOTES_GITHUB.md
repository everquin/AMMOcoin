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
| [AMMOcoin-v1.1.0-macOS-ARM64.dmg](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.dmg) | **Recommended** - Disk image with Qt wallet + CLI tools (67 MB) |
| [AMMOcoin-v1.1.0-macOS-ARM64.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz) | CLI binaries only (15 MB) |
| [AMMOcoin-v1.1.0-macOS-ARM64.zip](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.zip) | CLI binaries only (19 MB) |

**Install:** Open .dmg, drag AMMOcoin-Qt to Applications. On first launch: right-click > Open, or run `xattr -cr AMMOcoin-Qt.app`

### Windows x86_64

| File | Description |
|------|-------------|
| [AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe) | **Recommended** - NSIS installer with Start Menu, uninstaller, protocol handler (78 MB) |
| [AMMOcoin-v1.1.0-Windows-x86_64.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.tar.gz) | Portable binaries (41 MB) |
| [AMMOcoin-v1.1.0-Windows-x86_64.zip](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Windows-x86_64.zip) | Portable binaries (41 MB) |

**Install:** Run the .exe installer and follow the wizard. Launches from Start Menu.

### Linux x86_64 (Ubuntu/Debian)

| File | Description |
|------|-------------|
| [ammocoin-1.1.0-amd64.deb](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/ammocoin-1.1.0-amd64.deb) | **Recommended** - Debian package with systemd service (7 MB) |
| [AMMOcoin-v1.1.0-Linux-x86_64.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz) | Standalone binaries (11 MB) |
| [AMMOcoin-v1.1.0-Linux-x86_64.zip](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.zip) | Standalone binaries (11 MB) |

**Install:**
```bash
sudo dpkg -i ammocoin-1.1.0-amd64.deb
sudo systemctl start ammocoind
```

### Linux ARM64 / Raspberry Pi

| File | Description |
|------|-------------|
| [ammocoin-1.1.0-arm64.deb](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/ammocoin-1.1.0-arm64.deb) | **Recommended** - Debian package with systemd service, ARM-tuned config (6 MB) |
| [AMMOcoin-v1.1.0-Linux-ARM64.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-ARM64.tar.gz) | Standalone binaries (10 MB) |
| [AMMOcoin-v1.1.0-Linux-ARM64.zip](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-ARM64.zip) | Standalone binaries (10 MB) |

**Install:**
```bash
sudo dpkg -i ammocoin-1.1.0-arm64.deb
sudo systemctl start ammocoind
```

### Checksums

Full checksums file: [AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt)

```
# macOS ARM64
f29770bfc855f8bb9793cdf6aa02e8712697928cb06d6ff1a08f936e4ba74772  AMMOcoin-v1.1.0-macOS-ARM64.dmg
71048bb0096c421bdbe331705a2cb9b00b46b0642e2cbf81ed6bfb025076e881  AMMOcoin-v1.1.0-macOS-ARM64.tar.gz

# Windows x86_64
73c6de479ef705b59839aefb562cebab53c00fb4bf1b9739f53efad36a556683  AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe
66bd10254f2a43cf48b27e8a14699cf44e12ce4fdc3eb7bbfc3d6a2d9e1603ae  AMMOcoin-v1.1.0-Windows-x86_64.tar.gz

# Linux x86_64
4ff57d9df66370b34ffdec5ff97eb548709dd38c03b2e2e2dd104089c0792345  ammocoin-1.1.0-amd64.deb
082f1eb063b3098d0deaef9a8550a9965cb341d771140c4222fd33944c0f5509  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Linux ARM64
f0c340be5ddca9990556d019606f57af90fa4a03b29b56a5b86d28ec0203c29f  ammocoin-1.1.0-arm64.deb
b781fcaf22860302addaf8a412d48b0669e616328135fb4ac569265c1dc2d859  AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
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
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0/source

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

- **[Whitepaper v1.1.0](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/docs/whitepapers/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md)**
- **[Genesis Block Authority](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/V1.1.0_GENESIS_BLOCK_AUTHORITY.md)** - Single source of truth for genesis parameters
- **[Linux Build Instructions](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/docs/installation/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md)**
- **[Seed Node Quick Start](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/docs/operations/SEED_NODE_QUICK_START.md)**

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
**Repository:** [github.com/everquin/AMMOcoin-v1.1.0](https://github.com/everquin/AMMOcoin-v1.1.0)

---

**Genesis Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

If your node shows a different genesis hash, STOP and investigate!
