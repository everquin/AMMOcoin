# AMMOcoin v1.1.0 - Build from Source on Raspberry Pi

**Platform:** Raspberry Pi 3B+/4/5 (ARM64)
**OS:** Raspberry Pi OS (64-bit), Ubuntu 22.04 ARM
**Build Time:** 60-120 minutes
**Difficulty:** Intermediate

---

## Prerequisites

### Minimum Requirements

- **Raspberry Pi:** 3B+ or newer (4GB RAM recommended)
- **SD Card:** 32GB minimum (64GB recommended)
- **OS:** Raspberry Pi OS 64-bit or Ubuntu 22.04 ARM64
- **Power:** Official power supply (unstable power can corrupt builds)
- **Cooling:** Heatsink or fan recommended (build generates heat)

### Update Your System

```bash
sudo apt update
sudo apt upgrade -y
sudo reboot
```

After reboot, verify you're running 64-bit:
```bash
uname -m
# Should output: aarch64
```

If it says `armv7l`, you're running 32-bit. Please install 64-bit OS for best results.

---

## Install Build Dependencies

```bash
# Install base build tools
sudo apt install -y build-essential autoconf autoconf-archive automake \
    libtool pkg-config git curl wget

# Install required libraries
sudo apt install -y libssl-dev libboost-all-dev libdb-dev libdb++-dev \
    libevent-dev libzmq3-dev libminiupnpc-dev libnatpmp-dev \
    libgmp-dev libsodium-dev python3 python3-pip

# Install Rust (required for Sapling support)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env

# Verify installation
rustc --version
cargo --version
```

---

## Optimize for Raspberry Pi

### Increase Swap Space (Important!)

Compilation requires more RAM than most Pi models have:

```bash
# Stop swap
sudo dphys-swapfile swapoff

# Increase swap to 2GB
sudo sed -i 's/CONF_SWAPSIZE=100/CONF_SWAPSIZE=2048/' /etc/dphys-swapfile

# Restart swap
sudo dphys-swapfile setup
sudo dphys-swapfile swapon

# Verify
free -h
```

### Prevent Thermal Throttling

```bash
# Monitor temperature during build
watch -n 5 'vcgencmd measure_temp'
```

Keep temperature below 80°C. If it exceeds:
- Add heatsink/fan
- Reduce CPU usage: `make -j1` instead of `make -j4`

---

## Download and Build AMMOcoin v1.1.0

### Step 1: Clone the Repository

```bash
cd ~
git clone https://github.com/ammocoin/ammocoin.git ammocoin-v1.1.0
cd ammocoin-v1.1.0
```

**Or if you have a source archive:**

```bash
cd ~
tar -xzf ammocoin-v1.1.0-source.tar.gz
cd ammocoin-v1.1.0
```

### Step 2: Build AMMOcoin

**IMPORTANT for Raspberry Pi:** Use fewer parallel jobs to avoid memory issues:

```bash
# Generate build scripts
./autogen.sh

# Configure the build
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    --with-boost \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"

# Compile (use -j2 for Pi, -j1 if you have issues)
# This will take 60-120 minutes on Raspberry Pi
make -j2
```

**Build Time Estimates:**
- Raspberry Pi 5 (8GB): 40-60 minutes
- Raspberry Pi 4 (4GB): 60-90 minutes
- Raspberry Pi 3B+: 90-120 minutes

**If the build fails or Pi freezes:**
```bash
# Reboot
sudo reboot

# After reboot, resume with single-threaded build
cd ~/ammocoin-v1.1.0
make clean
make -j1  # Slower but more stable
```

### Step 3: Install Binaries

```bash
# Create local bin directory
mkdir -p ~/ammocoin-bin
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx ~/ammocoin-bin/

# Add to PATH
echo 'export PATH="$HOME/ammocoin-bin:$PATH"' >> ~/.bashrc
source ~/.bashrc

# Verify
ammocoind --version
```

