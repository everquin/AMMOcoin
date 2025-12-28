# AMMOcoin v1.1.0 - Distribution Scripts Guide

**Path A Deployment - Manual Distribution Tools**

This guide explains how to use the automated distribution scripts for deploying AMMOcoin v1.1.0 using Path A (manual distribution approach).

---

## Scripts Overview

### 1. `distribute-to-top-holders.py`
Automatically sends funds to the top 61 holders from `genesis-top-holders.json`.

### 2. `verify-claim.py`
Verifies ownership of v1.0 addresses and processes migration fund claims for the remaining 10,019 addresses.

---

## Prerequisites

**Before using these scripts:**

1. ✅ v1.1.0 network is running
2. ✅ `ammocoind` daemon is running and synced
3. ✅ Admin wallet has sufficient funds
4. ✅ You have both JSON data files:
   - `genesis-top-holders.json` (61 addresses)
   - `migration-fund-claims.json` (10,019 addresses)

---

## Script 1: Top 61 Holders Distribution

### Quick Start

```bash
# Test run (shows what would happen without sending)
python3 distribute-to-top-holders.py --dry-run

# Real distribution
python3 distribute-to-top-holders.py
```

### Features

✅ **Automatic validation** - Checks each address before sending
✅ **Batch processing** - Pauses every 10 transactions for confirmations
✅ **Resume capability** - Can restart from any position if interrupted
✅ **Transaction logging** - Creates detailed log of all transactions
✅ **Balance verification** - Ensures sufficient funds before starting

### Usage Examples

**1. Test run first (recommended):**
```bash
python3 distribute-to-top-holders.py --dry-run
```

**2. Send to all 61 holders:**
```bash
python3 distribute-to-top-holders.py
```

**3. Resume from holder #30 if interrupted:**
```bash
python3 distribute-to-top-holders.py --start-from 29
```

**4. Use custom batch size:**
```bash
python3 distribute-to-top-holders.py --batch-size 5
```

**5. Custom CLI path:**
```bash
python3 distribute-to-top-holders.py --cli-path /custom/path/to/ammocoin-cli
```

### What It Does

1. ✅ Loads `genesis-top-holders.json`
2. ✅ Checks daemon is running
3. ✅ Verifies wallet has sufficient balance
4. ✅ Validates each recipient address
5. ✅ Sends exact amount to each holder
6. ✅ Pauses every 10 transactions for confirmations
7. ✅ Creates detailed transaction log
8. ✅ Shows completion summary

### Transaction Log

Creates: `distribution-log-YYYYMMDD-HHMMSS.json`

```json
{
  "distribution_date": "2025-12-22T10:30:00",
  "total_transactions": 61,
  "transactions": [
    {
      "holder_number": 1,
      "address": "ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL",
      "amount": 36952699.9998,
      "status": "success",
      "txid": "abc123...",
      "timestamp": "2025-12-22T10:30:15"
    },
    ...
  ]
}
```

### Expected Timeline

- **Dry run:** 30 seconds
- **Full distribution:** 1-2 hours
  - 61 transactions
  - ~1 minute per transaction
  - Pauses every 10 transactions (6 pauses × 60 seconds)

---

## Script 2: Migration Fund Claims

### Quick Start

```bash
# Interactive mode (user-friendly)
python3 verify-claim.py

# Command line mode
python3 verify-claim.py --address <v1.0_addr> --signature <sig> --message <msg> --v1.1-address <new_addr> --send

# Show statistics
python3 verify-claim.py --stats
```

### Features

✅ **Signature verification** - Proves user owns v1.0 address
✅ **Duplicate prevention** - Won't pay same address twice
✅ **Interactive mode** - User-friendly for manual processing
✅ **Batch mode** - Command-line for automation
✅ **Claim logging** - Records all processed claims
✅ **Statistics** - Track migration fund usage

### Interactive Mode (Recommended for First Claims)

```bash
python3 verify-claim.py
```

**The script will guide you through:**
1. Enter v1.0 address
2. Check if eligible
3. Instructions for signing a message
4. Enter signature
5. Verify ownership
6. Process payment

### Command Line Mode (For Automation)

**Verify only (no payment):**
```bash
python3 verify-claim.py \
  --address ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL \
  --signature H123abc... \
  --message "I claim my AMMOcoin v1.1.0 migration"
```

