# AMMOcoin Documentation Reorganization Plan

**Date:** December 28, 2025
**Status:** Ready for Implementation
**Estimated Time:** 2-3 hours
**Priority:** High (Post-Launch Cleanup)

---

## Executive Summary

This plan reorganizes all AMMOcoin documentation into a professional, date-prefixed structure within the `/docs` directory. The reorganization improves maintainability, discoverability, and historical tracking.

---

## 1. Proposed Directory Structure

```
/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/
├── README.md (keep - main entry point)
├── AMMOcoin_Whitepaper_v1.1.0.md (keep - key document)
├── AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md (keep - key document)
├── docs/
│   ├── README.md (keep - documentation hub)
│   │
│   ├── user-guides/
│   │   ├── 01-wallet-setup.md
│   │   ├── 02-staking-guide.md
│   │   ├── 03-masternode-setup.md
│   │   ├── 04-node-setup.md
│   │   ├── 05-terminal-commands.md
│   │   ├── 06-dao-participation.md
│   │   ├── 08-security-guide.md
│   │   ├── 09-troubleshooting.md
│   │   └── 10-faq.md
│   │
│   ├── installation/
│   │   ├── 20251101_INSTALL_MACOS.md
│   │   ├── 20251115_UBUNTU_UPGRADE_GUIDE.md
│   │   ├── 20251115_UBUNTU_18.04_MIGRATION_NOTES.md
│   │   ├── 20251120_CROSS_COMPILATION_GUIDE.md
│   │   └── 20251125_VULTR_VPS_DEPLOYMENT.md
│   │
│   ├── build/
│   │   ├── 20251201_BUILD_FROM_SOURCE_LINUX.md
│   │   ├── 20251201_BUILD_FROM_SOURCE_RASPBERRY_PI.md
│   │   ├── 20251201_BUILD_FROM_SOURCE_WINDOWS.md
│   │   ├── 20251201_BUILD_SYSTEM_READY.md
│   │   ├── 20251205_BINARY_BUILD_SOLUTION.md
│   │   └── 20251205_BINARY_DISTRIBUTION_GUIDE.md
│   │
│   ├── migration/
│   │   ├── 20251210_MIGRATION_PLAN_v1.0_to_v1.1.0.md
│   │   ├── 20251220_USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md
│   │   ├── 20251220_LINUX_NODE_MIGRATION_GUIDE.md
│   │   ├── 20251222_MIGRATION_STATUS.md
│   │   ├── 20251222_MIGRATION_COMPLETE_SUMMARY.md
│   │   ├── 20251222_MIGRATION_COMPLETE_PACKAGE.md
│   │   ├── 20251222_MANUAL_SNAPSHOT_GUIDE.md
│   │   └── MIGRATION_CLAIM_FORM.html
│   │
│   ├── deployment/
│   │   ├── 20251215_PATH_A_DEPLOYMENT_PLAN.md
│   │   ├── 20251222_DEPLOYMENT_STATUS_PATH_A.md
│   │   ├── 20251222_NETWORK_BOOTSTRAP_GUIDE.md
│   │   ├── 20251223_PRODUCTION_DEPLOYMENT_READY.md
│   │   ├── 20251223_PRODUCTION_AUDIT_REPORT_v1.1.0.md
│   │   ├── 20251224_LAUNCH_DAY_CHECKLIST.md
│   │   ├── 20251224_LAUNCH_DAY_QUICK_REFERENCE.md
│   │   ├── 20251224_BINARY_TESTING_CHECKLIST.md
│   │   └── 20251225_RELEASE_V1.1.0_SUMMARY.md
│   │
│   ├── scripts/
│   │   ├── 20251220_DISTRIBUTION_SCRIPTS_README.md
│   │   ├── 20251220_MIGRATION_TOOLS_README.md
│   │   └── 20251228_create-snapshot-from-addresses.md
│   │
│   ├── status/
│   │   ├── 20251228_CURRENT_STATUS_REPORT.md
│   │   ├── 20251228_DEVELOPMENT_LOG.md
│   │   ├── 20251228_NEXT_STEPS_TO_COMPLETE.md
│   │   ├── 20251228_DEPLOYMENT_PACKAGE.md
│   │   ├── 20251215_MULTI_PLATFORM_RELEASE_SUMMARY.md
│   │   └── 20251220_NEXT_STEPS_WINDOWS_AND_MACOS.md
│   │
│   ├── communication/
│   │   └── 20251222_USER_ANNOUNCEMENT_EMAIL.md
│   │
│   ├── archive/
│   │   ├── 20251201_CRITICAL_GENESIS_BLOCK_ISSUE.md
│   │   ├── 20251201_GENESIS_BLOCK_FIX_INSTRUCTIONS.md
│   │   ├── 20251205_LINUX_BUILD_SUCCESS.md
│   │   └── 20251210_PROJECT_COMPLETION_SUMMARY.md
│   │
│   └── audit/
│       └── 20251228_COMPREHENSIVE_REPOSITORY_AUDIT.md
│
├── scripts/
│   ├── migration/
│   │   ├── distribute-to-top-holders.py
│   │   ├── verify-claim.py
│   │   ├── scan-all-balances.py
│   │   ├── v1.0-blockchain-scanner.py
│   │   ├── v1.0-snapshot-tool.py
│   │   ├── v1.1.0-genesis-generator.py
│   │   ├── generate-hybrid-genesis.py
│   │   ├── insert-genesis-into-chainparams.py
│   │   └── verify-migration.py
│   │
│   └── deployment/
│       └── deploy-seed-node.sh
│
├── migration-data/
│   ├── v1.0-complete-balance-snapshot.json
│   ├── genesis-top-holders.json
│   ├── migration-fund-claims.json
│   ├── migration-statistics.txt
│   └── v1.0-balance-snapshot-EXAMPLE.json
│
└── (build scripts remain in root)
    build-all.sh
    build-linux.sh
    build-windows.sh
    build-arm64.sh
    build-macos-native.sh
    etc.
```

