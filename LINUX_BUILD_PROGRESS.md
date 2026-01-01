# AMMOcoin v1.1.0 Linux x86_64 Build Progress

**Date:** January 1, 2026
**Status:** ⏳ IN PROGRESS

---

## Objective

Build production-ready Linux x86_64 binaries for AMMOcoin v1.1.0 with verified genesis block.

---

## Build Challenges & Solutions

### Challenge 1: UniValue Library Linking Errors
**Problem:** Initial Docker build failed with undefined references to `UniValue::pushKV()` and related functions.

**Root Cause:** The univalue library wasn't being built before the main binaries tried to link against it.

**Attempted Solution:** Built univalue, secp256k1, and chiabls as separate steps before main build.

**Result:** ❌ Created new problems (see Challenge 2)

### Challenge 2: Macro Collision - VERSION Conflict
**Problem:** Building chiabls separately caused the relic library to define `VERSION` macro, which conflicts with `NetMsgType::VERSION` in AMMOcoin code.

**Error:**
```
./chiabls/contrib/relic/include/relic_conf.h:583:17: error: expected unqualified-id before string constant
  583 | #define VERSION "0.1"
net_processing.cpp:1240:33: error: expected ')' before string constant
 1240 |     if (strCommand == NetMsgType::VERSION) {
```

**Solution:** Reverted to letting the build system handle all subdirectories together (standard autotools dependency management).

### Challenge 3: Architecture Mismatch
**Problem:** Building for ARM64 Linux instead of x86_64 Linux (target platform for VPS deployments).

**Root Cause:** Docker defaulted to host architecture (ARM64 Mac) without explicit platform specification.

**Solution:** Updated Dockerfile and build script to explicitly target `linux/amd64`:
```dockerfile
FROM --platform=linux/amd64 ubuntu:22.04
```

```bash
docker buildx build --platform linux/amd64 -f Dockerfile.linux -t ammocoin-linux-builder:v1.1.0 . --load
```

**Result:** ⏳ Currently building (emulation adds significant overhead)

---

## Current Build Configuration

### Docker Base
- **Platform:** linux/amd64 (x86_64)
- **Base Image:** Ubuntu 22.04 LTS
- **Build Method:** Docker cross-compilation with QEMU emulation

### Build Flags
```bash
./configure \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --enable-wallet \
    --with-incompatible-bdb \
    --with-boost \
    CXXFLAGS="-O2 -g" \
    LDFLAGS="-static-libgcc -static-libstdc++"
```

### Parallel Compilation
- **Make Jobs:** 2 (`make -j2`)
- **Reason:** Avoid memory exhaustion in Docker container

---

## Genesis Block Verification

✅ **Confirmed:** Source code contains correct v1.1.0 genesis block:

```
Genesis Hash:  00000da28f340848df488cd5cd49e4f40dbce9d37ab8fb9e8ec400b40b8fb162
Merkle Root:   58f0e4c39f4d2dce2c51cc1de1e2cd37ab4c1b41b7a2288805f683444ac63bd8
nTime:         1623089845 (June 7, 2021 19:30:45 UTC)
nNonce:        284486
Genesis Reward: 250,000,000 AMMO
```

---

## Expected Output

Once build completes, binaries will be available in `linux-binaries-v1.1.0/`:

- **ammocoind** - AMMOcoin daemon (~11 MB)
- **ammocoin-cli** - Command-line interface (~400 KB)
- **ammocoin-tx** - Transaction utility (~1.5 MB)

**Target Platform:** Linux x86_64 (Ubuntu 18.04+, Vultr VPS, standard VPS hosting)

---

## Build Timeline

| Step | Status | Duration |
|------|--------|----------|
| Docker image creation | ✅ Complete | ~3 min |
| Dependency installation | ✅ Complete | ~2 min |
| Rust installation | ✅ Complete | ~1 min |
| Source code autogen | ⏳ In Progress | ~30s |
| Configure | ⏳ Pending | ~2 min |
| Compilation | ⏳ Pending | ~15-30 min (emulated) |
| Linking | ⏳ Pending | ~2 min |
| Binary extraction | ⏳ Pending | ~10s |

**Note:** x86_64 emulation on ARM64 Mac adds 3-5x compilation overhead.

---

## Comparison with macOS Build

### macOS ARM64 Build (Completed ✅)
- **Platform:** Native ARM64 compilation
- **Build Time:** ~10 minutes
- **Result:** SUCCESS - Binaries verified and packaged
- **Package Size:** 4.5 MB (compressed)

### Linux x86_64 Build (In Progress ⏳)
- **Platform:** Emulated x86_64 on ARM64 host
- **Estimated Build Time:** 30-45 minutes
- **Expected Result:** SUCCESS (same source, proven build system)

---

## Lessons Learned

1. **Let autotools handle dependencies** - Manually building subdirectories causes macro pollution and linking order issues
2. **Always specify target platform** - Docker's automatic architecture selection can be misleading
3. **Cross-architecture builds are slow** - Emulation adds significant overhead (consider cloud builders for production)
4. **macOS build proves the code works** - Any Linux build issues are environment/config related, not code defects

---

## Next Steps (After Build Completes)

1. ✅ Verify binary architecture (`file ammocoind`)
2. ✅ Check genesis hash is embedded (`strings ammocoind | grep 00000da28f340848`)
3. ✅ Create release packages (tar.gz, zip)
4. ✅ Generate SHA256 checksums
5. ✅ Update release documentation
6. ✅ Create GitHub release

---

**Last Updated:** 2026-01-01 01:30 PST
**Build Log:** `/tmp/linux-x86_64-build.log`
