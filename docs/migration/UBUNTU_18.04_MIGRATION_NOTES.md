# AMMOcoin v1.1.0 - Ubuntu 18.04.6 LTS Migration Notes

**Critical Information for Ubuntu 18.04 Users**

Ubuntu 18.04.6 LTS (released 2018, standard support ended April 2023) has older dependencies that may cause build issues. This guide covers Ubuntu 18.04-specific considerations.

---

## ⚠️ IMPORTANT: Should You Upgrade Ubuntu First?

**Recommendation:** If possible, upgrade to Ubuntu 20.04 LTS or 22.04 LTS before migrating to AMMOcoin v1.1.0.

### Option A: Upgrade Ubuntu First (Recommended)

```bash
# Backup your v1.0 wallet FIRST!
mkdir -p ~/ammocoin-backups
cp ~/.ammocoin/wallet.dat ~/ammocoin-backups/wallet-v1.0-$(date +%Y%m%d).dat

# Stop v1.0 daemon
ammocoin-cli stop
sleep 30

# Update current system
sudo apt update
sudo apt upgrade -y

# Upgrade to Ubuntu 20.04 LTS
sudo do-release-upgrade

# After upgrade completes and reboot:
# Then follow the standard LINUX_NODE_MIGRATION_GUIDE.md
```

**Benefits of upgrading first:**
- ✅ Newer compilers (GCC 9+ vs GCC 7)
- ✅ Better dependency availability
- ✅ Longer support period (20.04 supported until 2025, 22.04 until 2027)
- ✅ Easier troubleshooting

### Option B: Stay on Ubuntu 18.04 (More Complex)

If you MUST stay on Ubuntu 18.04, follow the modifications below.

---

## Ubuntu 18.04 Specific Build Instructions

### Step 1: Check Your Current System

```bash
# Verify Ubuntu version
lsb_release -a
# Should show: Ubuntu 18.04.6 LTS

# Check GCC version
gcc --version
# Should show: gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0

# Check Boost version
dpkg -l | grep libboost
# Should show: libboost 1.65.1
```

### Step 2: Install Build Dependencies (Ubuntu 18.04)

**IMPORTANT:** Ubuntu 18.04 requires additional steps for some dependencies.

```bash
# Update package lists
sudo apt update
sudo apt upgrade -y

# Install base build tools
sudo apt install -y build-essential autoconf autoconf-archive automake \
    libtool pkg-config git curl wget software-properties-common

# Install available libraries
sudo apt install -y libssl-dev libboost-all-dev libdb-dev libdb++-dev \
    libevent-dev libzmq3-dev libminiupnpc-dev \
    libgmp-dev libsodium-dev python3 python3-pip

# Check if libnatpmp is available (might not be in 18.04 repos)
apt-cache search libnatpmp
```

### Step 3: Install libnatpmp (if missing)

Ubuntu 18.04 might not have libnatpmp-dev in default repositories:

```bash
# Check if it exists
dpkg -l | grep libnatpmp

# If NOT found, build from source:
cd /tmp
git clone https://github.com/miniupnp/libnatpmp.git
cd libnatpmp
make
sudo make install
sudo ldconfig
```

### Step 4: Install Rust (Required for Sapling)

Ubuntu 18.04 doesn't have Rust in default repositories:

```bash
# Install Rust using rustup (recommended method)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y

# Load Rust environment
source $HOME/.cargo/env

# Verify installation
rustc --version
cargo --version

# Should show: rustc 1.70+ and cargo 1.70+
```

### Step 5: Upgrade GCC/G++ (Optional but Recommended)

Ubuntu 18.04 ships with GCC 7.5. While this should work, GCC 8+ is recommended:

```bash
# Add toolchain PPA
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update

# Install GCC 9
sudo apt install -y gcc-9 g++-9

# Set GCC 9 as default
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 90

# Verify
gcc --version  # Should show gcc (Ubuntu 9.x)
g++ --version  # Should show g++ (Ubuntu 9.x)
```

### Step 6: Build AMMOcoin v1.1.0

**IMPORTANT:** On Ubuntu 18.04, the build may take longer and require adjustments.

```bash
# Clone repository
cd ~
git clone https://github.com/everquin/AMMOcoin.git ammocoin-v1.1.0
cd ammocoin-v1.1.0/source

# Generate build scripts
./autogen.sh

# Configure with Ubuntu 18.04 specific flags
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    --with-boost-libdir=/usr/lib/x86_64-linux-gnu \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

# Build (use fewer jobs on older systems)
# For 2 cores:
make -j2

# For 4 cores:
make -j4

# If build fails with memory errors, use single-threaded:
make -j1
```

