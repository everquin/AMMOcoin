# AMMOcoin v1.0 to v1.1.0 User Migration Guide

**Network Launch:** January 3, 2026
**Migration Deadline:** April 3, 2026 (90 days)
**Migration Method:** Signed-message claim process

---

## Overview

AMMOcoin v1.1.0 is a **completely new blockchain** — it is NOT an upgrade of v1.0. The two networks are separate and incompatible.

A **250,000,000 AMMO distribution fund** in the v1.1.0 genesis block covers all v1.0 balances (snapshot taken at block 434,881 on December 22, 2025). To receive your coins on v1.1.0, you must complete a claim process that proves you owned a v1.0 address.

**What v1.1.0 brings:**
- Modern PIVX 5.x codebase
- Sapling privacy (zkSNARK shielded transactions)
- Improved performance and security
- Pre-built binaries for all platforms (macOS, Windows, Linux x86_64, ARM64)

---

## Before You Start

### Back Up Your v1.0 Wallet

**Without your v1.0 wallet.dat, you cannot prove ownership and will lose your coins permanently.**

```bash
# Stop v1.0 daemon
ammocoin-cli stop

# Create backup
cp ~/.ammocoin/wallet.dat ~/ammocoin-v1.0-wallet-backup-$(date +%Y%m%d).dat

# Verify backup exists
ls -lh ~/ammocoin-v1.0-wallet-backup-*.dat
```

Store copies in multiple safe locations (USB drive, encrypted cloud storage, etc.).

---

## Step 1: Download and Install v1.1.0

