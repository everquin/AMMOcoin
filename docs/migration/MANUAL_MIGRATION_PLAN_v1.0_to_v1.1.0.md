# AMMOcoin Manual Migration Plan - v1.0 to v1.1.0

**Migration Type:** Manual Balance Transfer
**User Count:** ~20 users
**Status:** Active Migration Period
**Team Coordination Required:** Yes

---

## Overview

Since v1.1.0 is a **fresh blockchain** (not a continuation of v1.0), balances cannot transfer automatically. However, the AMMOcoin team will **manually honor v1.0 balances** for legitimate holders.

**Process:**
1. Team takes snapshot of v1.0 blockchain
2. Users prove ownership of v1.0 addresses
3. Users provide v1.1.0 addresses
4. Team manually sends equivalent v1.1.0 AMMO

---

## Migration Timeline

### Phase 1: Snapshot (COMPLETED)
**Snapshot Block:** 434,881 (December 22, 2025)
- Total addresses with balance: ~10,080
- Active users (>0 balance): ~20
- Total supply: 232,397,748 AMMO

### Phase 2: User Claims (30 days)
**Claim Period:** 90 days from network launch
- Users have 30 days to submit claims
- Proof of ownership required
- Must provide v1.1.0 receiving address

### Phase 3: Verification (Rolling)
- Team verifies ownership claims
- Checks v1.0 blockchain for actual balances
- Approves legitimate claims

### Phase 4: Distribution (Rolling)
- Team distributes v1.1.0 AMMO to verified claims
- Proportional to snapshot balances
- Tracked in public ledger

---

## For Users: How to Claim Your v1.0 Balance

### Prerequisites

**You need:**
1. Access to your v1.0 wallet with private keys
2. v1.1.0 wallet installed and running
3. Ability to sign messages (proves ownership)

### Step 1: Take Snapshot of Your v1.0 Balance

#### Run v1.0 Node with Snapshot Data
```bash
# Start v1.0 daemon (if not running)
/path/to/v1.0/ammocoind -datadir=$HOME/.ammocoin-v1.0 -daemon

# Wait for sync to complete
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 getinfo

# Check you're at or past snapshot block
# Snapshot block: 434,881
```

#### Get Your Balance at Snapshot
```bash
# List all your addresses with balances
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 listaddressgroupings

# Get balance for specific address
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 getreceivedbyaddress YOUR_ADDRESS 0
```

#### Record Your Information
Create a file `my-v10-claim.txt`:
```
v1.0 Address: AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME
Balance at Block 434,881: 50000.12345678 AMMO
Transaction History: (optional, helps verification)
  - tx1: abc123...
  - tx2: def456...
```

### Step 2: Install and Set Up v1.1.0

#### Download v1.1.0
```bash
# Download from GitHub release
# https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0-genesis-final

# For macOS ARM64:
curl -L -O https://github.com/everquin/AMMOcoin/releases/download/v1.1.0-genesis-final/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz

# Verify checksum
shasum -a 256 AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
# Should match: 8e37a2349b556c78aa8d98f56cc7849716d0f857a055646fd10a60bb024c9ab1

# Extract
tar -xzf AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
cd AMMOcoin-v1.1.0-macOS-ARM64/
```

#### Start v1.1.0 Node
```bash
# Delete any old v1.1.0 data (if exists)
rm -rf ~/.ammocoin

# Start v1.1.0 daemon
./ammocoind -daemon

# Wait for startup
sleep 10

# Verify correct genesis
./ammocoin-cli getblockhash 0
# MUST return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
```

#### Generate New v1.1.0 Receiving Address
```bash
# Generate a new address to receive your migrated AMMO
./ammocoin-cli getnewaddress "Migration Claim"

# Example output: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n

# IMPORTANT: Back up this address and your v1.1.0 wallet!
./ammocoin-cli backupwallet ~/ammocoin-v1.1.0-wallet-backup.dat
```

### Step 3: Prove Ownership of v1.0 Address

This is CRITICAL - you must prove you own the v1.0 address.