---

## Common Ubuntu 18.04 Build Issues

### Issue 1: "configure: error: libdb_cxx headers missing"

```bash
# Install Berkeley DB
sudo apt install -y libdb-dev libdb++-dev

# Retry configure with --with-incompatible-bdb flag
./configure --with-incompatible-bdb ...
```

### Issue 2: "error: 'optional' is not a member of 'std'"

This indicates C++17 support issue (rare with GCC 7.5+):

```bash
# Upgrade GCC to version 9 (see Step 5 above)
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install -y gcc-9 g++-9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 90
```

### Issue 3: "libnatpmp not found"

```bash
# Build libnatpmp from source (see Step 3 above)
cd /tmp
git clone https://github.com/miniupnp/libnatpmp.git
cd libnatpmp
make
sudo make install
sudo ldconfig
```

### Issue 4: Rust compilation errors

```bash
# Update Rust to latest stable
rustup update stable
rustup default stable

# Verify
rustc --version  # Should be 1.70+
```

### Issue 5: "virtual memory exhausted" during build

Ubuntu 18.04 VPS often have limited RAM:

```bash
# Increase swap space
sudo fallocate -l 4G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

# Verify
free -h

# Make permanent
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab

# Retry build with single thread
make clean
make -j1
```

### Issue 6: OpenSSL version mismatch

Ubuntu 18.04 has OpenSSL 1.1.0 (might need 1.1.1):

```bash
# Check current version
openssl version
# Shows: OpenSSL 1.1.0g

# This should still work, but if you get OpenSSL errors:
sudo apt install -y libssl1.1 libssl-dev

# Or compile from source if needed (advanced):
# wget https://www.openssl.org/source/openssl-1.1.1w.tar.gz
# tar -xzf openssl-1.1.1w.tar.gz
# cd openssl-1.1.1w
# ./config --prefix=/usr/local/ssl --openssldir=/usr/local/ssl
# make
# sudo make install
```

---

## Post-Build Verification

```bash
# After successful build, verify binaries
cd ~/ammocoin-v1.1.0/source/src

# Check binary dependencies
ldd ./ammocoind | grep "not found"
# Should return nothing (all dependencies found)

# Test version
./ammocoind --version
# Should show: AMMOcoin Core Daemon version v1.1.0.0-xxxxxxx
```

---

## Runtime Considerations for Ubuntu 18.04

### Systemd Service Configuration

Ubuntu 18.04 uses systemd 237 (older version). The service file should work, but verify:

```bash
# After creating service file (from main migration guide)
sudo systemctl daemon-reload
sudo systemctl enable ammocoind

# Check for errors
sudo systemctl status ammocoind

# View logs
journalctl -u ammocoind -f
```

### Firewall Configuration

Ubuntu 18.04 uses ufw by default:

```bash
# Allow AMMOcoin P2P port
sudo ufw allow 37020/tcp

# Allow RPC only from localhost (more secure)
# No firewall rule needed for localhost-only RPC

# Check status
sudo ufw status
```

---

## Masternode Specific Notes (Ubuntu 18.04)

If running a masternode on Ubuntu 18.04:

### 1. Check Network Configuration

```bash
# Verify external IP
curl ifconfig.me

# Verify port is accessible from outside
sudo netstat -tulpn | grep 37020
```

### 2. Masternode Configuration

```bash
# Edit config
nano ~/.ammocoin/ammocoin.conf

# Add masternode settings
cat >> ~/.ammocoin/ammocoin.conf << EOF

# Masternode Configuration (Ubuntu 18.04)
masternode=1
masternodeprivkey=YOUR_MASTERNODE_KEY_HERE
externalip=YOUR_EXTERNAL_IP:37020

# Ubuntu 18.04 may need lower connection limits
maxconnections=64
EOF
```

### 3. Monitor System Resources

Ubuntu 18.04 systems may have lower specs:

```bash
# Install monitoring tools
sudo apt install -y htop

# Monitor during operation
htop

# Check disk space
df -h

# Monitor network
sudo nethogs
```

---

## Performance Tuning for Ubuntu 18.04

### Optimize for Lower-Spec VPS

```bash
# Edit configuration for low-memory systems
cat >> ~/.ammocoin/ammocoin.conf << EOF

# Performance tuning for Ubuntu 18.04 / low-spec VPS
dbcache=512          # Reduce if you have < 2GB RAM
maxmempool=100       # Reduce mempool size
maxconnections=40    # Limit connections
par=1                # Script verification threads (reduce for low CPU)
EOF
```