Pre-built binaries are available for all platforms. Download from the [GitHub Release page](https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0) or the [AMMOcoin Downloads page](https://www.ammocoin.org/downloads.html).

### macOS (Apple Silicon)

Download and open the `.dmg` installer:
```
AMMOcoin-v1.1.0-macOS-ARM64.dmg
SHA256: 08dfb0be819eba85c3238f916e7c2464d1333f97a71a4c1caa0d9ebcea6fd7b6
```
Drag AMMOcoin to your Applications folder.

Or use the `.tar.gz` for CLI-only:
```bash
curl -LO https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
shasum -a 256 AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
# Expected: f314ff670ad1088cc64516be4b2f7667974f9937a3c2e1683844e5500cb709dd
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
sudo cp AMMOcoin-v1.1.0-macOS-ARM64/ammocoind AMMOcoin-v1.1.0-macOS-ARM64/ammocoin-cli /usr/local/bin/
```

### Windows

Download and run the installer:
```
AMMOcoin-v1.1.0-Windows-x86_64-Setup.exe
SHA256: 82f7a652b0c388e69f1a03be8eff11a514195c02f5f91357cf588f7a698a31c8
```
The NSIS installer includes the Qt wallet, daemon, CLI tools, Sapling parameters, and Start Menu shortcuts.

### Linux x86_64

**Option A: .deb package (Ubuntu/Debian — recommended)**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-amd64.deb
sha256sum AMMOcoin-v1.1.0-Linux-amd64.deb
# Expected: ae32a07effe874cf925e9e7c8dc604189f38113c54264ac47564a4e88fb53259
sudo dpkg -i AMMOcoin-v1.1.0-Linux-amd64.deb
```

**Option B: .tar.gz**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Expected: 41111899895744cf945079c544766199cc9e30398d2e239d76adf742a37f0b40
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx
```

### Linux ARM64 (Raspberry Pi 4/5)

**Option A: .deb package**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-arm64.deb
sha256sum AMMOcoin-v1.1.0-Linux-arm64.deb
# Expected: d4ded3c4d368ce1fe7f40d998c924a61419c481242e7420fcdf2ac7925b073f3
sudo dpkg -i AMMOcoin-v1.1.0-Linux-arm64.deb
```

**Option B: .tar.gz**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
sha256sum AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
# Expected: 42678ae20253b9acaa35732835a2a2a0ee552bb9a6b809ee683b5377d3f45014
tar -xzf AMMOcoin-v1.1.0-Linux-ARM64.tar.gz
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx
```

### All Checksums

See [AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt](https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt) for a complete list.

### Start the v1.1.0 Node

```bash
# Start daemon
ammocoind -daemon

# Wait for startup, then verify correct genesis block
ammocoin-cli getblockhash 0
# Must return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

---

## Step 2: Import v1.0 Keys into v1.1.0

You need your v1.0 private keys in the v1.1.0 wallet so you can sign messages proving ownership. Choose one of three methods:

### Method A: Copy wallet.dat (easiest)

```bash
# Stop v1.1.0 daemon
ammocoin-cli stop

# Copy v1.0 wallet file into v1.1.0 data directory
cp ~/ammocoin-v1.0-wallet-backup-*.dat ~/.ammocoin/wallet.dat

# Restart with rescan
ammocoind -daemon -rescan
```

### Method B: Import individual private keys

```bash
# From v1.0: export a private key
/path/to/v1.0/ammocoin-cli dumpprivkey "YOUR_V1.0_ADDRESS"

# In v1.1.0: import it (rescan=false for speed, rescan after all imports)
ammocoin-cli importprivkey "PRIVATE_KEY_HERE" "v1.0 import" false

# After importing all keys, rescan once
ammocoin-cli stop
ammocoind -daemon -rescan
```

### Method C: Dump/import entire wallet

```bash
# From v1.0: export all keys
/path/to/v1.0/ammocoin-cli dumpwallet ~/v1.0-wallet-export.txt

# In v1.1.0: import all keys
ammocoin-cli importwallet ~/v1.0-wallet-export.txt

# Delete the export file after import (contains private keys!)
rm ~/v1.0-wallet-export.txt
```

**IMPORTANT: Importing keys does NOT restore your balance.** The v1.1.0 blockchain has no record of v1.0 transactions. Your balance will show 0 until you complete the claim process below.

---

## Step 3: Generate a v1.1.0 Receiving Address

Create a new address where your claimed coins will be sent:

```bash
ammocoin-cli getnewaddress "Migration Claim"
# Example output: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n
```

Back up your v1.1.0 wallet after generating the address:
```bash
ammocoin-cli backupwallet ~/ammocoin-v1.1.0-wallet-backup.dat
```

---

## Step 4: Prove Ownership of Your v1.0 Address

Sign a message with your v1.0 address (now available in v1.1.0 after Step 2):

```bash
# If wallet is encrypted, unlock it first
ammocoin-cli walletpassphrase "your_passphrase" 300

# Sign the claim message
ammocoin-cli signmessage "YOUR_V1.0_ADDRESS" "I am migrating to AMMOcoin v1.1.0"

# Returns a signature like: INsQ7k9R3m... (long base64 string)
```

Save the signature — you will need it for the claim submission.

---

## Step 5: Submit Your Claim

Email **support@ammocoin.org** with the subject line: **Migration Claim - [Your v1.0 Address]**

Include:
1. **v1.0 Address:** (the address you signed with)
2. **Message signed:** `I am migrating to AMMOcoin v1.1.0`
3. **Signature:** (the base64 string from Step 4)
4. **v1.1.0 Receiving Address:** (from Step 3)

If you have multiple v1.0 addresses, submit a separate claim for each, or include all addresses with their signatures in one email.

---

## Step 6: Receive Your Coins

Claims are typically processed within **24-48 hours**. Once approved, you will receive v1.1.0 AMMO matching your v1.0 snapshot balance at block 434,881.

```bash
# Check your balance
ammocoin-cli getbalance

# View recent transactions
ammocoin-cli listtransactions "*" 10
```

---

## Masternode Operators

If you ran a masternode on v1.0, you must set up a **fresh masternode on v1.1.0** after claiming your collateral:

1. **Claim your v1.0 balance** (follow Steps 1-6 above — you need at least 10,000 AMMO)
2. **Set up a new VPS** running v1.1.0 (or upgrade your existing VPS)
3. **Configure the masternode** following the standard v1.1.0 masternode setup process
4. **Lock collateral** (10,000 AMMO) in your v1.1.0 wallet
5. **Start the masternode**

Your v1.0 masternode configuration does not carry over. Contact support@ammocoin.org if you need help with masternode setup.

---

## Verification Checklist

After completing migration:

- [ ] v1.1.0 node running and synced (`ammocoin-cli getblockchaininfo`)
- [ ] Balance received matches v1.0 snapshot balance (`ammocoin-cli getbalance`)
- [ ] Can create new addresses (`ammocoin-cli getnewaddress`)
- [ ] Can send a small test transaction
- [ ] Wallet encrypted (`ammocoin-cli encryptwallet "passphrase"` if not already)
- [ ] v1.1.0 wallet backed up
- [ ] v1.0 wallet backup stored safely (keep it!)

---

## Troubleshooting

### "Balance shows zero after importing keys"

This is expected. Importing keys only adds addresses to your wallet — it does not restore balances. You must complete the claim process (Steps 4-6) to receive your v1.1.0 coins.

### "Error: Wallet is encrypted"

Unlock your wallet before signing:
```bash
ammocoin-cli walletpassphrase "your_passphrase" 300
```

### "signmessage: Private key not available"

The v1.0 address was not imported correctly. Try importing the key again:
```bash
ammocoin-cli importprivkey "YOUR_V1.0_PRIVATE_KEY" "v1.0 import" true
```

### "Cannot connect to daemon"

Ensure v1.1.0 is running:
```bash
ammocoind -daemon
sleep 5
ammocoin-cli getinfo
```

### Node not syncing / no peers

Add seed nodes to your config file (`~/.ammocoin/ammocoin.conf`):
```
addnode=seed1.ammocoin.org:37020
addnode=seed2.ammocoin.org:37020
```

---

## FAQ

**Q: Will importing my v1.0 wallet restore my balance?**
A: No. v1.1.0 is a separate blockchain. Importing keys lets you prove ownership — you must then submit a claim to receive your coins.

**Q: Can I run both v1.0 and v1.1.0?**
A: Yes, but use different data directories (e.g., `-datadir=~/.ammocoin-v1.0` for v1.0).

**Q: What if I'm running a masternode?**
A: You must set up a fresh masternode on v1.1.0 after claiming your collateral. See the Masternode Operators section above.

**Q: Do I need to re-download the entire blockchain?**
A: Yes, v1.1.0 is a new blockchain starting from a new genesis block.

**Q: Will my address change?**
A: Your v1.0 addresses can be imported into v1.1.0 (same format), but you need a new v1.1.0 receiving address for the claim.

**Q: What if I miss the deadline?**
A: The claim period closes April 3, 2026. After that, unclaimed funds return to the community treasury. Contact support@ammocoin.org if you need an extension.

**Q: What happens to transaction history?**
A: v1.0 transaction history does not carry over. The v1.1.0 blockchain starts fresh.

---

## Security Best Practices

1. **Never share your private keys** with anyone
2. **Verify checksums** of all downloaded binaries before installing
3. **Back up before making changes** — both v1.0 and v1.1.0 wallets
4. **Test with a small amount first** if you have multiple addresses
5. **Delete exported key files** after import (`dumpwallet` output contains private keys)
6. **Keep your v1.0 wallet backup** even after successful migration

---

## Timeline

| Milestone | Date | Status |
|-----------|------|--------|
| v1.0 Snapshot (Block 434,881) | December 22, 2025 | Complete |
| v1.1.0 Network Launch | January 3, 2026 | Complete |
| Claim Period Opens | January 3, 2026 | Complete |
| **Claim Period Closes** | **April 3, 2026** | Active |
| Distribution Complete | May 2026 | Pending |

---

## Getting Help

- **Email:** support@ammocoin.org
- **GitHub Issues:** https://github.com/everquin/AMMOcoin/issues
- **Documentation:** [Migration docs](https://github.com/everquin/AMMOcoin/tree/main/docs/migration)

**Questions?** Contact support@ammocoin.org
