# AMMOcoin Manual Migration Plan - v1.0 to v1.1.0

**Migration Type:** On-chain disposal wallet transfer
**User Count:** ~20 users
**Status:** Active Migration Period
**Team Coordination Required:** Yes

---

## Overview

Since v1.1.0 is a **fresh blockchain** (not a continuation of v1.0), balances cannot transfer automatically. The AMMOcoin team facilitates migration through an **on-chain disposal wallet** process that creates immutable proof on both blockchains.

**Process:**
1. User emails transfermy@ammocoin.org with amount and v1.1.0 receiving address(es)
2. Team provides the v1.0 disposal wallet address
3. User sends v1.0 AMMO to the disposal wallet (on-chain transaction)
4. Team verifies the transfer on-chain, then sends equivalent v1.1.0 AMMO from the 250M distribution fund

**Why this approach:**
- On-chain proof on both blockchains — immutable and independently verifiable
- Amount is self-verifying from the v1.0 transaction itself
- Simple for users — just send coins (no CLI signing commands)
- Clean audit trail: every v1.0 disposal tx maps to a v1.1.0 distribution tx

---

## Migration Timeline

### Phase 1: Snapshot (COMPLETED)
**Snapshot Block:** 434,881 (December 22, 2025)
- Total addresses with balance: ~10,080
- Active users (>0 balance): ~20
- Total supply: 232,397,748 AMMO

### Phase 2: User Transfers (90 days)
**Transfer Period:** 90 days from network launch (January 3, 2026 — April 3, 2026)
- Users have 90 days to send v1.0 AMMO to the disposal wallet
- Any amount accepted — users can send all at once or in multiple transfers
- Users specify how to distribute the equivalent across v1.1.0 addresses

### Phase 3: Verification (Rolling)
- Team monitors disposal wallet for incoming v1.0 transactions
- Confirms on-chain receipt of each transfer
- Validates v1.1.0 receiving addresses

### Phase 4: Distribution (Rolling)
- Team sends equivalent v1.1.0 AMMO from the 250M distribution fund
- Distributed to user-specified v1.1.0 addresses in the requested proportions
- Both transaction IDs recorded in public migration ledger

---

## For Users: How to Transfer Your v1.0 Balance

### Prerequisites

**You need:**
1. Access to your v1.0 wallet (able to send transactions)
2. v1.1.0 wallet installed and running
3. Email access to contact transfermy@ammocoin.org

### Step 1: Install v1.1.0 and Generate Receiving Address(es)

```bash
# Download from GitHub release
# https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0

# Start v1.1.0 daemon
ammocoind -daemon

# Verify correct genesis
ammocoin-cli getblockhash 0
# MUST return: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2

# Generate receiving address(es)
ammocoin-cli getnewaddress "Migration"
# Example: Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n

# Back up v1.1.0 wallet
ammocoin-cli backupwallet ~/ammocoin-v1.1.0-wallet-backup.dat
```

Create multiple addresses if you want your balance split (e.g., staking, masternode collateral, savings).

### Step 2: Email the Team

Email **transfermy@ammocoin.org** with subject: **v1.0 Transfer Request**

Include:
- Amount you will send from your v1.0 wallet
- v1.1.0 receiving address(es) and how to distribute the amount

**Example — single address:**
```
I will be sending 50,000 AMMO from my v1.0 wallet to the disposal address.

Please send the full amount to:
  Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n — 50,000 AMMO
```

**Example — multiple addresses:**
```
I will be sending 60,000 AMMO from my v1.0 wallet to the disposal address.

Please distribute as follows:
  Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n — 40,000 AMMO (staking)
  Ah2mX9cL4sD1eW6hK9jB2nRvT3xYz7kQ2 — 10,000 AMMO (masternode collateral)
  Aj4pR8dN5tF2gH7iK3lM6oQ9sU1wX0yZ8 — 10,000 AMMO (savings)
```

Team will reply with the **v1.0 disposal wallet address**.

