# AMMOcoin Source Directory Audit

**Audit Date:** January 3, 2026
**Status:** 🔴 **CRITICAL CONFUSION - CONSOLIDATION REQUIRED**

---

## Executive Summary

The AMMOcoin repository currently has TWO source directories with conflicting purposes and redundant content. This creates confusion about which is the "official" source and leads to maintenance issues.

### Current State

| Directory | Size | Files | Purpose | Status |
|-----------|------|-------|---------|--------|
| **source** | 6.6 GB | 4,594 | **Active development & builds** | ✅ Production |
| **ammocoin-source** | 18 MB | 54 | Incomplete copy, legacy artifact | ❌ Redundant |

---

## Detailed Analysis

### source/

**Size:** 6.6 GB
**Files:** 4,594 source files
**Git Tracked:** Full repository

**Contents:**
- Complete C++ source code (all .cpp/.h files)
- Built binaries (ammocoind, ammocoin-cli, ammocoin-tx)
- All dependencies (Qt, secp256k1, univalue, chiabls, etc.)
- Build system (autotools, Cargo.toml for Rust)
- Complete test suite
- Documentation
- Compilation artifacts (.o files, Makefile, config.status)

**Genesis Block:**
```cpp
consensus.hashGenesisBlock = uint256S("0x000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2");
```
✅ **CORRECT** v1.1.0 genesis (250M AMMO premine)

**Usage:**
- This is the ACTUAL source directory used for all builds
- Contains working binaries at `source/src/`
- All build scripts ultimately compile from this directory

---

### ammocoin-source/

**Size:** 18 MB
**Files:** 54 files (only 2 tracked by git)
**Git Tracked:** Only 2 files:
  - `src/chainparams.cpp`
  - `src/secp256k1/src/libsecp256k1-config.h.in`

**Contents:**
- ONE source file: `src/chainparams.cpp` (IDENTICAL to source version)
- ONE backup: `src/chainparams.cpp.backup`
- Empty directory structure (depends/, doc/, build-aux/)
- Autotools artifacts (configure, Makefile.in, autom4te.cache)
- NO other source files
- NO binaries

**Genesis Block:**
```cpp
consensus.hashGenesisBlock = uint256S("0x000000593410213331b5adcc6a79054a984bfc9999825e579171f81f2eccddd2");
```
✅ Same as source (identical file)

**History:**
- Commit `a0e430c` (Dec 30, 2025) attempted to DELETE this directory:
  ```
  CLEANUP: Remove obsolete ammocoin-source directory

  This directory contained OLD v1.0 genesis block (000001c4...) which is
  incompatible with v1.1.0. Appears to be an old backup/alternate source tree.
  ```
- Most files were deleted but 2 files remained (likely re-added later)
- Directory still exists with minimal content

**Purpose:**
- ❓ **UNCLEAR** - appears to be abandoned cleanup attempt
- Not used for builds
- Contains only duplicate of chainparams.cpp
- Serves no active function

---

## References Analysis

### Documentation References to ammocoin-source

**docs/guides/LINUX_BINARY_DISTRIBUTION_GUIDE.md:**
```bash
# References Vultr VM path:
/opt/AMMOcoin-v1.1.0/ammocoin-source/src/ammocoind
```
This is CONFUSING because:
- Local repository uses `source`
- Remote VM uses `ammocoin-source` as directory name
- They refer to the SAME codebase, just cloned with different names

**docs/installation/UBUNTU_UPGRADE_GUIDE.md:**
```bash
sudo git clone https://github.com/everquin/AMMOcoin-v1.1.0.git ammocoin-source
cd ammocoin-source
```
This instructs users to clone the repo as "ammocoin-source" directory.

**Build Scripts (build-all.sh, build-linux.sh, build-arm64.sh):**
```bash
if [ ! -d "ammocoin-source" ] || [ ! -d "source" ]; then
    echo "❌ Error: Source directories not found"
    echo "Expected: ammocoin-source/ and source/"
    exit 1
fi
```
**CRITICAL BUG:** Scripts check for existence of ammocoin-source but NEVER USE IT!

---

## Problems Identified

### 1. Naming Confusion
- Repository has two directories with "source" in their names
- Unclear which is the "official" source directory
- Name `source` doesn't clearly indicate it's the primary source

### 2. Redundant Content
- `ammocoin-source/src/chainparams.cpp` is IDENTICAL to `source/src/chainparams.cpp`
- No reason for ammocoin-source to exist locally

### 3. Documentation Inconsistency
- Local repository uses `source`
- Remote VM documentation uses `ammocoin-source`
- Build scripts check for both (unnecessarily)

### 4. Failed Cleanup
- Commit `a0e430c` attempted to remove ammocoin-source
- Cleanup incomplete - directory persists
- Git still tracks 2 files from it