---

## 2. Date Prefix Convention

### Format: `yyyymmdd_FILENAME.md`

**Examples:**
- `20251228_COMPREHENSIVE_REPOSITORY_AUDIT.md`
- `20251222_DEPLOYMENT_STATUS_PATH_A.md`
- `20251220_USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md`

**Benefits:**
1. Files sort chronologically automatically
2. Easy to identify when document was created
3. Clear versioning for historical reference
4. No manual sorting needed

**Date to Use:**
- For new files: Creation date
- For migrated files: Approximate creation date (best guess from git log)
- For updated files: Keep original date + update note in file

---

## 3. Migration Steps

### Phase 1: Backup (5 minutes)

```bash
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin
git add -A
git commit -m "Pre-reorganization snapshot"
git tag pre-doc-reorg
```

### Phase 2: Create New Structure (10 minutes)

```bash
# Create new subdirectories
mkdir -p docs/user-guides
mkdir -p docs/installation
mkdir -p docs/build
mkdir -p docs/migration
mkdir -p docs/deployment
mkdir -p docs/scripts
mkdir -p docs/status
mkdir -p docs/communication
mkdir -p docs/archive
mkdir -p docs/audit
mkdir -p scripts/migration
mkdir -p scripts/deployment
mkdir -p migration-data
```

### Phase 3: Move User Guides (Already Done) ✅

User guides (01-10-*.md) are already properly organized in `/docs`.

### Phase 4: Migrate Installation Docs (15 minutes)

```bash
# Move from root to docs/installation/ with date prefixes
mv INSTALL_MACOS.md docs/installation/20251101_INSTALL_MACOS.md
mv UBUNTU_UPGRADE_GUIDE.md docs/installation/20251115_UBUNTU_UPGRADE_GUIDE.md
mv UBUNTU_18.04_MIGRATION_NOTES.md docs/installation/20251115_UBUNTU_18.04_MIGRATION_NOTES.md
mv CROSS_COMPILATION_GUIDE.md docs/installation/20251120_CROSS_COMPILATION_GUIDE.md
mv VULTR_VPS_DEPLOYMENT.md docs/installation/20251125_VULTR_VPS_DEPLOYMENT.md
```