### Step 3: Send v1.0 AMMO to Disposal Wallet

```bash
# Send specific amount
ammocoin-cli sendtoaddress "DISPOSAL_WALLET_ADDRESS" 50000

# Or send entire balance (fee subtracted from amount)
BALANCE=$(ammocoin-cli getbalance)
ammocoin-cli sendtoaddress "DISPOSAL_WALLET_ADDRESS" $BALANCE "" "" true

# Save the transaction ID
ammocoin-cli listtransactions "*" 1
```

You can send in multiple transactions — each will be matched.

### Step 4: Receive v1.1.0 AMMO

Once the team confirms your v1.0 transfer on-chain (typically 24-48 hours):

```bash
# Check your v1.1.0 balance
ammocoin-cli getbalance

# View recent transactions
ammocoin-cli listtransactions "*" 10
```

Team will email confirmation with v1.1.0 transaction ID(s).

---

## For Team: Verification and Distribution Process

### Step 1: Receive Transfer Requests

When a user emails transfermy@ammocoin.org:
1. Log the request in the tracking spreadsheet
2. Validate all provided v1.1.0 addresses
3. Reply with the v1.0 disposal wallet address

```
Transfer ID | User Email | v1.0 Amount | v1.1.0 Addresses | Status | Notes
T-001 | user@email.com | 50,000 | Af7k... (50k) | Awaiting v1.0 tx | -
T-002 | user2@email.com | 60,000 | Af7k... (40k), Ah2m... (10k), Aj4p... (10k) | Awaiting v1.0 tx | Multi-addr
```

### Step 2: Monitor Disposal Wallet

```bash
# Check disposal wallet for incoming transactions
ammocoin-cli listtransactions "*" 50

# Get balance of disposal wallet
ammocoin-cli getbalance

# Check specific transaction details
ammocoin-cli gettransaction "TXID"
```

Match incoming transactions to pending transfer requests by amount and timing.

### Step 3: Verify On-Chain Receipt

For each incoming v1.0 transaction:
1. Confirm the transaction has sufficient confirmations (6+)
2. Record the v1.0 txid
3. Verify the amount matches the user's stated transfer amount

```bash
# Verify transaction confirmations
ammocoin-cli gettransaction "V1.0_TXID"
# Look for "confirmations" field >= 6
```

### Step 4: Distribute v1.1.0 AMMO

For each confirmed v1.0 transfer, send the equivalent from the distribution fund:

```bash
# Validate v1.1.0 receiving address
ammocoin-cli validateaddress "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n"

# Send to single address
ammocoin-cli sendtoaddress "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n" 50000.00000000 "Migration T-001"

# For multi-address distributions, send to each
ammocoin-cli sendtoaddress "Af7kQ2mN8pRvT3xYz9cL4sD1eW6hK9jB2n" 40000.00000000 "Migration T-002a"
ammocoin-cli sendtoaddress "Ah2mX9cL4sD1eW6hK9jB2nRvT3xYz7kQ2" 10000.00000000 "Migration T-002b"
ammocoin-cli sendtoaddress "Aj4pR8dN5tF2gH7iK3lM6oQ9sU1wX0yZ8" 10000.00000000 "Migration T-002c"

# Record all v1.1.0 txids
```

### Step 5: Track and Report

**Migration Ledger (public):**
```
Transfer ID | v1.0 TXID | v1.0 Amount | v1.1.0 TXID(s) | v1.1.0 Amount | Status | Date
T-001 | abc123...def | 50,000 | xyz789...ghi | 50,000 | Complete | 2026-01-20
T-002 | def456...abc | 60,000 | aaa..., bbb..., ccc... | 60,000 | Complete | 2026-01-21

Total Migrated: 232,397,748 AMMO
Total Transfers Processed: 18
Pending Transfers: 2
```

Email the user with:
- Confirmation of receipt
- v1.1.0 transaction ID(s)
- Amounts sent to each address

---

