# AMMOcoin v1.0 → v1.1.0 Migration Plan
**Target Users:** ~20 users
**Current Block Height:** <500,000
**Network:** node1.ammocoin.org (78.141.194.140)
**Migration Method:** Balance Snapshot with Genesis Pre-allocation

---

## Executive Summary

Due to fundamental transaction encoding differences between v1.0 and v1.1.0, a direct blockchain upgrade is not possible. We will perform a **balance snapshot migration**, which is the industry-standard approach for major blockchain upgrades.

**What This Means:**
- ✅ **All user funds are preserved** - Every address keeps exact balance
- ✅ **Same private keys work** - Users just import keys into v1.1.0
- ✅ **Clean, modern codebase** - v1.1.0 based on latest PIVX
- ❌ **Transaction history lost** - Only final balances preserved
- ❌ **One-time migration event** - Cannot go back to v1.0

---

## Migration Timeline

### Week 1-2: Preparation & Communication
**Tasks:**
- [x] Identify technical requirements
- [ ] Announce migration to all 20 users
- [ ] Create migration support channel
- [ ] Test snapshot tools

**User Action:** None (just be aware migration is coming)

---

### Week 2-3: Snapshot & Genesis Generation
**Tasks:**
- [ ] Take final v1.0 balance snapshot at announced block height
- [ ] Generate v1.1.0 genesis block with all v1.0 balances
- [ ] Test new genesis on private testnet
- [ ] Verify all balances match exactly

**User Action:** None (monitoring only)

---

### Week 3-4: Testing & Documentation
**Tasks:**
- [ ] Private testnet validation with test balances
- [ ] Create step-by-step user migration guides
- [ ] Build migration verification tools
- [ ] Test with 2-3 volunteer users

**User Action:** Volunteers test migration process

---

### Week 4: Official Launch
**Tasks:**
- [ ] Deploy v1.1.0 binaries
- [ ] Start seed nodes
- [ ] Publish migration guide
- [ ] Provide 1-on-1 support for users

**User Action:** **MIGRATE THIS WEEK**

---

### Ongoing: Dual-Chain Support (Optional)
**Tasks:**
- [ ] Keep v1.0 nodes running for 30-90 days
- [ ] Monitor migration progress
- [ ] Help stragglers migrate
- [ ] Eventually sunset v1.0

**User Action:** Complete migration within 90 days

---

## Detailed Migration Process

### Phase 1: Taking the Snapshot

**Step 1: Announce Snapshot Block**
```
We will take a balance snapshot at block height: To be announced
Estimated date: To be announced

All balances at this block will be migrated to v1.1.0
```

**Step 2: Extract Balances**
```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin
chmod +x v1.0-snapshot-tool.py

# Update RPC credentials in script first!
python3 v1.0-snapshot-tool.py
```

**Output:**
```json
{
  "snapshot_info": {
    "block_height": 500000,
    "block_hash": "0x...",
    "total_addresses": 20,
    "total_supply": "XXX AMMO"
  },
  "balances": {
    "A1abc...": "1000000.00",
    "A2def...": "500000.00",
    ...
  }
}
```

---

### Phase 2: Generate v1.1.0 Genesis

**Step 1: Modify chainparams.cpp**

Replace genesis construction with pre-allocated balances:

```cpp
// Genesis block with v1.0 balance pre-allocation
CMutableTransaction txNew;
txNew.vin.resize(1);
txNew.vout.resize(20);  // One output per address

// Allocate balance to each v1.0 address
txNew.vout[0].nValue = 1000000 * COIN;  // Address A1abc...
txNew.vout[0].scriptPubKey = GetScriptForDestination(
    DecodeDestination("A1abc...")
);

txNew.vout[1].nValue = 500000 * COIN;  // Address A2def...
txNew.vout[1].scriptPubKey = GetScriptForDestination(
    DecodeDestination("A2def...")
);

// ... repeat for all 20 addresses
```

**Step 2: Recompile**
```bash
cd source
make clean
make -j8
```