### 5. Misleading Build Scripts
- Scripts require ammocoin-source to exist
- But never actually use it
- Creates false dependency

---

## Recommendations

### Option A: Complete Removal (RECOMMENDED)

**Action:** Delete ammocoin-source entirely and update all references

**Steps:**
1. Remove from git: `git rm -rf ammocoin-source/`
2. Update build scripts to remove ammocoin-source check
3. Update LINUX_BINARY_DISTRIBUTION_GUIDE.md
   - Change VM paths from `ammocoin-source` → `source`
   - Or note that VM uses different directory name
4. Update UBUNTU_UPGRADE_GUIDE.md
   - Clone as `source` OR
   - Document that directory name doesn't matter

**Pros:**
- ✅ Eliminates confusion
- ✅ Single source of truth
- ✅ Completes attempted cleanup from Dec 30
- ✅ Reduces repository clutter

**Cons:**
- ⚠️ Need to update documentation
- ⚠️ Need to update build scripts
- ⚠️ May break external references (if any exist)

---

### Option B: Rename source → ammocoin-source

**Action:** Rename primary source directory to match documentation

**Steps:**
1. `git mv source ammocoin-source`
2. Delete current empty ammocoin-source/
3. Update build scripts
4. Update all documentation references

**Pros:**
- ✅ Simpler name
- ✅ Matches VM documentation
- ✅ Shorter path names

**Cons:**
- ❌ Loses descriptive name "source" (which indicates it came from PIVX apps)
- ❌ Massive git operation
- ❌ Would break all existing references in issues, PRs, external docs

---

### Option C: Rename source → src

**Action:** Use simple, standard name for source directory

**Steps:**
1. `git mv source src`
2. `git rm -rf ammocoin-source`
3. Update all references
4. Update build scripts

**Pros:**
- ✅ Standard, clear naming (most projects use "src")
- ✅ Eliminates confusion
- ✅ Professional structure

**Cons:**
- ❌ Large git operation
- ❌ Breaks existing references
- ❌ Less descriptive of codebase origin

---

## Recommendation: Option A (Complete Removal)

**Reasoning:**
1. ammocoin-source serves NO purpose locally
2. Cleanup was already attempted (Dec 30) but incomplete
3. Minimal disruption - just remove redundant files
4. source is already established as the working directory
5. Can be done incrementally without breaking builds

**Implementation Priority:**
1. 🔴 **HIGH:** Remove ammocoin-source directory completely
2. 🟡 **MEDIUM:** Update build scripts to remove unnecessary check
3. 🟢 **LOW:** Update documentation (note VM may use different clone name)

---

## Clarification on VM vs Local Naming

**Key Insight:** The confusion stems from:

**Local Repository (Development):**
```
AMMOcoin/
├── source/  ← Primary source
└── ammocoin-source/              ← Redundant, should be removed
```

**Remote VM (Production):**
```
/opt/AMMOcoin-v1.1.0/
└── ammocoin-source/  ← Just a different clone name, SAME codebase
```

When users clone the repository, they can name it anything:
```bash
git clone https://github.com/everquin/AMMOcoin-v1.1.0.git my-custom-name
```

The UBUNTU_UPGRADE_GUIDE tells users to clone as "ammocoin-source" which is fine for the VM, but shouldn't create confusion in the repository itself.

**Resolution:** Keep source as the official source directory name in the repository, but document that when deploying to VMs, users may clone with any name they prefer.

---

## Action Plan

### Immediate Actions (Complete Cleanup)

1. **Remove ammocoin-source directory:**
   ```bash
   git rm -rf ammocoin-source/
   ```

2. **Update build scripts** (`scripts/build/build-all.sh`, `build-linux.sh`, `build-arm64.sh`):
   ```bash
   # Remove this check:
   if [ ! -d "ammocoin-source" ] || [ ! -d "source" ]; then

   # Replace with:
   if [ ! -d "source" ]; then
       echo "❌ Error: Source directory not found"
       echo "Expected: source/"
       exit 1
   fi
   ```

3. **Update LINUX_BINARY_DISTRIBUTION_GUIDE.md:**
   - Add note: "VM directory name may differ from local repository structure"
   - Clarify that `/opt/AMMOcoin-v1.1.0/ammocoin-source/` on VM refers to the cloned repository

4. **Commit and push:**
   ```
   git commit -m "CLEANUP: Complete removal of redundant ammocoin-source directory

   This directory was an incomplete cleanup artifact from Dec 30, 2025.
   It contained only duplicate files and served no active purpose.

   - Removed ammocoin-source/ entirely
   - Updated build scripts to remove unnecessary directory check
   - Clarified documentation regarding VM vs local directory naming

   The primary source directory is source/
   (Users may clone repository with any directory name they prefer)"
   ```

---

**Conclusion:** ammocoin-source is redundant, confusing, and should be completely removed. The primary source directory is and should remain `source/`.

