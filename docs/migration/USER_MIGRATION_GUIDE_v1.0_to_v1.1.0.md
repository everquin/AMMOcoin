# AMMOcoin v1.0 → v1.1.0 User Migration Guide

**Migration Date:** December 2025
**User Count:** ~20 users
**Migration Method:** Private Key Import (Compatible Addresses)

---

## Overview

AMMOcoin v1.1.0 is a major upgrade that provides:
- ✅ Modern PIVX 5.x codebase
- ✅ Enhanced privacy (Sapling)
- ✅ Improved performance
- ✅ Multi-platform support (Windows, macOS, Linux, ARM64)
- ✅ Better security

**Good News:** Your v1.0 private keys work directly in v1.1.0! Migration is simple.

---

## Migration Snapshot

**Snapshot taken at:**
- Block Height: **434,881**
- Date: **December 22, 2025**
- Total Addresses: **10,080**
- Total Supply: **232,397,748 AMMO**

All balances at this block height will be preserved when you import your private keys.

---

## Before You Start

### ⚠️ Critical: Back Up Your Wallet

**BEFORE doing anything, back up your v1.0 wallet:**

```bash
# Stop v1.0 daemon
ammocoin-cli stop

# Create backup
cp ~/.ammocoin/wallet.dat ~/ammocoin-v1.0-wallet-backup-$(date +%Y%m%d).dat

# Verify backup exists
ls -lh ~/ammocoin-v1.0-wallet-backup-*.dat
```

**Store this backup securely!** Keep multiple copies (USB drive, encrypted cloud storage, etc.)

---

## Migration Methods

You have **3 options** to migrate. Choose the one that works best for you:

### Option 1: Import Entire Wallet File (Easiest)

**Best for:** Most users

