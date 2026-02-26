# Quick Download Guide - AMMOcoin v1.1.0

**Version:** v1.1.0
**Release Date:** December 28, 2025
**Release Page:** https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0

---

## 📦 Direct Download Links

### Linux (Ubuntu 20.04/22.04/24.04) - x86_64

**Option 1: tar.gz (Recommended)**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
```

**Option 2: zip**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.zip
```

**Size:** 72 MB (compressed), ~198 MB (extracted)

---

### macOS (Apple Silicon - M1/M2/M3/M4)

```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/ammocoin-v1.1.0-macos-arm64.tar.gz
```

---

### Checksums (SHA256)

**Download checksums file:**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/CHECKSUMS-Linux.txt
```

**Verify your download:**
```bash
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Should match: 082f1eb063b3098d0deaef9a8550a9965cb341d771140c4222fd33944c0f5509

# Or automatically verify:
sha256sum -c CHECKSUMS-Linux.txt --ignore-missing
```

---

## ⚡ Quick Install (Linux)

### 1-Line Installation:

```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz && \
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz && \
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx && \
ammocoind --version
```

### Complete Setup (Copy and Paste):

```bash
# Download and install binaries
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx

# Install dependencies
sudo apt-get update
sudo apt-get install -y libboost-system1.71.0 libboost-filesystem1.71.0 \
    libboost-thread1.71.0 libboost-program-options1.71.0 \
    libevent-2.1-7 libzmq5 libsodium23

# Install zkSNARK parameters
mkdir -p ~/.ammocoin-params
cd ~/.ammocoin-params
wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
cd ~

# Create configuration
mkdir -p ~/.ammocoin-v1.1.0
cat > ~/.ammocoin-v1.1.0/ammocoin.conf << 'EOF'
listen=1
server=1
daemon=1
rpcuser=ammocoinrpc
rpcpassword=CHANGE_THIS_TO_SECURE_PASSWORD
rpcallowip=127.0.0.1
rpcport=51473
port=37020
maxconnections=125
addnode=seed1.ammocoin.org:37020
addnode=seed2.ammocoin.org:37020
EOF
chmod 600 ~/.ammocoin-v1.1.0/ammocoin.conf

# IMPORTANT: Change rpcpassword in config file!
# Use: openssl rand -hex 32

# Start node
ammocoind -datadir=~/.ammocoin-v1.1.0 -daemon

# Check status
sleep 5
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getinfo

# Verify genesis block
ammocoin-cli -datadir=~/.ammocoin-v1.1.0 getblockhash 0
# Should show: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

---

## ⚡ Quick Install (macOS)

```bash
# Download and install
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/ammocoin-v1.1.0-macos-arm64.tar.gz
tar -xzf ammocoin-v1.1.0-macos-arm64.tar.gz
sudo cp ammocoind ammocoin-cli ammocoin-tx /usr/local/bin/

# Verify
ammocoind --version

# Install zkSNARK parameters
mkdir -p ~/.ammocoin-params
cd ~/.ammocoin-params
curl -O https://download.z.cash/downloads/sapling-spend.params
curl -O https://download.z.cash/downloads/sapling-output.params
cd ~

# Create configuration (same as Linux above)
# Then start node with: ammocoind -datadir=~/.ammocoin-v1.1.0 -daemon
```

---

## ⚠️ CRITICAL for v1.0 Users

**If you have AMMOcoin v1.0 installed with wallet balances:**

🔴 **STOP!** Read this first: [V1.0_TO_V1.1.0_NODE_MIGRATION.md](https://github.com/everquin/AMMOcoin/blob/main/V1.0_TO_V1.1.0_NODE_MIGRATION.md)

**Key points:**
- v1.1.0 is a **completely new blockchain**
- Your v1.0 wallet contains **private keys** needed to claim v1.1.0 balances
- **NEVER delete** v1.0 wallet before claiming
- Use **separate data directories** (v1.0: `~/.ammocoin`, v1.1.0: `~/.ammocoin-v1.1.0`)

---

## 📚 Documentation Links

**Essential Reading:**
- **Complete Release Notes:** [RELEASE_NOTES_v1.1.0.md](https://github.com/everquin/AMMOcoin/blob/main/RELEASE_NOTES_v1.1.0.md)
- **User Migration Guide:** [USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md](https://github.com/everquin/AMMOcoin/blob/main/USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)
- **Node Operator Migration:** [V1.0_TO_V1.1.0_NODE_MIGRATION.md](https://github.com/everquin/AMMOcoin/blob/main/V1.0_TO_V1.1.0_NODE_MIGRATION.md)

**Installation Guides:**
- **Linux Binary Guide:** [LINUX_BINARY_DISTRIBUTION_GUIDE.md](https://github.com/everquin/AMMOcoin/blob/main/LINUX_BINARY_DISTRIBUTION_GUIDE.md)
- **Seed Node Quick Start:** [SEED_NODE_QUICK_START.md](https://github.com/everquin/AMMOcoin/blob/main/SEED_NODE_QUICK_START.md)
- **Vultr VM Commands:** [VULTR_VM_SETUP_COMMANDS.md](https://github.com/everquin/AMMOcoin/blob/main/VULTR_VM_SETUP_COMMANDS.md)

---

## 🔐 Security Checksums

**Linux x86_64:**
```
082f1eb063b3098d0deaef9a8550a9965cb341d771140c4222fd33944c0f5509  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
f9b9a7c572c30f5ee811d60e5bb19b77f166ebe86221fba65960f1ea96184d1c  AMMOcoin-v1.1.0-Linux-x86_64.zip
```

**Always verify before installing!**

---

## 🌐 Network Information

**Genesis Block:** `0x000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`

**Seed Nodes:**
- `seed1.ammocoin.org:37020`
- `seed2.ammocoin.org:37020`

**Ports:**
- P2P Network: 37020
- RPC Server: 51473 (localhost only recommended)

**Data Directory:** `~/.ammocoin-v1.1.0` (keep separate from v1.0!)

---

## 💡 Quick Tips

1. **Always verify checksums** before installation
2. **Use separate data directory** for v1.1.0 (`-datadir=~/.ammocoin-v1.1.0`)
3. **Never delete v1.0 wallet** (contains claim keys!)
4. **Strong RPC password** - Use `openssl rand -hex 32`
5. **Firewall**: Open port 37020 for P2P, keep 51473 localhost-only
6. **Monitor logs**: `tail -f ~/.ammocoin-v1.1.0/debug.log`

---

## 📞 Support

- **GitHub Release:** https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0
- **Issues:** https://github.com/everquin/AMMOcoin/issues
- **Discussions:** https://github.com/everquin/AMMOcoin/discussions

---

**Last Updated:** December 28, 2025
**Version:** v1.1.0
**Binary Compilation:** Ubuntu 20.04 LTS (Vultr VM)

✅ Ready for production deployment!

