# AMMOcoin v1.1.0 Network Bootstrap Guide

**Purpose:** Step-by-step guide to launch and bootstrap the AMMOcoin v1.1.0 network

**Date:** December 22, 2025

---

## Overview

This guide covers the complete process of launching the v1.1.0 network from scratch, including:
1. Deploying seed nodes
2. Generating initial supply
3. Distributing to holders
4. Establishing network stability

---

## Prerequisites

- [ ] All platform binaries built and tested
- [ ] 2-3 VPS servers ready (Ubuntu 22.04 recommended)
- [ ] Seed node deployment script ready
- [ ] Distribution scripts ready
- [ ] Admin wallet prepared

**Recommended VPS Specs:**
- CPU: 2 cores minimum
- RAM: 2GB minimum
- Storage: 40GB SSD minimum
- Bandwidth: Unmetered
- Provider: Vultr, DigitalOcean, Linode, etc.

---

## Phase 1: Deploy Seed Nodes

### Step 1.1: Prepare VPS Servers

**For each VPS:**

1. **Create Server**
   - OS: Ubuntu 22.04 LTS
   - Location: Geographically distributed (US, EU, Asia)
   - Firewall: SSH (22), AMMOcoin P2P (37020)

2. **Initial Setup**
   ```bash
   # SSH into server
   ssh root@YOUR_SERVER_IP

   # Update system
   apt update && apt upgrade -y

   # Create deployment directory
   mkdir -p /opt/ammocoin-deploy
   cd /opt/ammocoin-deploy
   ```

3. **Upload Binaries**
   ```bash
   # From your local machine
   scp build/linux/bin/ammocoind root@YOUR_SERVER_IP:/opt/ammocoin-deploy/
   scp build/linux/bin/ammocoin-cli root@YOUR_SERVER_IP:/opt/ammocoin-deploy/
   scp build/linux/bin/ammocoin-tx root@YOUR_SERVER_IP:/opt/ammocoin-deploy/
   scp deploy-seed-node.sh root@YOUR_SERVER_IP:/opt/ammocoin-deploy/
   ```

### Step 1.2: Run Deployment Script

**On each VPS:**

```bash
cd /opt/ammocoin-deploy
chmod +x deploy-seed-node.sh
./deploy-seed-node.sh 1  # Use 1, 2, 3 for each respective node
```

**Save the output!** It contains:
- External IP address
- RPC credentials
- Node configuration

### Step 1.3: Configure Seed Node Connections

**After all seed nodes are deployed, update their configurations:**

**Seed Node 1:**
```bash
nano /home/ammocoin/.ammocoin/ammocoin.conf
```

Add:
```
addnode=SEED_NODE_2_IP:37020
addnode=SEED_NODE_3_IP:37020
```

**Seed Node 2:**
```
addnode=SEED_NODE_1_IP:37020
addnode=SEED_NODE_3_IP:37020
```

**Seed Node 3:**
```
addnode=SEED_NODE_1_IP:37020
addnode=SEED_NODE_2_IP:37020
```

### Step 1.4: Start Seed Nodes

**On each VPS:**
```bash
systemctl start ammocoind
```

**Verify they're running:**
```bash
systemctl status ammocoind
journalctl -u ammocoind -f  # Watch logs
```

**Check connectivity:**
```bash
ammocoin-cli getinfo
ammocoin-cli getpeerinfo
```

Expected: Each node should show 2 connections (to the other 2 seed nodes)

---

## Phase 2: Generate Initial Supply

You need to create enough AMMO to distribute to holders. Total required: **232,397,748 AMMO**

### Option A: Proof of Stake (Recommended)

**Set up staking on one of your nodes:**

1. **Create Admin Wallet**
   ```bash
   ammocoin-cli getnewaddress "Admin"
   ```
   Save this address!

2. **Generate Initial Blocks (PoW if enabled)**
   ```bash
   # If PoW is available for initial blocks
   ammocoin-cli generate 100
   ```

   Or manually mine blocks if needed.

3. **Enable Staking**
   ```bash
   # If wallet is encrypted
   ammocoin-cli walletpassphrase "YOUR_PASSWORD" 999999999 true

   # Check staking status
   ammocoin-cli getstakingstatus
   ```

4. **Monitor Supply Generation**
   ```bash
   watch -n 10 'ammocoin-cli getinfo | grep -E "blocks|balance"'
   ```