1. **Install v1.1.0:**
   - Download from: [AMMOcoin Releases](https://github.com/everquin/AMMOcoin/releases)
   - Install for your platform (Windows/macOS/Linux)

2. **Stop both daemons:**
   ```bash
   # Stop v1.0 (if running)
   ammocoin-cli stop

   # Stop v1.1.0 (if running)
   ammocoin-cli stop
   ```

3. **Copy your v1.0 wallet to v1.1.0:**
   ```bash
   # Backup v1.1.0 directory first (if it exists)
   mv ~/.ammocoin ~/.ammocoin-v1.1.0-empty-backup

   # Copy entire v1.0 data directory
   cp -r ~/.ammocoin-v1.0 ~/.ammocoin

   # Or just copy the wallet file
   mkdir -p ~/.ammocoin
   cp ~/.ammocoin-v1.0/wallet.dat ~/.ammocoin/wallet.dat
   ```

4. **Start v1.1.0 daemon:**
   ```bash
   ammocoind -daemon

   # Wait for sync (this may take hours)
   watch ammocoin-cli getinfo
   ```

5. **Verify your balance:**
   ```bash
   ammocoin-cli getbalance
   ammocoin-cli listaddressgroupings
   ```

Your funds should appear once the blockchain is fully synced!

---

### Option 2: Import Private Keys (Advanced)

**Best for:** Users who want a fresh wallet or only need specific addresses

1. **Export private keys from v1.0:**
   ```bash
   # Start v1.0 daemon
   ammocoind-v1.0 -daemon

   # Get all addresses
   ammocoin-cli listreceivedbyaddress 0 true

   # Export private key for each address
   ammocoin-cli dumpprivkey "YOUR_ADDRESS_HERE"

   # Save these keys securely!
   ```

2. **Import into v1.1.0:**
   ```bash
   # Start v1.1.0 daemon
   ammocoind -daemon

   # Import each private key
   ammocoin-cli importprivkey "YOUR_PRIVATE_KEY_HERE" "label" false

   # After importing all keys, rescan blockchain
   ammocoin-cli stop
   ammocoind -daemon -rescan
   ```

3. **Wait for rescan and verify balance:**
   ```bash
   ammocoin-cli getbalance
   ```

---

### Option 3: Use Wallet Import Function

**Best for:** Users comfortable with wallet files

1. **Export v1.0 wallet:**
   ```bash
   ammocoin-cli dumpwallet ~/v1.0-wallet-export.txt
   ```

2. **Import into v1.1.0:**
   ```bash
   ammocoin-cli importwallet ~/v1.0-wallet-export.txt
   ```

---

## Verification Checklist

After migration, verify everything:

- [ ] **Balance matches v1.0:**
  ```bash
  ammocoin-cli getbalance
  ```

- [ ] **All addresses present:**
  ```bash
  ammocoin-cli listreceivedbyaddress 0 true
  ```

- [ ] **Transaction history visible:**
  ```bash
  ammocoin-cli listtransactions "*" 100
  ```

- [ ] **Can create new address:**
  ```bash
  ammocoin-cli getnewaddress
  ```

- [ ] **Wallet is encrypted (if it was before):**
  ```bash
  ammocoin-cli getwalletinfo
  ```

---

## Important Notes

### Network Timing

- **v1.0 network:** No longer maintained
- **v1.1.0 network launched:** January 3, 2026
- **Migration window:** 90 days
- **After migration window:** v1.0 network may be shut down

### What Happens to Transaction History?

- ❌ **Transaction history is NOT preserved** (new blockchain)
- ✅ **Balances ARE preserved** (from snapshot at block 434,881)
- ✅ **All future transactions** will be on v1.1.0 blockchain

### Address Compatibility

- ✅ **v1.0 and v1.1.0 use identical address format** (both start with 'A')
- ✅ **Private keys can be imported into v1.1.0**
- ⚠️ **wallet.dat files are NOT directly compatible** — use `dumpwallet`/`importwallet` or `dumpprivkey`/`importprivkey` to migrate keys
- ✅ **You can verify addresses match before migrating**

### What If I Don't Migrate?

If you don't migrate within 90 days:
1. Your v1.0 node will stop working when network shuts down
2. Your funds remain safe in your private keys
3. Contact support for manual migration assistance
4. You can ALWAYS recover funds if you have your private keys

---

## Troubleshooting

### "Balance shows zero after import"

**Solution:** The blockchain hasn't fully synced yet.
```bash
# Check sync status
ammocoin-cli getblockchaininfo

# Look for "verificationprogress" - should be 0.99999+ when synced
```

### "Error: Wallet is encrypted"

**Solution:** Unlock wallet first:
```bash
ammocoin-cli walletpassphrase "your_passphrase" 3600
```

### "Cannot import private key"

**Solution:** Start v1.1.0 daemon without rescan, import all keys, then rescan:
```bash
ammocoind -daemon
# Import all keys with rescan=false
ammocoin-cli importprivkey "KEY" "label" false
# After all imports
ammocoin-cli stop
ammocoind -daemon -rescan
```

### "Wallet version error"

**Solution:** v1.1.0 uses a newer wallet format. Use `dumpwallet`/`importwallet` instead:
```bash
# In v1.0
ammocoin-cli dumpwallet ~/wallet-export.txt

# In v1.1.0
ammocoin-cli importwallet ~/wallet-export.txt
```

---

## Getting Help

**Support Channels:**
- Email: support@ammocoin.org
- Discord: [Link]
- Telegram: [Link]
- GitHub Issues: https://github.com/everquin/AMMOcoin/issues

**Migration Support Hours:**
- Available 24/7 during migration period
- Average response time: <4 hours
- 1-on-1 assistance available for all users

---

## Migration Timeline

### Week 1-2: Testing Phase
- [ ] Download v1.1.0 binaries
- [ ] Test on secondary machine
- [ ] Verify balance import works

### Week 3-4: Migration Window Opens
- [ ] Official migration begins
- [ ] v1.0 and v1.1.0 networks both running
- [ ] Support team available 24/7

### Week 5-12: Migration Period
- [ ] All users migrate at their own pace
- [ ] Both networks remain operational
- [ ] Regular check-ins with users

### Week 13: v1.0 Sunset Notice
- [ ] Final reminder to migrate
- [ ] Assisted migration for remaining users
- [ ] Prepare for v1.0 shutdown

### Week 14+: v1.1.0 Only
- [ ] v1.0 network shutdown
- [ ] All users on v1.1.0
- [ ] Migration complete

---

## Security Best Practices

1. **Never share your private keys**
2. **Always backup before making changes**
3. **Test with small amounts first**
4. **Verify checksums of downloaded binaries**
5. **Use encrypted backups**
6. **Keep multiple backup copies**
7. **Store backups in different physical locations**

---

## FAQ

**Q: Will I lose my coins?**
A: No. If you have your private keys, your coins are safe forever.

**Q: Can I run both v1.0 and v1.1.0 at the same time?**
A: Yes, but use different data directories (`-datadir` flag).

**Q: What if I'm running a masternode?**
A: You'll need to set up a new masternode on v1.1.0. Contact support for masternode migration guide.

**Q: Do I need to re-download the entire blockchain?**
A: Yes, v1.1.0 is a new blockchain starting from the new genesis block.

**Q: Will my address change?**
A: No, addresses use the same format and will remain identical.

**Q: Can I send coins between v1.0 and v1.1.0?**
A: No, they are separate networks. Migration is one-way via private key import.

---

## Final Checklist

Before migration:
- [ ] Back up v1.0 wallet.dat
- [ ] Back up private keys
- [ ] Verify backup works (test restore)
- [ ] Download v1.1.0 binaries
- [ ] Verify binary checksums

During migration:
- [ ] Import wallet or private keys
- [ ] Wait for full blockchain sync
- [ ] Verify balance matches

After migration:
- [ ] Test sending small amount
- [ ] Encrypt wallet (if not already)
- [ ] Create new backup of v1.1.0 wallet
- [ ] Keep v1.0 backup safe (just in case)

---

**Migration Status:** Ready to begin
**Questions?** Contact support@ammocoin.org

🚀 **Welcome to AMMOcoin v1.1.0!**