**Verify and send payment:**
```bash
python3 verify-claim.py \
  --address ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL \
  --signature H123abc... \
  --message "I claim my AMMOcoin v1.1.0 migration" \
  --v1.1-address ANewV11AddressHere \
  --send
```

### How Users Create Signatures

**Users need to sign a message with their v1.0 address:**

**Option 1: Using v1.0 wallet GUI**
```
Tools → Sign Message
- Enter their address
- Enter message: "I claim my AMMOcoin v1.1.0 migration"
- Click "Sign"
- Copy signature
```

**Option 2: Using v1.0 CLI**
```bash
ammocoin-cli signmessage "ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL" "I claim my AMMOcoin v1.1.0 migration"
```

**They send you:**
- v1.0 address
- Signature
- Message they signed
- New v1.1.0 address to receive funds

### Claim Records

Creates: `processed-claims.json`

```json
{
  "claims": [
    {
      "v1_0_address": "ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL",
      "v1_1_address": "ANewV11AddressHere",
      "amount": 123.45678900,
      "txid": "def456...",
      "timestamp": "2025-12-22T11:00:00",
      "message": "I claim my AMMOcoin v1.1.0 migration",
      "signature": "H123abc..."
    }
  ]
}
```

### View Statistics

```bash
python3 verify-claim.py --stats
```

**Shows:**
- Total eligible addresses
- Total migration fund amount
- Claims processed
- Amount distributed
- Remaining claims
- Remaining amount

---

## Complete Deployment Workflow

### Phase 1: Prepare Admin Wallet

**1. Start your v1.1.0 node:**
```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin
./src/ammocoind -daemon
```

**2. Check it's running:**
```bash
./src/ammocoin-cli getinfo
```

**3. Get an address for mining/staking:**
```bash
./src/ammocoin-cli getnewaddress "Admin"
```

**4. Mine or stake to generate initial supply:**
```bash
# Enable staking if you have coins
./src/ammocoin-cli walletpassphrase "your_password" 99999999 true

# Or generate blocks manually (testnet/private network)
./src/ammocoin-cli generate 1000
```

**5. Verify balance:**
```bash
./src/ammocoin-cli getbalance
```

You need at least **218,707,052 AMMO** for top 61 distribution.

---

### Phase 2: Distribute to Top 61 Holders

**1. Test run first:**
```bash
python3 distribute-to-top-holders.py --dry-run
```

**2. Review the output - verify addresses and amounts**

**3. Run the actual distribution:**
```bash
python3 distribute-to-top-holders.py
```

**4. Monitor progress:**
- Script shows each transaction
- Pauses every 10 transactions
- Creates transaction log
- Shows final summary

**5. Verify completion:**
```bash
# Check transaction log
cat distribution-log-*.json | python3 -m json.tool

# Verify a few random addresses
./src/ammocoin-cli getreceivedbyaddress "ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL"
```

---

### Phase 3: Fund Migration Address

**Transfer migration fund amount to the migration address:**

```bash
./src/ammocoin-cli sendtoaddress "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs" 13690696.25046043
```

**Verify it arrived:**
```bash
./src/ammocoin-cli getreceivedbyaddress "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs"
```

**⚠️ CRITICAL: Back up the private key for this address!**

```bash
./src/ammocoin-cli dumpprivkey "Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs"
```

Store this private key securely - you'll need it to process claims.

---

### Phase 4: Process Migration Claims

**As users submit claims:**

**1. Check migration fund status:**
```bash
python3 verify-claim.py --stats
```

**2. Process each claim interactively:**
```bash
python3 verify-claim.py
```

**OR process in batch mode:**
```bash
python3 verify-claim.py \
  --address <v1.0_addr> \
  --signature <sig> \
  --message <msg> \
  --v1.1-address <new_addr> \
  --send
```

**3. Monitor processed claims:**
```bash
cat processed-claims.json | python3 -m json.tool
```

---

## Security Best Practices

### Private Key Security

✅ **Migration fund private key is CRITICAL**
- Back it up in multiple secure locations
- Encrypt backups
- Never share it
- Use hardware wallet if possible

### Transaction Safety

✅ **Always test first**
- Use `--dry-run` for top 61 distribution
- Verify signatures before sending claims
- Double-check addresses