### Phase 5: Migrate Build Docs (15 minutes)

```bash
# Move existing /docs build files to docs/build/ with dates
mv docs/BUILD_FROM_SOURCE_LINUX.md docs/build/20251201_BUILD_FROM_SOURCE_LINUX.md
mv docs/BUILD_FROM_SOURCE_RASPBERRY_PI.md docs/build/20251201_BUILD_FROM_SOURCE_RASPBERRY_PI.md
mv docs/BUILD_FROM_SOURCE_WINDOWS.md docs/build/20251201_BUILD_FROM_SOURCE_WINDOWS.md
mv docs/BUILD_SYSTEM_READY.md docs/build/20251201_BUILD_SYSTEM_READY.md
mv docs/BINARY_BUILD_SOLUTION.md docs/build/20251205_BINARY_BUILD_SOLUTION.md
mv docs/BINARY_DISTRIBUTION_GUIDE.md docs/build/20251205_BINARY_DISTRIBUTION_GUIDE.md
```

### Phase 6: Migrate Migration Docs (20 minutes)

```bash
# From /docs to docs/migration/ with dates
mv docs/MIGRATION_PLAN_v1.0_to_v1.1.0.md docs/migration/20251210_MIGRATION_PLAN_v1.0_to_v1.1.0.md
mv docs/MIGRATION_STATUS.md docs/migration/20251222_MIGRATION_STATUS.md
mv docs/MIGRATION_COMPLETE_SUMMARY.md docs/migration/20251222_MIGRATION_COMPLETE_SUMMARY.md
mv docs/MIGRATION_COMPLETE_PACKAGE.md docs/migration/20251222_MIGRATION_COMPLETE_PACKAGE.md
mv docs/LINUX_NODE_MIGRATION_GUIDE.md docs/migration/20251220_LINUX_NODE_MIGRATION_GUIDE.md
mv docs/MANUAL_SNAPSHOT_GUIDE.md docs/migration/20251222_MANUAL_SNAPSHOT_GUIDE.md
# Keep MIGRATION_CLAIM_FORM.html without date prefix (it's a web form)
mv docs/MIGRATION_CLAIM_FORM.html docs/migration/MIGRATION_CLAIM_FORM.html

# From root to docs/migration/ with dates
mv USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md docs/migration/20251220_USER_MIGRATION_GUIDE_v1.0_to_v1.1.0.md
```

### Phase 7: Migrate Deployment Docs (20 minutes)

```bash
# From /docs to docs/deployment/ with dates
mv docs/PATH_A_DEPLOYMENT_PLAN.md docs/deployment/20251215_PATH_A_DEPLOYMENT_PLAN.md
mv docs/PRODUCTION_DEPLOYMENT_READY.md docs/deployment/20251223_PRODUCTION_DEPLOYMENT_READY.md
mv docs/PRODUCTION_AUDIT_REPORT_v1.1.0.md docs/deployment/20251223_PRODUCTION_AUDIT_REPORT_v1.1.0.md
mv docs/LAUNCH_DAY_CHECKLIST.md docs/deployment/20251224_LAUNCH_DAY_CHECKLIST.md
mv docs/LAUNCH_DAY_QUICK_REFERENCE.md docs/deployment/20251224_LAUNCH_DAY_QUICK_REFERENCE.md
mv docs/BINARY_TESTING_CHECKLIST.md docs/deployment/20251224_BINARY_TESTING_CHECKLIST.md
mv docs/RELEASE_V1.1.0_SUMMARY.md docs/deployment/20251225_RELEASE_V1.1.0_SUMMARY.md

# From root to docs/deployment/ with dates
mv DEPLOYMENT_STATUS_PATH_A.md docs/deployment/20251222_DEPLOYMENT_STATUS_PATH_A.md
mv NETWORK_BOOTSTRAP_GUIDE.md docs/deployment/20251222_NETWORK_BOOTSTRAP_GUIDE.md
```

