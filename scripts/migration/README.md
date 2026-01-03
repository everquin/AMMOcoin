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

See `docs/MIGRATION_COMPLETE_SUMMARY.md` for detailed usage instructions.

---

**Status**: Migration tools complete and tested
**Last Updated**: January 3, 2026
