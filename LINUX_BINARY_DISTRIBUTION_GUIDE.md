# Linux Binary Distribution Guide

**Date:** December 28, 2025
**Platform:** Ubuntu 20.04/22.04/24.04 LTS (x86_64)
**Source VM:** 48.141.194.140 (seed1.ammocoin.org)

---

## 📦 Binary Location on VM

The compiled Linux binaries are located at:
```
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-cli
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-tx
```

---

## 🔽 Downloading Binaries

### From Your Local Terminal:

```bash
# Run the automated download script
./DOWNLOAD_LINUX_BINARIES.sh

# Or download manually:
scp root@48.141.194.140:/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind ./binaries-linux-v1.1.0/
scp root@48.141.194.140:/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-cli ./binaries-linux-v1.1.0/
scp root@48.141.194.140:/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoin-tx ./binaries-linux-v1.1.0/
```

---

## ⚠️ CRITICAL: v1.0 vs v1.1.0 Command Conflicts

### The Situation on VM:

**v1.0 Installation:**
- Location: `/usr/bin/`
- In system PATH: YES
- Running `ammocoind` executes: v1.0

**v1.1.0 Installation:**
- Location: `/opt/AMMOcoin-v1.1.0/ammocoin-source/src/`
- In system PATH: NO
- Running `ammocoind` executes: v1.0 (NOT v1.1.0!)

### How to Run v1.1.0 on VM:

```bash
# ❌ WRONG - This runs v1.0:
ammocoind

# ✅ CORRECT - This runs v1.1.0:
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind

# Best practice: Use absolute path or create alias
alias ammocoind-v1.1.0='/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind'
```

### Separate Data Directories:

```bash
# v1.0 data (DO NOT DELETE - contains wallet keys!)
/root/.ammocoin/

# v1.1.0 data (new, isolated)
/root/.ammocoin-v1.1.0/
```

### Running Both Versions Simultaneously:

```bash
# v1.0 (if you need it running)
ammocoind -datadir=/root/.ammocoin -port=37021 -rpcport=8333 -daemon

# v1.1.0 (on standard ports)
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind \
  -datadir=/root/.ammocoin-v1.1.0 \
  -port=37020 \
  -rpcport=8332 \
  -daemon
```

---

## 📋 Binary Verification

Once downloaded, verify the binaries:

```bash
cd binaries-linux-v1.1.0/

# Check file sizes
ls -lh

# Check architecture
file ammocoind
# Should show: ELF 64-bit LSB executable, x86-64

# Check version (requires running on Linux)
./ammocoind --version
# Should show: AMMOcoin Core Daemon version v1.1.0.0

# Verify genesis block in code
strings ammocoind | grep "000005cb7068246016a7cc43aedde75eee3de551f24afca2b0dc28cfc4fb3329"
# Should match v1.1.0 genesis block
```

---

## 📦 Packaging for Distribution

After downloading, create distribution packages:

```bash
# Create tar.gz archive
cd binaries-linux-v1.1.0/
tar -czf ../releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz ammocoind ammocoin-cli ammocoin-tx

# Create zip archive
zip ../releases/AMMOcoin-v1.1.0-Linux-x86_64.zip ammocoind ammocoin-cli ammocoin-tx

# Generate checksums
cd ../releases/
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz >> CHECKSUMS.txt
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.zip >> CHECKSUMS.txt
```

---

## 🚀 User Installation Instructions

Users downloading these binaries should follow this process:

### 1. Download and Extract

```bash
# Download from GitHub releases
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Verify checksum
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Compare with CHECKSUMS.txt

# Extract
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
```

### 2. Install Binaries

**Option A: System-wide installation (replaces v1.0)**

⚠️ **WARNING:** Only use this if you've backed up v1.0 wallet!

```bash
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx
```

**Option B: User-local installation (safe, v1.0 preserved)**

```bash
mkdir -p ~/.local/bin
cp ammocoind ammocoin-cli ammocoin-tx ~/.local/bin/
chmod +x ~/.local/bin/ammocoin*

# Add to PATH (add to ~/.bashrc)
export PATH="$HOME/.local/bin:$PATH"
```

**Option C: Specific directory (recommended for testing)**

