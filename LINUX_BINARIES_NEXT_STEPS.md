# Linux Binaries - Next Steps

**Status:** ✅ Binaries compiled on VM (48.141.194.140)
**Date:** December 28, 2025

---

## 📋 Current Situation

### On Vultr VM (48.141.194.140):

**✅ Compiled binaries ready:**
- `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind`
- `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-cli`
- `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-tx`

**⚠️ Important v1.0/v1.1.0 Conflict:**
- v1.0 is installed in `/usr/bin/` (in PATH)
- v1.1.0 is in `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/` (NOT in PATH)
- Running `ammocoind` alone executes v1.0, NOT v1.1.0!
- Separate data directory created: `/root/.ammocoin-v1.1.0`

**To run v1.1.0 on VM:**
```bash
# Use full path
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind -datadir=/root/.ammocoin-v1.1.0

# Or create alias
alias ammocoind-v1.1.0='/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind'
```

### On Your Local Mac:

**✅ Created:**
- `DOWNLOAD_LINUX_BINARIES.sh` - Script to download binaries from VM
- `PACKAGE_LINUX_BINARIES.sh` - Script to package binaries for distribution
- `LINUX_BINARY_DISTRIBUTION_GUIDE.md` - Complete user installation guide

**⏸️ Waiting for:**
- You to download binaries from VM to local machine

---

## 🚀 Step-by-Step Instructions

### Step 1: Download Binaries (Run from Local Terminal)

Open a **new terminal window** on your Mac (not Claude Code) and run:

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin
./DOWNLOAD_LINUX_BINARIES.sh
```

This will download all three binaries to `binaries-linux-v1.1.0/` directory.

**Expected files:**
- `binaries-linux-v1.1.0/ammocoind` (~15-20 MB)
- `binaries-linux-v1.1.0/ammocoin-cli` (~2-5 MB)
- `binaries-linux-v1.1.0/ammocoin-tx` (~2-5 MB)

---

### Step 2: Package Binaries (Back in Claude Code)

Once download completes, tell me and I'll run:

```bash
./PACKAGE_LINUX_BINARIES.sh
```

This will create:
- `releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz`
- `releases/AMMOcoin-v1.1.0-Linux-x86_64.zip`
- `releases/CHECKSUMS-Linux.txt`

---

### Step 3: Commit to GitHub

```bash
git add binaries-linux-v1.1.0/
git add releases/AMMOcoin-v1.1.0-Linux-x86_64.*
git add releases/CHECKSUMS-Linux.txt
git add LINUX_BINARY_DISTRIBUTION_GUIDE.md
git add DOWNLOAD_LINUX_BINARIES.sh
git add PACKAGE_LINUX_BINARIES.sh
git add LINUX_BINARIES_NEXT_STEPS.md

git commit -m "Add Linux x86_64 binaries and distribution guide for v1.1.0"
git push origin main
```

---

### Step 4: Test v1.1.0 on VM (Optional)

Before distributing, verify v1.1.0 works correctly on the VM:

```bash
# SSH into VM
ssh root@48.141.194.140

# Create config for v1.1.0
mkdir -p /root/.ammocoin-v1.1.0

cat > /root/.ammocoin-v1.1.0/ammocoin.conf << 'EOF'
listen=1
server=1
daemon=1

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=$(openssl rand -hex 32)
rpcallowip=127.0.0.1
rpcport=8332

# Network
port=37020
maxconnections=125
EOF

# Start v1.1.0 daemon
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind \
  -datadir=/root/.ammocoin-v1.1.0 \
  -daemon

# Check status
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-cli \
  -datadir=/root/.ammocoin-v1.1.0 \
  getinfo

# Verify correct genesis block (v1.1.0 Path A)
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-cli \
  -datadir=/root/.ammocoin-v1.1.0 \
  getblockhash 0
