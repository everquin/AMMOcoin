# Genesis Block Fix Instructions - AMMOcoin v1.1.0

**Purpose**: Restore v1.0 genesis block compatibility
**File**: `ammocoin-apps-from-ammocoin/src/chainparams.cpp`
**Estimated Time**: 15 minutes + recompile (10 minutes)

---

## Required Changes

### Change 1: Genesis Message (Line 57)

**Current (v1.1.0 - WRONG)**:
```cpp
const char* pszTimestamp = "AMMOcoin Genesis Block - June 7 2021 - New Era of Privacy";
```

**Should be (v1.0 - CORRECT)**:
```cpp
const char* pszTimestamp = "Diligently We Forge From 7 June 2021 Evermore With AMMO In Our Crypto ";
```

⚠️ **Note**: The trailing space in the v1.0 message is important! It affects the hash.

---

### Change 2: Genesis Block Parameters (Line 195)

**Current (v1.1.0 - WRONG)**:
```cpp
genesis = CreateGenesisBlock(1623089845, 1299334, 0x1e0ffff0, 1, 1000 * COIN);
```

**Should be (v1.0 - CORRECT)**:
```cpp
genesis = CreateGenesisBlock(1623089845, 22256134, 0x1e0ffff0, 1, 1000 * COIN);
```

**Changed**: nNonce from `1299334` → `22256134`

---

### Change 3: Genesis Hash (Line 196)

**Current (v1.1.0 - WRONG)**:
```cpp
consensus.hashGenesisBlock = uint256S("0x0000075a4b9573ee2b4401c0ae785fb451d8355c91b6ed7d7a3420fe590cad58");
```

**Should be (v1.0 - CORRECT)**:
```cpp
consensus.hashGenesisBlock = uint256S("0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845");
```

---

### Change 4: Genesis Hash Assertion (Line 199)

**Current (v1.1.0 - WRONG)**:
```cpp
assert(consensus.hashGenesisBlock == uint256S("0x0000075a4b9573ee2b4401c0ae785fb451d8355c91b6ed7d7a3420fe590cad58"));
```

**Should be (v1.0 - CORRECT)**:
```cpp
assert(consensus.hashGenesisBlock == uint256S("0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"));
```

---

### Change 5: Merkle Root Assertion (Line 201)

**Current (v1.1.0 - COMMENTED OUT)**:
```cpp
// assert(genesis.hashMerkleRoot == uint256S("0x5a81ca998866f10edd5a0c5aff4380f8272dbf56d68fa150d461861fb139faba"));
```

**Should be (v1.0 - ENABLED AND CORRECT)**:
```cpp
assert(genesis.hashMerkleRoot == uint256S("0xc8b9e6af9becf659d6edb2aa8e261d036e95fc336ca4bd419cccf344fadb7fd4"));
```

---

### Change 6: Add Seed Nodes (Lines 303-305)

**Current (v1.1.0 - EMPTY)**:
```cpp
// Note that of those with the service bits flag, most only support a subset of possible options
// AMMOcoin seed nodes - using hardcoded nodes from chainparamsseeds.h
// vSeeds.emplace_back("seed.ammocoin.org", true);     // Primary DNS Seeder
// vSeeds.emplace_back("seed2.ammocoin.org", true);    // Secondary DNS Seeder
```

**Should be (v1.0 - WITH SEED NODES)**:
```cpp
// Note that of those with the service bits flag, most only support a subset of possible options
// AMMOcoin seed nodes - restored from v1.0
vSeeds.emplace_back("78.141.194.140", "78.141.194.140");
vSeeds.emplace_back("147.182.245.102", "147.182.245.102");
vSeeds.emplace_back("seed1.ammocoin.org", "seed1.ammocoin.org");
vSeeds.emplace_back("seed2.ammocoin.org", "seed2.ammocoin.org");
```

**Note**: Change `emplace_back` format to match v1.0 CDNSSeedData format or keep modern format.

---

### Change 7: Checkpoint Hash (Line 159)

**Current (v1.1.0 - CORRECT but verify)**:
```cpp
{ 0, uint256S("000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845")},
```

✅ This is already correct! It references the v1.0 genesis hash.

---

## Summary of Changes

| Line | Current (WRONG) | Correct (v1.0) | Type |
|------|-----------------|----------------|------|
| 57 | Different message | "Diligently We Forge..." | String |
| 195 | nNonce: 1299334 | nNonce: 22256134 | Number |
| 196 | 0x0000075a... | 0x000001c4... | Hash |
| 199 | 0x0000075a... | 0x000001c4... | Hash |
| 201 | (commented out) | 0xc8b9e6af... | Hash |
| 303-306 | (empty/commented) | Add 4 seed nodes | Config |

---

## Complete Fixed Code Sections

### Section 1: CreateGenesisBlock Function (Lines 55-60)

```cpp
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Diligently We Forge From 7 June 2021 Evermore With AMMO In Our Crypto ";
    const CScript genesisOutputScript = CScript() << ParseHex("049f0878e7c014c51fcb3f4f5571710833c0369aacba72546a6935c8c52d4dfdfee07cce4224c61904358c3e06faecbb9c2f286dccd864fd9dc3b061552084f752") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}
```

### Section 2: CMainParams Constructor Genesis (Lines 195-202)

```cpp
genesis = CreateGenesisBlock(1623089845, 22256134, 0x1e0ffff0, 1, 1000 * COIN);
consensus.hashGenesisBlock = uint256S("0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845");

// Genesis block verification using original AMMOcoin v1.0 genesis
assert(consensus.hashGenesisBlock == uint256S("0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"));
assert(genesis.hashMerkleRoot == uint256S("0xc8b9e6af9becf659d6edb2aa8e261d036e95fc336ca4bd419cccf344fadb7fd4"));
```

