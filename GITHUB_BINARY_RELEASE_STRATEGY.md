# GitHub Binary Release Strategy

**Issue:** GitHub file size limits prevent committing large binaries to repository
**Solution:** Use GitHub Releases for binary distribution (industry standard)

---

## ❌ Problem: GitHub File Size Limits

When attempting to push Linux binaries to GitHub:

```
remote: error: File binaries-linux-v1.1.0/ammocoind is 168.72 MB;
this exceeds GitHub's file size limit of 100.00 MB

remote: warning: File releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz is 71.92 MB;
this is larger than GitHub's recommended maximum file size of 50.00 MB
```

### GitHub Limits:
- **Hard limit:** 100 MB per file (rejected)
- **Recommended limit:** 50 MB per file (warning)
- **Repository limit:** 1 GB total (soft limit)
- **Git LFS limit:** 2 GB per file (requires LFS)

### Our Binary Sizes:
- `ammocoind`: 168.72 MB ❌ (exceeds 100 MB hard limit)
- `ammocoin-cli`: 6.2 MB ✅
- `ammocoin-tx`: 23 MB ✅
- `AMMOcoin-v1.1.0-Linux-x86_64.tar.gz`: 71.92 MB ⚠️ (exceeds 50 MB recommendation)
- `AMMOcoin-v1.1.0-Linux-x86_64.zip`: 72.03 MB ⚠️ (exceeds 50 MB recommendation)

---

## ✅ Solution: GitHub Releases (Recommended)

**GitHub Releases** is the proper way to distribute binaries for cryptocurrency projects.

### Why GitHub Releases?

1. **No file size limits** (up to 2 GB per file)
2. **Separate from source code** (keeps repo clean)
3. **Version-tagged** (users download specific versions)
4. **Checksums visible** (in release notes)
5. **Standard practice** (Bitcoin, Ethereum, Monero all use this)
6. **Better UX** (users know where to find official binaries)

### Examples:
- **Bitcoin Core:** https://github.com/bitcoin/bitcoin/releases
- **Monero:** https://github.com/monero-project/monero/releases
- **Litecoin:** https://github.com/litecoin-project/litecoin/releases

All use GitHub Releases for binary distribution, NOT commits to main repo.

---

## 🎯 Recommended Approach

### What to Commit to Repository:
- ✅ Source code
- ✅ Documentation
- ✅ Build scripts
- ✅ Checksums file (text, small)
- ❌ Large compiled binaries

### What to Upload to GitHub Releases:
- ✅ All compiled binaries (any size)
- ✅ Distribution packages (tar.gz, zip)
- ✅ Platform-specific builds (Linux, macOS, Windows, ARM)
- ✅ Release notes with checksums

---

## 📋 Implementation Steps

### Step 1: Update .gitignore

Exclude large binary directories from git tracking:

```bash
# Add to .gitignore:
binaries-linux-v1.1.0/
binaries-macos-arm64/
binaries-windows/
releases/*.tar.gz
releases/*.zip
releases/*.dmg
```

### Step 2: Commit Only Checksums

```bash
git add releases/CHECKSUMS-Linux.txt
git add .gitignore
git commit -m "Add Linux binary checksums (binaries distributed via GitHub Releases)"
git push origin main
```

### Step 3: Create Git Tag for v1.1.0

```bash
git tag -a v1.1.0 -m "AMMOcoin v1.1.0 Release - Path A Migration

Major release with complete blockchain restart (Path A).

Features:
- Fresh genesis block (0x0000075a...)
- Migration distribution to v1.0 holders
- zkSNARK privacy transactions (Sapling)
- Improved staking and masternode support

Binaries available for:
- Linux x86_64 (Ubuntu 20.04+)
- macOS ARM64 (Apple Silicon)

See release notes for migration guide."

git push origin v1.1.0
```

### Step 4: Create GitHub Release

**Via GitHub Web UI:**

1. Go to: https://github.com/everquin/AMMOcoin-v1.1.0/releases/new
2. Choose tag: `v1.1.0`
3. Release title: `AMMOcoin v1.1.0 - Path A Migration`
4. Add release notes (see template below)
5. Attach binary files:
   - `AMMOcoin-v1.1.0-Linux-x86_64.tar.gz`
   - `AMMOcoin-v1.1.0-Linux-x86_64.zip`
   - `ammocoin-v1.1.0-macos-arm64.tar.gz`
   - `CHECKSUMS-Linux.txt`
6. Mark as "Latest release"
7. Publish

**Via GitHub CLI (gh):**

```bash
gh release create v1.1.0 \
  --title "AMMOcoin v1.1.0 - Path A Migration" \
  --notes-file RELEASE_NOTES_v1.1.0.md \
  releases/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz \
  releases/AMMOcoin-v1.1.0-Linux-x86_64.zip \
  releases/ammocoin-v1.1.0-macos-arm64.tar.gz \
  releases/CHECKSUMS-Linux.txt
```

---

## 📝 Release Notes Template

```markdown
# AMMOcoin v1.1.0 - Path A Migration

**Release Date:** December 28, 2025
**Release Type:** Major Release - New Blockchain (Path A)

---

## ⚠️ CRITICAL: Path A Migration

**This is a completely new blockchain, NOT a fork of v1.0!**

- **v1.0 Genesis:** `0x000001c4...` (old blockchain)
- **v1.1.0 Genesis:** `0x0000075a...` (new blockchain)

**Your v1.0 wallet is required to claim v1.1.0 balances.**

📖 **Migration Guide:** [V1.0_TO_V1.1.0_NODE_MIGRATION.md](link)

---

## 📦 Downloads

### Linux (Ubuntu 20.04/22.04/24.04)

**Recommended:** Use pre-compiled binaries for fastest setup

```bash
# Download
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Verify checksum
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Should match: 917cd4365b352ad7800ba9dd2c388408cba0341ff6da1ba8aa33f84515e73acb