5. **Wait for Sufficient Supply**
   - Continue staking until balance >= 232,397,748 AMMO
   - This may take hours/days depending on block rewards
   - Monitor regularly

### Option B: Pre-Mine (If Genesis Allows)

If your genesis block or early blocks have high rewards:

```bash
# Generate initial blocks
ammocoin-cli generate 1000

# Check balance
ammocoin-cli getbalance
```

### Option C: Manual Supply Transfer

If you control a specific address with funds:

```bash
# Import private key
ammocoin-cli importprivkey "YOUR_PRIVATE_KEY"

# Wait for sync
ammocoin-cli getbalance
```

---

## Phase 3: Distribute to Top 61 Holders

Once you have sufficient supply:

### Step 3.1: Verify Distribution Data

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin

# Check the distribution list
cat genesis-top-holders.json | jq '.top_holders | length'
# Should show: 61

# Check total amount needed
cat genesis-top-holders.json | jq '.total_top_supply'
# Should show: 218707052.20974243
```

### Step 3.2: Ensure Admin Wallet Has Funds

```bash
# Check your balance
./ammocoin-cli getbalance

# Should be >= 218,707,052.20 AMMO
```

If insufficient, continue staking/mining until you have enough.

### Step 3.3: Run Test Distribution (Dry Run)

```bash
python3 distribute-to-top-holders.py --dry-run
```

Review the output carefully:
- [ ] All 61 addresses shown
- [ ] Amounts match genesis-top-holders.json
- [ ] Total matches expected
- [ ] No errors

### Step 3.4: Execute Real Distribution

```bash
python3 distribute-to-top-holders.py
```

**This will:**
1. Validate each address
2. Send exact amounts to each holder
3. Pause every 10 transactions for confirmations
4. Create a detailed transaction log

**Expected time:** 1-2 hours

### Step 3.5: Verify Distributions

```bash
# Check the transaction log
cat distribution-log-*.json | jq '.total_transactions'
# Should show: 61

# Check for any failures
cat distribution-log-*.json | jq '.transactions[] | select(.status == "failed")'
# Should be empty

# Verify a few random addresses
./ammocoin-cli getreceivedbyaddress "ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL"
# Should show expected amount
```

### Step 3.6: Notify Top Holders

Send personalized emails to top 61 holders:

```
Subject: Your AMMOcoin v1.1.0 Balance is Ready

Dear AMMOcoin Holder,

Your balance has been successfully transferred to the v1.1.0 network.

Address: [THEIR ADDRESS]
Amount: [THEIR AMOUNT] AMMO
Transaction ID: [TXID]

To access your funds:
1. Download AMMOcoin v1.1.0
2. Import your private key (the same one from v1.0)
3. Your full balance will appear immediately

Download: [LINK]

Thank you!
```

---

## Phase 4: Set Up Migration Fund

### Step 4.1: Fund the Migration Address

```bash
# Send migration fund amount
./ammocoin-cli sendtoaddress "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs" 13690696.25046043

# Save the transaction ID
```

### Step 4.2: Verify Migration Fund

```bash
# Check the address received funds
./ammocoin-cli getreceivedbyaddress "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs"
# Should show: 13690696.25046043
```

### Step 4.3: Backup Migration Fund Private Key

**CRITICAL SECURITY STEP:**

```bash
# Dump private key
./ammocoin-cli dumpprivkey "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs"

# SAVE THIS SECURELY!
# Multiple encrypted backups in different locations
```

**Storage recommendations:**
1. Encrypted USB drive (offline)
2. Password manager (encrypted)
3. Paper wallet (in safe/vault)
4. Never store unencrypted
5. Never share with anyone

---

## Phase 5: Network Health Checks

### Step 5.1: Verify Network Stability

**Check all seed nodes:**

```bash
# On each seed node
ammocoin-cli getinfo

# Verify:
# - All nodes at same block height
# - Each has 2+ peer connections
# - No error messages
```

**Check blockchain integrity:**

```bash
# Verify blockchain is valid
ammocoin-cli verifychain

# Check best block hash matches across nodes
ammocoin-cli getbestblockhash
```

### Step 5.2: Verify Balances

**Top 61 holders:**
```bash
# Sample check of 5 random addresses
for addr in $(cat genesis-top-holders.json | jq -r '.top_holders[0,10,20,30,40].address'); do
    echo "Checking $addr"
    ./ammocoin-cli getreceivedbyaddress "$addr"