**Step 3: Test New Genesis**
```bash
# Start daemon with new genesis
./src/ammocoind -daemon -datadir=/tmp/test-genesis

# Verify genesis hash
./src/ammocoin-cli getblockhash 0

# Should output new genesis hash (different from v1.0)
```

---

### Phase 3: User Migration

**User Guide: Migrating from v1.0 to v1.1.0**

#### Before You Start:
- ⏰ **Time Required:** 15-30 minutes
- 💾 **Backup v1.0 wallet** before proceeding
- 📝 **Write down your balance** from v1.0 to verify later
- 🔐 **Never share private keys** with anyone

---

#### Step 1: Backup Your v1.0 Wallet

**Option A: GUI Wallet**
1. Open AMMOcoin v1.0 wallet
2. Click **File → Backup Wallet**
3. Save `wallet-v1.0-backup.dat` to safe location
4. Store in multiple places (USB drive, cloud, etc.)

**Option B: Manual Backup**
```bash
# Find your wallet.dat
# macOS: ~/Library/Application Support/AMMOcoin/
# Linux: ~/.ammocoin/
# Windows: %APPDATA%\AMMOcoin\

cp wallet.dat wallet-v1.0-backup.dat
```

---

#### Step 2: Export Your Private Keys

**Option A: Export All Keys at Once**
```bash
# In v1.0 Debug Console (Help → Debug → Console):
walletpassphrase "your_password" 600
dumpwallet "/path/to/ammocoin-keys-backup.txt"
```

**Option B: Export Individual Keys**
```bash
# For each address with balance:
dumpprivkey "A1abc..."
# Copy and save the private key securely
# Format: 5abc123def... (starts with 5 or K/L)
```

**⚠️ CRITICAL: Store Private Keys Securely**
- Write them down on paper
- Store in password manager
- Keep multiple backups
- NEVER share them

---

#### Step 3: Verify Your Balance

Before installing v1.1.0, verify your current balance:

```bash
# In v1.0 wallet:
getbalance

# Example output: 1000000.00 AMMO
# Write this down to verify after migration
```

---

#### Step 4: Install v1.1.0

**macOS:**
```bash
# Download v1.1.0 DMG from official site
# Open DMG and drag AMMOcoin-Qt to Applications
# v1.1.0 uses different data directory, won't conflict with v1.0
```

**Linux:**
```bash
wget https://github.com/everquin/AMMOcoin/releases/download/v1.1.0/AMMOcoin-Linux-x86_64.tar.gz
tar -xzf AMMOcoin-Linux.tar.gz
cd AMMOcoin/
./ammocoind -daemon
```

**Windows:**
```
Download AMMOcoin-Setup.exe
Run installer
Launch AMMOcoin v1.1.0
```

---

#### Step 5: Import Private Keys to v1.1.0

**Wait for sync to complete first!**
- Let v1.1.0 sync to current block height
- Status bar shows "Synced" or "Up to date"

**Then import keys:**

**Option A: Import Wallet File**
```bash
# In v1.1.0 Debug Console:
importwallet "/path/to/ammocoin-keys-backup.txt"
```

**Option B: Import Individual Keys**
```bash
# In v1.1.0 Debug Console:
# For each private key you exported:
importprivkey "5abc123def..."
```

**This may take 5-10 minutes** as wallet rescans blockchain.

---

#### Step 6: Verify Your Balance

After import completes:

```bash
# In v1.1.0 wallet:
getbalance

# Should match your v1.0 balance EXACTLY
# If not, contact support immediately!
```

**Visual Verification:**
1. Check each address in v1.1.0 wallet
2. Balances should match v1.0 exactly
3. Transactions will be empty (only genesis transaction shows)

---

#### Step 7: Test Small Transaction

Before using normally, test with small amount:

1. Send 1 AMMO to another address you control
2. Wait for confirmation
3. Verify it arrives
4. If successful, v1.1.0 is working correctly!

---

#### Step 8: Keep v1.0 Wallet Backup

**DO NOT DELETE v1.0 wallet** for at least 90 days:
- Keep wallet-v1.0-backup.dat safe
- In case any issues arise
- After 90 days and confirmed working, can archive

---

## Migration Support

**If You Have Problems:**

