# AMMOcoin v1.1.0 - Quick Deployment Guide

**30-Minute Deployment Checklist**

---

## ✅ Pre-Flight Check

All binaries ready:
- [x] macOS ARM64: 4 MB ✅
- [x] Linux x86_64: 112 MB ✅
- [x] Windows x86_64: 17 MB ✅
- [x] Checksums generated ✅
- [x] Release notes ready ✅

---

## 🚀 Deploy in 5 Steps

### Step 1: Create GitHub Release (5 min)

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases
./create-github-release.sh
```

**Result:** https://github.com/everquin/AMMOcoin-v1.1.0/releases/tag/v1.1.0

---

### Step 2: Fix Website Whitepaper Link (2 min)

```bash
/tmp/fix-website-whitepaper-links.sh
```

Then:
```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/website_ammocoin
git diff  # Review changes
git add index.html downloads.html
git commit -m "Fix whitepaper link to correct path"
git push origin main
```

**Result:** Cloudflare auto-deploys to ammocoin.org

---

### Step 3: Clean Up Repository (1 min)

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/releases
./cleanup-releases.sh
```

---

### Step 4: Commit Documentation (2 min)

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin
git add releases/README.md
git add releases/DEPLOYMENT_INSTRUCTIONS.md
git add releases/cleanup-releases.sh
git add FINAL_DEPLOYMENT_SUMMARY.md
git add QUICK_DEPLOY.md
git commit -m "Add v1.1.0 release documentation and deployment automation"
git push origin main
```

---

### Step 5: Verify & Announce (20 min)

#### A. Test Downloads (10 min)
Visit: https://github.com/everquin/AMMOcoin-v1.1.0/releases/tag/v1.1.0

Download each platform and verify:
```bash
# macOS
sha256sum AMMOcoin-v1.1.0-macOS-ARM64.tar.gz
# Should match: 578eead2eb47d1ed7258d091e9581891390894ed17e3e03c32eac5d98c56e9a0

# Linux
sha256sum AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
# Should match: db7b90a98da45080467bb03a11e0de60bffe962888288ba74edb6eb4e646942c

# Windows
certutil -hashfile AMMOcoin-v1.1.0-Windows-x86_64.zip SHA256
# Should match: 6e643a98e97ba698b4b55cf324706186739f1f0f7ec97d2a3176b1227ec1dcee
```

#### B. Test Website (5 min)
- [ ] Visit https://ammocoin.org
- [ ] Click migration banner → Should go to /migration.html
- [ ] Visit https://ammocoin.org/downloads.html
- [ ] Click "Download macOS Binaries" → Should go to GitHub release
- [ ] Click "Whitepaper v1.1.0" → Should go to GitHub (correct path)

#### C. Announce (5 min)
```
🎉 AMMOcoin v1.1.0 is LIVE!

✅ macOS, Linux & Windows binaries ready
✅ Enhanced security & privacy
✅ New genesis block

Download: https://github.com/everquin/AMMOcoin-v1.1.0/releases
Guide: https://ammocoin.org/migration.html

#AMMOcoin #Crypto
```

Post to:
- [ ] Twitter: @AMMOcoin
- [ ] Facebook: facebook.com/ammocoin
- [ ] YouTube: Community tab

---

## 🆘 Rollback (if needed)

If critical issues found:

```bash
# Mark release as pre-release
gh release edit v1.1.0 --prerelease --repo everquin/AMMOcoin-v1.1.0

# Add warning to website
# Edit /Volumes/CRUCIAL_2TB/GITHUB/website_ammocoin/index.html
# Change banner text to include "TESTING - DO NOT USE"
```

---

## 📊 Success Metrics

After deployment, monitor:
- GitHub release download count (target: 100+ in first week)
- Website traffic to /downloads.html
- GitHub issues (respond within 24 hours)
- Node count on network

---

## 🔗 Quick Links

**Release:** https://github.com/everquin/AMMOcoin-v1.1.0/releases/tag/v1.1.0
**Website:** https://ammocoin.org
**Downloads:** https://ammocoin.org/downloads.html
**Migration:** https://ammocoin.org/migration.html

---

**Total time:** ~30 minutes
**Last updated:** January 5, 2026