```bash
sudo mkdir -p /opt/ammocoin-v1.1.0/bin
sudo cp ammocoind ammocoin-cli ammocoin-tx /opt/ammocoin-v1.1.0/bin/
sudo chmod +x /opt/ammocoin-v1.1.0/bin/*

# Run with full path
/opt/ammocoin-v1.1.0/bin/ammocoind --version
```

### 3. Install Dependencies

```bash
# Required runtime dependencies
sudo apt-get update
sudo apt-get install -y \
    libboost-system1.71.0 \
    libboost-filesystem1.71.0 \
    libboost-thread1.71.0 \
    libboost-program-options1.71.0 \
    libevent-2.1-7 \
    libzmq5 \
    libsodium23

# For Ubuntu 22.04, package versions may differ:
sudo apt-get install -y \
    libboost-system1.74.0 \
    libboost-filesystem1.74.0 \
    libboost-thread1.74.0 \
    libboost-program-options1.74.0 \
    libevent-2.1-7 \
    libzmq5 \
    libsodium23
```

### 4. Install zkSNARK Parameters

```bash
mkdir -p ~/.ammocoin-params
cd ~/.ammocoin-params
wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
```

### 5. Create Configuration

```bash
mkdir -p ~/.ammocoin-v1.1.0

cat > ~/.ammocoin-v1.1.0/ammocoin.conf << EOF
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

# Seed nodes
addnode=seed1.ammocoin.org:37020
addnode=seed2.ammocoin.org:37020
EOF

chmod 600 ~/.ammocoin-v1.1.0/ammocoin.conf
```

### 6. Start the Node

```bash
ammocoind -datadir=~/.ammocoin-v1.1.0 -daemon

# Check status
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getinfo
```

---

## 🔐 Security Verification

### Binary Signing (Future Enhancement)

Current binaries are unsigned. Future releases should include:
- GPG signatures
- Reproducible builds
- Checksums in release notes

### Checksum Verification

Always verify checksums before installation:

```bash
# Download checksum file
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/CHECKSUMS.txt

# Verify
sha256sum -c CHECKSUMS.txt --ignore-missing
```

---

## 📊 Binary Information

### Expected File Sizes (Approximate)

```
ammocoind:    ~15-20 MB (stripped) or ~100-150 MB (with debug symbols)
ammocoin-cli: ~2-5 MB (stripped) or ~10-20 MB (with debug symbols)
ammocoin-tx:  ~2-5 MB (stripped) or ~10-20 MB (with debug symbols)
```

### Supported Platforms

**Currently Compiled:**
- Ubuntu 20.04 LTS (x86_64)
- Ubuntu 22.04 LTS (x86_64)
- Ubuntu 24.04 LTS (x86_64)

**Dependencies:**
- glibc 2.31+ (Ubuntu 20.04+)
- libstdc++6 (GCC 9+)
- Boost 1.71+
- Berkeley DB 4.8 (built-in, no external dependency needed)

**Should work on:**
- Debian 10+ (Buster or later)
- Linux Mint 20+
- Pop!_OS 20.04+
- Other Ubuntu-based distributions

---

## 🆘 Troubleshooting

### "ammocoind: command not found"

```bash
# Use full path
/opt/ammocoin-v1.1.0/bin/ammocoind --version

# Or add to PATH
export PATH="/opt/ammocoin-v1.1.0/bin:$PATH"
```

### "error while loading shared libraries"

```bash
# Install missing dependencies
sudo apt-get install -y libboost-all-dev libevent-dev libzmq3-dev libsodium-dev

# Check what's missing
ldd ammocoind | grep "not found"
```

### Wrong version running

```bash
# Check which binary is being executed
which ammocoind

# Check version explicitly
/opt/ammocoin-v1.1.0/bin/ammocoind --version
```

### v1.0 wallet concerns

See `V1.0_TO_V1.1.0_NODE_MIGRATION.md` for comprehensive migration guide.

---

## 📞 Support

- **Migration Guide:** `V1.0_TO_V1.1.0_NODE_MIGRATION.md`
- **Quick Start:** `SEED_NODE_QUICK_START.md`
- **VM Setup:** `VULTR_VM_SETUP_COMMANDS.md`
- **Network Bootstrap:** `NETWORK_BOOTSTRAP_GUIDE.md`

---

**Last Updated:** December 28, 2025
**Binary Version:** v1.1.0.0
**Compiled On:** Ubuntu 20.04 LTS (Vultr VM)
**Compiler:** GCC 9.4.0
**Architecture:** x86_64 (64-bit)