### Reduce Logging (Save Disk Space)

```bash
# Edit config
nano ~/.ammocoin/ammocoin.conf

# Add
cat >> ~/.ammocoin/ammocoin.conf << EOF

# Reduce logging
debug=0
shrinkdebugfile=1
EOF
```

---

## Backup Strategy for Ubuntu 18.04

Ubuntu 18.04 may not have access to newer backup tools:

```bash
# Install backup tools
sudo apt install -y rsync

# Create backup script
cat > ~/backup-ammocoin.sh << 'EOF'
#!/bin/bash
BACKUP_DIR="$HOME/ammocoin-backups"
DATE=$(date +%Y%m%d-%H%M%S)

mkdir -p "$BACKUP_DIR"

# Stop daemon
ammocoin-cli stop
sleep 30

# Backup wallet
cp ~/.ammocoin/wallet.dat "$BACKUP_DIR/wallet-$DATE.dat"

# Backup config
cp ~/.ammocoin/ammocoin.conf "$BACKUP_DIR/ammocoin-$DATE.conf"

# Restart daemon
ammocoind -daemon

echo "Backup completed: $BACKUP_DIR"
EOF

chmod +x ~/backup-ammocoin.sh

# Run weekly backups
(crontab -l 2>/dev/null; echo "0 2 * * 0 $HOME/backup-ammocoin.sh") | crontab -
```

---

## Testing Checklist for Ubuntu 18.04

After migration, verify everything works:

- [ ] Daemon starts: `ammocoind -daemon`
- [ ] RPC responds: `ammocoin-cli getinfo`
- [ ] Wallet loads: `ammocoin-cli getwalletinfo`
- [ ] Network connects: `ammocoin-cli getconnectioncount` (should be > 0)
- [ ] Blockchain syncs: `ammocoin-cli getblockchaininfo`
- [ ] Signature works: `ammocoin-cli signmessage "ADDRESS" "test"`
- [ ] Service works: `sudo systemctl status ammocoind`
- [ ] Auto-start works: `sudo reboot` then check daemon running

---

## When to Consider Upgrading Ubuntu

You should upgrade from Ubuntu 18.04 if:

1. **Build fails repeatedly** despite following this guide
2. **Dependencies are incompatible** and can't be resolved
3. **You want long-term support** (18.04 ESM ends 2028, but limited)
4. **Performance is poor** with v1.1.0
5. **You plan to run this node for years** (better to upgrade now)

### Safe Upgrade Path

```bash
# Backup everything
cp -r ~/.ammocoin ~/ammocoin-backup-pre-upgrade
cp ~/ammocoin-backups/* /external/storage/

# Upgrade to 20.04
sudo do-release-upgrade

# After upgrade, rebuild AMMOcoin v1.1.0
# (Follow standard LINUX_NODE_MIGRATION_GUIDE.md)
```

---

## Support for Ubuntu 18.04 Users

If you encounter Ubuntu 18.04-specific issues:

1. **Check logs:**
   ```bash
   tail -100 ~/.ammocoin/debug.log
   ```

2. **Check system logs:**
   ```bash
   journalctl -xe
   ```

3. **Report issues with full details:**
   - Ubuntu version: `lsb_release -a`
   - GCC version: `gcc --version`
   - Build error output
   - System specs: `cat /proc/cpuinfo | grep "model name" | head -1`
   - Memory: `free -h`

4. **Contact support:**
   - Email: support@ammocoin.org
   - Subject: "Ubuntu 18.04 Migration Issue - v1.1.0"

---

## Summary: Ubuntu 18.04 Migration Path

### Recommended Path (Easiest)

1. ✅ Backup v1.0 wallet
2. ✅ Upgrade Ubuntu to 20.04 or 22.04
3. ✅ Follow standard LINUX_NODE_MIGRATION_GUIDE.md

### Alternative Path (More Complex)

1. ✅ Backup v1.0 wallet
2. ✅ Install additional dependencies (libnatpmp, Rust, possibly GCC 9)
3. ✅ Build with Ubuntu 18.04-specific configure flags
4. ✅ Follow standard migration process for wallet/claim
5. ✅ Apply performance tuning for older system

**Bottom Line:** Ubuntu 18.04 CAN run AMMOcoin v1.1.0, but upgrading Ubuntu first is highly recommended for easier setup and better long-term support.

---

*Last Updated: December 22, 2025*
*Ubuntu 18.04.6 LTS - AMMOcoin v1.1.0 Compatibility Notes*
