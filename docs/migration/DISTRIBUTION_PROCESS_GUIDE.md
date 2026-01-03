# AMMOcoin v1.1.0 Distribution Process Guide

**Purpose:** Team manual distribution of 250M AMMO premine to verified v1.0 users
**Distribution Fund:** 250,000,000 AMMO at address AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME
**Total to Distribute:** ~232,397,748 AMMO (based on v1.0 snapshot)
**Buffer:** ~17,602,252 AMMO for adjustments/late claims

---

## Overview

The v1.1.0 genesis block contains 250M AMMO in a single address controlled by the team's paper wallet. Users submit claims proving ownership of v1.0 addresses, and the team verifies and distributes the appropriate amounts.

---

## Prerequisites

### Required Access
- ✅ Paper wallet private key for AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME
- ✅ Running v1.1.0 node with wallet
- ✅ Running v1.0 node (for verification)
- ✅ v1.0 snapshot data (balances at block 434,881)

### Import Paper Wallet to v1.1.0 Node

```bash
# Import the paper wallet private key
ammocoin-cli importprivkey "PAPER_WALLET_PRIVKEY_HERE" "Distribution Fund" false

# Verify balance
ammocoin-cli getbalance
# Should show: 250000000.00000000

# Check specific account
ammocoin-cli getbalance "Distribution Fund"
# Should show: 250000000.00000000
```

---

## User Claim Submission Process

### What Users Must Provide

1. **v1.0 Address** - The address that held AMMO on v1.0 blockchain
2. **v1.1.0 Address** - Where they want to receive their v1.1.0 AMMO
3. **Signed Message** - Cryptographic proof they control the v1.0 address
4. **Date** - When claim was submitted

### Claim Message Format

**Standard message template:**
```
I claim my AMMOcoin v1.0 balance for migration to v1.1.0.
v1.0 Address: [THEIR_V1.0_ADDRESS]
v1.1.0 Address: [THEIR_V1.1.0_ADDRESS]
Date: [YYYY-MM-DD]
```

**Example:**
```
I claim my AMMOcoin v1.0 balance for migration to v1.1.0.
v1.0 Address: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n
v1.1.0 Address: Ag8Xp4mR7fN2qK5tW8hL9vD6eY3cJ1nM4s
Date: 2025-12-30
```

### How Users Create Signature

**Using v1.0 wallet:**
```bash
# User runs this with their v1.0 daemon
/path/to/v1.0/ammocoin-cli signmessage \
  "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n" \
  "I claim my AMMOcoin v1.0 balance for migration to v1.1.0.
v1.0 Address: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n
v1.1.0 Address: Ag8Xp4mR7fN2qK5tW8hL9vD6eY3cJ1nM4s
Date: 2025-12-30"
```

**Returns signature:**
```
H8xK2mN9pRvT3xYz9cL4sD1eW6hK9jB2nAf7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n==
```

---

## Team Verification Process

### Step 1: Receive Claim

Log claim in `DISTRIBUTION_TRACKING_TEMPLATE.csv`:
- Claim ID (sequential)
- Date submitted
- v1.0 address
- v1.1.0 address
- Signature
- Status: "Pending"

### Step 2: Verify Signature

**Using v1.0 daemon:**
```bash
/path/to/v1.0/ammocoin-cli verifymessage \
  "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n" \
  "H8xK2mN9pRvT3xYz9cL4sD1eW6hK9jB2nAf7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n==" \
  "I claim my AMMOcoin v1.0 balance for migration to v1.1.0.
v1.0 Address: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n
v1.1.0 Address: Ag8Xp4mR7fN2qK5tW8hL9vD6eY3cJ1nM4s
Date: 2025-12-30"
```

**Expected result:**
```
true    ← Valid signature, user controls this address
false   ← Invalid signature, REJECT claim
```

### Step 3: Look Up v1.0 Balance

**Check v1.0 snapshot data:**

Option A: Query v1.0 node at block 434,881
```bash
# Must use v1.0 node synced to at least block 434,881
/path/to/v1.0/ammocoin-cli getreceivedbyaddress "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n" 1
```

Option B: Check pre-generated snapshot CSV
```csv
v1.0 Address,Balance at Block 434881
Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n,50000.00000000
...
```

**Record balance in tracking spreadsheet.**

### Step 4: Validate v1.1.0 Address

**Using v1.1.0 daemon:**
```bash
ammocoin-cli validateaddress "Ag8Xp4mR7fN2qK5tW8hL9vD6eY3cJ1nM4s"
```

**Check output:**
```json
{
  "isvalid": true,
  "address": "Ag8Xp4mR7fN2qK5tW8hL9vD6eY3cJ1nM4s",
  ...
}
```

