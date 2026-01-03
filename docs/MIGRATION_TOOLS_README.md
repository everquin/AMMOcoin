# AMMOcoin v1.0 → v1.1.0 Migration Tools

## Overview

This directory contains automated tools to migrate AMMOcoin from v1.0 to v1.1.0 using the balance snapshot method. Due to fundamental transaction encoding differences between v1.0 (PIVX 3.x) and v1.1.0 (PIVX 5.x), a direct blockchain upgrade is not possible. Instead, we perform a balance snapshot migration where all v1.0 balances are preserved in a new v1.1.0 genesis block.

**Impact:**
- ✅ All user funds preserved (exact balances maintained)
- ✅ Same private keys work in v1.1.0
- ✅ Clean, modern codebase based on latest PIVX
- ❌ Transaction history not preserved
- ❌ One-time migration event (cannot revert)

---

## Migration Tools

### 1. v1.0-snapshot-tool.py

**Purpose:** Extract all address balances from v1.0 blockchain

**Features:**
- Connects to v1.0 node via RPC
- Extracts all UTXOs and calculates balances
- Generates snapshot JSON with metadata
- No external dependencies (uses Python stdlib)

**Usage:**
```bash
# 1. Update RPC credentials in the script
nano v1.0-snapshot-tool.py
# Edit: V1_RPC_USER and V1_RPC_PASSWORD

# 2. Run the snapshot tool
python3 v1.0-snapshot-tool.py

# Output: v1.0-balance-snapshot.json
```

**Requirements:**
- Access to v1.0 node RPC (node1.ammocoin.org:37020)
- Valid RPC credentials with wallet access
- Python 3.6+

**Output Format:**
```json
{
  "snapshot_info": {
    "timestamp": "2025-12-01T12:00:00",
    "block_height": 450000,
    "block_hash": "0x...",
    "network": "mainnet",
    "total_addresses": 20,
    "total_supply": "XXX.XXXXXXXX"
  },
  "balances": {
    "Aaddress1...": "1000000.00000000",
    "Aaddress2...": "500000.00000000",
    ...
  }
}
```

---

### 2. v1.1.0-genesis-generator.py

**Purpose:** Generate C++ code for v1.1.0 genesis block with pre-allocated balances

**Features:**
- Reads snapshot JSON
- Generates production-ready C++ code
- Creates balance summary report
- Includes genesis mining instructions

**Usage:**
```bash
# Generate genesis code from snapshot
python3 v1.1.0-genesis-generator.py v1.0-balance-snapshot.json

# Outputs:
# - v1.1.0-genesis-code.cpp (C++ code for chainparams.cpp)
# - v1.1.0-migration-summary.txt (human-readable summary)
```

**Generated Code Features:**
- Pre-allocates all v1.0 balances
- Sorted by balance (largest first)
- Well-commented with addresses and amounts
- Includes genesis mining template
- Ready to insert into chainparams.cpp

---

## Complete Migration Workflow

### Phase 1: Snapshot v1.0 Balances

**Step 1:** Coordinate with users
```
Announce snapshot block height in advance
Recommended: Choose block height 1-2 weeks in future
Example: "Snapshot will be taken at block 500,000"
```

**Step 2:** Configure snapshot tool
```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin
nano v1.0-snapshot-tool.py

# Update these values:
V1_RPC_USER = "actual_rpc_username"
V1_RPC_PASSWORD = "actual_rpc_password"
```

**Step 3:** Wait for snapshot block
```bash
# Monitor v1.0 blockchain
./ammocoin-cli-v1.0 getblockchaininfo

# When snapshot block is reached, take snapshot
python3 v1.0-snapshot-tool.py
```

**Step 4:** Verify snapshot
```bash
# Review the snapshot file
cat v1.0-balance-snapshot.json | python3 -m json.tool

# Verify:
# - Total addresses matches expected (~20)
# - Total supply matches expected
# - All known large holders are included
# - Balances look correct
```

---

### Phase 2: Generate v1.1.0 Genesis

**Step 1:** Generate genesis code
```bash
python3 v1.1.0-genesis-generator.py v1.0-balance-snapshot.json

# Review generated files:
cat v1.1.0-migration-summary.txt
cat v1.1.0-genesis-code.cpp
```

**Step 2:** Update chainparams.cpp
```bash
cd source/src
nano chainparams.cpp

# Replace the CMainParams() constructor with generated code
# from v1.1.0-genesis-code.cpp
```

**Step 3:** Enable genesis mining
```bash
# In chainparams.cpp, uncomment the mining code section:
/*  <-- Remove this line
printf("Mining genesis block...\n");
while (UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit)) {
    genesis.nNonce++;
    ...
}
*/  <-- Remove this line
```

**Step 4:** Compile and mine genesis
```bash
cd source
make clean
make -j8

# Run to mine genesis (will print values then exit)
./src/ammocoind -printtoconsole
```

**Step 5:** Set final genesis values
```bash
# Copy the output values:
# nNonce: XXXXXXX
# Genesis hash: 0x...
# Merkle root: 0x...

# Update chainparams.cpp:
genesis.nNonce = XXXXXXX;
consensus.hashGenesisBlock = uint256S("0x...");
assert(genesis.hashMerkleRoot == uint256S("0x..."));
assert(consensus.hashGenesisBlock == uint256S("0x..."));

# Comment out the mining code again
```

**Step 6:** Final compilation
```bash
make clean
make -j8

# Test the daemon
./src/ammocoind -daemon
./src/ammocoin-cli getblockchaininfo
./src/ammocoin-cli stop
```

