# AMMOcoin v1.1.0 - Launch Day Quick Reference

**Date:** [TO BE FILLED]
**Network Launch Time:** [TO BE FILLED]

---

## 🚀 LAUNCH SEQUENCE

### T-24 Hours: Final Preparations

```bash
# 1. Verify all seed nodes are ready
ssh seed1.ammocoin.org "ammocoind --version"
ssh seed2.ammocoin.org "ammocoind --version"
ssh seed3.ammocoin.org "ammocoind --version"

# 2. Verify migration fund wallet is ready
ammocoin-cli -datadir=/path/to/migration-fund getinfo

# 3. Test automated distribution script (dry run)
./distribute_to_top_holders.sh --dry-run

# 4. Verify website updates are staged
curl https://ammocoin.org/downloads | grep "v1.1.0"
```

### T-1 Hour: Final Checks

- [ ] All seed nodes synchronized
- [ ] Block explorer ready (if applicable)
- [ ] Email notifications queued
- [ ] Social media posts drafted
- [ ] Support team on standby
- [ ] Emergency contact list confirmed

### T-0: LAUNCH

```bash
# 1. Start seed nodes (run on each seed server)
ammocoind -daemon

# 2. Verify network startup
ammocoin-cli getinfo
ammocoin-cli getpeerinfo | grep "addr"

# 3. Publish binaries on website
# Upload: ammocoin-v1.1.0-macos-arm64.tar.gz
# Upload: ammocoin-v1.1.0-macos-arm64.tar.gz.sha256

# 4. Send email notifications
./send_migration_emails.sh

# 5. Post announcements
# - Website
# - Twitter
# - Discord
# - Telegram
# - Forum

# 6. Monitor initial connections
watch -n 5 'ammocoin-cli getconnectioncount'
```

---

## 📊 MONITORING COMMANDS

### Network Health

```bash
# Connection count
ammocoin-cli getconnectioncount

# Peer information
ammocoin-cli getpeerinfo

# Blockchain info
ammocoin-cli getblockchaininfo

# Network hash rate
ammocoin-cli getnetworkhashps

# Memory pool
ammocoin-cli getmempoolinfo
```

### Seed Node Status

```bash
# Check all seed nodes
for seed in seed1 seed2 seed3; do
  echo "=== $seed.ammocoin.org ==="
  ssh $seed.ammocoin.org "ammocoin-cli getinfo"
  echo ""
done
```

### Migration Fund

```bash
# Check migration fund balance
ammocoin-cli -datadir=/path/to/migration-fund getbalance

# List recent transactions
ammocoin-cli -datadir=/path/to/migration-fund listtransactions

# Check specific address
ammocoin-cli -datadir=/path/to/migration-fund listaddressgroupings
```

---

## 📧 COMMUNICATION TEMPLATES

### Website Announcement

```
🚀 AMMOcoin v1.1.0 Network is LIVE!

The AMMOcoin v1.1.0 network has successfully launched!

Downloads:
- macOS ARM64: [Download] (4.6M)
- Windows: [Build from Source Guide]
- Linux: [Build from Source Guide]
- Raspberry Pi: [Build from Source Guide]

Migration Information:
- Top 61 holders: Check your email for v1.1.0 address
- All other holders: Follow migration guide
- Deadline: 90 days from today

Need Help? support@ammocoin.org
```

### Twitter Announcement

```
🚀 #AMMOcoin v1.1.0 is LIVE!

✅ Enhanced privacy features
✅ Improved network performance
✅ Modern codebase

📥 Download: ammocoin.org/downloads
📖 Migration Guide: ammocoin.org/migrate
⏰ Migration Window: 90 days

#Cryptocurrency #Blockchain
```

### Email to Top 61 Holders