## Disposal Wallet Management

### Disposal Wallet Address
**v1.0 Address:** `TO_BE_ASSIGNED`

This is a team-controlled address on the v1.0 chain. All migrated v1.0 AMMO is sent here. The accumulated balance serves as a permanent on-chain record of total migrated funds.

### Distribution Fund
**v1.1.0 Address:** `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME` (genesis 250M AMMO)

```bash
# Check remaining distribution fund balance
ammocoin-cli getbalance
```

### Accounting
- v1.0 disposal wallet balance should always equal total v1.1.0 distributed amount
- Any discrepancy requires investigation
- Regular audits: compare disposal wallet received total with distribution fund spent total

---

## Security and Fraud Prevention

### Verification Safeguards

The disposal wallet approach has built-in fraud prevention:
- **On-chain proof:** User must actually own and send the v1.0 coins — no way to fake a blockchain transaction
- **Amount verification:** The v1.0 transaction amount is immutable — team sends exactly what was received
- **No replay attacks:** v1.0 and v1.1.0 are completely separate chains

### Red Flags to Watch For
- Requests to change v1.1.0 addresses after v1.0 transfer is sent (possible account compromise)
- Unusually large transfers without prior communication
- Multiple transfer requests from the same email with different v1.1.0 addresses

### Handling Edge Cases

**User sends wrong amount:**
- If they sent less than intended: they can send additional transfers
- If they sent more than intended: distribute the full amount received (the v1.0 tx is the source of truth)

**User wants to change v1.1.0 addresses:**
- Before v1.1.0 distribution: OK, update the request
- After v1.1.0 distribution: cannot be reversed — user must handle on v1.1.0 side

**Disputed transfers:**
- The v1.0 transaction is immutable proof of who sent the coins
- Only the sender (controller of the v1.0 private key) could have initiated the transfer

---

## User FAQs

### Q: How much can I transfer?
**A:** Any amount. You can send your entire v1.0 balance at once or split it across multiple transfers.

### Q: Can I split my balance across multiple v1.1.0 addresses?
**A:** Yes. In your email to transfermy@ammocoin.org, specify each v1.1.0 address and the amount to send to each.

### Q: How long does it take?
**A:** Once your v1.0 transfer confirms on-chain, the team typically processes the v1.1.0 distribution within 24-48 hours.

### Q: What if I have multiple v1.0 addresses?
**A:** Send from each address separately, or consolidate to one address first then send. Email the team with details for each transfer.

### Q: What if I lost access to my v1.0 wallet?
**A:** Unfortunately, without your v1.0 wallet you cannot send coins to the disposal wallet. There is no alternative method — the on-chain transfer is the proof of ownership.

### Q: Is there a deadline?
**A:** Yes, the migration period is 90 days (closing April 3, 2026). Late transfers may be considered case-by-case but are not guaranteed.

### Q: What happens to unclaimed balances?
**A:** After the migration period, remaining distribution fund balances will be returned to the community treasury.

---

## Contact and Support

### For Users

**Transfer Requests:**
- Email: transfermy@ammocoin.org
- Subject: "v1.0 Transfer Request"

**Get Help:**
- GitHub: https://github.com/everquin/AMMOcoin/issues
- Documentation: See [User Migration Guide](USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md)

### For Team

**Migration Coordination:**
- Primary contact: [Team lead]
- Disposal wallet manager: [Specify]
- Distribution wallet: `AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME`

---

## Timeline Summary

| Phase | Duration | Status |
|-------|----------|--------|
| Snapshot Taken | December 22, 2025 | Complete |
| v1.1.0 Launch | January 3, 2026 | Complete |
| Migration Period Opens | January 3, 2026 | Complete |
| Migration Period Closes | April 3, 2026 | Pending |
| Distribution Complete | May 2026 | Pending |

---

**Last Updated:** March 1, 2026
**Status:** Active Migration Plan
**Questions?** Contact team at transfermy@ammocoin.org
