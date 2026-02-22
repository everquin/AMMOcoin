# AMMOcoin v1.1.0 - Official Release

**Release Date:** December 30, 2025
**Tag:** v1.1.0-genesis-final
**Status:** Production Ready (macOS ARM64 available now, Linux coming soon)

---

## 🎉 What's New in v1.1.0

### Fresh Blockchain Start with Paper Wallet Genesis

This release introduces a **completely new blockchain** with the paper wallet private key embedded in the genesis block, providing a clean start for the AMMOcoin network.

**Genesis Block Parameters:**
```
Hash:        000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
Merkle Root: a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab
nNonce: 942131
nTime:       1623089845 (June 7, 2021 - 23:04:05 UTC)
```

**Paper Wallet (Genesis Coinbase):**
```
Address:     AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME
Public Key:  049f0878e7c014c51fcb3f4f5571710833c0369aacba72546a6935c8c52d4dfdfee07cce4224c61904358c3e06faecbb9c2f286dccd864fd9dc3b061552084f752
```

---

## ⚠️ CRITICAL: This is NOT an Upgrade - It's a Restart

**THIS IS A FRESH BLOCKCHAIN** - completely incompatible with v1.0

### What This Means:
- ❌ **NO migration** from v1.0 blockchain
- ❌ **NO compatibility** with v1.0 nodes
- ✅ **MUST delete** old blockchain data (~/.ammocoin)
- ✅ **MUST download** new v1.1.0 binaries
- ✅ **ALL nodes** must upgrade simultaneously

### Why the Restart?
- Genesis block now contains the paper wallet private key
- Properly mined genesis with correct proof-of-work
- Elimination of all previous genesis block issues
- Clean network start with verified parameters

---

## 📦 Downloads

### macOS ARM64 (Apple Silicon)

**Available NOW:**

| File | Size | SHA256 Checksum |
|------|------|-----------------|
| [AMMOcoin-v1.1.0-macOS-ARM64.tar.gz](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0-genesis-final/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz) | 4.6 MB | `8e37a2349b556c78aa8d98f56cc7849716d0f857a055646fd10a60bb024c9ab1` |
| [AMMOcoin-v1.1.0-macOS-ARM64.zip](https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0-genesis-final/AMMOcoin-v1.1.0-macOS-ARM64.zip) | 4.6 MB | `1e41792ec576361a3d270a37209dc062faba200d7409812d271691202554a41d` |

**Contains:**
- `ammocoind` (11 MB) - Daemon/Node
- `ammocoin-cli` (382 KB) - Command-line interface
- `ammocoin-tx` (1.4 MB) - Transaction utility

### Linux x86_64

**Coming Soon** - Build instructions available in repository:
- See: `LINUX_BUILD_INSTRUCTIONS_v1.1.0.md`
- Build from tag: `v1.1.0-genesis-final`

### Windows

**To Be Announced** - Not required for initial network launch

---

## 🚀 Installation Guide

### macOS ARM64 (Apple Silicon)

#### 1. Download and Extract
```bash
# Download (choose tar.gz or zip)
curl -L -O https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0-genesis-final/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz

# Verify checksum
shasum -a 256 AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
# Should match: 8e37a2349b556c78aa8d98f56cc7849716d0f857a055646fd10a60bb024c9ab1

# Extract
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
cd AMMOcoin-v1.1.0-macOS-ARM64/
```

#### 2. Delete Old Blockchain Data (REQUIRED!)
```bash
# ⚠️ WARNING: This deletes ALL blockchain data and wallets!
# Backup wallets first if they have balances (they shouldn't in v1.0)
rm -rf ~/.ammocoin
```

#### 3. Install Binaries
```bash
# Option A: Install to /usr/local/bin
sudo cp ammocoind ammocoin-cli ammocoin-tx /usr/local/bin/
sudo chmod +x /usr/local/bin/ammocoin*

# Option B: Run from current directory
chmod +x ammocoind ammocoin-cli ammocoin-tx
```

#### 4. Configure Node
```bash
mkdir -p ~/.ammocoin
cat > ~/.ammocoin/ammocoin.conf <<EOF
rpcuser=yourusername
rpcpassword=yourpassword
rpcport=8332
server=1
daemon=1
EOF
```

#### 5. Start Node
```bash
ammocoind -daemon
# Or if running from current directory:
./ammocoind -daemon
```

#### 6. Verify Genesis Block
```bash
# Wait a few seconds for startup
sleep 10

# Check genesis hash
ammocoin-cli getblockhash 0
# MUST return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

**If genesis hash doesn't match, DO NOT USE - contact support!**

---

## 🔍 Verification

### Verify Downloaded Binaries

#### Check Checksums
```bash
# Download checksums file
curl -L -O https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0-genesis-final/CHECKSUMS-macOS-ARM64.txt

# Verify
shasum -a 256 -c CHECKSUMS-macOS-ARM64.txt
```

#### Verify Genesis in Binary
```bash
strings ammocoind | grep "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
# Should return 2-3 matches
```

### Verify Running Node
```bash
# Get genesis hash
ammocoin-cli getblockhash 0

# Get blockchain info
ammocoin-cli getblockchaininfo