### Phase 8: Migrate Script Docs (10 minutes)

```bash
# From root to docs/scripts/ with dates
mv DISTRIBUTION_SCRIPTS_README.md docs/scripts/20251220_DISTRIBUTION_SCRIPTS_README.md
mv docs/MIGRATION_TOOLS_README.md docs/scripts/20251220_MIGRATION_TOOLS_README.md
mv create-snapshot-from-addresses.md docs/scripts/20251228_create-snapshot-from-addresses.md
```

### Phase 9: Migrate Status Docs (15 minutes)

```bash
# From root to docs/status/ with dates
mv CURRENT_STATUS_REPORT.md docs/status/20251228_CURRENT_STATUS_REPORT.md
mv DEVELOPMENT_LOG.md docs/status/20251228_DEVELOPMENT_LOG.md
mv NEXT_STEPS_TO_COMPLETE.md docs/status/20251228_NEXT_STEPS_TO_COMPLETE.md
mv DEPLOYMENT_PACKAGE.md docs/status/20251228_DEPLOYMENT_PACKAGE.md

# From /docs to docs/status/ with dates
mv docs/MULTI_PLATFORM_RELEASE_SUMMARY.md docs/status/20251215_MULTI_PLATFORM_RELEASE_SUMMARY.md
mv docs/NEXT_STEPS_WINDOWS_AND_MACOS.md docs/status/20251220_NEXT_STEPS_WINDOWS_AND_MACOS.md
```

### Phase 10: Migrate Communication Docs (5 minutes)

```bash
# From root to docs/communication/ with dates
mv USER_ANNOUNCEMENT_EMAIL.md docs/communication/20251222_USER_ANNOUNCEMENT_EMAIL.md
```

### Phase 11: Archive Historical Docs (10 minutes)

```bash
# From root to docs/archive/ with dates
mv CRITICAL_GENESIS_BLOCK_ISSUE.md docs/archive/20251201_CRITICAL_GENESIS_BLOCK_ISSUE.md
mv GENESIS_BLOCK_FIX_INSTRUCTIONS.md docs/archive/20251201_GENESIS_BLOCK_FIX_INSTRUCTIONS.md

# From /docs to docs/archive/ with dates
mv docs/LINUX_BUILD_SUCCESS.md docs/archive/20251205_LINUX_BUILD_SUCCESS.md
mv docs/PROJECT_COMPLETION_SUMMARY.md docs/archive/20251210_PROJECT_COMPLETION_SUMMARY.md
```

### Phase 12: Move Scripts (15 minutes)

```bash
# Migration scripts
mv distribute-to-top-holders.py scripts/migration/
mv verify-claim.py scripts/migration/
mv scan-all-balances.py scripts/migration/
mv v1.0-blockchain-scanner.py scripts/migration/
mv v1.0-snapshot-tool.py scripts/migration/
mv v1.1.0-genesis-generator.py scripts/migration/
mv generate-hybrid-genesis.py scripts/migration/
mv insert-genesis-into-chainparams.py scripts/migration/
mv verify-migration.py scripts/migration/

# Deployment scripts
mv deploy-seed-node.sh scripts/deployment/

# Make scripts executable
chmod +x scripts/migration/*.py
chmod +x scripts/deployment/*.sh
```

### Phase 13: Move Migration Data (10 minutes)

```bash
# Move data files
mv v1.0-complete-balance-snapshot.json migration-data/
mv genesis-top-holders.json migration-data/
mv migration-fund-claims.json migration-data/
mv migration-statistics.txt migration-data/
mv v1.0-balance-snapshot-EXAMPLE.json migration-data/

# Create README
cat > migration-data/README.md << 'EOF'
# AMMOcoin Migration Data

This directory contains the v1.0 blockchain snapshot data used for the v1.1.0 migration.

## Files

- **v1.0-complete-balance-snapshot.json** (580 KB) - Complete snapshot of all addresses at block 434,881
  - 10,080 addresses
  - 232.4M AMMO total
  - Snapshot date: December 2025

- **genesis-top-holders.json** (7.3 KB) - Top 61 holders (manual distribution)
  - 94.11% of total supply (218.7M AMMO)
  - Distributed directly to holders

- **migration-fund-claims.json** (987 KB) - Migration fund claims
  - 10,019 addresses
  - 5.89% of supply (13.7M AMMO)
  - Claim-based distribution

- **migration-statistics.txt** (2 KB) - Summary statistics

- **v1.0-balance-snapshot-EXAMPLE.json** - Example format

## Security Note

This data is intentionally public for transparency. All addresses and balances are from the public v1.0 blockchain.
EOF
```

