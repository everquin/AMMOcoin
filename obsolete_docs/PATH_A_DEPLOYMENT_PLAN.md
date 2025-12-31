# AMMOcoin v1.1.0 - Path A Deployment Plan

**Migration Strategy:** Quick Launch with Manual Distribution
**Date:** December 22, 2025
**Status:** Ready for deployment

---

## Overview

Path A uses the **existing working v1.1.0 code** with **manual distribution** to the top 61 holders.

**Advantages:**
- ✅ Uses proven, stable code
- ✅ Lower risk (fixable errors)
- ✅ Can launch TODAY
- ✅ Transparent to users

---

## Phase 1: Build & Package (Today - 3-4 hours)

### Step 1: Build Cross-Platform Binaries

**Start Docker Desktop, then run:**

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin

# Build all platforms at once (recommended)
./build-all.sh

# OR build individually:
./build-linux.sh      # Linux x86_64
./build-windows.sh    # Windows x64
./build-arm64.sh      # ARM64/Raspberry Pi
```

**Expected output locations:**
- Linux: `build/linux/bin/`
- Windows: `build/windows/bin/`
- ARM64: `build/arm64/bin/`
- macOS: Already compiled in `ammocoin-apps-from-ammocoin/src/`

**Build time:** ~3-4 hours total

### Step 2: Test Each Platform Binary

```bash
# Linux (via Docker)
docker run -it --rm -v $(pwd)/build/linux/bin:/bin ubuntu:22.04 /bin/ammocoind --version

# Windows (if you have Windows machine/VM)
# Copy to Windows and test

# macOS (already tested)
./ammocoin-apps-from-ammocoin/src/ammocoind --version
```

### Step 3: Create Release Packages

For each platform, package:
1. Daemon (`ammocoind`)
2. CLI tool (`ammocoin-cli`)
3. TX utility (`ammocoin-tx`)
4. README with quick start instructions
5. Sample configuration file

**Package names:**
- `ammocoin-v1.1.0-linux-x86_64.tar.gz`
- `ammocoin-v1.1.0-windows-x64.zip`
- `ammocoin-v1.1.0-arm64.tar.gz`
- `ammocoin-v1.1.0-macos-arm64.dmg`

---

## Phase 2: Network Launch (Day 1)

### Option A: Fresh v1.1.0 Network (Recommended)

**Launch a completely new v1.1.0 blockchain:**

1. **Deploy seed nodes** (2-3 VPS servers)
   ```bash
   # On each seed node:
   ammocoind -daemon -addnode=SEED1_IP -addnode=SEED2_IP
   ```

2. **Mine initial blocks** to create supply
   - Set up 2-3 nodes mining/staking
   - Generate ~1000 blocks to stabilize network
   - Create admin wallet with funds

3. **Test transaction flow**
   - Send test transactions between nodes
   - Verify confirmations
   - Check wallet synchronization

### Option B: Continue from v1.0 (More Complex)

Modify v1.1.0 to recognize v1.0 genesis and continue the chain. **Not recommended** due to the transaction encoding incompatibility we discovered.

---

## Phase 3: User Communication (Day 1-2)

### Send Migration Announcement

**To all ~20 users, send:**

**Subject:** AMMOcoin v1.1.0 Upgrade - Action Required

**Message:**

```
Dear AMMOcoin Community,

We're excited to announce the release of AMMOcoin v1.1.0!

🚀 What's New:
- Enhanced privacy features (Sapling)
- Improved performance
- Multi-platform support (Windows, macOS, Linux, ARM64)
- Modern codebase (PIVX 5.x)

📅 Migration Timeline:
- v1.1.0 Network Launch: [DATE]
- Migration Window: 90 days
- v1.0 Sunset: [DATE + 90 days]

💰 Your Funds Are Safe:
All balances from v1.0 block 434,881 will be preserved.

📥 Download v1.1.0:
[DOWNLOAD LINKS]

📖 Migration Guide:
See attached USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md

🆘 Need Help?
- Email: support@ammocoin.org
- 1-on-1 assistance available