done
```

**Migration fund:**
```bash
./ammocoin-cli getreceivedbyaddress "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs"
```

### Step 5.3: Transaction Tests

```bash
# Create a test address
TEST_ADDR=$(./ammocoin-cli getnewaddress "Test")

# Send a small test transaction
./ammocoin-cli sendtoaddress "$TEST_ADDR" 1.0

# Wait for confirmation
./ammocoin-cli gettransaction [TXID]

# Verify it arrived
./ammocoin-cli getreceivedbyaddress "$TEST_ADDR"
```

### Step 5.4: Staking Verification

```bash
# Check if staking is active
./ammocoin-cli getstakingstatus

# Expected:
# - "staking": true
# - "mintablecoins": true
# - "stakingbalance": > 0
```

---

## Phase 6: DNS & Infrastructure

### Step 6.1: Set Up DNS Seeders (Optional but Recommended)

**Create DNS A records:**
```
seed1.ammocoin.org → SEED_NODE_1_IP
seed2.ammocoin.org → SEED_NODE_2_IP
seed3.ammocoin.org → SEED_NODE_3_IP
```

**Update chainparams.cpp** (for future releases):
```cpp
vSeeds.emplace_back("seed1.ammocoin.org", true);
vSeeds.emplace_back("seed2.ammocoin.org", true);
vSeeds.emplace_back("seed3.ammocoin.org", true);
```

### Step 6.2: Set Up Block Explorer (Optional)

**Options:**
- Iquidus Explorer
- Insight Explorer
- Custom explorer

**Benefits:**
- Users can verify transactions
- Transparency
- Network statistics

### Step 6.3: Set Up Network Monitor

**Simple monitoring script:**

```bash
#!/bin/bash
# network-monitor.sh

NODES=(
    "SEED_NODE_1_IP"
    "SEED_NODE_2_IP"
    "SEED_NODE_3_IP"
)

for node in "${NODES[@]}"; do
    echo "Checking $node..."
    ssh ammocoin@$node "ammocoin-cli getinfo" || echo "ERROR: $node unreachable"
done
```

Run via cron every 5 minutes.

---

## Phase 7: Launch Announcement

### Step 7.1: Prepare Announcement Materials

- [ ] User announcement email (use template)
- [ ] Download pages updated with binaries
- [ ] Migration guide finalized
- [ ] Support channels ready
- [ ] FAQ prepared

### Step 7.2: Announce to Community

**Send announcements via:**
1. Email to all holders
2. Website announcement
3. Social media (if applicable)
4. Discord/Telegram
5. Forum posts

**Key information to include:**
- v1.1.0 is live
- Download links
- Migration instructions
- Support contact
- Timeline (90-day window)

### Step 7.3: Monitor Initial Response

**First 24 hours:**
- Watch support channels closely
- Monitor network health
- Track migration activity
- Address any issues immediately

---

## Troubleshooting

### Issue: Seed Nodes Won't Connect

**Diagnosis:**
```bash
# Check firewall
sudo ufw status

# Check if daemon is running
systemctl status ammocoind

# Check network connectivity
ping SEED_NODE_IP

# Check specific port
telnet SEED_NODE_IP 37020
```

**Solutions:**
- Ensure port 37020 is open in firewall
- Verify addnode entries in ammocoin.conf
- Restart daemons
- Check logs: `journalctl -u ammocoind -f`

### Issue: Not Generating Blocks

**Diagnosis:**
```bash
ammocoin-cli getstakingstatus
ammocoin-cli getmininginfo
```

**Solutions:**
- Unlock wallet: `ammocoin-cli walletpassphrase "pass" 999999999 true`
- Ensure sufficient balance
- Wait for coin maturity (100 confirmations)
- Check network has active stakers

### Issue: Transactions Not Confirming

**Diagnosis:**
```bash
ammocoin-cli getmempoolinfo
ammocoin-cli getrawmempool
ammocoin-cli gettransaction [TXID]
```

**Solutions:**
- Ensure network is generating blocks
- Check transaction fee is sufficient
- Verify transaction is valid
- Check if inputs are confirmed

### Issue: Distribution Script Fails

**Check:**
- Wallet has sufficient balance
- Daemon is responsive
- Addresses are valid
- No RPC connection issues

**Resume:**
```bash
# Check last successful holder in log
cat distribution-log-*.json | jq '.transactions[-1].holder_number'

