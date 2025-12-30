# AMMOcoin v1.1.0 - Comprehensive Audit and Update Plan

**Date:** December 30, 2025
**Purpose:** Systematically update all files to use correct v1.1.0 genesis block
**Authority Document:** V1.1.0_GENESIS_BLOCK_AUTHORITY.md

---

## CORRECT Genesis Block (MUST USE)
```
Hash:    00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434
nNonce:  511628
nTime:   1623089845
Merkle:  ee2ff761e587117fb338182b9fa5b3555ab4510941590fe0577b1fd726c74aec
PubKey:  049f0878e7c014c51fcb3f4f5571710833c0369aacba72546a6935c8c52d4dfdfee07cce4224c61904358c3e06faecbb9c2f286dccd864fd9dc3b061552084f752
```

## DEPRECATED Hashes (MUST DELETE)
```
v1.0:           00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434
Broken v1.1.0:  00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434
```

---

## Phase 1: Source Code Updates

### ✅ COMPLETED
1. `ammocoin-apps-from-ammocoin/src/chainparams.cpp`
   - Status: UPDATED with correct genesis
   - Genesis hash: 00000f14...
   - nNonce: 511628
   - Assertions: Correct

### ⏳ NEEDS UPDATE
2. `ammocoin-source/src/chainparams.cpp`
   - Action: UPDATE or DELETE entire directory (appears to be backup/old code)
   - Decision needed: Is this directory still used?

---

## Phase 2: Documentation Files

### Files with OLD v1.0 Genesis (000001c4...)

#### DELETE (Obsolete/Confusing)
- [ ] `CRITICAL_GENESIS_BLOCK_ISSUE.md` - Describes old problems, no longer relevant
- [ ] `GENESIS_BLOCK_FIX_INSTRUCTIONS.md` - Instructions for old genesis, obsolete
- [ ] `compute_genesis.cpp` - References old genesis
- [ ] `test_genesis.cpp` - References old genesis

#### UPDATE with New Genesis
- [ ] `DEVELOPMENT_LOG.md` - Update genesis references
- [ ] `USER_ANNOUNCEMENT_EMAIL.md` - Update genesis hash

### Files with BROKEN v1.1.0 Genesis (0000075a...)

#### DELETE (Invalid Information)
- [ ] None identified as standalone files

#### UPDATE with Correct Genesis
- [ ] `NETWORK_LAUNCH_DEPLOYMENT.md` - Update all genesis references and verification commands
- [ ] `NETWORK_BOOTSTRAP_GUIDE.md` - Update genesis hash
- [ ] `START_NETWORK_NOW.md` - Update genesis verification
- [ ] `TEST_LOCAL_NODE_MACOS.md` - Update genesis checks
- [ ] `V1.0_TO_V1.1.0_NODE_MIGRATION.md` - Update expected genesis
- [ ] `QUICK_DOWNLOAD_GUIDE_v1.1.0.md` - Update genesis info
- [ ] `RELEASE_NOTES_v1.1.0.md` - Update genesis block info
- [ ] `RELEASE_COMPLETE_v1.1.0.md` - Update genesis hash
- [ ] `LINUX_BINARIES_NEXT_STEPS.md` - Update verification commands
- [ ] `LINUX_BINARY_DISTRIBUTION_GUIDE.md` - Update genesis check
- [ ] `docs/20251228_COMPREHENSIVE_REPOSITORY_AUDIT.md` - Update genesis info
- [ ] `docs/PRODUCTION_AUDIT_REPORT_v1.1.0.md` - Update genesis hash

### Scripts with Genesis References
- [ ] `scripts/deploy-and-start-network.sh` - Update genesis verification
- [ ] `scripts/setup-seed-node.sh` - Update genesis checks
- [ ] `scripts/test-local-macos.sh` - Update genesis validation

---

## Phase 3: Test Files

### Python/Shell Test Files
- [ ] `ammocoin-apps-from-ammocoin/test/functional/*` - Check for genesis references
- [ ] Review and update test expectations

---

## Phase 4: Binary Releases

### Current Binaries (INVALID - Must Rebuild)
- [ ] `releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz`
  - Current genesis: 000001c4... (OLD v1.0)
  - Action: DELETE and REBUILD with correct genesis

- [ ] `releases/AMMOcoin-v1.1.0-Linux-x86_64.zip`
  - Current genesis: 000001c4... (OLD v1.0)
  - Action: DELETE and REBUILD with correct genesis

- [ ] `releases/CHECKSUMS-Linux.txt`
  - Action: REGENERATE after rebuild

### New Binaries Needed
- [ ] macOS ARM64 binaries (build from updated source)
- [ ] macOS x86_64 binaries (if needed)
- [ ] Windows binaries (if needed)

---

## Phase 5: Deployment Updates

### Seed Node (seed1.ammocoin.org)
- [ ] Stop current node
- [ ] Backup any important data (should be none)
- [ ] Delete old blockchain data: `rm -rf ~/.ammocoin/*`
- [ ] Upload new binaries with correct genesis
- [ ] Start node
- [ ] Verify genesis: `ammocoin-cli getblockhash 0`
- [ ] Expected: `00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434`

---

## Phase 6: Git Repository Cleanup

### Files to DELETE
```bash
# Obsolete genesis-related files
rm -f CRITICAL_GENESIS_BLOCK_ISSUE.md
rm -f GENESIS_BLOCK_FIX_INSTRUCTIONS.md
rm -f compute_genesis.cpp
rm -f test_genesis.cpp
rm -f v1.1.0-genesis-code.cpp
rm -f generate-hybrid-genesis.py
rm -f insert-genesis-into-chainparams.py
rm -f v1.1.0-genesis-generator.py
rm -f v1.1.0-hybrid-genesis.cpp

# Old/invalid binaries
rm -f releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
rm -f releases/AMMOcoin-v1.1.0-Linux-x86_64.zip
rm -f releases/CHECKSUMS-Linux.txt

# Possibly old source backup (check first)
# rm -rf ammocoin-source/  # Only if confirmed obsolete
```

