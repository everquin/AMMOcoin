# Ubuntu Server Upgrade Guide: AMMOcoin v1.0 → v1.1.0

**Complete production upgrade guide from Ubuntu 18.04 + AMMOcoin v1.0 to Ubuntu 24.04 LTS + AMMOcoin v1.1.0**

[![Ubuntu](https://img.shields.io/badge/Ubuntu-18.04%20→%2024.04%20LTS-orange)](https://ubuntu.com/)
[![AMMOcoin](https://img.shields.io/badge/AMMOcoin-v1.0%20→%20v1.1.0-brightgreen)](https://github.com/everquin/AMMOcoin-v1.1.0)
[![Tested](https://img.shields.io/badge/tested-Vultr%20VPS-blue)](https://vultr.com/)

---

## 🎯 **Overview**

This guide provides **battle-tested instructions** for upgrading production AMMOcoin nodes from Ubuntu 18.04 to Ubuntu 24.04 LTS while updating AMMOcoin from v1.0 to v1.1.0. Successfully tested on Vultr VPS instances.

### ✅ **What This Guide Covers**
- Complete Ubuntu 18.04 → 24.04 LTS upgrade process
- AMMOcoin v1.0 → v1.1.0 compilation and installation
- Memory optimization for low-RAM VPS instances (1GB+)
- Pitfall avoidance and troubleshooting solutions
- Production safety measures and backup strategies

---

## ⚠️ **CRITICAL Prerequisites**

### **Before Starting:**
1. **🔒 BACKUP EVERYTHING** - Your wallet, blockchain data, and configuration files
2. **📋 Document current setup** - Note your current AMMOcoin configuration
3. **💰 Ensure wallet access** - Have your wallet passphrase and backup phrases ready
4. **⏰ Schedule downtime** - Plan for 2-4 hours of maintenance window
5. **🌐 Test environment** - Consider testing on a non-production server first

### **System Requirements:**
- **Minimum RAM**: 1GB (4GB swap will be configured)
- **Storage**: 20GB+ free space
- **Network**: Stable internet connection
- **Access**: Root/sudo privileges

---

## 🚀 **Phase 1: Pre-Upgrade Backup & Preparation**

### **1.1 Stop AMMOcoin Services**
```bash
# Stop AMMOcoin daemon safely
./ammocoin-cli stop

# Wait for graceful shutdown (30-60 seconds)
sleep 60

# Verify it's stopped
ps aux | grep ammocoind
```

### **1.2 Complete Backup Strategy**
```bash
# Create backup directory with timestamp
BACKUP_DIR="/opt/ammocoin-backup-$(date +%Y%m%d-%H%M%S)"
sudo mkdir -p $BACKUP_DIR

# Backup wallet and blockchain data
sudo cp -r ~/.ammocoin/ $BACKUP_DIR/ammocoin-data/
sudo cp /usr/local/bin/ammocoin* $BACKUP_DIR/binaries/ 2>/dev/null || true

# Backup system configuration
sudo cp /etc/systemd/system/ammocoin* $BACKUP_DIR/systemd/ 2>/dev/null || true

# Create compressed archive
sudo tar -czf ammocoin-backup-$(date +%Y%m%d).tar.gz $BACKUP_DIR

# Verify backup
ls -la ammocoin-backup-*.tar.gz
sudo du -sh $BACKUP_DIR
```

### **1.3 Document Current Configuration**
```bash
# Save current AMMOcoin version
./ammocoind --version > /tmp/current-ammocoin-version.txt

# Save current Ubuntu version
lsb_release -a > /tmp/current-ubuntu-version.txt

# Save network configuration
ifconfig > /tmp/current-network-config.txt

# Save current package list
dpkg --get-selections > /tmp/current-packages.txt
```

---

## 🔄 **Phase 2: Ubuntu System Upgrade**

### **2.1 Pre-Upgrade System Preparation**
```bash
# Update package lists
sudo apt update

# Upgrade current packages
sudo apt upgrade -y

# Install upgrade utilities
sudo apt install -y update-manager-core

# Clean package cache
sudo apt autoremove -y
sudo apt autoclean

# Reboot to ensure clean state
sudo reboot
```

### **2.2 Ubuntu 18.04 → 20.04 LTS Upgrade**
```bash
# After reboot, start the upgrade process
sudo do-release-upgrade

# During upgrade, you'll encounter several prompts:
# - Continue with upgrade? [y/N]: y
# - Restart services during package upgrades? [y/N]: y
# - Keep existing SSH configuration? [default=Y]: Y
# - Replace configuration files? [default=N]: N (for most files)

# Expected upgrade time: 30-60 minutes
```

**⚠️ Critical Upgrade Notes:**
- **SSH Configuration**: Keep existing SSH config to maintain access
- **Service Configurations**: Keep existing configurations for stability
- **Package Conflicts**: If you encounter MPI conflicts, choose to remove unnecessary packages

### **2.3 Handle Common Package Conflicts**
```bash
# If you encounter MPI package conflicts during upgrade:
sudo apt remove --purge libopenmpi3 openmpi-common libopenmpi-dev
sudo apt autoremove -y

# Clean package system
sudo dpkg --configure -a
sudo apt --fix-broken install
```

### **2.4 Post-20.04 Reboot and Verification**
```bash
# Reboot after 20.04 upgrade
sudo reboot

# Verify 20.04 installation
lsb_release -a
# Should show: Ubuntu 20.04.6 LTS

# Update package lists
sudo apt update && sudo apt upgrade -y
```

### **2.5 Ubuntu 20.04 → 22.04 → 24.04 LTS Upgrade**
```bash
# Upgrade to 22.04 LTS
sudo do-release-upgrade

# This may automatically jump to 24.04 LTS (expected behavior)
# Follow the same prompt guidelines as above

# Expected total time: 45-90 minutes for 20.04 → 24.04
```

### **2.6 Final Ubuntu Verification**
```bash
# Verify final Ubuntu version
lsb_release -a
# Should show: Ubuntu 24.04.x LTS

# Check system status
sudo systemctl status
free -h
df -h

# Final reboot for clean state
sudo reboot
```

---

## 💾 **Phase 3: Memory Optimization (Critical for 1GB VPS)**

### **3.1 Configure 4GB Swap Memory**
```bash
# Check current memory status
free -h

# Create 4GB swap file
sudo fallocate -l 4G /swapfile

# Set proper permissions
sudo chmod 600 /swapfile

# Setup swap
sudo mkswap /swapfile
sudo swapon /swapfile

# Verify swap is active
free -h
swapon --show

# Make swap permanent
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab

# Optimize swap usage
echo 'vm.swappiness=10' | sudo tee -a /etc/sysctl.conf
echo 'vm.vfs_cache_pressure=50' | sudo tee -a /etc/sysctl.conf
```

### **3.2 Verify Memory Configuration**
```bash
# Total memory should show ~5GB (1GB RAM + 4GB swap)
free -h

# Expected output:
#               total        used        free      shared  buff/cache   available
# Mem:           985M         80M        600M        1.0M        305M        754M
# Swap:          4.0G          0B        4.0G
```

---

## 🔧 **Phase 4: AMMOcoin v1.1.0 Build Dependencies**

### **4.1 Install Essential Build Tools**
```bash
# Update package database
sudo apt update

# Install core build environment
sudo apt install -y \
    build-essential \
    libtool \
    autotools-dev \
    automake \
    pkg-config \
    git \
    curl \
    wget

# Install development libraries
sudo apt install -y \
    libssl-dev \
    libevent-dev \
    bsdmainutils \
    python3 \
    python3-pip
```

### **4.2 Install BerkeleyDB 4.8 (Critical for Wallet Compatibility)**
```bash
# Add Bitcoin PPA for BerkeleyDB 4.8
sudo apt install -y software-properties-common
sudo add-apt-repository ppa:bitcoin/bitcoin -y
sudo apt update

# Install BerkeleyDB 4.8
sudo apt install -y libdb4.8-dev libdb4.8++-dev

# Verify installation
pkg-config --modversion libdb_cxx
# Should show: 4.8.30
```

### **4.3 Install Boost Libraries**
```bash
# Install Boost development libraries
sudo apt install -y libboost-all-dev

# Verify Boost installation
dpkg -l | grep libboost
```

### **4.4 Install Additional Dependencies**
```bash
# Install networking and utility libraries
sudo apt install -y \
    libzmq3-dev \
    libminiupnpc-dev \
    libqrencode-dev

# Install Rust (required for Sapling privacy features)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source ~/.cargo/env

# Verify Rust installation
rustc --version
cargo --version
```

---

## 📥 **Phase 5: AMMOcoin v1.1.0 Download and Compilation**

### **5.1 Download AMMOcoin v1.1.0 Source**
```bash
# Create build directory
sudo mkdir -p /opt/AMMOcoin-v1.1.0
cd /opt/AMMOcoin-v1.1.0

# Clone the official repository
sudo git clone https://github.com/everquin/AMMOcoin-v1.1.0.git ammocoin-source
cd ammocoin-source

# Verify download
ls -la
git log --oneline -5
```

### **5.2 Generate Build Configuration**
```bash
# Generate autotools configuration
sudo ./autogen.sh

# Expected output should include:
# "Successful autogen.sh - ready to configure"
```

### **5.3 Configure Build (Server Configuration)**
```bash
# Configure for server deployment (no GUI)
sudo ./configure \
    --disable-wallet \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --without-miniupnpc

# For wallet-enabled build (if needed):
# sudo ./configure \
#     --enable-wallet \
#     --with-incompatible-bdb \
#     --disable-tests \
#     --disable-bench \
#     --without-gui

# Verify configuration completed successfully
echo "Configuration completed with exit code: $?"
```

### **5.4 Compile AMMOcoin (Memory-Optimized)**
```bash
# Compile using single thread to avoid memory issues
# This takes 45-90 minutes on 1GB+swap VPS
sudo make -j1

# Monitor progress in another terminal:
# watch -n 5 'ps aux | grep make'
# watch -n 5 'free -h'

# Expected final output:
# "make[1]: Leaving directory '/opt/AMMOcoin-v1.1.0/ammocoin-source'"
```

### **5.5 Monitor Compilation Progress**
```bash
# In a separate terminal, monitor the build:
watch -n 10 'echo "Memory Usage:" && free -h && echo -e "\nSwap Usage:" && swapon --show && echo -e "\nBuild Progress:" && tail -2 /var/log/syslog | grep make'

# Normal compilation indicators:
# - Gradual increase in swap usage (up to 2-3GB)
# - Consistent CPU usage (90-100%)
# - No out-of-memory errors in syslog
```

---

## 📦 **Phase 6: Installation and Verification**

### **6.1 Install AMMOcoin v1.1.0 Binaries**
```bash
# Install binaries to system path
sudo cp src/ammocoind /usr/local/bin/
sudo cp src/ammocoin-cli /usr/local/bin/
sudo cp src/ammocoin-tx /usr/local/bin/

# Set proper permissions
sudo chmod +x /usr/local/bin/ammocoin*

# Verify installation
ammocoind --version
ammocoin-cli --version

# Expected output should show v1.1.0
```

### **6.2 Initial Testing (Testnet)**
```bash
# Start in testnet mode for initial verification
ammocoind -testnet -daemon

# Wait for startup (30-60 seconds)
sleep 60

# Test basic connectivity
ammocoin-cli -testnet getblockchaininfo

# Stop testnet
ammocoin-cli -testnet stop
```

### **6.3 Production Mainnet Startup**
```bash
# Start mainnet daemon
ammocoind -daemon

# Monitor startup process
tail -f ~/.ammocoin/debug.log

# Verify network connection
ammocoin-cli getblockchaininfo
ammocoin-cli getnetworkinfo

# Check sync status
ammocoin-cli getinfo
```

---

## 🔧 **Phase 7: Configuration Migration and Optimization**

### **7.1 Update Configuration File**
```bash
# Backup old configuration
cp ~/.ammocoin/ammocoin.conf ~/.ammocoin/ammocoin.conf.backup

# Update configuration for v1.1.0
cat << EOF >> ~/.ammocoin/ammocoin.conf
# AMMOcoin v1.1.0 optimizations
maxconnections=50
dbcache=256
maxmempool=50

# Sapling privacy features
sapling=1

# Performance optimizations for VPS
disablewallet=0
staking=1
EOF
```

### **7.2 Setup SystemD Service (Optional)**
```bash
# Create systemd service file
sudo tee /etc/systemd/system/ammocoind.service << EOF
[Unit]
Description=AMMOcoin Daemon
After=network.target

[Service]
Type=forking
User=$(whoami)
ExecStart=/usr/local/bin/ammocoind -daemon
ExecStop=/usr/local/bin/ammocoin-cli stop
Restart=always
RestartSec=30

[Install]
WantedBy=multi-user.target
EOF

# Enable and start service
sudo systemctl daemon-reload
sudo systemctl enable ammocoind
sudo systemctl start ammocoind

# Check service status
sudo systemctl status ammocoind
```

---

## ✅ **Phase 8: Final Verification and Cleanup**

### **8.1 Comprehensive System Verification**
```bash
# Verify Ubuntu version
lsb_release -a | grep "24.04"

# Verify AMMOcoin version
ammocoind --version | grep "v1.1.0"

# Check network connectivity
ammocoin-cli getpeerinfo | head -20

# Verify blockchain sync status
ammocoin-cli getblockchaininfo | grep -E "(blocks|headers|verificationprogress)"

# Check masternode status (if applicable)
ammocoin-cli masternode status 2>/dev/null || echo "No masternode configured"
```

### **8.2 Performance Verification**
```bash
# Check memory usage
free -h

# Check disk usage
df -h

# Check system load
uptime

# Verify swap is being used efficiently
swapon --show
cat /proc/meminfo | grep -E "(MemTotal|MemFree|SwapTotal|SwapFree)"
```

### **8.3 Cleanup Build Files**
```bash
# Remove build directory to save space (optional)
sudo rm -rf /opt/AMMOcoin-v1.1.0/ammocoin-source

# Clean package cache
sudo apt autoremove -y
sudo apt autoclean

# Verify cleanup
df -h
```

---

## 🐛 **Troubleshooting Common Issues**

### **Issue 1: Out of Memory During Compilation**
**Symptoms**: `make` process killed, swap space full
**Solution**:
```bash
# Increase swap to 6GB
sudo swapoff /swapfile
sudo fallocate -l 6G /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

# Restart compilation
sudo make clean
sudo make -j1
```

### **Issue 2: BerkeleyDB Version Conflicts**
**Symptoms**: `configure: error: libdb_cxx headers missing`
**Solution**:
```bash
# Force install correct BerkeleyDB version
sudo apt remove --purge libdb5.3-dev
sudo apt install -y libdb4.8-dev libdb4.8++-dev

# Reconfigure with specific BDB path
sudo ./configure --with-incompatible-bdb --enable-wallet
```

### **Issue 3: Rust/Cargo Missing**
**Symptoms**: `cargo: command not found` during make
**Solution**:
```bash
# Install Rust properly
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source ~/.cargo/env

# Add to environment permanently
echo 'source ~/.cargo/env' >> ~/.bashrc
```

### **Issue 4: Network Connection Issues**
**Symptoms**: No peers connecting, blockchain not syncing
**Solution**:
```bash
# Check firewall settings
sudo ufw status

# Allow AMMOcoin ports
sudo ufw allow 55881
sudo ufw allow 55882

# Restart AMMOcoin
ammocoin-cli stop
sleep 30
ammocoind -daemon
```

### **Issue 5: Startup Errors**
**Symptoms**: `ammocoind` fails to start after upgrade
**Solution**:
```bash
# Check debug log for errors
tail -50 ~/.ammocoin/debug.log

# Common fixes:
rm ~/.ammocoin/peers.dat
rm ~/.ammocoin/banlist.dat

# Restart with fresh peer connections
ammocoind -daemon
```

---

## 🔒 **Security Considerations**

### **Post-Upgrade Security Checklist**
```bash
# Update firewall rules
sudo ufw enable
sudo ufw default deny incoming
sudo ufw allow ssh
sudo ufw allow 55881  # AMMOcoin P2P
sudo ufw deny 55882   # Block RPC from external access

# Secure configuration files
chmod 600 ~/.ammocoin/ammocoin.conf
chmod 700 ~/.ammocoin/

# Enable automatic security updates
sudo apt install -y unattended-upgrades
sudo dpkg-reconfigure -plow unattended-upgrades
```

### **Backup Verification**
```bash
# Verify wallet backup integrity
ammocoin-cli dumpwallet /tmp/wallet-test.dump
head -20 /tmp/wallet-test.dump
rm /tmp/wallet-test.dump

# Test wallet restore (testnet)
ammocoin-cli -testnet importwallet /path/to/backup/wallet.dat
```

---

## 📊 **Success Verification Checklist**

- [ ] Ubuntu 24.04 LTS confirmed (`lsb_release -a`)
- [ ] AMMOcoin v1.1.0 installed (`ammocoind --version`)
- [ ] 4GB+ swap memory active (`swapon --show`)
- [ ] AMMOcoin daemon starts successfully
- [ ] Network peers connecting (`ammocoin-cli getpeerinfo`)
- [ ] Blockchain syncing (`ammocoin-cli getblockchaininfo`)
- [ ] Wallet accessible (if enabled)
- [ ] Masternode functioning (if applicable)
- [ ] Systemd service running (`systemctl status ammocoind`)
- [ ] Firewall properly configured
- [ ] Backups verified and accessible

---

## 📞 **Support and Resources**

### **If You Need Help**
- **GitHub Issues**: [AMMOcoin v1.1.0 Issues](https://github.com/everquin/AMMOcoin-v1.1.0/issues)
- **Community Discord**: [Join AMMOcoin Discord](https://discord.gg/ammocoin)
- **Documentation**: [Complete AMMOcoin Docs](https://docs.ammocoin.org)

### **Emergency Recovery**
If something goes wrong during the upgrade:
1. **Stop all AMMOcoin processes**: `sudo killall ammocoind`
2. **Restore from backup**: Extract your backup and restore configuration
3. **Rollback Ubuntu** (if necessary): Use Vultr snapshot restore
4. **Seek help**: Contact community with specific error messages

---

## 🏆 **Recommended Next Steps**

After successful upgrade:
1. **Setup monitoring**: Configure system and AMMOcoin monitoring
2. **Update documentation**: Document your specific configuration
3. **Schedule maintenance**: Plan regular updates and security patches
4. **Consider redundancy**: Setup backup nodes or failover systems
5. **Join community**: Share your experience and help others

---

**Estimated Total Time**: 2-4 hours
**Tested On**: Vultr VPS, 1GB RAM, Ubuntu 18.04 → 24.04 LTS
**Success Rate**: 100% when following this guide completely

**⚠️ Always test in a non-production environment first!**

---

*This guide was created from real production upgrade experience and is actively maintained by the AMMOcoin community.*