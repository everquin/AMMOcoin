# AMMOcoin v1.1.0 - Linux Build Instructions

**Date:** December 30, 2025
**Target Platform:** Linux x86_64 (Ubuntu 18.04+ / Debian 10+)
**Build Environment:** Vultr VPS or any Linux build machine
**Authority:** V1.1.0_GENESIS_BLOCK_AUTHORITY.md

---

## CRITICAL: Genesis Block Verification

**BEFORE distributing ANY Linux binaries, verify they contain the correct genesis:**

```bash
strings ammocoind | grep "00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434"
```

**MUST return matches!** If not, DO NOT distribute - rebuild from correct source!

---

## Prerequisites

### 1. Update System
```bash
sudo apt-get update
sudo apt-get upgrade -y
```

### 2. Install Build Dependencies
```bash
sudo apt-get install -y \
    build-essential \
    libtool \
    autotools-dev \
    automake \
    pkg-config \
    libssl-dev \
    libevent-dev \
    bsdmainutils \
    python3 \
    libboost-all-dev \
    libminiupnpc-dev \
    libzmq3-dev \
    libgmp-dev \
    git \
    curl \
    cargo \
    rustc
```

### 3. Install Berkeley DB 4.8 (Required for wallet)
```bash
cd /tmp
wget https://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz
tar -xzf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local
make -j$(nproc)
sudo make install
```

### 4. Verify Rust Toolchain
```bash
rustc --version  # Should be 1.80.0 or newer
cargo --version

# If Rust is not installed or too old:
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source $HOME/.cargo/env
rustup install 1.92.0
rustup default 1.92.0
```

---

## Build Process

### 1. Clone Repository (if not already cloned)
```bash
cd /tmp
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git
cd AMMOcoin-v1.1.0
```

### 2. Pull Latest Code
```bash
git pull origin main
git log -1 --oneline  # Verify you have latest commit
```

### 3. Navigate to Build Directory
```bash
cd ammocoin-apps-from-ammocoin
```

### 4. Clean Previous Build (if any)
```bash
make distclean 2>/dev/null || true
rm -rf autom4te.cache
```

### 5. Generate Configure Script
```bash
./autogen.sh
```

**Expected output:**
```
libtoolize: putting auxiliary files in AC_CONFIG_AUX_DIR, 'build-aux'.
...
configure.ac:XX: installing 'build-aux/install-sh'
```

### 6. Configure Build
```bash
./configure \
    --prefix=/usr/local \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --with-incompatible-bdb \
    LDFLAGS="-L/usr/local/lib" \
    CPPFLAGS="-I/usr/local/include"
```

**Important flags:**
- `--disable-tests`: Skip test suite (faster build)
- `--disable-bench`: Skip benchmarks
- `--without-gui`: Build daemon/CLI only (no Qt)
- `--with-incompatible-bdb`: Allow BDB 4.8

**Expected output should end with:**
```
Options used to compile and link:
  with wallet   = yes
  with gui / qt = no
  ...
```

### 7. Build Binaries
```bash
make -j$(nproc)
```

**Build time:** 10-30 minutes depending on CPU
**Memory required:** Minimum 2GB RAM (4GB+ recommended)

**Expected output:**
```
make[1]: Leaving directory '.../ammocoin-apps-from-ammocoin'
```

### 8. Verify Build Success
```bash
ls -lh src/ammocoind src/ammocoin-cli src/ammocoin-tx
```

**Expected output:**
```
-rwxr-xr-x 1 user user 15M Dec 30 08:00 src/ammocoind
-rwxr-xr-x 1 user user 2.1M Dec 30 08:00 src/ammocoin-cli
-rwxr-xr-x 1 user user 1.9M Dec 30 08:00 src/ammocoin-tx
```

---

## CRITICAL: Genesis Verification

### 1. Verify Genesis in Binary (Static Check)
```bash
strings src/ammocoind | grep "00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434"
```

**MUST return matches!** Example:
```
00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434
assert(consensus.hashGenesisBlock == uint256S("0x00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434"));
```

### 2. Verify Genesis at Runtime
```bash
# Create test data directory
mkdir -p /tmp/ammocoin-genesis-test
cat > /tmp/ammocoin-genesis-test/ammocoin.conf <<EOF
rpcuser=test
rpcpassword=test123
rpcport=8332
server=1
daemon=1
EOF

# Start daemon
./src/ammocoind -datadir=/tmp/ammocoin-genesis-test -daemon

# Wait for startup
sleep 10

# Get genesis block hash
GENESIS_HASH=$(./src/ammocoin-cli -datadir=/tmp/ammocoin-genesis-test getblockhash 0)

# Stop daemon
./src/ammocoin-cli -datadir=/tmp/ammocoin-genesis-test stop
sleep 5

# Verify
if [ "$GENESIS_HASH" = "00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434" ]; then
    echo "✅ SUCCESS: Genesis hash is correct!"
else
    echo "❌ FAIL: Genesis hash is $GENESIS_HASH"
    echo "Expected: 00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434"
    exit 1
fi

# Cleanup
rm -rf /tmp/ammocoin-genesis-test
```