#### Sign a Message with Your v1.0 Address
```bash
# Create a unique message including your v1.1.0 address
MESSAGE="I claim v1.0 balance for migration to v1.1.0 address: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n - Date: $(date -u +%Y-%m-%d)"

# Sign with v1.0 wallet
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 signmessage "AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME" "$MESSAGE"

# Returns signature like:
# INsQ7k9R3m... (long base64 string)
```

#### Save Your Claim Package
Create `my-claim-package.txt`:
```
=== AMMOcoin v1.0 to v1.1.0 Migration Claim ===

v1.0 Address: AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME
v1.0 Balance at Block 434,881: 50000.12345678 AMMO

v1.1.0 Receiving Address: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n

Proof of Ownership (Signed Message):
Message: "I claim v1.0 balance for migration to v1.1.0 address: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n - Date: 2026-01-15"
Signature: INsQ7k9R3m...

Contact Email: support@ammocoin.com (for verification)
Submission Date: 2026-01-15

Optional: Transaction IDs showing balance history
- abc123...
- def456...
```

### Step 4: Submit Claim to Team

**Submit your claim package to:**
- **Email:** migration@ammocoin.org (or team-specified contact)
- **Subject:** "v1.0 to v1.1.0 Migration Claim - [Your v1.0 Address]"
- **Attach:** `my-claim-package.txt`

**Or submit via:**
- GitHub issue (if public migration tracking)
- Discord/Telegram (if community channel exists)
- Team-specified claim form

### Step 5: Wait for Verification

**Team will:**
1. Verify signature is valid for v1.0 address
2. Check v1.0 blockchain for actual balance at block 434,881
3. Confirm v1.1.0 address is valid
4. Approve or request additional information

**Timeline:**
- Initial review: 1-3 business days
- Additional verification (if needed): 2-5 days
- Distribution after approval: 1-7 days

### Step 6: Receive v1.1.0 AMMO

Once approved, team will send v1.1.0 AMMO to your receiving address:

```bash
# Check your v1.1.0 balance
./ammocoin-cli getbalance

# List recent transactions
./ammocoin-cli listtransactions "*" 10

# Verify you received the correct amount
./ammocoin-cli getreceivedbyaddress "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n"
```

**What you should receive:**
- Amount matching your v1.0 snapshot balance
- Sent from team distribution address
- Transaction ID for your records

---

## For Large Holders (Special Considerations)

If you hold **>10,000 AMMO**, team may require additional verification:

### Enhanced Verification Options

#### Option 1: Multiple Signed Messages
```bash
# Sign multiple messages with different timestamps
MESSAGE1="Migration claim - Part 1 - $(date -u +%Y-%m-%d)"
MESSAGE2="Migration claim - Part 2 - $(date -u +%Y-%m-%d)"

/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 signmessage "YOUR_ADDRESS" "$MESSAGE1"
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 signmessage "YOUR_ADDRESS" "$MESSAGE2"
```

#### Option 2: Small Test Transaction
```bash
# Send small amount from v1.0 address to team verification address
# This proves you control the private key

/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 sendtoaddress "TEAM_VERIFICATION_ADDRESS" 1.0

# Include transaction ID in claim
```

#### Option 3: Video Call Verification
- Schedule call with team
- Demonstrate wallet control in real-time
- Sign message during call

---

## For Team: Verification and Distribution Process

### Step 1: Receive and Log Claims

Create tracking spreadsheet:
```
Claim ID | v1.0 Address | v1.0 Balance | v1.1.0 Address | Signature | Status | Notes
001 | Ae3M... | 50000.12 | Af7k... | INsQ... | Pending | -
002 | Ab8X... | 125000.00 | Ah2m... | JOtR... | Pending | Large holder
...
```

### Step 2: Verify Each Claim

#### Verify Signature
```bash
# Use v1.0 CLI to verify signature
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 verifymessage \
  "AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME" \
  "INsQ7k9R3m..." \
  "I claim v1.0 balance for migration to v1.1.0 address: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n - Date: 2026-01-15"

# Returns: true (valid) or false (invalid)
```

