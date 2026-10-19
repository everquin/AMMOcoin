# AMMOcoin v1.0 → v1.1.0 Migration Scripts

Python scripts for migrating balances from AMMOcoin v1.0 to v1.1.0.

## Scripts

### Balance Snapshot Tools

**v1.0-snapshot-tool.py** - Extract all balances from v1.0 blockchain
- Connects to v1.0 RPC node
- Scans entire blockchain for balances
- Outputs: `v1.0-complete-balance-snapshot.json`

**scan-all-balances.py** - Alternative balance scanner
- Similar to v1.0-snapshot-tool.py
- Different scanning methodology

**v1.0-blockchain-scanner.py** - Full blockchain scanner
- Comprehensive blockchain analysis
- Balance extraction and validation

### Distribution Tools

**distribute-to-top-holders.py** - Distribute genesis funds to top holders
- Reads balance snapshot
- Creates genesis premine distribution
- Used for Option 2.5 (team distribution premine)

### Verification Tools

**verify-migration.py** - Verify migration accuracy
```bash
python3 scripts/migration/verify-migration.py docs/migration/data/v1.0-balance-snapshot-EXAMPLE.json
```

**verify-claim.py** - Verify individual user claims
- Validates user signatures
- Confirms v1.0 ownership
- Authorizes v1.1.0 distribution

## Data Files

Migration data files are located in `docs/migration/data/`:
- `v1.0-complete-balance-snapshot.json` - Full production snapshot
- `v1.0-balance-snapshot-EXAMPLE.json` - Example snapshot for testing
- `DISTRIBUTION_TRACKING_TEMPLATE.csv` - Template for tracking claims
- `migration-statistics.txt` - Migration statistics report
- `v1.1.0-migration-summary.txt` - Migration summary

## Usage

v1.0 → v1.1 airdrop payout (AMMO-D-2026-10-18-12/-13; see docs/compliance/AIRDROPS.md):

1. `build-pledges.py --check` — the pledge list matches the snapshot.
2. `verify-pledges.py signatures.csv --cli "<ammocoin-cli -datadir=…>"` — all 61 signed.
3. `build-payout-holders.py signatures.csv --cli … --output payout-holders.json`.
4. `migration-prepare.py --holders payout-holders.json --fan-out fanout-addresses.txt --change-address <reserve change>` —
   ONE transaction splitting the reserve into one UTXO per batch (fan-out addresses: one per batch, generated on the
   offline signer and imported watch-only). Sign offline, broadcast, wait for confirmations.
5. `migration-prepare.py --holders payout-holders.json --change-address <reserve change>` — the payout batches, each
   spending its own fan-out UTXO; balances over 10M are split into ≤10M outputs in separate transactions.
6. `migration-sign-offline.py`, then `migration-broadcast.py`, then `verify-migration.py`.

Tests: `python3 scripts/migration/test_migration_prepare.py`.

Older detail: `docs/MIGRATION_COMPLETE_SUMMARY.md`.

---

**Status**: Migration tools complete and tested
**Last Updated**: January 3, 2026