---

## Migration from v1.0 to v1.1.0

### IMPORTANT: Backup First!

```bash
# Backup your v1.0 wallet
mkdir -p ~/backups
cp ~/.ammocoin/wallet.dat ~/backups/wallet-v1.0-$(date +%Y%m%d).dat

# Backup configuration
cp ~/.ammocoin/ammocoin.conf ~/backups/ammocoin-v1.0.conf 2>/dev/null || true
cp ~/.ammocoin/masternode.conf ~/backups/masternode-v1.0.conf 2>/dev/null || true

# Verify backup
ls -lh ~/backups/
```

**Copy backup to external storage:**
```bash
# If you have USB drive mounted at /media/pi/USB
cp ~/backups/* /media/pi/USB/ammocoin-backups/
```

---

### Migration Process

#### Step 1: Stop v1.0 Daemon (if running)

```bash
# Stop v1.0
ammocoin-cli stop 2>/dev/null || true

# Wait for shutdown
sleep 10

# Verify stopped
ps aux | grep ammocoind
```

#### Step 2: Prepare v1.1.0 Data Directory

```bash
# Rename old directory
mv ~/.ammocoin ~/.ammocoin-v1.0

# Create new directory
mkdir -p ~/.ammocoin

# Copy wallet
cp ~/.ammocoin-v1.0/wallet.dat ~/.ammocoin/
```

#### Step 3: Create Configuration File

```bash
# Generate random RPC password
RPCPASS=$(openssl rand -base64 32)

# Create config
cat > ~/.ammocoin/ammocoin.conf << EOF
# AMMOcoin v1.1.0 Configuration

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=$RPCPASS
rpcallowip=127.0.0.1

# Network
listen=1
server=1
daemon=1

# Raspberry Pi Optimizations
dbcache=512        # Limit memory usage (MB)
maxmempool=100     # Limit mempool size (MB)
maxconnections=40  # Limit connections

# Add seed nodes (will be provided at launch)
# addnode=seed1.ammocoin.org
# addnode=seed2.ammocoin.org
# addnode=seed3.ammocoin.org
EOF
```

#### Step 4: Start AMMOcoin v1.1.0

```bash
# Start the daemon
ammocoind -daemon

# Wait for startup (Pi is slower)
sleep 15

# Check status
ammocoin-cli getinfo
```

#### Step 5: Check Your v1.0 Balance

```bash
# View balance
ammocoin-cli getbalance

# List all addresses with balances
ammocoin-cli listaddressgroupings
```

**Note:** This shows your v1.0 balance. You need to claim it on the v1.1.0 network.

#### Step 6: Generate v1.1.0 Address

```bash
# Create new receiving address
NEW_ADDRESS=$(ammocoin-cli getnewaddress "Migrated Wallet")
echo "Your new v1.1.0 address: $NEW_ADDRESS"

# Save it
echo $NEW_ADDRESS > ~/v1.1.0-address.txt
cat ~/v1.1.0-address.txt
```

#### Step 7: Prove Ownership of v1.0 Address

```bash
# Replace with your actual v1.0 address
V10_ADDRESS="YOUR_V1.0_ADDRESS_HERE"

# Sign message
SIGNATURE=$(ammocoin-cli signmessage "$V10_ADDRESS" "I am migrating to AMMOcoin v1.1.0")

# Display claim info
echo "================================"
echo "Migration Claim Information"
echo "================================"
echo "v1.0 Address: $V10_ADDRESS"
echo "Message: I am migrating to AMMOcoin v1.1.0"
echo "Signature: $SIGNATURE"
echo "v1.1.0 Address: $NEW_ADDRESS"
echo "================================"

# Save to file
cat > ~/migration-claim.txt << EOF
v1.0 Address: $V10_ADDRESS
Message: I am migrating to AMMOcoin v1.1.0
Signature: $SIGNATURE
v1.1.0 Address: $NEW_ADDRESS
Date: $(date)
Raspberry Pi Model: $(cat /proc/device-tree/model)
EOF
```