#### Verify Balance on v1.0 Blockchain
```bash
# Check balance at snapshot block 434,881
# Use v1.0 node synced to at least that height

/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 getreceivedbyaddress "AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME" 0

# Compare to claimed amount
```

#### Verify v1.1.0 Address Valid
```bash
# Check v1.1.0 address is valid
ammocoin-cli validateaddress "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n"

# Returns: {"isvalid": true, ...}
```

### Step 3: Approve or Reject

**Approve if:**
- ✅ Signature is valid
- ✅ v1.0 balance matches claim (within 0.1%)
- ✅ v1.1.0 address is valid
- ✅ No red flags (duplicate claims, fraud indicators)

**Reject if:**
- ❌ Invalid signature
- ❌ Balance mismatch
- ❌ Invalid v1.1.0 address
- ❌ Suspicious activity

**Request more info if:**
- ⚠️ Large holder (>10k AMMO)
- ⚠️ Multiple addresses claimed by same person
- ⚠️ Unusual transaction history

### Step 4: Distribute v1.1.0 AMMO

#### Prepare Distribution Wallet

The team will need v1.1.0 AMMO to distribute. Options:

**Option A: Use Genesis Wallet**
```bash
# Import paper wallet private key (has genesis 250M AMMO)

# Verify balance
ammocoin-cli getbalance
# Should show: 1000.00000000
```

**Option B: Mine Additional Blocks**
```bash
# Mine blocks to create distribution supply
# (Requires mining setup)

ammocoin-cli generate 1000  # If regtest/testnet
# Or actual mining on mainnet
```

**Option C: Create Distribution Premine**
*Note: Would require code changes and rebuilding - not recommended at this stage*

#### Send to Verified Claims

For each approved claim:
```bash
# Send exact amount to user's v1.1.0 address
ammocoin-cli sendtoaddress "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n" 50000.12345678 "Migration v1.0 Claim 001"

# Record transaction ID
# Update spreadsheet with TXID and status: Completed
```

### Step 5: Track and Report

**Create public ledger:**
```
Migration Transaction Ledger

Claim ID | v1.0 Address | Amount | v1.1.0 TXID | Status | Date
001 | Ae3M...1EKs | 50000.12 | abc123...def | Completed | 2026-01-20
002 | Ab8X...2Fm | 125000.00 | def456...ghi | Completed | 2026-01-21
...

Total Migrated: 232,397,748 AMMO
Total Claims Processed: 18
Pending Claims: 2
```

---

## Migration Supply Management

### Total Supply Considerations

**v1.0 Snapshot:**
- Total supply: 232,397,748 AMMO
- Active holder addresses: ~20
- Distribution needed: 232M+ AMMO

### Creating Distribution Supply

#### Scenario 1: Use Genesis + Mining
```
Genesis reward: 1,000 AMMO
Mining for 30 days: ~X AMMO (depends on block time/rewards)
Total available: 1,000 + X AMMO
```

**Process:**
1. Use genesis 250M AMMO for small claims first
2. Mine blocks to create additional supply
3. Distribute to larger claims as supply builds

#### Scenario 2: Staged Distribution
```
Week 1: Distribute first 1,000 AMMO to smallest claims
Week 2-4: Mine and distribute to medium claims
Month 2: Complete large holder distributions
```

#### Scenario 3: Proportional Initial Distribution
If total supply < total claims:
```
Distribution % = Available Supply / Total Claims
Each user gets: Claimed Amount * Distribution %
Remaining distributed as more is mined
```

**Example:**
- Available: 10,000 AMMO mined
- Total claims: 232,397,748 AMMO
- Distribution: 0.0043% initially
- User claiming 50,000 gets: 50,000 * 0.0043% = 2.15 AMMO
- Rest comes later as more is mined

---

## Security and Fraud Prevention

### Red Flags to Watch For

