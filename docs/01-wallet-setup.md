# 🪙 AMMOcoin Wallet Setup & Usage Guide

This comprehensive guide will help you download, install, and use your AMMOcoin wallet safely and efficiently.

## 📥 Download & Installation

> ⚠️ **v1.1.1 (upcoming) is a mandatory hard fork.** From block 2,776 the network runs Proof-of-Stake and uses new network magic bytes, so v1.0 and v1.1.0 wallets can no longer connect. Install v1.1.1 when it is published on the official GitHub releases page. Download links and checksums will be added at release time - do not install binaries from any other source. See [Release Notes v1.1.1](release-notes/RELEASE_NOTES_v1.1.1_DRAFT.md).

### Windows Installation
1. **Download** the v1.1.1 Windows release from the official GitHub releases page (once published)
2. **Run** the installer as Administrator
3. **Accept** the license agreement
4. **Choose** installation directory (default recommended)
5. **Wait** for installation to complete
6. **Launch** AMMOcoin-Qt from Start Menu

### macOS Installation
1. **Download** the v1.1.1 macOS release from the official GitHub releases page (once published)
2. **Open** the .dmg file
3. **Drag** AMMOcoin-Qt to Applications folder
4. **Right-click** → Open (first time only, for security)
5. **Allow** network connections in firewall prompt

### Linux Installation
The Linux binaries need **glibc 2.34 or newer** (Ubuntu 22.04 LTS or newer; Ubuntu 24.04 is tested). Ubuntu 18.04 and 20.04 cannot run them - upgrade or reinstall the OS first. Check with `ldd --version`.

```bash
# Ubuntu/Debian (22.04+) - after downloading the v1.1.1 release archive
tar -xzf AMMOcoin-v1.1.1-Linux-x86_64.tar.gz
cd bin
chmod +x ammocoind ammocoin-cli ammocoin-tx
./ammocoind -daemon
```

## 🚀 First Launch Setup

### Initial Synchronization
When you first open your wallet:

1. **Wait for sync** - The wallet needs to download the blockchain
   - ⏱️ **Initial sync**: 30-60 minutes (depending on internet speed)
   - 📊 **Progress bar** shows sync status
   - 🔄 **Keep wallet open** until "Synced" appears

2. **Create/Restore Wallet**
   - **New wallet**: Auto-generated on first run
   - **Restore wallet**: Use backup seed phrase or wallet.dat file

3. **v1.0 holders** - Your v1.0 balance (snapshot at block 434,881) is airdropped to the **same addresses** on v1.1. Keep your v1.0 `wallet.dat`, put a copy in the v1.1.1 data folder, and **send nothing anywhere**. Never trust an emailed "disposal address". See [v1.0 Balance Airdrop](migration/V1.0_BALANCE_AIRDROP.md).

### Wallet Encryption (CRITICAL SECURITY STEP)
**🔒 Encrypt your wallet immediately after setup:**

1. Go to **Settings** → **Encrypt Wallet**
2. Create a **strong password** (mix of letters, numbers, symbols)
3. **Write down password** in a safe place
4. **Confirm** encryption
5. **Wallet will restart** - this is normal

> ⚠️ **WARNING**: If you lose your password, your coins are permanently lost!

## 🎛️ Wallet Interface Overview

### Main Dashboard
- **Balance** - Your available AMMO coins
- **Recent Transactions** - Latest sends/receives
- **Sync Status** - Network connection indicator
- **Staking Status** - Shows if staking is active

### Navigation Tabs

#### 💰 Overview Tab
- Current balance breakdown
- Recent transaction history
- Network statistics
- Staking rewards summary

#### 📤 Send Tab
- **Recipient Address** - Where to send coins
- **Amount** - How many AMMO to send
- **Fee** - Network transaction fee
- **Comment** - Optional memo (private)

#### 📥 Receive Tab
- **Your Addresses** - Generate new receiving addresses
- **QR Codes** - For easy mobile scanning
- **Address Labels** - Organize your addresses

#### 📊 Transactions Tab
- Complete transaction history
- Filter by date, amount, or type
- Export to CSV for records

#### 🏛️ Masternodes Tab (Advanced)
- View masternode status
- Manage masternode keys
- Monitor masternode rewards

## 💸 Sending AMMOcoin

### Basic Send Process
1. **Click** "Send" tab
2. **Enter** recipient's address
   - Copy/paste address carefully
   - Use QR scanner if available
   - Double-check address before sending
3. **Enter** amount to send
4. **Set** transaction fee:
   - **Economy**: Slower confirmation (lower fee)
   - **Normal**: Standard confirmation (recommended)
   - **Fast**: Quick confirmation (higher fee)
5. **Add** label/comment (optional)
6. **Click** "Send"
7. **Enter** wallet password
8. **Confirm** transaction details
9. **Wait** for network confirmation

### Fee Guidelines
| Priority | Fee | Confirmation Time |
|----------|-----|-------------------|
| Economy | 0.001 AMMO | 9-15 minutes |
| Normal | 0.01 AMMO | 3-9 minutes |
| Fast | 0.1 AMMO | 3-6 minutes |

