# AMMOcoin v1.1.0 - Installation on macOS

**Platform:** macOS 11+ (Big Sur or newer)
**Architecture:** Apple Silicon (M1/M2/M3) and Intel
**Installation Time:** 5-10 minutes (using pre-built binaries)
**Difficulty:** Easy

---

## Method 1: Install Pre-Built Binaries (Recommended - Apple Silicon Only)

### Step 1: Download Binaries

Download the official macOS ARM64 binaries:

**Option A: Direct Download**
- Visit: https://ammocoin.org/downloads
- Download: `AMMOcoin-v1.1.0-macOS-ARM64.tar.gz`

**Option B: Via Terminal**
```bash
cd ~/Downloads
curl -LO https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz

# Verify checksum
shasum -a 256 AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
# Should match: feea58d2ec34d7758eefa8d4ca04eb5a3d6e5a98a5d67d19f1d2ff69d07cdeb3
```

### Step 2: Extract and Install

```bash
# Extract archive
cd ~/Downloads
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz

# Create application directory
mkdir -p ~/Applications/AMMOcoin

# Move binaries
mv AMMOcoin-v1.1.0-macOS-ARM64/* ~/Applications/AMMOcoin/

# Add to PATH (optional)
echo 'export PATH="$HOME/Applications/AMMOcoin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

### Step 3: First Run - Security Approval

macOS will block unsigned applications. You need to approve them:

```bash
# Try to run
~/Applications/AMMOcoin/ammocoind --version
```

You'll see: **"ammocoind cannot be opened because it is from an unidentified developer"**

**To approve:**

1. Open **System Preferences** → **Privacy & Security**
2. Scroll down to see: "ammocoind was blocked"
3. Click **"Open Anyway"**
4. Click **"Open"** in the confirmation dialog

Repeat for each binary:
```bash
~/Applications/AMMOcoin/ammocoin-cli --version
~/Applications/AMMOcoin/ammocoin-tx --version
```

**Alternative method (faster):**
```bash
# Remove quarantine attribute from all binaries
xattr -dr com.apple.quarantine ~/Applications/AMMOcoin/*

# Now they should run without prompts
~/Applications/AMMOcoin/ammocoind --version
```

### Step 4: Verify Installation

```bash
~/Applications/AMMOcoin/ammocoind --version
```

Expected output:
```
AMMOcoin Core Daemon version v1.1.0.0-f89ff1e-dirty
```

---

## Method 2: Build from Source (Intel Macs or Advanced Users)

### Prerequisites

#### Install Homebrew

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### Install Xcode Command Line Tools

```bash
xcode-select --install
```

#### Install Dependencies

```bash
# Install required libraries
brew install autoconf automake libtool pkg-config boost openssl@3 \
    libevent zmq miniupnpc libnatpmp gmp libsodium berkeley-db@4

# Install Rust
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env
```

### Build AMMOcoin

```bash
# Clone repository
cd ~
git clone https://github.com/everquin/AMMOcoin.git ammocoin-v1.1.0
cd ammocoin-v1.1.0

# Build
./autogen.sh
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-boost=$(brew --prefix boost) \
    --with-openssl=$(brew --prefix openssl@3)

make -j$(sysctl -n hw.ncpu)

# Install
mkdir -p ~/Applications/AMMOcoin
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx ~/Applications/AMMOcoin/
```

---

## Migration from v1.0 to v1.1.0

### IMPORTANT: Backup First!

```bash
# Create backup directory
mkdir -p ~/AMMOcoin-Backups

# Backup v1.0 wallet
cp ~/Library/Application\ Support/AMMOcoin/wallet.dat \
   ~/AMMOcoin-Backups/wallet-v1.0-$(date +%Y%m%d).dat

# Backup configuration
cp ~/Library/Application\ Support/AMMOcoin/ammocoin.conf \
   ~/AMMOcoin-Backups/ammocoin-v1.0.conf 2>/dev/null || true

# Verify backup
ls -lh ~/AMMOcoin-Backups/
```

**Store backup on external drive or cloud storage!**

### Migration Process

#### Step 1: Stop v1.0 Application

If you have the old AMMOcoin v1.0 app running:
- Quit the application completely
- Or stop the daemon:
```bash
ammocoin-cli stop 2>/dev/null || true
sleep 10
```

#### Step 2: Prepare v1.1.0 Data Directory

```bash
# Rename old directory
mv ~/Library/Application\ Support/AMMOcoin \
   ~/Library/Application\ Support/AMMOcoin-v1.0

# Create new directory
mkdir -p ~/Library/Application\ Support/AMMOcoin

# Copy wallet from v1.0
cp ~/Library/Application\ Support/AMMOcoin-v1.0/wallet.dat \
   ~/Library/Application\ Support/AMMOcoin/
```

#### Step 3: Create Configuration File

```bash
# Generate random RPC password
RPCPASS=$(openssl rand -base64 32)

# Create configuration
cat > ~/Library/Application\ Support/AMMOcoin/ammocoin.conf << EOF
# AMMOcoin v1.1.0 Configuration

# RPC Settings
rpcuser=ammocoinrpc
rpcpassword=$RPCPASS
rpcallowip=127.0.0.1

# Network
listen=1
server=1
daemon=1

# Seed nodes (will be provided at launch)
# addnode=seed1.ammocoin.org
# addnode=seed2.ammocoin.org
# addnode=seed2.ammocoin.org
EOF

echo "Configuration created with RPC password: $RPCPASS"
```

#### Step 4: Start AMMOcoin v1.1.0

```bash
# Start daemon
~/Applications/AMMOcoin/ammocoind -daemon

# Wait for startup
sleep 10

# Check status
~/Applications/AMMOcoin/ammocoin-cli getinfo
```

#### Step 5: Check Your v1.0 Balance

```bash
# View balance
~/Applications/AMMOcoin/ammocoin-cli getbalance

# List all addresses with balances
~/Applications/AMMOcoin/ammocoin-cli listaddressgroupings
```

**Note:** This shows your OLD v1.0 balance. You need to claim it on the NEW v1.1.0 network.

#### Step 6: Generate v1.1.0 Address

```bash
# Create new receiving address
NEW_ADDRESS=$(~/Applications/AMMOcoin/ammocoin-cli getnewaddress "Migrated Wallet")
echo "Your new v1.1.0 address: $NEW_ADDRESS"

# Save it
echo $NEW_ADDRESS > ~/Desktop/v1.1.0-address.txt
```

#### Step 7: Prove Ownership of v1.0 Address

```bash
# Replace with your actual v1.0 address
V10_ADDRESS="YOUR_V1.0_ADDRESS_HERE"

# Sign a message
SIGNATURE=$(~/Applications/AMMOcoin/ammocoin-cli signmessage "$V10_ADDRESS" "I am migrating to AMMOcoin v1.1.0")

# Display claim information
echo "================================"
echo "Migration Claim Information"
echo "================================"
echo "v1.0 Address: $V10_ADDRESS"
echo "Message: I am migrating to AMMOcoin v1.1.0"
echo "Signature: $SIGNATURE"
echo "v1.1.0 Address: $NEW_ADDRESS"
echo "================================"

# Save to file on Desktop
cat > ~/Desktop/migration-claim.txt << EOF
AMMOcoin v1.0 to v1.1.0 Migration Claim

v1.0 Address: $V10_ADDRESS
Message: I am migrating to AMMOcoin v1.1.0
Signature: $SIGNATURE
v1.1.0 Address: $NEW_ADDRESS
Date: $(date)
System: macOS $(sw_vers -productVersion)
EOF

# Open file to review
open ~/Desktop/migration-claim.txt
```

#### Step 8: Submit Migration Claim

**Option A: Via Web Form** (Easiest)

1. Open browser: https://ammocoin.org/migrate
2. Fill in information from `~/Desktop/migration-claim.txt`
3. Submit

**Option B: Via Email**

1. Open Mail app
2. Compose new email to: support@ammocoin.org
3. Subject: `Migration Claim - [YOUR_V1.0_ADDRESS]`
4. Attach or paste contents of `~/Desktop/migration-claim.txt`
5. Send

#### Step 9: Wait for Processing

Claims processed within 24-48 hours. Check balance:

```bash
# Check balance periodically
~/Applications/AMMOcoin/ammocoin-cli getbalance
```

Or set up automatic checking:
```bash
# Check every 5 minutes
watch -n 300 '~/Applications/AMMOcoin/ammocoin-cli getbalance'
```

---

## Daily Usage

### Start the Daemon

```bash
~/Applications/AMMOcoin/ammocoind -daemon
```

### Create Command Aliases (Optional)

Add to `~/.zshrc`:

```bash
echo 'alias ammocoind="$HOME/Applications/AMMOcoin/ammocoind"' >> ~/.zshrc
echo 'alias ammocoin-cli="$HOME/Applications/AMMOcoin/ammocoin-cli"' >> ~/.zshrc
source ~/.zshrc
```

Now you can just type:
```bash
ammocoin-cli getbalance
```

### Common Commands

```bash
# Check status
ammocoin-cli getinfo

# Check balance
ammocoin-cli getbalance

# Get blockchain info
ammocoin-cli getblockchaininfo

# Send AMMO
ammocoin-cli sendtoaddress "RECIPIENT_ADDRESS" AMOUNT

# Get new receiving address
ammocoin-cli getnewaddress "Label"

# List recent transactions
ammocoin-cli listtransactions

# Backup wallet
ammocoin-cli backupwallet "$HOME/Desktop/wallet-backup-$(date +%Y%m%d).dat"

# Stop daemon
ammocoin-cli stop
```

---

## Auto-Start on Login (Optional)

### Method 1: Using LaunchAgent

Create launch agent:

```bash
mkdir -p ~/Library/LaunchAgents

cat > ~/Library/LaunchAgents/org.ammocoin.ammocoind.plist << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>org.ammocoin.ammocoind</string>
    <key>ProgramArguments</key>
    <array>
        <string>$HOME/Applications/AMMOcoin/ammocoind</string>
        <string>-daemon</string>
    </array>
    <key>RunAtLoad</key>
    <true/>
    <key>KeepAlive</key>
    <false/>
    <key>StandardOutPath</key>
    <string>$HOME/Library/Logs/ammocoind.log</string>
    <key>StandardErrorPath</key>
    <string>$HOME/Library/Logs/ammocoind-error.log</string>
</dict>
</plist>
EOF

# Load the agent
launchctl load ~/Library/LaunchAgents/org.ammocoin.ammocoind.plist

# Check status
launchctl list | grep ammocoin
```

### Method 2: Using Login Items

1. Open **System Preferences** → **Users & Groups**
2. Click **Login Items**
3. Click **+** to add
4. Navigate to `~/Applications/AMMOcoin/`
5. Select `ammocoind`
6. Check **Hide** to start minimized

---

## Building GUI Wallet (Optional)

If you want a graphical wallet interface:

```bash
# Install Qt dependencies
brew install qt@5

# Build from source with GUI
cd ~/ammocoin-v1.1.0
./configure \
    --enable-wallet \
    --with-gui=qt5 \
    --with-boost=$(brew --prefix boost) \
    --with-openssl=$(brew --prefix openssl@3) \
    --with-qt=$(brew --prefix qt@5)

make -j$(sysctl -n hw.ncpu)

# Create application bundle
make deploy

# Copy to Applications
cp -r AMMOcoin-Qt.app /Applications/
```

Run the GUI wallet:
```bash
open /Applications/AMMOcoin-Qt.app
```

---

## Troubleshooting

### "Cannot be opened because it is from an unidentified developer"

**Solution:**
```bash
# Remove quarantine
xattr -dr com.apple.quarantine ~/Applications/AMMOcoin/*

# Or approve in System Preferences → Privacy & Security
```

### "dyld: Library not loaded"

Missing dependencies:

**Solution:**
```bash
# If using Homebrew built version
brew install boost openssl@3 libevent zmq miniupnpc

# Check what's missing
otool -L ~/Applications/AMMOcoin/ammocoind
```

### "Cannot obtain a lock on data directory"

Another instance running:

**Solution:**
```bash
# Stop existing instance
ammocoin-cli stop
sleep 10

# Or force kill
pkill ammocoind
sleep 5

# Start fresh
ammocoind -daemon
```

### "Error loading wallet.dat"

Wallet corrupted:

**Solution:**
```bash
# Restore from backup
ammocoin-cli stop
cp ~/AMMOcoin-Backups/wallet-v1.0-*.dat \
   ~/Library/Application\ Support/AMMOcoin/wallet.dat
ammocoind -daemon
```

### Build Errors

**Error: "configure: error: libdb_cxx not found"**

```bash
brew install berkeley-db@4
./configure --with-incompatible-bdb ...
```

**Error: "Rust not found"**

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env
```

---

## Performance Tuning

### Optimize Configuration

Edit `~/Library/Application Support/AMMOcoin/ammocoin.conf`:

```ini
# For better performance
dbcache=4096      # More cache (MB) - adjust based on RAM
maxmempool=300    # Larger mempool
maxconnections=125 # More connections

# For lower resource usage
dbcache=1024
maxmempool=100
maxconnections=40
```

---

## Uninstallation

If you need to remove AMMOcoin:

```bash
# Stop daemon
ammocoin-cli stop
sleep 10

# Remove binaries
rm -rf ~/Applications/AMMOcoin

# Remove data (BE CAREFUL - backs up wallet first)
cp ~/Library/Application\ Support/AMMOcoin/wallet.dat ~/wallet-final-backup.dat
rm -rf ~/Library/Application\ Support/AMMOcoin

# Remove launch agent (if configured)
launchctl unload ~/Library/LaunchAgents/org.ammocoin.ammocoind.plist
rm ~/Library/LaunchAgents/org.ammocoin.ammocoind.plist

# Remove aliases
sed -i '' '/ammocoin/d' ~/.zshrc
```

---

## Support

- Email: support@ammocoin.org
- Documentation: https://docs.ammocoin.org
- macOS Forum: https://forum.ammocoin.org/macos
- GitHub Issues: https://github.com/everquin/AMMOcoin/issues

---

## Quick Reference

```bash
# Daily Commands
ammocoind -daemon                              # Start
ammocoin-cli getinfo                          # Status
ammocoin-cli getbalance                       # Balance
ammocoin-cli sendtoaddress "addr" amount      # Send
ammocoin-cli getnewaddress                    # New address
ammocoin-cli stop                             # Stop

# Maintenance
ammocoin-cli backupwallet ~/Desktop/backup.dat  # Backup
tail -f ~/Library/Application\ Support/AMMOcoin/debug.log  # Logs
ammocoin-cli getpeerinfo | grep addr           # Check peers
ammocoin-cli getblockchaininfo                # Sync status

# Troubleshooting
ps aux | grep ammocoind                        # Check if running
pkill ammocoind && sleep 5 && ammocoind -daemon  # Force restart
ls -la ~/Library/Application\ Support/AMMOcoin/  # View data directory
```

---

**Migration Deadline:** 90 days from network launch
**Current Network:** v1.1.0
**Platform:** macOS 11+ (Intel & Apple Silicon)
**Status:** Active
