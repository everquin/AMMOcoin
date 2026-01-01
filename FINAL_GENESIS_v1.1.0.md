# AMMOcoin v1.1.0 FINAL Genesis Block

**Date:** January 1, 2026
**Status:** ✅ FINAL - Production Ready

## Genesis Block Parameters

```
Genesis Hash:   000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
Merkle Root:    a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab
Genesis Time:   1623089845 (June 7, 2021)
Genesis Nonce:  1299391
Genesis nBits:  0x1e0ffff0
Genesis Reward: 250,000,000 AMMO
```

## Distribution Address

**Address:** AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME
**Public Key:** 0398413a7db9d8605f5447c40fab3026c7cce7b0dbec8e6ea94f5582b2adaa877d
**Type:** Compressed public key (33 bytes)

## Coinbase Transaction

The genesis block contains a single coinbase transaction that creates 250,000,000 AMMO sent to the distribution address above.

**Timestamp Message:**
```
AMMOcoin Genesis Block - June 7 2021 - New Era of Privacy
```

## Implementation Files

- `ammocoin-apps-from-ammocoin/src/chainparams.cpp` (lines 60, 161, 200, 291-292)
- `ammocoin-source/src/chainparams.cpp` (synchronized)
- `.github/workflows/build-release.yml` (verification checks)

## Verification

All binaries built from this codebase will:
1. Assert the genesis hash matches `000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2`
2. Assert the merkle root matches `a4b9dffe1a0e162f632ee851de1414adb433ab2303619c54fb859caa315042ab`
3. Verify nNonce 1299391 produces a valid proof-of-work solution

## Build Status

### macOS ARM64
- ✅ Built: January 1, 2026
- ✅ Genesis Verified: Daemon tested, correct hash confirmed
- ✅ Package: `releases/AMMOcoin-v1.1.0-macOS-ARM64.tar.gz` (3.9 MB)
- ✅ Checksums: `releases/CHECKSUMS-macOS-ARM64.txt`

### Linux x86_64
- ⏳ Pending: GitHub Actions build will be triggered on push

## Distribution Plan

The 250M AMMO will be distributed by the team to verified v1.0 holders using the private key for address AGkC8ydBWwyYE612V1Ag1mL4itp9Tv4KME after the network launches and the genesis block achieves sufficient confirmations (100+ blocks for coinbase maturity).

## Change History

### January 1, 2026 - FINAL Genesis Mined
- Mined fresh genesis block with correct parameters
- nNonce found: 1299391
- Hash verified: 000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2
- Updated all source files
- Purged conflicting documentation
- Built and verified macOS ARM64 binaries
- Updated GitHub Actions workflow

**This is the FINAL genesis block - no further changes will be made.**

---

## WARNING: Data Consistency

ALL builds (macOS, Linux, Windows, etc.) MUST use these exact parameters. Any deviation will result in incompatible blockchains and network splits.

The codebase has been purged of all conflicting genesis references to ensure clean, consistent compilation across all platforms.