**Suspicious Claims:**
- Same signature used for multiple addresses
- Recently moved v1.0 balances (after snapshot)
- Addresses with no transaction history before snapshot
- Duplicate v1.1.0 receiving addresses
- Claims for addresses on exchange wallets

### Verification Steps for Large Claims

For claims >10,000 AMMO:
1. ✅ Verify signature (required)
2. ✅ Check transaction history on v1.0 blockchain
3. ✅ Confirm address had balance before snapshot
4. ✅ Request additional proof (second signature, test tx, or video call)
5. ✅ Wait 48 hours cooling-off period
6. ✅ Distribute in tranches (25% per week)

### Handling Disputed Claims

If multiple people claim same v1.0 address:
1. Request additional proof from all claimants
2. Check which claim has valid signature
3. If both valid, investigate for wallet theft
4. Hold distribution pending resolution
5. May require manual investigation

---

## User FAQs

### Q: Will I receive exactly my v1.0 balance?
**A:** Yes, if your claim is verified, you'll receive the exact amount you had at block 434,881.

### Q: How long does migration take?
**A:** Verification typically takes 1-3 days. Distribution depends on available supply (may be staged).

### Q: What if I have multiple v1.0 addresses?
**A:** Submit separate claims for each address, or include all in one claim with signatures for each.

### Q: Can I use the same address for v1.1.0?
**A:** No. v1.1.0 is a fresh blockchain. You must generate a new v1.1.0 address. (However, you can import your v1.0 private keys if you want to reuse addresses conceptually - just know the balances won't automatically be there.)

### Q: What if I lost access to my v1.0 wallet?
**A:** Unfortunately, without private keys you cannot prove ownership. No exception can be made.

### Q: Is there a deadline?
**A:** Yes, claim period is 30 days. Late claims may be considered case-by-case but not guaranteed.

### Q: What happens to unclaimed balances?
**A:** After claim period, unclaimed balances may be burned or returned to development fund. Team will announce policy.

---

## Contact and Support

### For Users

**Submit Claims:**
- Email: migration@ammocoin.org
- Subject: "Migration Claim - [Your v1.0 Address]"

**Get Help:**
- Discord/Telegram: [Community channels]
- GitHub: https://github.com/everquin/AMMOcoin/issues
- Documentation: See repository guides

### For Team

**Migration Coordination:**
- Primary contact: [Team lead]
- Verification team: [List members]
- Distribution wallet: [Specify address/multisig]

---

## Timeline Summary

| Phase | Duration | Status |
|-------|----------|--------|
| Snapshot Taken | December 22, 2025 | ✅ Complete |
| v1.1.0 Launch | December 30, 2025 | ✅ Complete |
| Claim Period Opens | January 1, 2026 | ⏳ Pending |
| Claim Period Closes | January 31, 2026 | ⏳ Pending |
| Distribution Complete | February 28, 2026 | ⏳ Pending |

---

## Appendix: Batch Claim Processing Script

For team use - verify multiple claims efficiently:

```bash
#!/bin/bash
# verify-claims.sh

CLAIMS_FILE="claims-list.csv"  # Format: v10addr,v11addr,amount,signature,message

while IFS=, read -r v10addr v11addr amount signature message; do
    echo "Verifying claim for $v10addr..."

    # Verify signature
    VALID=$(/path/to/v1.0/ammocoin-cli verifymessage "$v10addr" "$signature" "$message")

    if [ "$VALID" = "true" ]; then
        # Check v1.0 balance
        BALANCE=$(/path/to/v1.0/ammocoin-cli getreceivedbyaddress "$v10addr" 0)

        echo "  Signature: ✅ VALID"
        echo "  v1.0 Balance: $BALANCE AMMO"
        echo "  Claimed: $amount AMMO"

        # Compare amounts (allowing 0.1% difference for rounding)
        # Add logic here

    else
        echo "  Signature: ❌ INVALID"
    fi

    echo "---"
done < "$CLAIMS_FILE"
```

---

**Last Updated:** December 30, 2025
**Status:** Active Migration Plan
**Questions?** Contact team at migration@ammocoin.org