✅ **Monitor the blockchain**
- Verify transactions confirm
- Check recipient balances
- Keep transaction logs

### Claim Verification

✅ **Never trust without signature**
- Always require message signature
- Verify signature matches address
- Check for duplicate claims

---

## Troubleshooting

### "Daemon is not responsive"

**Fix:**
```bash
cd ammocoin-apps-from-ammocoin
./src/ammocoind -daemon
# Wait 30 seconds
./src/ammocoin-cli getinfo
```

### "Insufficient balance"

**Fix:**
```bash
# Check balance
./src/ammocoin-cli getbalance

# Mine/stake more blocks
./src/ammocoin-cli generate 100

# Or wait for staking rewards
./src/ammocoin-cli getstakingstatus
```

### "Invalid signature"

**Causes:**
- User signed wrong message
- User used wrong address
- Signature copied incorrectly

**Fix:** Ask user to sign again with exact message.

### Distribution interrupted

**Resume from where it stopped:**
```bash
# Check log to see last completed holder number
cat distribution-log-*.json

# Resume from next holder (e.g., if stopped at 29)
python3 distribute-to-top-holders.py --start-from 29
```

### Transaction not confirming

**Check network:**
```bash
./src/ammocoin-cli getinfo
```

Look for:
- `connections` > 3 (network is alive)
- `blocks` increasing (chain is syncing/staking)

**If stuck:**
```bash
# Check mempool
./src/ammocoin-cli getmempoolinfo

# Check specific transaction
./src/ammocoin-cli gettransaction <txid>
```

---

## Expected Results

### Top 61 Distribution Success

```
📊 DISTRIBUTION SUMMARY
============================================================
Total holders:    61
Successful:       61 ✅
Failed:           0 ❌
Total sent:       218,707,052.20 AMMO
============================================================
```

### Migration Fund Statistics

```
📊 MIGRATION FUND STATISTICS
============================================================
Migration fund address: Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs

Total eligible addresses: 10,019
Total fund amount:        13,690,696.25046043 AMMO

Processed claims:         0
Processed amount:         0.00000000 AMMO

Remaining claims:         10,019
Remaining amount:         13,690,696.25046043 AMMO
============================================================
```

---

## Timeline Estimates

| Task | Time | Notes |
|------|------|-------|
| Top 61 dry run | 30 sec | Verify before real run |
| Top 61 distribution | 1-2 hours | 61 txs with pauses |
| Fund migration address | 5 min | Single transaction |
| Process each claim | 2-5 min | Including verification |
| Expected total claims | 20-50 | Out of 10,019 eligible |

**Realistic migration window:** 90 days

---

## Support Workflow

### User Claims Their Balance

**1. User contacts you with:**
- v1.0 address: `ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL`

**2. You verify eligibility:**
```bash
python3 verify-claim.py
# Enter their address
# System shows if eligible and amount
```

**3. Instruct user to sign message:**
```
Please sign this exact message with your v1.0 address:
"I claim my AMMOcoin v1.1.0 migration"

Send back:
- The signature
- Your new v1.1.0 address
```

**4. User sends you:**
- Signature: `H123abc...`
- v1.1.0 address: `ANewV11AddressHere`

**5. You process claim:**
```bash
python3 verify-claim.py \
  --address ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL \
  --signature H123abc... \
  --message "I claim my AMMOcoin v1.1.0 migration" \
  --v1.1-address ANewV11AddressHere \
  --send
```

**6. You send user the TXID for verification**

---

## Files Generated

| File | Purpose |
|------|---------|
| `distribution-log-*.json` | Top 61 distribution record |
| `processed-claims.json` | Migration fund claims log |
| `*.log` | Script execution logs |

**Keep all files for audit trail!**

---

## Next Steps

After distribution is complete:

1. ✅ Verify all 61 holders received funds
2. ✅ Verify migration fund is funded
3. ✅ Announce migration to users
4. ✅ Set up claim submission form/email
5. ✅ Process claims as they arrive
6. ✅ Monitor migration progress
7. ✅ Plan v1.0 network sunset after 90 days

---

**You're ready to deploy! 🚀**

See `PATH_A_DEPLOYMENT_PLAN.md` for complete deployment strategy.