### Section 3: Seed Nodes (Lines 303-306)

Replace the commented section with:
```cpp
// AMMOcoin seed nodes - restored from v1.0
vSeeds.push_back(CDNSSeedData("78.141.194.140", "78.141.194.140"));
vSeeds.push_back(CDNSSeedData("147.182.245.102", "147.182.245.102"));
vSeeds.push_back(CDNSSeedData("seed1.ammocoin.org", "seed1.ammocoin.org"));
vSeeds.push_back(CDNSSeedData("seed2.ammocoin.org", "seed2.ammocoin.org"));
```

OR if using modern format:
```cpp
// AMMOcoin seed nodes - restored from v1.0
vSeeds.emplace_back("78.141.194.140", false);
vSeeds.emplace_back("147.182.245.102", false);
vSeeds.emplace_back("seed1.ammocoin.org", true);
vSeeds.emplace_back("seed2.ammocoin.org", true);
```

---

## Verification After Changes

### Step 1: Recompile
```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin
make clean
make -j$(sysctl -n hw.ncpu)
```

**Expected**: Compilation should succeed WITHOUT assertion errors.

### Step 2: Verify Genesis Hash
```bash
cd src
./ammocoind -printtoconsole -debug 2>&1 | grep -i genesis | head -5
```

**Expected Output**:
```
Genesis block hash: 000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845
```

### Step 3: Check Version
```bash
./ammocoind --version
```

**Expected**: Should show v1.1.0 with fixed genesis

### Step 4: Test Daemon Start
```bash
./ammocoind -daemon
sleep 5
./ammocoin-cli getinfo
```

**Expected**: Daemon starts successfully and responds to RPC

### Step 5: Verify Checkpoint (Optional)
```bash
./ammocoin-cli getblockhash 0
```

**Expected Output**:
```
000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845
```

---

## Testing Connectivity with v1.0 Network

If v1.0 nodes are still running:

```bash
# Try connecting to known v1.0 seed node
./ammocoind -connect=78.141.194.140

# Or
./ammocoind -connect=147.182.245.102
```

**Expected**: Should connect and sync blocks if v1.0 network is active.

---

## What If v1.0 Network is Dead?

If there are no active v1.0 nodes:

1. **Option A: Bootstrap from v1.0 blockchain**
   - Find v1.0 wallet.dat or blockchain data
   - Copy to v1.1.0 data directory
   - Start v1.1.0 daemon
   - Should recognize existing blocks

2. **Option B: Fresh Start (Only if v1.0 is completely abandoned)**
   - Keep the new genesis (current v1.1.0)
   - Document this as "AMMOcoin 2.0" or new chain
   - But this loses all v1.0 history!

---

## Quick Fix Script

Save this as `fix_genesis.sh`:

```bash
#!/bin/bash
FILE="/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin/src/chainparams.cpp"

# Backup original
cp "$FILE" "${FILE}.backup.$(date +%Y%m%d)"

# Fix 1: Genesis message (line 57)
sed -i '' 's/AMMOcoin Genesis Block - June 7 2021 - New Era of Privacy/Diligently We Forge From 7 June 2021 Evermore With AMMO In Our Crypto /g' "$FILE"

# Fix 2: nNonce (line 195)
sed -i '' 's/CreateGenesisBlock(1623089845, 1299334,/CreateGenesisBlock(1623089845, 22256134,/g' "$FILE"

# Fix 3 & 4: Genesis hash (lines 196 and 199)
sed -i '' 's/0x0000075a4b9573ee2b4401c0ae785fb451d8355c91b6ed7d7a3420fe590cad58/0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845/g' "$FILE"

# Fix 5: Merkle root (line 201) - more complex, do manually

echo "✅ Basic fixes applied. You still need to:"
echo "1. Manually fix line 201 (merkle root assertion)"
echo "2. Add seed nodes at lines 303-306"
echo "3. Review changes in: ${FILE}.backup.$(date +%Y%m%d)"
```

---

## Files to Update After Fix

After fixing and recompiling, these files/binaries need to be regenerated:

1. **All macOS binaries**: ammocoind, ammocoin-cli, ammocoin-tx
2. **Windows binaries**: Run `./build-windows.sh`
3. **Linux binaries**: Run `./build-linux.sh`
4. **ARM64 binaries**: Run `./build-arm64.sh`
5. **Flutter app binaries**: Update embedded daemon in `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin_App/binaries/`

---

## Post-Fix Checklist

- [ ] Backup current chainparams.cpp
- [ ] Apply all 7 changes
- [ ] Recompile successfully
- [ ] Verify genesis hash matches v1.0
- [ ] Test daemon starts without errors
- [ ] Verify getblockhash 0 returns correct genesis
- [ ] Test network connectivity (if v1.0 nodes exist)
- [ ] Rebuild all platform binaries
- [ ] Update Flutter app embedded binaries
- [ ] Update documentation
- [ ] Test full sync (if possible)

---

## Questions Before Proceeding

1. **Are there active v1.0 nodes running?**
   - Can test with: `nc -zv 78.141.194.140 37020`
   - Or: `nc -zv 147.182.245.102 37020`

2. **Is there existing v1.0 blockchain data to preserve?**
   - Check for wallet.dat with balances
   - Check for any v1.0 block data

3. **Should we maintain v1.0 compatibility?**
   - **YES** (recommended): Apply this fix
   - **NO**: Document as new chain, lose v1.0 history

---

**READY TO APPLY FIX?**

Please confirm:
1. You want to maintain v1.0 blockchain compatibility
2. You're ready for me to apply these changes
3. You're ready to recompile all binaries

Then I can make these changes automatically for you.
