# AMMOcoin v1.1.0 - Build from Source on Windows

**Platform:** Windows 10/11 (64-bit)
**Build Time:** 30-60 minutes
**Difficulty:** Intermediate

---

## Prerequisites

### 1. Install WSL2 (Windows Subsystem for Linux)

Open PowerShell as Administrator and run:

```powershell
wsl --install -d Ubuntu-22.04
```

Restart your computer when prompted, then set up your Ubuntu username and password.

### 2. Update WSL Ubuntu

Open Ubuntu from Start Menu and run:

```bash
sudo apt update
sudo apt upgrade -y
```

---

## Install Build Dependencies

Run these commands in your Ubuntu WSL terminal:

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
```

---

## Download and Build AMMOcoin v1.1.0

### Step 1: Clone the Repository

```bash
cd ~
git clone https://github.com/ammocoin/ammocoin.git ammocoin-v1.1.0
cd ammocoin-v1.1.0
```

**If you don't have the repository URL, extract from the source archive:**

```bash
cd ~
# Copy the source from Windows to WSL
cp /mnt/c/Users/YourUsername/Downloads/ammocoin-v1.1.0-source.tar.gz .
tar -xzf ammocoin-v1.1.0-source.tar.gz
cd ammocoin-v1.1.0
```

### Step 2: Build AMMOcoin

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

# Compile (this takes 20-40 minutes)
make -j$(nproc)
```

**If you encounter errors during build**, try:
```bash
make clean
make -j1  # Single-threaded build (slower but more stable)
```

### Step 3: Install Binaries

```bash
sudo make install
```

Or copy to a local directory:

```bash
mkdir -p ~/ammocoin-bin
cp src/ammocoind src/ammocoin-cli src/ammocoin-tx ~/ammocoin-bin/
```

---

## Verify Installation

```bash
~/ammocoin-bin/ammocoind --version
```

Expected output:
```
AMMOcoin Core Daemon version v1.1.0.0-xxxxxxx
```

---

## Migration from v1.0 to v1.1.0

### IMPORTANT: Backup First!

**On your Windows system:**

1. Locate your v1.0 wallet:
   - Default location: `C:\Users\YourUsername\AppData\Roaming\AMMOcoin\wallet.dat`

2. **Copy wallet.dat to a safe location** (USB drive, encrypted backup, etc.)

3. Also backup:
   - `ammocoin.conf` (if you have custom settings)
   - `masternode.conf` (if running a masternode)

### Migration Process

**Method 1: Using WSL (Recommended for Windows users)**

#### Step 1: Stop v1.0 Wallet (if running)

Close your Windows AMMOcoin v1.0 wallet application completely.

#### Step 2: Copy wallet.dat to WSL

```bash
# Create AMMOcoin data directory in WSL
mkdir -p ~/.ammocoin

# Copy wallet from Windows to WSL
cp /mnt/c/Users/YourUsername/AppData/Roaming/AMMOcoin/wallet.dat ~/.ammocoin/
```

#### Step 3: Start AMMOcoin v1.1.0

```bash
# Start the daemon
~/ammocoin-bin/ammocoind -daemon

# Wait 10 seconds for startup
sleep 10

# Check status
~/ammocoin-bin/ammocoin-cli getinfo
```

#### Step 4: Verify Your Balance

```bash
~/ammocoin-bin/ammocoin-cli getbalance
```

Your v1.0 balance should show here. **This balance will NOT work on v1.1.0 network** - you need to claim it from the migration fund.

#### Step 5: Get Your v1.0 Address and Balance

```bash
# List all addresses with balances
~/ammocoin-bin/ammocoin-cli listaddressgroupings
```

Make note of your address and balance.

#### Step 6: Generate v1.1.0 Address

```bash
~/ammocoin-bin/ammocoin-cli getnewaddress "My v1.1.0 Wallet"
```

Save this new address - this is where you'll receive your migrated AMMO.

#### Step 7: Prove Ownership of v1.0 Address

```bash
# Sign a message with your v1.0 address
~/ammocoin-bin/ammocoin-cli signmessage "YOUR_V1.0_ADDRESS" "I am migrating to AMMOcoin v1.1.0"
```