Best regards,
AMMOcoin Development Team
```

**Attachments:**
- `USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md`
- Platform-specific binaries

---

## Phase 4: Manual Distribution (Days 2-7)

### Top 61 Holders Distribution

**You have the list:** `genesis-top-holders.json`

**Distribution Process:**

1. **Set up your admin wallet** with funds
   ```bash
   ammocoind -daemon
   ammocoin-cli getnewaddress "Admin"
   # Mine/stake to this address to get funds
   ```

2. **Load the distribution list**
   ```bash
   # Use the provided distribution script (see below)
   python3 distribute-to-top-holders.py
   ```

3. **Send to each holder** (automated script handles this)
   - Script reads `genesis-top-holders.json`
   - Sends exact amounts to each address
   - Logs all transactions
   - Provides verification report

4. **Verify distributions**
   - Check each transaction confirmed
   - Provide txids to users
   - Let users verify their balances

**Estimated Time:** 1-2 hours (mostly waiting for confirmations)

### Small Holders Migration Fund

**You control:** `AeLWWVfT293noSbYpRJBN6xMsKk5ksgggC` (13,690,696 AMMO)

**Claim Process:**

1. **User submits claim request**
   - Provides v1.0 address
   - Signs message proving ownership
   - Submits via web form or email

2. **You verify claim** (automated tool provided)
   ```bash
   python3 verify-claim.py <v1.0_address> <signature>
   ```

3. **Send funds if verified**
   ```bash
   ammocoin-cli sendtoaddress <v1.1.0_address> <amount>
   ```

4. **Log the claim** for audit trail

**Expected claims:** 10,019 addresses (but likely only 20-50 active users)

---

## Phase 5: Ongoing Support (Days 8-90)

### Daily Tasks
- Monitor network health
- Process migration fund claims
- Answer user questions
- Check blockchain sync status

### Weekly Tasks
- Review migration progress
- Update users on statistics
- Address any technical issues
- Adjust support as needed

### Month 3
- Final migration push
- Assist remaining stragglers
- Plan v1.0 sunset
- Prepare for full v1.1.0 operation

---

## Distribution Scripts

### Automated Top 61 Distribution Script

**File:** `distribute-to-top-holders.py` (created below)

Automatically sends funds to all 61 top holders from `genesis-top-holders.json`.

### Claim Verification Script

**File:** `verify-claim.py` (created below)

Verifies user owns v1.0 address and calculates exact amount owed.

---

## Risk Management

### What Could Go Wrong & How to Fix

**Problem:** Network won't start
- **Fix:** Check seed nodes, verify ports open, review logs

**Problem:** Transactions not confirming
- **Fix:** Ensure nodes are connected, check if staking/mining active

**Problem:** User doesn't receive funds
- **Fix:** Check txid, verify address, resend if needed

**Problem:** Wrong amount sent
- **Fix:** Send correction amount (+ or -)

**Problem:** Migration fund runs low
- **Fix:** Transfer more from admin wallet

**All problems are fixable!** That's why Path A is safer.

---

## Success Metrics

### Week 1
- [ ] Network stable with 10+ nodes
- [ ] Top 61 holders distributed (100%)
- [ ] 50%+ of users downloaded v1.1.0
- [ ] No critical bugs reported

### Month 1
- [ ] 80%+ of users migrated
- [ ] Network producing blocks consistently
- [ ] Migration fund claims processed smoothly
- [ ] Positive user feedback

### Month 3
- [ ] 95%+ of users migrated
- [ ] v1.0 network sunset complete
- [ ] All balances verified and accounted for
- [ ] Full v1.1.0 adoption achieved

---

## Emergency Contacts

**Technical Issues:**
- You (project lead)
- [Technical team members]

**User Support:**
- support@ammocoin.org
- Discord/Telegram channels
- 1-on-1 assistance available

**Infrastructure:**
- VPS provider (Vultr)
- Seed node operators

---

## Checklist Before Launch

**Technical:**
- [ ] All platform binaries built and tested
- [ ] Seed nodes deployed and synced
- [ ] Admin wallet set up with funds
- [ ] Distribution scripts tested
- [ ] Backup systems in place

**Communication:**
- [ ] User announcement drafted
- [ ] Migration guide finalized
- [ ] Support channels ready
- [ ] FAQ prepared

**Documentation:**
- [ ] User migration guide
- [ ] Technical deployment docs
- [ ] Distribution logs prepared
- [ ] Audit trail system ready

**Team:**
- [ ] Support team briefed
- [ ] Emergency procedures documented
- [ ] Escalation paths defined
- [ ] 24/7 coverage planned (first week)

---

## Timeline Summary

**Day 0 (Today):**
- Build binaries (3-4 hours)
- Test packages (1 hour)
- Deploy seed nodes (2 hours)
**Total: 6-7 hours**

**Day 1:**
- Launch network
- Send user announcement
- Begin top 61 distribution
**Total: 3-4 hours**

**Days 2-7:**
- Complete top 61 distribution
- Process initial migration fund claims
- Monitor network stability
- Provide user support
**Total: 2-3 hours/day**

**Days 8-90:**
- Ongoing support
- Claim processing
- Network monitoring
**Total: 1 hour/day average**

---

## Cost Estimate

**Infrastructure:**
- 3x VPS seed nodes: $36-60/month
- Domain/SSL: $20/year
**Monthly: ~$40-60**

**Time Investment:**
- Week 1: ~20-30 hours
- Weeks 2-4: ~10 hours/week
- Months 2-3: ~5 hours/week
**Total: ~80-100 hours over 3 months**

**Return:**
- Successful v1.1.0 migration
- Happy users
- Modern, maintainable codebase
- Foundation for future growth

---

## Final Notes

**Path A is the safe choice because:**
1. Uses proven code
2. Errors are fixable
3. Transparent process
4. Lower stress deployment

**You're ready to launch!**

Start Docker, build the binaries, and you can have v1.1.0 running today.

🚀 **Let's make this happen!**