### Phase 14: Update README.md Files (20 minutes)

Update `docs/README.md` to reflect new structure:

```bash
# Edit docs/README.md to include new sections and directory structure
```

Update main `README.md` to reference documentation organization.

### Phase 15: Clean Up (10 minutes)

```bash
# Remove backup files from source
rm ammocoin-apps-from-ammocoin/src/chainparams.cpp.backup
rm ammocoin-apps-from-ammocoin/src/chainparams.cpp.backup.pre-fix
rm ammocoin-apps-from-ammocoin/src/chainparams.cpp.broken

# Verify no orphaned .md files in root (except whitepapers and README)
ls *.md
# Should only show:
# - README.md
# - AMMOcoin_Whitepaper_v1.1.0.md
# - AMMOcoin_Comprehensive_Whitepaper_v1.1.0.md
```

### Phase 16: Update .gitignore (5 minutes)

```bash
# Append comprehensive .gitignore
cat >> .gitignore << 'EOF'

# Build artifacts
*.o
*.lo
*.la
*.a
*.so
*.dylib
*.dll
*.exe
Makefile
Makefile.in
.deps/
.dirstamp
.libs/
autom4te.cache/
build-aux/
config.status
configure
libtool
aclocal.m4

# macOS
.DS_Store
._*
*.app/

# Compiled binaries (keep in releases/)
ammocoin-apps-from-ammocoin/src/ammocoind
ammocoin-apps-from-ammocoin/src/ammocoin-cli
ammocoin-apps-from-ammocoin/src/ammocoin-tx

# Build directories
build/
ammocoin-apps-from-ammocoin/depends/built/
ammocoin-apps-from-ammocoin/depends/work/
ammocoin-apps-from-ammocoin/depends/sources/
ammocoin-apps-from-ammocoin/depends/x86_64-w64-mingw32/

# Backup files
*.backup
*.backup.*
*.broken
*~

# IDE
.vscode/
.idea/
*.swp

# Distribution packages
*.dmg
*.tar.gz
*.zip

# Data directories
.ammocoin/
EOF
```

### Phase 17: Git Commit (10 minutes)

```bash
# Stage all changes
git add -A

# Commit reorganization
git commit -m "MAJOR: Documentation reorganization with date prefixes

- Organized all documentation into /docs with subdirectories
- Added yyyymmdd_ date prefix convention to all docs
- Moved scripts to /scripts/migration and /scripts/deployment
- Moved migration data to /migration-data
- Created /docs/archive for historical documents
- Updated .gitignore for build artifacts and macOS files
- Removed backup files from source tree

Directory structure:
- docs/user-guides/ - User-facing documentation
- docs/installation/ - Platform installation guides
- docs/build/ - Build from source documentation
- docs/migration/ - v1.0 to v1.1.0 migration docs
- docs/deployment/ - Deployment plans and status
- docs/scripts/ - Script documentation
- docs/status/ - Status reports and logs
- docs/communication/ - User communications
- docs/archive/ - Historical documents
- docs/audit/ - Audit reports
- scripts/migration/ - Migration automation
- scripts/deployment/ - Deployment automation
- migration-data/ - v1.0 snapshot data

All files now follow yyyymmdd_FILENAME.md convention for chronological sorting."
```

---

## 4. Updated Documentation Hub

After reorganization, update `docs/README.md`:

```markdown
# AMMOcoin Documentation Hub

Welcome to the complete AMMOcoin v1.1.0 documentation!

## Quick Start

- **New Users**: [User Guides](./user-guides/)
- **Installation**: [Installation Guides](./installation/)
- **Developers**: [Build Documentation](./build/)
- **Migration**: [v1.0 → v1.1.0 Migration](./migration/)

## Documentation Structure

### [📱 User Guides](./user-guides/)
Step-by-step guides for wallet setup, staking, masternodes, and more.

### [💻 Installation](./installation/)
Platform-specific installation and deployment guides.

### [🔨 Build](./build/)
Build from source instructions for all platforms.

### [🔄 Migration](./migration/)
v1.0 to v1.1.0 migration documentation and tools.

### [🚀 Deployment](./deployment/)
Production deployment plans and status tracking.

### [📜 Scripts](./scripts/)
Documentation for automation scripts.

### [📊 Status](./status/)
Current status reports and development logs.

### [💬 Communication](./communication/)
User announcements and communications.

### [📦 Archive](./archive/)
Historical documents and decision records.

### [📋 Audit](./audit/)
Security and code audits.

## Naming Convention

All documentation files follow the format: `yyyymmdd_FILENAME.md`

This ensures:
- Chronological sorting
- Clear creation dates
- Easy version tracking

## Contributing

When adding new documentation:
1. Use the date prefix format: `yyyymmdd_`
2. Place in the appropriate subdirectory
3. Update this README if adding new categories
4. Use clear, descriptive filenames

---

*Last updated: December 28, 2025 • AMMOcoin Development Team*
```

---

## 5. Validation Steps

After completing migration:

```bash
# 1. Verify root directory is clean
cd /Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin
ls *.md
# Should only show: README.md and whitepapers

# 2. Verify docs structure
tree docs -L 2

# 3. Verify scripts moved
ls scripts/migration/
ls scripts/deployment/

# 4. Verify migration data moved
ls migration-data/

# 5. Verify no broken links
# (Manual check of README files)

# 6. Verify git status
git status
```

---

## 6. Rollback Plan

If issues arise:

```bash
# Restore pre-reorganization state
git reset --hard pre-doc-reorg
git tag -d pre-doc-reorg
```

---

## 7. Communication

**Internal Note:** This reorganization is a cosmetic change that does not affect functionality. It can be completed post-launch without impacting users.

**Git Commit Message:** See Phase 17 above for comprehensive commit message.

---

## 8. Timeline

| Phase | Duration | Total Time |
|-------|----------|------------|
| 1. Backup | 5 min | 0:05 |
| 2. Create Structure | 10 min | 0:15 |
| 3. User Guides | 0 min (done) | 0:15 |
| 4. Installation Docs | 15 min | 0:30 |
| 5. Build Docs | 15 min | 0:45 |
| 6. Migration Docs | 20 min | 1:05 |
| 7. Deployment Docs | 20 min | 1:25 |
| 8. Script Docs | 10 min | 1:35 |
| 9. Status Docs | 15 min | 1:50 |
| 10. Communication | 5 min | 1:55 |
| 11. Archive | 10 min | 2:05 |
| 12. Move Scripts | 15 min | 2:20 |
| 13. Migration Data | 10 min | 2:30 |
| 14. Update READMEs | 20 min | 2:50 |
| 15. Clean Up | 10 min | 3:00 |
| 16. .gitignore | 5 min | 3:05 |
| 17. Git Commit | 10 min | 3:15 |

**Total Estimated Time:** 3 hours 15 minutes

---

## 9. Benefits

**Organization:**
- ✅ All docs in logical categories
- ✅ Chronological sorting automatic
- ✅ Clear separation of concerns

**Maintainability:**
- ✅ Easy to find relevant documentation
- ✅ Clear document history
- ✅ Reduced root directory clutter

**Professionalism:**
- ✅ Industry-standard organization
- ✅ Clear versioning
- ✅ Scalable structure

---

**Status:** Ready for implementation
**Priority:** Post-launch cleanup (does not block production)
**Assigned:** Repository maintainer

