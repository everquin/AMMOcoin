# AMMOcoin v1.1.0 Deployment Instructions

This guide covers the final steps to publish the v1.1.0 release to the public.

---

## Prerequisites

✅ All binaries built and tested:
- macOS ARM64: `AMMOcoin-macOS-ARM64.tar.gz` (4 MB) ✅
- Linux x86_64: `AMMOcoin-Linux-x86_64.tar.gz` (112 MB) ✅
- Windows x86_64: `AMMOcoin-Windows-x86_64.tar.gz` (17 MB) ✅

✅ Checksums generated: `AMMOcoin-ALL-PLATFORMS-CHECKSUMS.txt` ✅

✅ Release notes prepared: `RELEASE_NOTES_v1.1.0.md` ✅

✅ Documentation complete ✅

---

## Step 1: Create GitHub Release

### Option A: Using the Script (Recommended)

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases
./create-github-release.sh
```

This will:
1. Create a new GitHub release tagged `v1.1.0`
2. Upload all platform binaries (tar.gz and zip files)
3. Upload the checksums file
4. Attach the release notes

### Option B: Manual Upload via GitHub Web Interface

1. Go to: https://github.com/everquin/AMMOcoin/releases/new
2. Tag: `v1.1.0`
3. Title: `AMMOcoin v1.1.0 - Multi-Platform Release`
4. Copy-paste content from `RELEASE_NOTES_v1.1.0.md`
5. Upload these files:
   - `AMMOcoin-macOS-ARM64.tar.gz`
   - `AMMOcoin-macOS-ARM64.zip`
   - `AMMOcoin-Linux-x86_64.tar.gz`
   - `AMMOcoin-Windows-x86_64.tar.gz`
   - `AMMOcoin-Windows-x86_64.zip`
   - `AMMOcoin-ALL-PLATFORMS-CHECKSUMS.txt`
6. Click "Publish release"

---

## Step 2: Clean Up Repository

After the GitHub Release is created, clean up the local releases folder:

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases

# Remove binary directories (keep only archives)
rm -rf AMMOcoin-macOS-ARM64/
rm -rf AMMOcoin-Windows-x86_64/
rm -rf Windows-Binaries/

# Keep only:
# - Archive files (.tar.gz, .zip)
# - Checksum files
# - README.md
# - Release notes
# - This deployment guide
```

**What to keep in /releases:**
- ✅ `README.md` - User-facing download guide
- ✅ `RELEASE_NOTES_v1.1.0.md` - Release notes
- ✅ `AMMOcoin-ALL-PLATFORMS-CHECKSUMS.txt` - Checksums
- ✅ `create-github-release.sh` - Release automation script
- ✅ `DEPLOYMENT_INSTRUCTIONS.md` - This file
- ❌ Binary directories (uploaded to GitHub, not needed in repo)

---

## Step 3: Update Website

### Update Whitepaper Link

The website currently links to an old whitepaper from 2022. Update it:

**File:** `/Volumes/CRUCIAL_2TB/GITHUB/website_ammocoin/downloads.html`

The site already links to the new whitepaper at:
```
https://github.com/everquin/AMMOcoin/blob/main/AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md
```

This is correct! ✅

### Verify Website Content

The website is already updated with v1.1.0 information:

1. ✅ **index.html** - Migration banner is active
2. ✅ **downloads.html** - Updated with v1.1.0 download links
3. ✅ **migration.html** - Complete migration guide
4. ✅ All pages link to GitHub releases

**No website changes needed!** Everything is already in place.

---

## Step 4: Deploy Website to Cloudflare

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/website_ammocoin

# Verify git status
git status

# If there are uncommitted changes to migration.html or downloads.html:
git add .
git commit -m "Update for v1.1.0 release deployment"
git push origin main

# Cloudflare Pages will automatically deploy
```

Cloudflare Pages will automatically deploy from the `main` branch.

---

## Step 5: Verify Deployment

### Check GitHub Release
1. Visit: https://github.com/everquin/AMMOcoin/releases/tag/v1.1.0
2. Verify all 6 files are attached
3. Verify release notes display correctly
4. Test download links

### Check Website
1. Visit: https://ammocoin.org
2. Verify migration banner is visible
3. Visit: https://ammocoin.org/downloads.html
4. Click "Download macOS Binaries" - should go to GitHub release
5. Verify all download links work

### Check Checksums
```bash
# Download each binary from GitHub
# Verify checksums match
sha256sum AMMOcoin-*.tar.gz
```

---

## Step 6: Commit Repository Changes

After cleaning up:

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin

git add releases/README.md
git add releases/DEPLOYMENT_INSTRUCTIONS.md
git add releases/*.md
git add releases/*.txt
git commit -m "Add release documentation and checksums for v1.1.0"
git push origin main
```

---

## Step 7: Announce the Release

### Update README.md
Add a prominent link to the release:

```markdown
## Download v1.1.0

Pre-built binaries are available for:
- **macOS ARM64** (M1/M2/M3)
- **Linux x86_64** (Ubuntu 20.04+, Debian 11+)
- **Windows x86_64** (Windows 10/11)

[Download from GitHub Releases](https://github.com/everquin/AMMOcoin/releases/latest)
```

### Announcement Channels
- [ ] Post to Twitter (@AMMOcoin)
- [ ] Post to Facebook (facebook.com/ammocoin)
- [ ] Post to YouTube community tab
- [ ] Email newsletter (if you have one)
- [ ] Update Discord/Telegram (if applicable)

---

## Rollback Plan

If issues are discovered after release:

1. **Mark release as "Pre-release"** on GitHub
2. **Add warning banner** to website
3. **Fix the issue**
4. **Create v1.1.1** with the fix
5. **Deprecate v1.1.0**

---

## Success Checklist

Before announcing publicly, verify:

- [ ] GitHub release created with all 6 files
- [ ] All download links work
- [ ] Checksums verified
- [ ] Website displays correctly on ammocoin.org
- [ ] Migration guide accessible
- [ ] All documentation links work
- [ ] macOS binary runs without quarantine issues
- [ ] Linux binary runs on Ubuntu 20.04
- [ ] Windows binary runs on Windows 10/11
- [ ] Genesis block hash verified in all binaries

---

## Post-Release Monitoring

Monitor for the first 48 hours:

- [ ] GitHub release downloads count
- [ ] GitHub issues for installation problems
- [ ] Website analytics for traffic spike
- [ ] Node count (how many nodes are syncing)
- [ ] Network hash rate
- [ ] Community feedback on social media

---

## Questions or Issues?

- Review the troubleshooting section in `releases/README.md`
- Check GitHub Issues
- Review build logs in GitHub Actions

---

**Prepared by:** Claude Code
**Date:** January 5, 2026
**Release:** AMMOcoin v1.1.0