### Commits Needed
1. Commit: "CRITICAL: Update to correct v1.1.0 genesis block (00000f14...)"
   - Update chainparams.cpp
   - Add V1.1.0_GENESIS_BLOCK_AUTHORITY.md

2. Commit: "Update all documentation for correct v1.1.0 genesis"
   - Update all .md files
   - Update all scripts

3. Commit: "Remove obsolete genesis-related files"
   - Delete obsolete files
   - Clean up old binaries

4. Tag: `v1.1.0-genesis-final`
   - Tag the final commit
   - This is the build source for all platforms

---

## Phase 7: Build Process

### Build Order
1. **Linux** (Primary platform)
   - Build on Vultr VM or similar
   - Verify genesis before distribution
   - Create tar.gz and .zip
   - Generate checksums

2. **macOS** (Already built locally)
   - Already compiled with correct genesis
   - Package into distributable format
   - Generate checksums

3. **Windows** (If needed)
   - Cross-compile or build on Windows
   - Verify genesis
   - Create installer/zip
   - Generate checksums

### Build Verification Script
```bash
#!/bin/bash
# verify-genesis.sh

EXPECTED_HASH="00000f14ee7c9dc7580690364c94dbc86a4368bec1f7842be09063a662bc1434"

# Check binary
if strings ammocoind | grep -q "$EXPECTED_HASH"; then
    echo "✅ Binary contains correct genesis hash"
else
    echo "❌ FAIL: Binary does not contain correct genesis hash!"
    exit 1
fi

# Runtime check (if node can start)
./ammocoind -daemon
sleep 5
ACTUAL_HASH=$(./ammocoin-cli getblockhash 0 2>/dev/null)
./ammocoin-cli stop

if [ "$ACTUAL_HASH" = "$EXPECTED_HASH" ]; then
    echo "✅ Runtime genesis hash is correct"
else
    echo "❌ FAIL: Runtime genesis hash is $ACTUAL_HASH"
    exit 1
fi

echo "✅ ALL GENESIS CHECKS PASSED"
```

---

## Phase 8: Documentation Updates

### Create New Docs
- [ ] `V1.1.0_GENESIS_BLOCK_AUTHORITY.md` ✅ DONE
- [ ] `BUILD_INSTRUCTIONS_v1.1.0.md` - Step-by-step build process
- [ ] `DEPLOYMENT_CHECKLIST_v1.1.0.md` - Pre-launch checklist

### Update Existing Docs
- [ ] `README.md` - Update with v1.1.0 genesis info
- [ ] `CONTRIBUTING.md` - Add genesis verification requirements

---

## Phase 9: Testing & Verification

### Pre-Deployment Tests
- [ ] Single node starts successfully
- [ ] Genesis hash verification passes
- [ ] Wallet creation works
- [ ] Address generation works (should match paper wallet)
- [ ] RPC commands functional

### Multi-Node Tests
- [ ] Two nodes connect to each other
- [ ] Peer discovery works
- [ ] Genesis block matches on both nodes
- [ ] Block propagation works (when first block is mined)

### Cross-Platform Tests
- [ ] Linux <-> macOS connection
- [ ] Linux <-> Windows connection (if applicable)
- [ ] All platforms show same genesis hash

---

## Phase 10: Final Checklist

### Before ANY Binary Distribution
- [ ] All source code updated
- [ ] All documentation updated
- [ ] All obsolete files deleted
- [ ] Git repository clean and tagged
- [ ] Binaries built from tagged commit
- [ ] Genesis verification passed on all binaries
- [ ] Test deployment successful
- [ ] Peer connection tests passed

### Before Public Announcement
- [ ] Seed node(s) running with correct genesis
- [ ] Binaries available for download
- [ ] Documentation published
- [ ] Migration guide available
- [ ] Support channels ready

---

## Update Priority

### CRITICAL (Do First)
1. Update all source code files
2. Delete obsolete/confusing documentation
3. Rebuild Linux binaries
4. Update seed node

### HIGH (Do Second)
5. Update all deployment documentation
6. Update test scripts
7. Create verification tools
8. Build macOS/Windows binaries

### MEDIUM (Do Third)
9. Update README and contributing docs
10. Clean up git repository
11. Create final release

---

## Tracking Progress

Use this checklist to track updates:

### Source Code: 1/2 Complete (50%)
- [x] ammocoin-apps-from-ammocoin/src/chainparams.cpp
- [ ] ammocoin-source/src/chainparams.cpp (or DELETE)

### Documentation: 0/15 Complete (0%)
- [ ] (List each file as updated)

### Scripts: 0/3 Complete (0%)
- [ ] (List each script as updated)

### Binaries: 0/3 Complete (0%)
- [ ] Linux rebuild
- [ ] macOS package
- [ ] Windows build (if needed)

### Deployment: 0/1 Complete (0%)
- [ ] seed1.ammocoin.org updated

---

## Notes

- All updates must reference V1.1.0_GENESIS_BLOCK_AUTHORITY.md as source of truth
- Any conflicts should be resolved in favor of the authority document
- No exceptions to genesis parameters
- All platforms must use identical source code commit

---

**Last Updated:** December 30, 2025
**Status:** Planning Complete, Execution In Progress