---

### Phase 3: Testing

**Step 1:** Private testnet validation
```bash
# Start fresh node
rm -rf /tmp/ammocoin-v1.1.0-test
./src/ammocoind -datadir=/tmp/ammocoin-v1.1.0-test -daemon

# Verify genesis
./src/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test getblockhash 0
# Should match consensus.hashGenesisBlock

# Generate some blocks
./src/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test generate 10
```

**Step 2:** Balance verification
```bash
# Import a v1.0 private key
./src/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test importprivkey "KEY"

# Check balance - should match v1.0 snapshot exactly
./src/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test getbalance
```

**Step 3:** Transaction testing
```bash
# Test sending coins
./src/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test sendtoaddress "ADDRESS" 1.0

# Verify transaction confirms
./src/ammocoin-cli -datadir=/tmp/ammocoin-v1.1.0-test listtransactions
```

---

### Phase 4: User Migration

**Step 1:** Deploy v1.1.0 binaries
- Compile for all platforms (macOS, Windows, Linux)
- Create installers/packages
- Upload to GitHub releases
- Announce to users

**Step 2:** User migration process
Each user needs to:
1. Backup v1.0 wallet
2. Export private keys from v1.0
3. Install v1.1.0
4. Import private keys to v1.1.0
5. Verify balance matches

**Step 3:** Support
- Provide 1-on-1 assistance for large holders
- Monitor migration progress
- Help stragglers complete migration
- Keep v1.0 nodes running for 90 days

---

## File Descriptions

### Migration Tools
- `v1.0-snapshot-tool.py` - Extract v1.0 balances via RPC
- `v1.1.0-genesis-generator.py` - Generate genesis C++ code from snapshot
- `v1.0-balance-snapshot-EXAMPLE.json` - Example snapshot format
- `MIGRATION_TOOLS_README.md` - This file

### Migration Documentation
- `MIGRATION_PLAN_v1.0_to_v1.1.0.md` - Complete migration guide
- `MIGRATION_TOOLS_README.md` - Tool usage documentation

### Generated Files (after running tools)
- `v1.0-balance-snapshot.json` - Actual v1.0 balance snapshot
- `v1.1.0-genesis-code.cpp` - Generated C++ code
- `v1.1.0-migration-summary.txt` - Balance summary report

---

## Security Considerations

### Snapshot Security
- **Verify total supply:** Must match expected v1.0 total
- **Cross-check large holders:** Manually verify top 5-10 addresses
- **Multiple backups:** Keep snapshot JSON in multiple secure locations
- **Hash verification:** Record and verify block hash at snapshot height

### Genesis Security
- **Code review:** Have multiple developers review generated code
- **Test thoroughly:** Validate on private testnet first
- **Balance verification:** All balances must be verifiable
- **No funds lost:** Every satoshi must be accounted for

### User Security
- **Private key safety:** Emphasize importance of backups
- **Phishing protection:** Only official download links
- **Migration support:** Provide trusted support channels
- **Verify balances:** Users must confirm balances match

---

## Troubleshooting

### Snapshot Tool Issues

**Problem:** "Connection reset by peer"
```
Solution:
- Check if RPC port is publicly accessible
- Verify RPC credentials are correct
- Ensure node allows external RPC connections
- Try connecting from same network as node
```

**Problem:** "No balances found"
```
Solution:
- Ensure wallet is loaded on node
- Check RPC user has wallet permissions
- Verify listunspent command works manually
```

### Genesis Generator Issues

**Problem:** "Snapshot file not found"
```
Solution:
- Run v1.0-snapshot-tool.py first
- Specify correct path to snapshot file
- Check file permissions
```

**Problem:** "Invalid JSON"
```
Solution:
- Validate snapshot file with: python3 -m json.tool snapshot.json
- Re-run snapshot tool if corrupted
```

### Compilation Issues

**Problem:** "Undefined reference to DecodeDestination"
```
Solution:
- Ensure all necessary headers are included
- Check that base58.h and key_io.h are included
- Verify chainparams.cpp syntax is correct
```

**Problem:** "Genesis mining takes too long"
```
Solution:
- This is normal - can take 5-30 minutes depending on hardware
- Monitor nNonce counter to see progress
- On slow machines, consider compiling on faster system
```

---

## Testing Checklist

Before production deployment:

- [ ] Snapshot tool successfully extracts all v1.0 balances
- [ ] Genesis generator creates valid C++ code
- [ ] Generated code compiles without errors
- [ ] Genesis block mines successfully
- [ ] Private testnet starts with new genesis
- [ ] Genesis block hash is unique (different from v1.0)
- [ ] Imported private keys show correct balances
- [ ] Test transactions confirm successfully
- [ ] All 20 users accounted for in snapshot
- [ ] Total supply matches v1.0 exactly
- [ ] Top holders verified manually
- [ ] User migration guide tested with volunteers
- [ ] Multi-platform binaries compiled and tested

---

## Support

**Technical Questions:**
- Review MIGRATION_PLAN_v1.0_to_v1.1.0.md
- Check troubleshooting section above
- Contact development team

**Large Balance Holders:**
- Request 1-on-1 migration assistance
- Will verify balances step-by-step
- Priority support provided

**Emergency Issues:**
- Do not panic - funds are safe with private keys
- Contact support immediately
- Have snapshot data ready

---

## License

These migration tools are part of the AMMOcoin project and follow the same MIT license as the main codebase.

---

**Last Updated:** December 1, 2025
**Version:** 1.0
**Status:** Production Ready