```
Subject: AMMOcoin v1.1.0 Launch - Your Migration Address

Dear AMMOcoin Holder,

The AMMOcoin v1.1.0 network is now live!

Your v1.0 balance has been automatically migrated to:

v1.1.0 Address: [FILLED BY SCRIPT]
Migrated Amount: [FILLED BY SCRIPT] AMMO

Please verify this balance in your v1.1.0 wallet.

Installation Guide: https://ammocoin.org/downloads
Support: support@ammocoin.org
```

### Email to All Other Holders

```
Subject: AMMOcoin v1.1.0 Migration - Action Required

Dear AMMOcoin Holder,

The AMMOcoin v1.1.0 network is now live! You must migrate your holdings within 90 days.

Migration Steps:
1. Install AMMOcoin v1.1.0
2. Generate new v1.1.0 address
3. Sign message with your v1.0 address
4. Submit claim at: ammocoin.org/migrate

Detailed Guide: https://ammocoin.org/migration-guide
Deadline: [90 days from today]
Support: support@ammocoin.org
```

---

## 🔧 COMMON OPERATIONS

### Process Migration Claim

```bash
# 1. Receive claim email/form submission
V10_ADDRESS="[from claim]"
V11_ADDRESS="[from claim]"
MESSAGE="I am migrating to AMMOcoin v1.1.0"
SIGNATURE="[from claim]"

# 2. Verify signature
ammocoin-cli verifymessage "$V10_ADDRESS" "$SIGNATURE" "$MESSAGE"
# Expected: true

# 3. Check v1.0 balance in snapshot
grep "$V10_ADDRESS" migration_snapshot.csv

# 4. Send from migration fund
AMOUNT="[balance from snapshot]"
ammocoin-cli -datadir=/path/to/migration-fund sendtoaddress "$V11_ADDRESS" $AMOUNT "Migration claim for $V10_ADDRESS"

# 5. Record transaction
echo "$(date),$V10_ADDRESS,$V11_ADDRESS,$AMOUNT,$TXID" >> migration_claims_processed.csv

# 6. Send confirmation email to user
```

### Automated Distribution (Top 61)

```bash
# Run the automated distribution script
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/migration-tools
./distribute_to_top_holders.sh

# Monitor progress
tail -f distribution.log

# Verify all transactions confirmed
ammocoin-cli -datadir=/path/to/distribution-wallet listtransactions | grep "category" | grep "send"
```

### Check Migration Progress

```bash
# Total claimed so far
CLAIMED=$(cat migration_claims_processed.csv | awk -F',' '{sum+=$4} END {print sum}')
echo "Claimed: $CLAIMED AMMO"

# Remaining in fund
REMAINING=$(ammocoin-cli -datadir=/path/to/migration-fund getbalance)
echo "Remaining: $REMAINING AMMO"

# Percentage migrated
echo "scale=2; ($CLAIMED / 13690696.25) * 100" | bc
```

---

## 🚨 EMERGENCY PROCEDURES

### Network Not Starting

```bash
# Check seed node logs
tail -100 ~/.ammocoin/debug.log

# Common issues:
# - Port 37020 blocked by firewall
# - Configuration error
# - Data directory permissions

# Restart with debug logging
ammocoind -daemon -debug=net -debug=rpc
```

### No Peer Connections

```bash
# Manually add peers
ammocoin-cli addnode "seed1.ammocoin.org" "add"
ammocoin-cli addnode "seed2.ammocoin.org" "add"
ammocoin-cli addnode "seed3.ammocoin.org" "add"

# Check firewall
sudo ufw status
sudo ufw allow 37020/tcp

# Check if port is listening
netstat -an | grep 37020
```

### Migration Fund Wallet Issues

```bash
# Wallet locked
ammocoin-cli -datadir=/path/to/migration-fund walletpassphrase "PASSPHRASE" 3600

# Insufficient balance (should not happen)
ammocoin-cli -datadir=/path/to/migration-fund getbalance

# Transaction failed
ammocoin-cli -datadir=/path/to/migration-fund gettransaction TXID
```

### Invalid Signature in Claim