## 📨 Receiving AMMOcoin

### Generate Receiving Address
1. **Click** "Receive" tab
2. **Click** "New Address"
3. **Add** label (e.g., "Payment from John")
4. **Copy** the generated address
5. **Share** address with sender
   - Use QR code for mobile users
   - Double-check address when sharing

### Address Security Tips
- **Generate new address** for each transaction
- **Label addresses** for easy tracking
- **Never share private keys** - only addresses
- **Verify address** before sharing

## 🔐 Wallet Security Best Practices

### Essential Security Steps
1. **✅ Encrypt wallet** with strong password
2. **✅ Backup wallet** regularly
3. **✅ Keep software updated**
4. **✅ Use antivirus software**
5. **✅ Don't share private keys**

### Backup Your Wallet

#### Method 1: Seed Phrase Backup
1. Go to **Help** → **Debug Window** → **Console**
2. Type: `dumpwallet backup.txt`
3. **Save file** in secure location
4. **Write down** seed phrase on paper
5. **Store paper backup** in safe place

#### Method 2: Wallet.dat Backup
1. **Close** AMMOcoin wallet
2. **Navigate** to data directory:
   - Windows: `%APPDATA%\AMMOcoinCore\`
   - macOS: `~/Library/Application Support/AMMOcoinCore/`
   - Linux: `~/.ammocoincore/`
   - (v1.0 and v1.1.0 used `AMMOcoin` / `.ammocoin` - keep any `wallet.dat` you find there too)
3. **Copy** `wallet.dat` file
4. **Store** in multiple secure locations
5. **Test restore** on different computer

### Two-Factor Security
- **Hardware wallet** integration (if supported)
- **Multi-signature** addresses for large amounts
- **Cold storage** for long-term holdings

## 🔧 Configuration & Settings

### Basic Settings
- **Language** - Choose your preferred language
- **Display Unit** - AMMO, mAMMO or µAMMO (the wallet shows amounts in AMMO only; it has no price feed)
- **Decimal Places** - Precision for amounts
- **Theme** - Light or dark mode

### Network Settings
- **Proxy Configuration** - For Tor/VPN users
- **Port Settings** - Advanced networking
- **Peer Connections** - Manual node connections

### Advanced Options
Access via **Help** → **Debug Window** → **Options**

```
# Common configuration (ammocoin.conf)
server=1
daemon=1
rpcuser=yourusername
rpcpassword=strongpassword
rpcallowip=127.0.0.1
staking=1
# Mainnet ports (defaults): P2P 37020, RPC 51473
```

## 📱 Mobile & Remote Access

### Web Wallet Access
- Use only official AMMOcoin web wallets
- Never enter private keys on web forms
- Verify SSL certificates and URLs

### Mobile Apps
- Download only from official app stores
- Verify app developer credentials
- Use for small amounts only

## 🆘 Troubleshooting Common Issues

### Wallet Won't Start
1. **Check** if another instance is running
2. **Restart** computer
3. **Check** available disk space (need 5GB+)
4. **Linux:** "Cannot find the Sapling parameters" means `~/.ammocoin-params` is missing or `HOME` is not set (systemd units need `Environment=HOME=...`)
5. **Verify** wallet.dat isn't corrupted

### Sync Issues
1. **Check** internet connection
2. **Add** manual nodes:
   - Settings → Options → Network
   - Add peer addresses, e.g. `78.141.194.140:37020` (seed1) and `104.238.165.56:37020` (seed2.ammocoin.org)
   - Make sure you are running v1.1.1 - older versions cannot connect after the fork
3. **Reset** blockchain data (keep wallet.dat!)

### Transaction Not Confirming
1. **Wait** - network congestion can delay confirmations
2. **Check** transaction fee was sufficient
3. **Verify** recipient address is correct
4. **Contact** support if >24 hours

### Forgotten Password
- **❌ Cannot be recovered** - passwords are not stored
- **Restore** from backup if available
- **Prevention**: Store password securely

## 📞 Getting Help

### Self-Help Resources
- [Troubleshooting Guide](./09-troubleshooting.md)
- [FAQ](./10-faq.md)
- [Community Forum](https://forum.ammocoin.org)

### Community Support
- **Discord**: AMMOcoin Official Server
- **Telegram**: @AMMOcoinSupport
- **Reddit**: r/AMMOcoin

### Emergency Contact
- **Critical Issues**: emergency@ammocoin.org
- **Security Issues**: security@ammocoin.org

---

## ✅ Quick Setup Checklist

- [ ] Downloaded v1.1.1 from the official GitHub releases page
- [ ] Installed and launched successfully
- [ ] Wallet fully synchronized
- [ ] Created strong encryption password
- [ ] Backed up wallet (seed + wallet.dat), and kept any v1.0 wallet.dat
- [ ] Tested receiving address generation
- [ ] Made small test transaction
- [ ] Documented password securely

**🎉 Congratulations! Your AMMOcoin wallet is ready to use securely.**

---

*Next: Learn about [Staking](./02-staking-guide.md) to earn rewards with your AMMO coins.*