# Resume from next holder
python3 distribute-to-top-holders.py --start-from [NEXT_NUMBER]
```

---

## Post-Launch Monitoring

### Daily Checks (Week 1)

**Every day:**
- [ ] Check all seed nodes are online
- [ ] Verify block production is stable
- [ ] Monitor peer connections
- [ ] Check for error logs
- [ ] Review support requests
- [ ] Track migration progress

**Commands:**
```bash
# Quick health check script
#!/bin/bash
echo "=== Network Health ==="
ammocoin-cli getinfo | grep -E "blocks|connections|balance"
ammocoin-cli getstakingstatus | grep staking
ammocoin-cli getpeerinfo | wc -l
echo "=== Mempool ==="
ammocoin-cli getmempoolinfo
echo "=== Recent Blocks ==="
ammocoin-cli getblockcount
```

### Weekly Checks (Month 1)

- [ ] Review migration statistics
- [ ] Process migration fund claims
- [ ] Update users on progress
- [ ] Address any technical issues
- [ ] Monitor network hashrate/stakerate
- [ ] Check for software updates needed

### Monthly Checks

- [ ] Full network audit
- [ ] Review security logs
- [ ] Update documentation
- [ ] Plan for v1.0 sunset
- [ ] Assess migration completion rate

---

## Success Criteria

**Week 1:**
- [ ] Network stable with 10+ nodes
- [ ] Blocks generated consistently
- [ ] Top 61 distributions complete (100%)
- [ ] 50%+ of users have downloaded v1.1.0
- [ ] No critical bugs

**Month 1:**
- [ ] 80%+ of users migrated
- [ ] Migration fund claims processed smoothly
- [ ] Network performance solid
- [ ] Positive user feedback

**Month 3:**
- [ ] 95%+ of users migrated
- [ ] v1.0 network ready for sunset
- [ ] All balances verified
- [ ] Full v1.1.0 adoption

---

## Emergency Procedures

### If Major Bug Found

1. **Assess severity**
2. **Stop distributions if necessary**
3. **Communicate to users immediately**
4. **Deploy fix**
5. **Test thoroughly**
6. **Resume operations**

### If Seed Node Goes Down

1. **Identify which node**
2. **Check other nodes are stable**
3. **Restart failed node**
4. **If unrecoverable, deploy replacement**
5. **Update DNS if needed**

### If Fork Detected

1. **Identify the fork point**
2. **Determine which chain is correct**
3. **If needed, release fix**
4. **Communicate to network**
5. **Guide nodes to correct chain**

---

## Rollback Plan (Emergency Only)

**If catastrophic failure occurs within first 48 hours:**

1. **Stop all operations immediately**
2. **Assess the situation**
3. **Communicate transparently to users**
4. **If necessary, delay launch and fix issues**
5. **Test fixes thoroughly before retry**

**Important:** Once users have migrated, rollback becomes increasingly difficult and should be avoided unless absolutely necessary.

---

## Checklist

### Pre-Launch
- [ ] All binaries tested
- [ ] VPS servers ready
- [ ] Seed nodes deployed
- [ ] Seed nodes connected
- [ ] Distribution scripts tested
- [ ] Documentation complete
- [ ] Support channels ready

### Launch Day
- [ ] Seed nodes started
- [ ] Initial supply generated
- [ ] Network stable
- [ ] Distributions executed
- [ ] Migration fund funded
- [ ] Announcement sent

### Post-Launch
- [ ] Daily health checks
- [ ] Process migration claims
- [ ] Monitor user feedback
- [ ] Address issues promptly
- [ ] Track migration progress

---

## Contact & Support

**Technical Issues:**
- Lead Developer: [YOUR EMAIL]

**Infrastructure:**
- VPS Provider: [SUPPORT LINK]

**Community:**
- Discord: [LINK]
- Telegram: [LINK]

---

**Network launched:** ________________

**Launched by:** ________________

**Status:** ⬜ SUCCESSFUL / ⬜ ISSUES ENCOUNTERED

**Notes:**
________________________________________________________________
________________________________________________________________