This creates a cryptographic signature proving you own the address.

#### Step 8: Submit Migration Claim

**Option A: Via Web Form** (Easiest)

1. Go to: https://ammocoin.org/migrate (or the official migration URL)
2. Enter your v1.0 address
3. Enter the signed message: `I am migrating to AMMOcoin v1.1.0`
4. Enter the signature from Step 7
5. Enter your NEW v1.1.0 address from Step 6
6. Submit

**Option B: Via Email**

Send an email to: support@ammocoin.org

Subject: `Migration Claim - [YOUR_V1.0_ADDRESS]`

Body:
```
v1.0 Address: [Your v1.0 address]
v1.0 Balance: [Your balance]
Message: I am migrating to AMMOcoin v1.1.0
Signature: [Signature from Step 7]
v1.1.0 Address: [Your new v1.1.0 address]
```

#### Step 9: Wait for Confirmation

You should receive your migrated AMMO within 24-48 hours. Check your balance:

```bash
~/ammocoin-bin/ammocoin-cli getbalance
```

---

## Running AMMOcoin v1.1.0 Daily

### Start the Daemon

```bash
~/ammocoin-bin/ammocoind -daemon
```

### Common Commands

```bash
# Check status
~/ammocoin-bin/ammocoin-cli getinfo

# Check balance
~/ammocoin-bin/ammocoin-cli getbalance

# Send AMMO
~/ammocoin-bin/ammocoin-cli sendtoaddress "RECIPIENT_ADDRESS" AMOUNT

# Get new receiving address
~/ammocoin-bin/ammocoin-cli getnewaddress

# Backup wallet
~/ammocoin-bin/ammocoin-cli backupwallet "/mnt/c/Users/YourUsername/Desktop/wallet-backup.dat"

# Stop daemon
~/ammocoin-bin/ammocoin-cli stop
```

### Access from Windows

To make commands easier, create a batch file on Windows:

**File: `C:\ammocoin-cli.bat`**
```batch
@echo off
wsl ~/ammocoin-bin/ammocoin-cli %*
```

Then you can run from Windows CMD/PowerShell:
```
ammocoin-cli getbalance
ammocoin-cli sendtoaddress "ADDRESS" 10
```

---

## Troubleshooting

### Build Errors

**Error: "configure: error: libdb_cxx headers missing"**
```bash
sudo apt install -y libdb++-dev
```

**Error: "Rust compiler not found"**
```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source $HOME/.cargo/env
```

**Error: "cargo build failed"**

The Rust/Sapling components may have compatibility issues. Try building without GUI:
```bash
./configure --disable-tests --disable-bench --without-gui --enable-wallet
make
```

### Runtime Errors

**Error: "Cannot obtain a lock on data directory"**

Another instance is running. Stop it:
```bash
~/ammocoin-bin/ammocoin-cli stop
# Wait 10 seconds
sleep 10
~/ammocoin-bin/ammocoind -daemon
```

**Error: "Error loading wallet.dat"**

Wallet may be corrupted. Restore from backup:
```bash
~/ammocoin-bin/ammocoin-cli stop
cp ~/wallet-backup.dat ~/.ammocoin/wallet.dat
~/ammocoin-bin/ammocoind -daemon
```

---

## Building a GUI Wallet (Advanced)

If you want a graphical interface similar to the old Windows wallet:

```bash
# Install Qt5 dependencies
sudo apt install -y qtbase5-dev qttools5-dev qttools5-dev-tools \
    libqrencode-dev libprotobuf-dev protobuf-compiler

# Rebuild with GUI
./configure --enable-wallet --with-gui
make -j$(nproc)

# Install
sudo make install
```

Then run from WSL:
```bash
ammocoin-qt &
```

The wallet GUI will open in an X11 window (requires WSLg on Windows 11, or X server like VcXsrv on Windows 10).

---

## Support

- Email: support@ammocoin.org
- Documentation: https://docs.ammocoin.org
- GitHub Issues: https://github.com/ammocoin/ammocoin/issues

---

**Migration Deadline:** 90 days from launch
**Current Network:** v1.1.0
**Status:** Active