# Should show: 0000075a4b9573ee2b4401c0ae785fb451d8355c91b6ed7d7a3420fe590cad58
```

---

## 🔐 v1.0 Wallet Safety

**CRITICAL:** v1.0 is still installed and running on the VM.

### v1.0 Data Location:
- Wallet: `/root/.ammocoin/wallet.dat`
- Blockchain: `/root/.ammocoin/blocks/`

### v1.1.0 Data Location:
- Wallet: `/root/.ammocoin-v1.1.0/wallet.dat` (new, empty)
- Blockchain: `/root/.ammocoin-v1.1.0/blocks/` (new blockchain)

**These are COMPLETELY SEPARATE:**
- v1.0 wallet contains keys to claim v1.1.0 balances
- NEVER delete v1.0 data until migration is complete
- See `V1.0_TO_V1.1.0_NODE_MIGRATION.md` for full details

---

## 📊 Binary Information

### Platform Details:
- **Architecture:** x86_64 (64-bit)
- **OS:** Ubuntu 20.04 LTS
- **Compiler:** GCC 9.4.0
- **Linked Libraries:** Boost 1.71, libevent, libzmq, libsodium
- **Berkeley DB:** 4.8 (statically linked with atomic.h patch)

### Binary Capabilities:
- ✅ Full node (daemon)
- ✅ RPC server
- ✅ P2P networking (port 37020)
- ✅ Staking support
- ✅ zkSNARK privacy transactions (Sapling)
- ✅ Transaction creation and signing

### Compatibility:
- Ubuntu 20.04, 22.04, 24.04 LTS
- Debian 10+ (Buster or later)
- Linux Mint 20+
- Other Ubuntu-based distributions with glibc 2.31+

---

## 📦 Distribution Strategy

Once binaries are on GitHub, users can:

### Quick Install (Recommended):
```bash
# Download pre-compiled binaries
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Verify checksum
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Extract and install
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx

# Install dependencies
sudo apt-get install -y libboost-system1.71.0 libboost-filesystem1.71.0 \
    libboost-thread1.71.0 libboost-program-options1.71.0 \
    libevent-2.1-7 libzmq5 libsodium23

# Start node
ammocoind -daemon
```

### Compile from Source:
Users who prefer to compile can still use:
```bash
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0
sudo bash scripts/setup-seed-node.sh
```

---

## 🎯 Next Immediate Actions

1. **You:** Run `./DOWNLOAD_LINUX_BINARIES.sh` from your Mac terminal
2. **You:** Tell me when download completes
3. **Me:** Run `./PACKAGE_LINUX_BINARIES.sh` to create distribution packages
4. **Me:** Commit and push binaries to GitHub
5. **Optional:** Test v1.1.0 on VM to verify it works
6. **Then:** Create GitHub release with all binaries (Linux + macOS)

---

## 📝 Documentation Status

**Created and ready:**
- ✅ `LINUX_BINARY_DISTRIBUTION_GUIDE.md` - Complete user installation guide
- ✅ `DOWNLOAD_LINUX_BINARIES.sh` - Automated download from VM
- ✅ `PACKAGE_LINUX_BINARIES.sh` - Automated packaging script
- ✅ `V1.0_TO_V1.1.0_NODE_MIGRATION.md` - Migration safety guide
- ✅ `SEED_NODE_QUICK_START.md` - Quick start with v1.0 warnings
- ✅ `VULTR_VM_SETUP_COMMANDS.md` - Step-by-step VM setup

**Will create after binaries are committed:**
- ⏸️ GitHub Release notes
- ⏸️ Updated README with download links

---

## ❓ Questions Answered

### Q: "Can I download binaries to my local device?"
**A:** Yes! Use the `DOWNLOAD_LINUX_BINARIES.sh` script or manual scp commands.

### Q: "Which version runs when I type 'ammocoind'?"
**A:** v1.0 (from `/usr/bin/`). To run v1.1.0, use full path: `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind`

### Q: "How do I avoid conflicts?"
**A:** Use separate data directories (`-datadir` flag) and different ports. See migration guide.

### Q: "What about my v1.0 wallet?"
**A:** CRITICAL - Never delete it! Contains private keys needed to claim v1.1.0 balances.

### Q: "Should users compile or use binaries?"
**A:** Both options available. Binaries are faster (5 min vs 30 min), but some users prefer to compile.

---

**Ready to proceed!** Run the download script when you're ready.