#### Step 8: Submit Migration Claim

**Option A: Via Web Form** (Easiest if you have browser access)

1. Open browser on Pi or another device
2. Go to: https://ammocoin.org/migrate
3. Enter information from `~/migration-claim.txt`
4. Submit

**Option B: Via Email from Pi**

```bash
# Install mail utilities if needed
sudo apt install -y mailutils

# Send claim email
cat ~/migration-claim.txt | mail -s "Migration Claim - $V10_ADDRESS" support@ammocoin.org
```

**Option C: Copy file to another device**

```bash
# If you have USB drive
cp ~/migration-claim.txt /media/pi/USB/

# Or display to copy manually
cat ~/migration-claim.txt
```

Then email contents to: support@ammocoin.org

Subject: `Migration Claim - [YOUR_V1.0_ADDRESS]`

#### Step 9: Wait for Processing

Claims are processed within 24-48 hours. Monitor your balance:

```bash
# Check balance every 5 minutes
watch -n 300 'ammocoin-cli getbalance'
```

---

## Running AMMOcoin v1.1.0 on Raspberry Pi

### Start the Daemon

```bash
ammocoind -daemon
```

### Common Commands

```bash
# Status
ammocoin-cli getinfo

# Balance
ammocoin-cli getbalance

# Temperature check (important for Pi!)
vcgencmd measure_temp

# Send AMMO
ammocoin-cli sendtoaddress "ADDRESS" AMOUNT

# Get new address
ammocoin-cli getnewaddress

# Backup
ammocoin-cli backupwallet "$HOME/wallet-backup-$(date +%Y%m%d).dat"

# Stop
ammocoin-cli stop
```

### Auto-start on Boot

```bash
# Create systemd service
sudo tee /etc/systemd/system/ammocoind.service > /dev/null << EOF
[Unit]
Description=AMMOcoin v1.1.0 Daemon
After=network.target

[Service]
Type=forking
User=pi
Group=pi
ExecStart=/home/pi/ammocoin-bin/ammocoind -daemon -conf=/home/pi/.ammocoin/ammocoin.conf -datadir=/home/pi/.ammocoin
ExecStop=/home/pi/ammocoin-bin/ammocoin-cli -conf=/home/pi/.ammocoin/ammocoin.conf stop
Restart=on-failure
RestartSec=30
Nice=10

[Install]
WantedBy=multi-user.target
EOF

# Enable and start
sudo systemctl daemon-reload
sudo systemctl enable ammocoind
sudo systemctl start ammocoind

# Check status
sudo systemctl status ammocoind

# View logs
journalctl -u ammocoind -f
```

---

## Raspberry Pi Specific Optimizations

### Monitor Resources

```bash
# Install monitoring tools
sudo apt install -y htop

# Monitor during operation
htop

# Check temperature
watch -n 5 'vcgencmd measure_temp'

# Check disk space
df -h
```

### Optimize Configuration

Edit `~/.ammocoin/ammocoin.conf`:

```ini
# For Raspberry Pi 3B+ (2GB RAM or less)
dbcache=512
maxmempool=50
maxconnections=20

# For Raspberry Pi 4 (4GB+ RAM)
dbcache=1024
maxmempool=100
maxconnections=40

# For Raspberry Pi 5 (8GB RAM)
dbcache=2048
maxmempool=200
maxconnections=80
```

### Move Blockchain to External Storage (Recommended)

The blockchain can grow large. Use USB drive:

```bash
# Format USB drive (SKIP if already formatted)
# WARNING: This erases the drive!
sudo mkfs.ext4 /dev/sda1

# Create mount point
sudo mkdir -p /mnt/ammocoin-data

# Mount drive
sudo mount /dev/sda1 /mnt/ammocoin-data

# Change ownership
sudo chown pi:pi /mnt/ammocoin-data

# Move data
ammocoin-cli stop
sleep 10
mv ~/.ammocoin/* /mnt/ammocoin-data/
rm -rf ~/.ammocoin
ln -s /mnt/ammocoin-data ~/.ammocoin

# Auto-mount on boot
echo '/dev/sda1 /mnt/ammocoin-data ext4 defaults 0 2' | sudo tee -a /etc/fstab

# Start daemon
ammocoind -daemon
```

---

## Troubleshooting

### Build Issues

**Error: "virtual memory exhausted"**

Increase swap space:
```bash
sudo dphys-swapfile swapoff
sudo sed -i 's/CONF_SWAPSIZE=.*/CONF_SWAPSIZE=4096/' /etc/dphys-swapfile
sudo dphys-swapfile setup
sudo dphys-swapfile swapon
```

**Error: "internal compiler error"**

Thermal throttling or memory issue:
```bash
# Check temperature
vcgencmd measure_temp

# If > 80°C, cool down and use -j1
make clean
make -j1
```

**Error: "ld: cannot find -lboost_system"**

Install Boost:
```bash
sudo apt install -y libboost-all-dev
```

### Runtime Issues

**Daemon slow to start:**

Raspberry Pi is slower. Wait 30 seconds:
```bash
sleep 30
ammocoin-cli getinfo
```

**High CPU usage:**

Normal during sync. Monitor:
```bash
top -p $(pgrep ammocoind)
```

**Out of disk space:**

Move to USB drive (see Optimizations section above).

**Sync taking too long:**

Add more peers:
```bash
ammocoin-cli addnode "seed1.ammocoin.org" "add"
ammocoin-cli addnode "seed2.ammocoin.org" "add"
```

---

## Performance Tips

1. **Use wired Ethernet** instead of WiFi for better stability
2. **Use quality power supply** - undervoltage causes crashes
3. **Add cooling** - heatsink minimum, fan recommended
4. **Use external USB SSD** - much faster than SD card
5. **Limit services** - disable unnecessary services:
   ```bash
   sudo systemctl disable bluetooth
   sudo systemctl disable cups
   ```

---

## Running a Lightweight Node

If your Pi struggles, run as a lightweight node:

```bash
# Edit config
cat >> ~/.ammocoin/ammocoin.conf << EOF

# Lightweight Node Settings
prune=2000       # Keep only 2GB of blockchain
maxmempool=50    # Reduce mempool
maxconnections=8 # Reduce connections
EOF

# Restart
ammocoin-cli stop
sleep 10
ammocoind -daemon
```

**Note:** Pruned nodes can't serve full blockchain to other peers.

---

## Support

- Email: support@ammocoin.org
- Documentation: https://docs.ammocoin.org
- Raspberry Pi Forum: https://forum.ammocoin.org/raspberry-pi
- GitHub Issues: https://github.com/ammocoin/ammocoin/issues

---

## Quick Reference

```bash
# Status Commands
ammocoind -daemon                          # Start
ammocoin-cli getinfo                      # Status
ammocoin-cli getbalance                   # Balance
vcgencmd measure_temp                     # Temperature
df -h                                     # Disk space
free -h                                   # Memory

# Maintenance
journalctl -u ammocoind -f                # Logs
ammocoin-cli getpeerinfo | wc -l          # Peer count
ammocoin-cli getblockchaininfo            # Sync status
ammocoin-cli backupwallet ~/backup.dat    # Backup

# Troubleshooting
sudo systemctl restart ammocoind          # Restart service
tail -f ~/.ammocoin/debug.log             # View debug log
ammocoin-cli stop && sleep 10 && ammocoind -daemon  # Manual restart
```

---

**Migration Deadline:** 90 days from network launch
**Current Network:** v1.1.0
**Status:** Active
**Raspberry Pi Support:** Full support for Pi 3B+, 4, and 5