If `isvalid: false`, **REJECT** and ask user for correct address.

### Step 5: Distribute Funds

**Send from distribution fund:**
```bash
ammocoin-cli sendtoaddress \
  "Ag8Xp4mR7fN2qK5tW8hL9vD6eY3cJ1nM4s" \
  50000.00000000 \
  "v1.0 migration claim - verified"
```

**Returns transaction hash:**
```
abc123def456789...
```

### Step 6: Update Tracking

In `DISTRIBUTION_TRACKING_TEMPLATE.csv`:
- Amount Distributed: 50000.00000000
- TX Hash: abc123def456789...
- Date Distributed: 2025-12-30
- Status: "Complete"

---

## Verification Checklist (Per Claim)

Before distributing, verify:

- [ ] Signature is valid (verifymessage returns `true`)
- [ ] v1.0 address had balance at block 434,881
- [ ] v1.1.0 address is valid (validateaddress returns `isvalid: true`)
- [ ] Amount matches snapshot balance
- [ ] No duplicate claim for this v1.0 address
- [ ] Claim is recorded in tracking spreadsheet

**If ANY checkbox fails: DO NOT DISTRIBUTE**

---

## Common Scenarios

### Scenario 1: User Has Multiple v1.0 Addresses

**Solution:** User must submit separate claims for each address with separate signatures.

**Example:**
```
Claim 1:
- v1.0: Af7kQ2... (50,000 AMMO)
- Signature for Af7kQ2...
- v1.1.0: Ag8Xp4... (destination)

Claim 2:
- v1.0: Ab8Xp4... (125,000 AMMO)
- Signature for Ab8Xp4...
- v1.1.0: Ag8Xp4... (same destination OK)

Total distributed to Ag8Xp4...: 175,000 AMMO
```

### Scenario 2: User Lost v1.0 Private Key

**Solution:** Cannot verify ownership. **REJECT** claim.

**Reason:** Without private key, cannot sign message. No signature = no proof of ownership.

**Possible exception:** If user can provide other proof (transaction history, communication records), team may consider manual review on case-by-case basis.

### Scenario 3: User Wants to Split Distribution

**Example:** User has 50,000 AMMO but wants:
- 30,000 to address A
- 20,000 to address B

**Solution:** Honor request if signature is valid.

**Process:**
```bash
# Distribution 1
ammocoin-cli sendtoaddress "ADDRESS_A" 30000.00000000 "v1.0 claim - partial 1/2"

# Distribution 2
ammocoin-cli sendtoaddress "ADDRESS_B" 20000.00000000 "v1.0 claim - partial 2/2"
```

Record both transactions in tracking spreadsheet.

### Scenario 4: Disputed Balance Amount

**User claims:** 100,000 AMMO
**Snapshot shows:** 75,000 AMMO

**Solution:** Snapshot is authoritative. Distribute 75,000 AMMO.

**If user disputes:**
1. Ask user to provide v1.0 transaction proof
2. Re-verify snapshot at block 434,881
3. If snapshot is correct, explain to user
4. If snapshot is wrong, correct and distribute proper amount

### Scenario 5: Late Claim (After Initial Distribution Period)

**Solution:** Accept late claims if:
- Valid signature
- Funds remaining in distribution pool
- User provides valid reason for delay (optional)

**Track separately:** Mark as "Late Claim" in Notes column.

---

## Security Measures

### Signature Verification

**CRITICAL:** ALWAYS verify signatures using v1.0 daemon.

**DO NOT:**
- Accept unsigned claims
- Trust user-provided balances without verification
- Skip signature check "just this once"

**WHY:** Anyone can claim any v1.0 address. Only the private key holder can create a valid signature.

### Duplicate Prevention

**Before distributing, check:**
```bash
# Search tracking spreadsheet for v1.0 address
grep "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n" DISTRIBUTION_TRACKING_TEMPLATE.csv
```

**If found and status is "Complete":**
- This address already claimed
- **REJECT** duplicate claim
- Inform user they already received distribution

### Private Key Security

**Distribution fund private key:**
- Keep secure, offline when not distributing
- Only import to node when actively processing claims
- Use encrypted backup
- Consider using separate distribution node (not public-facing)

---

## Distribution Fund Monitoring

### Check Remaining Balance

```bash
# Total balance in distribution account
ammocoin-cli getbalance "Distribution Fund"
```

### Calculate Distributed So Far

```bash
# Sum all "Amount Distributed" in tracking spreadsheet
# Or use RPC:
ammocoin-cli listtransactions "Distribution Fund" 1000 | grep -A5 "category.*send"
```