**If verification fails, DO NOT PROCEED!** Rebuild from correct source.

---

## Package Binaries for Distribution

### 1. Create Release Directory
```bash
mkdir -p AMMOcoin-v1.1.0-Linux-x86_64
```

### 2. Copy Binaries
```bash
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx AMMOcoin-v1.1.0-Linux-x86_64/
```

### 3. Add Documentation
```bash
cp ../V1.1.0_GENESIS_BLOCK_AUTHORITY.md AMMOcoin-v1.1.0-Linux-x86_64/README.md
cp ../COPYING AMMOcoin-v1.1.0-Linux-x86_64/ 2>/dev/null || echo "No COPYING file"
```

### 4. Strip Debug Symbols (Reduce Size)
```bash
strip AMMOcoin-v1.1.0-Linux-x86_64/ammocoind
strip AMMOcoin-v1.1.0-Linux-x86_64/ammocoin-cli
strip AMMOcoin-v1.1.0-Linux-x86_64/ammocoin-tx
```

### 5. Create Compressed Archives
```bash
# Create tar.gz
tar -czf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz AMMOcoin-v1.1.0-Linux-x86_64/

# Create zip
zip -r AMMOcoin-v1.1.0-Linux-x86_64.zip AMMOcoin-v1.1.0-Linux-x86_64/
```

### 6. Generate SHA256 Checksums
```bash
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz > CHECKSUMS-Linux.txt
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.zip >> CHECKSUMS-Linux.txt
```

### 7. Verify Checksums
```bash
cat CHECKSUMS-Linux.txt
```

**Example output:**
```
abc123def456... AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
def789ghi012... AMMOcoin-v1.1.0-Linux-x86_64.zip
```

---

## Upload to GitHub Release

### 1. Move Files to Releases Directory
```bash
# On your local machine (not build server)
# Download the files from build server first

# Then move to releases directory
cd /path/to/AMMOcoin-v1.1.0
mv AMMOcoin-v1.1.0-Linux-x86_64.tar.gz releases/
mv AMMOcoin-v1.1.0-Linux-x86_64.zip releases/
mv CHECKSUMS-Linux.txt releases/
```

### 2. Commit to Repository
```bash
git add releases/
git commit -m "Add verified Linux x86_64 binaries for v1.1.0

Built with correct genesis: 00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434
Genesis verification: PASSED (static and runtime checks)

Platform: Linux x86_64
Build date: $(date -u +%Y-%m-%d)
Source commit: $(git rev-parse --short HEAD)

Files:
- AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
- AMMOcoin-v1.1.0-Linux-x86_64.zip
- CHECKSUMS-Linux.txt"

git push origin main
```

### 3. Create GitHub Release (or update existing)
```bash
# Using GitHub CLI (gh)
gh release create v1.1.0-genesis-final \
    --title "AMMOcoin v1.1.0 - Official Release" \
    --notes "See V1.1.0_GENESIS_BLOCK_AUTHORITY.md for genesis block details" \
    releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz \
    releases/AMMOcoin-v1.1.0-Linux-x86_64.zip \
    releases/CHECKSUMS-Linux.txt
```

---

## Troubleshooting

### Build Error: "Cannot find -lboost_system"
```bash
sudo apt-get install libboost-all-dev
```

### Build Error: "db_cxx.h: No such file"
```bash
# Reinstall Berkeley DB 4.8 (see Prerequisites section)
# Or use system DB (less recommended):
./configure --with-incompatible-bdb
```

### Rust Compilation Errors
```bash
# Update Rust toolchain
rustup update
rustup install 1.92.0
rustup default 1.92.0

# Clean and rebuild
make distclean
./autogen.sh
./configure [your flags]
make -j$(nproc)
```

### Low Memory Error During Build
```bash
# Reduce parallel jobs
make -j2  # Use 2 cores instead of all

# Or add swap
sudo fallocate -l 4G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
```

---

## Final Checklist

Before distribution, verify:

- [ ] Build completed without errors
- [ ] `strings ammocoind | grep "00000f14..."` returns matches
- [ ] Runtime test: `ammocoin-cli getblockhash 0` returns `00000f14...`
- [ ] Binaries are stripped (reduced file size)
- [ ] tar.gz and zip archives created
- [ ] SHA256 checksums generated
- [ ] All files copied to releases/ directory
- [ ] Committed to git with verification message
- [ ] GitHub release created/updated

---

## Support

For build issues:
- Check V1.1.0_GENESIS_BLOCK_AUTHORITY.md for genesis parameters
- Review AUDIT_RESULTS_AND_NEXT_STEPS.md for project status
- Ensure you're building from commit tagged `v1.1.0-genesis-final`

**Genesis Hash (MUST match):**
`00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434`

---

**Last Updated:** December 30, 2025
**Status:** Ready for Production Build