# Extract
tar -xzf AMMOcoin-v1.1.0-Linux-x86_64.tar.gz

# Install
sudo install -m 0755 -o root -g root -t /usr/local/bin ammocoind ammocoin-cli ammocoin-tx
```

**Files:**
- `AMMOcoin-v1.1.0-Linux-x86_64.tar.gz` (72 MB) - Recommended
- `AMMOcoin-v1.1.0-Linux-x86_64.zip` (72 MB) - Alternative format

### macOS (Apple Silicon - M1/M2/M3)

```bash
# Download
wget https://github.com/everquin/AMMOcoin-v1.1.0/releases/download/v1.1.0/ammocoin-v1.1.0-macos-arm64.tar.gz

# Extract
tar -xzf ammocoin-v1.1.0-macos-arm64.tar.gz

# Install
sudo cp ammocoind ammocoin-cli ammocoin-tx /usr/local/bin/
```

**Files:**
- `ammocoin-v1.1.0-macos-arm64.tar.gz`

### Windows

Coming soon (build in progress)

---

## 🔐 Checksums (SHA256)

**Linux:**
```
917cd4365b352ad7800ba9dd2c388408cba0341ff6da1ba8aa33f84515e73acb  AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
8cc8d9a3b96b92305cd99393f79598cf3ca3611693000d2da1f9727aadd161f7  AMMOcoin-v1.1.0-Linux-x86_64.zip
```

Download `CHECKSUMS-Linux.txt` for verification.

---

## 📋 Installation Instructions

See [LINUX_BINARY_DISTRIBUTION_GUIDE.md](link) for complete installation guide.

**Quick start:**

1. Install runtime dependencies:
```bash
sudo apt-get install -y \
    libboost-system1.71.0 libboost-filesystem1.71.0 \
    libboost-thread1.71.0 libboost-program-options1.71.0 \
    libevent-2.1-7 libzmq5 libsodium23
```

2. Install zkSNARK parameters:
```bash
mkdir -p ~/.ammocoin-params
cd ~/.ammocoin-params
wget https://download.z.cash/downloads/sapling-spend.params
wget https://download.z.cash/downloads/sapling-output.params
```

3. Create configuration:
```bash
mkdir -p ~/.ammocoin-v1.1.0
# Add ammocoin.conf (see guide)
```

4. Start node:
```bash
ammocoind -datadir=~/.ammocoin-v1.1.0 -daemon
```

---

## 🔧 Technical Details

**Compilation:**
- Platform: Ubuntu 20.04 LTS
- Compiler: GCC 9.4.0
- Architecture: x86_64
- Berkeley DB: 4.8 (with modern GCC patch)
- Build type: Debug symbols included

**Features:**
- ✅ Full node support
- ✅ Staking
- ✅ Masternode support
- ✅ zkSNARK privacy transactions (Sapling)
- ✅ P2P networking (port 37020)
- ✅ RPC server (port 8332)

**Compatibility:**
- Ubuntu 20.04/22.04/24.04 LTS
- Debian 10+ (Buster or later)
- Linux Mint 20+
- Other Ubuntu-based distributions

---

## 💰 Migration Distribution

**Top 61 Holders:** 218.7M AMMO (94.11%) - Automatic distribution
**Remaining Holders:** 13.7M AMMO (5.89%) - Claim-based migration fund

See [USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md](link) for claim instructions.

---

## 📚 Documentation

- [User Migration Guide](link)
- [Node Migration Guide](link)
- [Network Bootstrap Guide](link)
- [Linux Binary Distribution Guide](link)

---

## 🛡️ Security

**IMPORTANT:** Always verify checksums before installation!

```bash
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Compare with checksum above
```

Future releases will include GPG signatures for additional security.

---

## 🐛 Known Issues

None currently. Report issues at: https://github.com/everquin/AMMOcoin-v1.1.0/issues

---

## 📞 Support

- GitHub Issues: https://github.com/everquin/AMMOcoin-v1.1.0/issues
- Documentation: Repository docs/ folder
```

---

## 🔄 Alternative: Git LFS

If you want to keep binaries in the repo, use Git Large File Storage:

```bash
# Install Git LFS
brew install git-lfs  # macOS
# or
sudo apt-get install git-lfs  # Ubuntu

# Initialize
git lfs install

# Track large files
git lfs track "binaries-linux-v1.1.0/*"
git lfs track "releases/*.tar.gz"
git lfs track "releases/*.zip"

# Add .gitattributes
git add .gitattributes

# Commit and push (LFS handles large files)
git add binaries-linux-v1.1.0/ releases/
git commit -m "Add Linux binaries via Git LFS"
git push origin main
```

**Pros:**
- Binaries stored in repo history
- Automatic downloads for cloners

**Cons:**
- Requires Git LFS setup for all users
- LFS bandwidth/storage limits on GitHub
- More complex for users unfamiliar with LFS

**Recommendation:** Still use GitHub Releases even with LFS.

---

## 🎯 Final Recommendation

**For AMMOcoin v1.1.0:**

1. ✅ Use GitHub Releases for binary distribution (standard practice)
2. ✅ Commit checksums to repository (small text files)
3. ✅ Keep raw binaries locally (not in git)
4. ✅ Update documentation with download links
5. ❌ Don't commit large binaries to main repository

This approach:
- Follows cryptocurrency industry standards
- Provides best user experience
- Avoids GitHub limits
- Keeps repository clean and fast

---

**Next Steps:**
1. Update .gitignore to exclude binary directories
2. Commit only checksums
3. Create git tag v1.1.0
4. Create GitHub Release with binaries attached
5. Update documentation with release download links