```bash
# Verify signature manually
ammocoin-cli verifymessage "ADDRESS" "SIGNATURE" "I am migrating to AMMOcoin v1.1.0"

# If false:
# - Ask user to re-sign
# - Verify they're using v1.0 wallet
# - Check message is exactly: "I am migrating to AMMOcoin v1.1.0"
# - No extra spaces or characters
```

### Too Many Support Requests

```bash
# Triage priorities:
# P0 - Cannot sync blockchain
# P1 - Cannot migrate funds
# P2 - Installation questions
# P3 - General questions

# Standard responses in: /support-responses/
```

---

## 📈 SUCCESS METRICS

### Hour 1
- [ ] At least 10 peer connections across all seed nodes
- [ ] First block mined
- [ ] Top 61 distribution transactions broadcasted
- [ ] Website accessible and downloads working

### Day 1
- [ ] 100+ network nodes
- [ ] Top 61 distributions confirmed (6+ confirmations)
- [ ] First migration fund claims processed
- [ ] No critical issues reported

### Week 1
- [ ] Top 61 distributions 100% complete
- [ ] 50+ migration fund claims processed
- [ ] 1000+ network nodes
- [ ] Block explorer operational (if applicable)

### Month 1
- [ ] 25% of migration fund claimed
- [ ] Active community engagement
- [ ] No security incidents
- [ ] Stable network performance

### Day 90 (Migration Deadline)
- [ ] 90%+ of migration fund claimed
- [ ] All claims processed
- [ ] Migration statistics published
- [ ] Network operating normally

---

## 📞 CONTACT LIST

### Core Team
- **Lead Developer:** [NAME] - [PHONE] - [EMAIL]
- **Network Admin:** [NAME] - [PHONE] - [EMAIL]
- **Community Manager:** [NAME] - [PHONE] - [EMAIL]
- **Support Lead:** [NAME] - [PHONE] - [EMAIL]

### Emergency Contacts
- **Hosting Provider:** [COMPANY] - [SUPPORT NUMBER]
- **DNS Provider:** [COMPANY] - [SUPPORT NUMBER]
- **Email Service:** [COMPANY] - [SUPPORT NUMBER]

### Escalation Path
1. Support tickets → Support Lead
2. Technical issues → Network Admin
3. Code bugs → Lead Developer
4. PR/Communication → Community Manager

---

## 📝 LOGGING AND TRACKING

### Migration Claims Log

```bash
# Format: Date,V1.0_Address,V1.1.0_Address,Amount,TX_ID,Status
echo "$(date),ADDRESS1,ADDRESS2,1000.00,TXID,completed" >> migration_claims_processed.csv
```

### Issue Tracking

```bash
# Format: Date,Issue_ID,Severity,Description,Status
echo "$(date),001,P1,User cannot sync,investigating" >> issues.csv
```

### Network Metrics

```bash
# Collect every hour
echo "$(date),$(ammocoin-cli getconnectioncount),$(ammocoin-cli getblockcount)" >> network_metrics.csv
```

---

## ✅ POST-LAUNCH CHECKLIST (24 Hours)

- [ ] All seed nodes operational
- [ ] Network hash rate stable
- [ ] Top 61 distributions complete
- [ ] First migration claims processed
- [ ] No critical bugs reported
- [ ] Website downloads working
- [ ] Email notifications sent
- [ ] Social media announcements posted
- [ ] Support team briefed
- [ ] Monitoring dashboards active
- [ ] Backup procedures tested
- [ ] Incident response plan verified

---

## 📚 QUICK REFERENCE LINKS

- **Installation Guides:** `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/INSTALL_MACOS.md` (and others)
- **Migration Plan:** `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/MIGRATION_PLAN_DETAILED.md`
- **Deployment Checklist:** `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/DEPLOYMENT_CHECKLIST.md`
- **Emergency Procedures:** `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/EMERGENCY_PROCEDURES.md`
- **Release Summary:** `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/RELEASE_V1.1.0_SUMMARY.md`

---

**Good luck with the launch! 🚀**

*Last Updated: December 22, 2025*