### Running Totals

| Metric | Amount |
|--------|--------|
| Initial fund | 250,000,000 AMMO |
| Total claimed (snapshot) | 232,397,748 AMMO |
| Distributed so far | [Track in spreadsheet] |
| Remaining | [Check wallet balance] |
| Unclaimed | [Calculate] |

---

## Workflow Summary

```
1. User submits claim
   ↓
2. Team logs in tracking spreadsheet
   ↓
3. Team verifies signature (v1.0 daemon)
   ↓
4. Team checks v1.0 balance (snapshot)
   ↓
5. Team validates v1.1.0 address
   ↓
6. Team sends distribution (v1.1.0 daemon)
   ↓
7. Team updates tracking spreadsheet
   ↓
8. (Optional) Team notifies user of completion
```

**Average time per claim:** 5-10 minutes
**For 20 users:** ~2-4 hours total processing time

---

## Troubleshooting

### Issue: Signature Verification Fails

**Check:**
- Message format exactly matches (including line breaks)
- v1.0 address is correct
- Signature wasn't truncated/modified
- Using v1.0 daemon, not v1.1.0

**Solution:** Ask user to re-sign with exact message format.

### Issue: v1.1.0 Address Invalid

**Error:** `validateaddress` returns `isvalid: false`

**Cause:** Wrong address format, typo, or wrong network

**Solution:** Ask user to:
1. Generate new address from v1.1.0 wallet
2. Double-check for typos
3. Ensure it's a v1.1.0 address (starts with 'A')

### Issue: Transaction Fails

**Error:** `Insufficient funds` despite 250M balance

**Cause:** Funds not confirmed or wallet issue

**Check:**
```bash
ammocoin-cli getbalance "Distribution Fund" 0  # Unconfirmed
ammocoin-cli getbalance "Distribution Fund" 1  # Confirmed
```

**Solution:** Wait for confirmations or restart daemon.

---

## Record Keeping

### Required Records

1. **DISTRIBUTION_TRACKING_TEMPLATE.csv** - Master tracking spreadsheet
2. **Claim submissions** - Original emails/messages from users
3. **Signatures** - All signed messages
4. **Transaction hashes** - All distribution TXs
5. **Balance snapshot** - v1.0 balances at block 434,881

### Audit Trail

Every distribution must have:
- Who: User's v1.0 address
- What: Amount distributed
- When: Date
- Where: v1.1.0 destination address
- Proof: Signature + TX hash

This allows complete auditability and dispute resolution.

---

## Timeline Recommendations

### Week 1: Announcement
- Announce distribution process to community
- Provide claim submission instructions
- Set submission deadline (e.g., 30 days)

### Weeks 2-4: Claim Collection
- Accept and log claims
- Send confirmations to users
- Answer questions

### Week 5: Verification & Distribution
- Process all claims
- Verify signatures
- Distribute funds
- Update tracking

### Week 6+: Late Claims
- Accept late claims on case-by-case basis
- Process as they arrive

---

## Final Steps

### When All Claims Processed

**Calculate totals:**
```bash
# Check remaining balance
ammocoin-cli getbalance "Distribution Fund"
```

**Options for remaining funds:**
1. **Reserve for late claims** - Keep in distribution fund
2. **Team allocation** - Move to team wallet
3. **Burn** - Send to unspendable address
4. **Community decision** - Let users vote

**Document final status:**
- Total claims: [X]
- Total distributed: [Y] AMMO
- Remaining: [Z] AMMO
- Status: Complete

---

## Support Resources

### v1.0 Daemon Commands
```bash
# Start v1.0 node
/path/to/v1.0/ammocoind -datadir=$HOME/.ammocoin-v1.0 -daemon

# Verify message
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 verifymessage "ADDRESS" "SIGNATURE" "MESSAGE"

# Check balance
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 getreceivedbyaddress "ADDRESS"

# Stop v1.0 node
/path/to/v1.0/ammocoin-cli -datadir=$HOME/.ammocoin-v1.0 stop
```

### v1.1.0 Daemon Commands
```bash
# Check distribution fund balance
ammocoin-cli getbalance "Distribution Fund"

# Validate address
ammocoin-cli validateaddress "ADDRESS"

# Send distribution
ammocoin-cli sendtoaddress "ADDRESS" AMOUNT "comment"

# List recent transactions
ammocoin-cli listtransactions "Distribution Fund" 100

# Get transaction details
ammocoin-cli gettransaction "TXHASH"
```

---

**Distribution Process Version:** 1.0
**Last Updated:** December 30, 2025
**Compatible with:** AMMOcoin v1.1.0 (250M Distribution Premine)
