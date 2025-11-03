# AMMOcoin v1.1.0 Binary Distribution Guide

## 🎯 Current Status

**SOURCE CODE**: ✅ Complete and Production-Ready
- Full PIVX → AMMOcoin transformation (373,485+ lines)
- All trademark compliance achieved
- BLS integration and Sapling privacy transactions
- Cross-platform build system configured

**BINARIES**: ⚠️ Need Redistribution Solution
- Previously built successfully: ammocoind (242MB), ammocoin-cli (20MB), ammocoin-tx (33MB)
- Removed from git due to GitHub's 100MB file size limit
- Build system ready for regeneration

---

## 💾 Binary Distribution Solutions

### Option 1: Git LFS (Git Large File Storage) - RECOMMENDED

```bash
# Install Git LFS (if not already installed)
git lfs install

# Set up LFS tracking for binary directories
git lfs track "binaries-linux-v*/*"
git lfs track "binaries-windows-v*/*"
git lfs track "binaries-macos-v*/*"
git lfs track "*.exe"
git lfs track "*.dmg"
git lfs track "*.deb"
git lfs track "*.rpm"

# Commit LFS configuration
git add .gitattributes
git commit -m "Add Git LFS tracking for AMMOcoin binaries"

# Build and add binaries
mkdir -p binaries-linux-v1.1.0
cd ammocoin-apps-from-ammocoin
make -j$(nproc) all
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx ../binaries-linux-v1.1.0/

# Add binaries via LFS
git add binaries-linux-v1.1.0/
git commit -m "Add AMMOcoin v1.1.0 Linux binaries via Git LFS"
git push origin main
```

### Option 2: GitHub Releases - PROFESSIONAL

```bash
# Create release with binary attachments
gh release create v1.1.0 \
  --title "AMMOcoin v1.1.0 - Complete Privacy Cryptocurrency" \
  --notes "Complete PIVX transformation with Sapling privacy transactions" \
  binaries-linux-v1.1.0/ammocoind \
  binaries-linux-v1.1.0/ammocoin-cli \
  binaries-linux-v1.1.0/ammocoin-tx
```

### Option 3: Separate Binary Repository

```bash
# Create dedicated binary repository
gh repo create AMMOcoin-binaries --public
git clone https://github.com/everquin/AMMOcoin-binaries.git
cd AMMOcoin-binaries

# Organize by platform and version
mkdir -p v1.1.0/{linux,windows,macos}
# Add binaries and documentation
```

---

## 🔨 Binary Build Instructions

### Prerequisites
```bash
sudo apt-get update
sudo apt-get install -y build-essential libtool autotools-dev autoconf \
    pkg-config libssl-dev libevent-dev bsdmainutils python3 \
    libboost-all-dev libdb4.8-dev libdb4.8++-dev libminiupnpc-dev \
    libzmq3-dev libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev \
    qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev
```

### Build Process
```bash
cd ammocoin-apps-from-ammocoin
./autogen.sh
./configure --with-incompatible-bdb --disable-tests --disable-bench --enable-wallet
make -j$(nproc)

# Results:
# src/ammocoind     - Full node daemon (242MB)
# src/ammocoin-cli  - Command line interface (20MB)
# src/ammocoin-tx   - Transaction utility (33MB)
```

---

## 🚀 Quick Start for Users

### Download Options

1. **Git LFS (Developers)**:
   ```bash
   git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
   cd AMMOcoin-v1.1.0
   git lfs pull  # Download large binaries
   ```

2. **GitHub Releases (Users)**:
   - Go to: https://github.com/everquin/AMMOcoin-v1.1.0/releases
   - Download platform-specific binaries
   - Verify checksums

3. **Direct Build (Advanced)**:
   ```bash
   git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
   cd AMMOcoin-v1.1.0
   ./BUILDME.sh  # Automated build script
   ```

---

## 🔐 Security & Verification

### Binary Verification
```bash
# Check binary signatures
sha256sum binaries-linux-v1.1.0/*
# Verify against published hashes

# Test functionality
./binaries-linux-v1.1.0/ammocoind --version
./binaries-linux-v1.1.0/ammocoin-cli --help
```

### Supported Platforms
- ✅ **Linux x86_64** - Primary target, fully tested
- ✅ **Linux ARM64** - Raspberry Pi, cloud instances
- 🔄 **Windows x64** - Cross-compilation ready
- 🔄 **macOS x64/ARM64** - Native compilation ready

---

## 📦 Distribution Packages

### Future Package Formats
- `.deb` packages for Debian/Ubuntu
- `.rpm` packages for RedHat/CentOS
- `.dmg` installer for macOS
- `.exe` installer for Windows
- Docker images for containerized deployment

---

## 🤝 Contributing

To add new platform binaries:

1. Fork the repository
2. Set up build environment for your platform
3. Build using provided scripts
4. Test binaries thoroughly
5. Submit pull request with binary verification

---

This guide ensures professional distribution of AMMOcoin binaries while maintaining
security, accessibility, and compliance with platform limitations.