1. **Balance doesn't match:**
   - Double-check all private keys imported
   - Check for addresses with multiple keys
   - Contact support with address list

2. **Can't export private keys:**
   - Ensure wallet is unlocked
   - Try `walletpassphrase "password" 600` first
   - Contact support for assistance

3. **v1.1.0 won't sync:**
   - Check internet connection
   - Ensure ports not blocked
   - Contact support

4. **Large balance holders:**
   - We can assist with 1-on-1 migration
   - Contact us before migrating
   - We'll verify everything step-by-step

**Support Channels:**
- Email: support@ammocoin.org
- Discord: [link]
- Telegram: [link]
- Response time: <24 hours

---

## Technical Details

### Why This Migration Method?

**Problem:** v1.0 and v1.1.0 use different transaction encoding:
- v1.0: Older PIVX 3.x transaction format
- v1.1.0: Modern PIVX 5.x transaction format
- Merkle roots computed differently
- Cannot validate v1.0 blocks in v1.1.0

**Solution:** Snapshot + Genesis Pre-allocation:
- Take final v1.0 balances at specific block
- Create v1.1.0 genesis with those balances
- Users import same private keys
- Balances appear automatically

**Industry Precedent:**
- Bitcoin Cash (BCH) from Bitcoin (BTC)
- Ethereum Classic (ETC) from Ethereum (ETH)
- Litecoin Cash (LCC) from Litecoin (LTC)
- Standard approach for incompatible upgrades

---

### Genesis Block Structure

```cpp
// v1.1.0 Genesis with v1.0 Snapshot (Block 500,000)
// Snapshot Date: See announcement for details
// Total Supply: See announcement for details
// Total Addresses: 20

CMainParams() {
    // Genesis allocates all v1.0 balances
    CMutableTransaction txNew;
    txNew.vin.resize(1);
    txNew.vout.resize(20);

    // Pre-allocated addresses (from v1.0 snapshot)
    // [Generated automatically from snapshot]

    genesis.nTime = [Snapshot timestamp];
    genesis.nNonce = [Computed];
    genesis.hashMerkleRoot = [Computed from allocated balances];

    // New genesis hash (different from v1.0)
    consensus.hashGenesisBlock = [Computed];
}
```

---

## FAQ

**Q: Will I lose my coins?**
A: No! Every address keeps its exact balance. You just import your private keys into v1.1.0.

**Q: Can I use my old private keys?**
A: Yes! Same private keys work in v1.1.0. That's how you access your migrated balance.

**Q: What happens to my transaction history?**
A: Transaction history is lost. Only final balances are preserved. This is normal for this type of migration.

**Q: What if I miss the migration period?**
A: We'll keep v1.0 nodes running for 90 days. You can migrate anytime during that period. After 90 days, contact support for help.

**Q: Do I need to do anything before snapshot block?**
A: No. Your balance at the snapshot block is what counts. Just make sure you have your private keys backed up.

**Q: Can I keep using v1.0?**
A: v1.0 will be sunset after 90 days. All future development will be on v1.1.0. Please migrate within 90 days.

**Q: What about masternodes?**
A: Masternode collateral (10,000 AMMO) will be preserved. You'll need to set up masternode again in v1.1.0 with same keys.

**Q: Is this safe?**
A: Yes. This is the standard industry approach for major upgrades. Your funds are safe as long as you control your private keys.

---

## Security Checklist

- [ ] Backup v1.0 wallet
- [ ] Export all private keys
- [ ] Store private keys in 3+ secure locations
- [ ] Verify balance before migration
- [ ] Install v1.1.0 from official source only
- [ ] Let v1.1.0 fully sync before importing
- [ ] Import all private keys
- [ ] Verify balance matches in v1.1.0
- [ ] Test small transaction
- [ ] Keep v1.0 backup for 90 days

---

## Contact

**Questions about migration?**
Email: support@ammocoin.org
Response Time: <24 hours

**Large balance holders:**
Request 1-on-1 migration assistance

**Emergency:**
If you encounter issues during migration, contact support immediately.

---

**Last Updated:** December 1, 2025
**Version:** 1.0
**Status:** DRAFT - Awaiting approval