# Should show:
# "blocks": 0
# "bestblockhash": "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
```

---

## 📚 Documentation

### Essential Reading
- **[V1.1.0_GENESIS_BLOCK_AUTHORITY.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/V1.1.0_GENESIS_BLOCK_AUTHORITY.md)** - Single source of truth for genesis parameters
- **[EXECUTION_COMPLETE_v1.1.0.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/EXECUTION_COMPLETE_v1.1.0.md)** - Complete execution summary
- **[LINUX_BUILD_INSTRUCTIONS_v1.1.0.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/LINUX_BUILD_INSTRUCTIONS_v1.1.0.md)** - Build Linux binaries from source

### For Node Operators
- **[SEED_NODE_UPDATE_GUIDE_v1.1.0.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/SEED_NODE_UPDATE_GUIDE_v1.1.0.md)** - Update seed nodes
- **[USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)** - User upgrade guide

---

## 🛠️ Building from Source

### Prerequisites
- Git
- C++ compiler (GCC/Clang)
- Rust toolchain (1.80.0+)
- Boost libraries
- Berkeley DB 4.8
- OpenSSL
- Other dependencies (see build guide)

### Build Instructions

#### Clone Repository
```bash
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0
```

#### Checkout Release Tag
```bash
git checkout v1.1.0-genesis-final
```

#### Follow Platform-Specific Guide
- **Linux:** See `LINUX_BUILD_INSTRUCTIONS_v1.1.0.md`
- **macOS:** Build process documented in repository
- **Windows:** Cross-compile or native build (instructions TBD)

#### Verify Before Using
```bash
# CRITICAL: Verify genesis in built binary
strings src/ammocoind | grep "000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2"
# MUST return matches!
```

---

## 🌐 Network Information

### Seed Nodes
- **seed1.ammocoin.org** - Primary seed node (update pending)

### Network Ports
- **P2P Port:** 8338
- **RPC Port:** 8332 (localhost only by default)

### Genesis Block
```
Hash: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

**ALL nodes MUST have this genesis hash or they cannot connect!**

---

## ⚡ Quick Start Checklist

Before connecting to the network:

- [ ] Downloaded correct binaries for your platform
- [ ] Verified SHA256 checksums
- [ ] Deleted old blockchain data (`rm -rf ~/.ammocoin`)
- [ ] Installed new v1.1.0 binaries
- [ ] Created fresh configuration file
- [ ] Started node with `-daemon`
- [ ] Verified genesis hash matches: `00000f14...`
- [ ] Checked `getblockchaininfo` shows blocks: 0

---

## 🐛 Known Issues

### macOS Gatekeeper
If macOS prevents you from running the binaries:
```bash
sudo xattr -dr com.apple.quarantine ammocoind ammocoin-cli ammocoin-tx
```

### No Peers Connecting
- Normal at launch - network is starting fresh
- Ensure port 8338 is open in firewall
- Add seed nodes manually if needed:
  ```bash
  ammocoin-cli addnode "seed1.ammocoin.org:8338" "add"
  ```

### "Cannot find genesis block" Error
- This means you're running binaries with wrong genesis
- Verify checksums match exactly
- Re-download if needed
- DO NOT use v1.0 binaries!

---

## 💬 Support & Community

### Getting Help
- **GitHub Issues:** [Report bugs or ask questions](https://github.com/everquin/AMMOcoin-v1.1.0/issues)
- **Documentation:** Check repository docs for detailed guides

### Contributing
- Build and test binaries for your platform
- Report issues with clear reproduction steps
- Submit pull requests for improvements

---

## 🔐 Security Notes

### Paper Wallet Private Key
The genesis block contains the paper wallet private key. This key:
- ✅ Holds the genesis 250M AMMO reward
- ✅ Is documented in V1.1.0_GENESIS_BLOCK_AUTHORITY.md
- ✅ Is intentionally public for this fresh start
- ⚠️ Should be treated carefully in production

### Verify Everything
- Always verify SHA256 checksums
- Always verify genesis hash in binaries
- Never run unverified binaries
- Build from source if unsure

---

## 📋 Changelog

### v1.1.0 (December 30, 2025)

#### Added
- New genesis block with paper wallet key integration
- Complete documentation suite
- Automated build system improvements
- Genesis verification procedures

#### Changed
- **BREAKING:** Fresh blockchain start - incompatible with v1.0
- Updated all genesis block parameters
- Improved build configuration

#### Fixed
- Genesis block mining with correct nNonce: 942131)
- Proof-of-work validation
- Build system compatibility issues

#### Removed
- All v1.0 blockchain data (manual deletion required)
- Old genesis block references

---

## 🎯 What's Next

### Short Term
- [ ] Linux x86_64 binaries released
- [ ] Seed nodes updated and verified
- [ ] Network launch coordinated
- [ ] Community announcement

### Medium Term
- [ ] Windows binaries available
- [ ] Additional platform support
- [ ] Network growth and stability

---

## 📜 License

Distributed under the MIT License. See `COPYING` file in repository.

---

## 👥 Credits

**Development:** AMMOcoin Core Development Team
**Release Coordination:** Claude Code (AI Assistant)
**Community:** All node operators and contributors

---

## ⚠️ Final Reminder

**THIS IS A FRESH BLOCKCHAIN START**

Before connecting:
1. ✅ Delete old blockchain data
2. ✅ Install v1.1.0 binaries
3. ✅ Verify genesis hash
4. ✅ Connect to network

**Genesis Hash:** `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

If your node shows a different genesis hash, STOP and investigate!

---

**Questions?** See [V1.1.0_GENESIS_BLOCK_AUTHORITY.md](https://github.com/everquin/AMMOcoin-v1.1.0/blob/main/V1.1.0_GENESIS_BLOCK_AUTHORITY.md) for complete specifications.
