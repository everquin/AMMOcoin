# Release Checklist - AMMOcoin v1.1.1

Steps to publish the v1.1.1 Proof-of-Stake hard fork release. Work top to bottom; do not skip a box. Signing details: [docs/release/SIGNING.md](release/SIGNING.md). User-facing notes: [docs/release-notes/RELEASE_NOTES_v1.1.1.md](release-notes/RELEASE_NOTES_v1.1.1.md).

Compliance: release notes and the release page are public copy. Run [docs/compliance/REVIEW_CHECKLIST.md](compliance/REVIEW_CHECKLIST.md) (on the `compliance-docs` branch until merged) before publishing. The release page must contain no price, market cap, exchange rate, fiat amount, ROI/APR/APY/yield figure, "investment" wording, "where to buy" or exchange links.

---

## 1. Freeze the source

- [ ] All v1.1.1 work is merged into `v1.1.1-pos-fork` (or the branch chosen for release) and that branch is merged to `main` by reviewed PR.
- [ ] `source/configure.ac` and the committed `source/configure` both say `1.1.1` (`CLIENT_VERSION_MAJOR/MINOR/REVISION`, `CLIENT_VERSION_IS_RELEASE=true`).
- [ ] Mainnet consensus values match the release notes: PoS at 2,776 (`source/src/chainparams.cpp`), `nRewardZCV2Height` 1,153,160, `nRewardV55Height` 3,715,200, `nMNBlockReward` 3 AMMO, `nMNCollateralAmt` 10,000 AMMO, `nBudgetCycleBlocks` 43,200, `nStakeMinDepth` 600, ports 37020 / 51473.
- [ ] Unit tests pass, including `source/src/test/budget_tests.cpp`.
- [ ] No build outputs, local binaries or secrets are staged (`git status` clean apart from known local-only files).

## 2. Tag

- [ ] Create an annotated (preferably signed) tag on the release commit:
  ```bash
  git tag -s v1.1.1 -m "AMMOcoin v1.1.1 - Proof-of-Stake hard fork at block 2,776"
  git push origin v1.1.1
  ```
- [ ] If `scripts/release/allowed_signers` gets the release public key in this release, that commit is **before** the tag (users verify against `allowed_signers` at the tag).

## 3. Build all platforms (CI)

Run, or confirm green runs of, each workflow on the tagged commit:

| Workflow | Produces |
|---|---|
| `build-linux-static.yml` | `AMMOcoin-v1.1.1-Linux-x86_64.tar.gz`, `.zip`, `AMMOcoin-v1.1.1-Linux-amd64.deb`, `AMMOcoin-v1.1.1-Linux-x86_64-CHECKSUM.txt`, `AMMOcoin-v1.1.1-Linux-x86_64-Qt.tar.gz`, `AMMOcoin-v1.1.1-Linux-x86_64-Qt.AppImage`, `AMMOcoin-v1.1.1-Linux-x86_64-Qt-CHECKSUM.txt` |
| `build-arm64.yml` | `AMMOcoin-v1.1.1-Linux-ARM64.tar.gz`, `.zip`, `AMMOcoin-v1.1.1-Linux-arm64.deb`, `AMMOcoin-v1.1.1-Linux-ARM64-CHECKSUM.txt`, `AMMOcoin-v1.1.1-Linux-ARM64-Qt.tar.gz`, `AMMOcoin-v1.1.1-Linux-ARM64-Qt.AppImage`, `AMMOcoin-v1.1.1-Linux-ARM64-Qt-CHECKSUM.txt` |
| `build-windows-only.yml` | `AMMOcoin-v1.1.1-Windows-x86_64-Setup.exe`, `.zip`, `.tar.gz`, `AMMOcoin-v1.1.1-Windows-x86_64-CHECKSUM.txt` |
| `build-macos.yml` (arm64 + x86_64) | `AMMOcoin-v1.1.1-macOS-ARM64.{dmg,tar.gz,zip,SHA256}`, `AMMOcoin-v1.1.1-macOS-x86_64.{dmg,tar.gz,zip,SHA256}` |

For every run:

- [ ] Version check step passed (`scripts/ci/check-build-version.sh`: `v1.1.1`, no `-dirty`).
- [ ] Genesis hash check passed.
- [ ] Smoke tests passed (Linux Qt regtest GUI test, `.deb` test, macOS regtest daemon + offscreen Qt).
- [ ] **macOS:** the run shows **no** "Unsigned macOS build" warning. The verify step passed `otool` minos <= 13.0, no Homebrew paths, `codesign` / `spctl` and `stapler validate`. Ad-hoc signed packages are never published.
- [ ] Windows Setup.exe is over 40 MB (bundles the Sapling parameters).

## 4. Create the GitHub release (draft first)

- [ ] Create a **draft** release for tag `v1.1.1`, title `AMMOcoin v1.1.1 - Proof-of-Stake Hard Fork`.
- [ ] Body: the release notes, with the "release candidate" status line replaced by the publication date. Keep the "not an offer, not investment advice" note.
- [ ] Download each workflow's artifact zip from the Actions run and attach the files inside it (all files in the table above, including every `…-CHECKSUM.txt` and `….SHA256`). Do not attach `Windows-Binaries` / individual-binary artifacts or debug logs.
- [ ] Spot-check each per-platform checksum file locally: `sha256sum -c <file>-CHECKSUM.txt`, `shasum -a 256 -c AMMOcoin-v1.1.1-macOS-<ARCH>.SHA256`.
- [ ] Mark as **mandatory upgrade** in the first line of the body.

## 5. Combined checksums (`release-checksums.yml`)

- [ ] Publish the release. The **Release combined checksums** workflow runs on `release: published` and uploads `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt`.
- [ ] If assets were added or replaced after publishing, or the release was published by a workflow token, re-run it by hand (Actions -> Release combined checksums -> Run workflow, tag `v1.1.1`). It deletes a now-stale `.sig`.
- [ ] Workflow passed its cross-checks: every asset matches its per-platform `…-CHECKSUM.txt` / `….SHA256`, and both macOS architectures have dmg + tar.gz + zip listed.

## 6. Sign and verify SHA256SUMS

- [ ] **Precondition:** `scripts/release/allowed_signers` contains the release public key (`release@ammocoin.org ssh-ed25519 …`). As of this checklist it contains **no key line**, so a signature cannot yet be verified by users. Until a key is pinned, publish without a `.sig` and say so on the release page.
- [ ] On the offline signing machine, download `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt` from the release and sign it:
  ```bash
  AMMOCOIN_SIGN_KEY=~/.ssh/ammocoin_release_ed25519 \
    ./scripts/release/sign-release.sh AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt
  ```
- [ ] Upload `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt.sig` to the release.
- [ ] Verify from a **fresh** clone at tag `v1.1.1`, using files downloaded from the release page (not the local copies):
  ```bash
  ./scripts/release/verify-release.sh AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt   # ends with "Signature is valid."
  sha256sum -c AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt                          # every line OK
  ```
- [ ] Paste the combined checksums into the release body (template below).

## 7. Post-release checks

- [ ] Install from the release on a clean Ubuntu 24.04 VPS with `install-node.sh --tarball <release URL> --sha256 <hash>`; node syncs past block 2,775 and connects to seed1 / seed2.
- [ ] `.deb` installs and `systemctl status ammocoind` is active.
- [ ] macOS DMG opens on a Mac that has never run AMMOcoin, with no Gatekeeper prompt beyond the standard "downloaded from the internet" dialog.
- [ ] Windows Setup.exe installs, starts and syncs.
- [ ] Seed nodes (seed1.ammocoin.org, seed2.ammocoin.org) run v1.1.1 (`getnetworkinfo` subversion).

## 8. Update the website and docs

- [ ] ammocoin.org downloads page: link every file **on the GitHub release** (no self-hosted binaries), show its SHA256 from the combined file, link `…CHECKSUMS.txt` and `.sig`, macOS minimum 13, Linux glibc 2.34+.
- [ ] Remove "upcoming" / "release candidate" banners on the website and in `docs/` (`README.md`, `docs/README.md`, `docs/01`-`04`, `docs/10-faq.md`, `docs/migration/V1.0_BALANCE_AIRDROP.md`, white paper pending-release banner).
- [ ] Wallet app and explorer point to v1.1.1 and the new ports; no price feed is added.
- [ ] Run the compliance review checklist on every changed page; record a DECISIONS entry if anything economic changed.
- [ ] Announce on project channels with the release link only. No price, value or return language; no "buy" call to action.

## 9. Airdrop transparency (if done with this release)

- [ ] Publish the snapshot file hash, airdrop txids and reserve / QuarterMaster addresses as described in `docs/compliance/AIRDROPS.md` (on the `compliance-docs` branch).

---

## SHA256SUMS template (release body)

Fill from `AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt`. Replace every `<sha256>`; do not hand-type hashes.

```text
AMMOcoin v1.1.1 - SHA256 checksums
Signed file: AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt (+ .sig, verify with scripts/release/verify-release.sh at tag v1.1.1)

<sha256>  AMMOcoin-v1.1.1-Linux-ARM64-Qt.AppImage
<sha256>  AMMOcoin-v1.1.1-Linux-ARM64-Qt.tar.gz
<sha256>  AMMOcoin-v1.1.1-Linux-ARM64.tar.gz
<sha256>  AMMOcoin-v1.1.1-Linux-ARM64.zip
<sha256>  AMMOcoin-v1.1.1-Linux-amd64.deb
<sha256>  AMMOcoin-v1.1.1-Linux-arm64.deb
<sha256>  AMMOcoin-v1.1.1-Linux-x86_64-Qt.AppImage
<sha256>  AMMOcoin-v1.1.1-Linux-x86_64-Qt.tar.gz
<sha256>  AMMOcoin-v1.1.1-Linux-x86_64.tar.gz
<sha256>  AMMOcoin-v1.1.1-Linux-x86_64.zip
<sha256>  AMMOcoin-v1.1.1-Windows-x86_64-Setup.exe
<sha256>  AMMOcoin-v1.1.1-Windows-x86_64.tar.gz
<sha256>  AMMOcoin-v1.1.1-Windows-x86_64.zip
<sha256>  AMMOcoin-v1.1.1-macOS-ARM64.dmg
<sha256>  AMMOcoin-v1.1.1-macOS-ARM64.tar.gz
<sha256>  AMMOcoin-v1.1.1-macOS-ARM64.zip
<sha256>  AMMOcoin-v1.1.1-macOS-x86_64.dmg
<sha256>  AMMOcoin-v1.1.1-macOS-x86_64.tar.gz
<sha256>  AMMOcoin-v1.1.1-macOS-x86_64.zip
```

Sapling parameters (fetched from download.z.cash, not release assets):

```text
8e48ffd23abb3a5fd9c5589204f32d9c31285a04b78096ba40a79b75677efc13  sapling-spend.params
2f0ebbcbb9bb0bcffe95a397e7eba89c29eb4dde6191c339db88570e3f3fb0e4  sapling-output.params
```

Verify:

```bash
./scripts/release/verify-release.sh AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt
sha256sum -c AMMOcoin-v1.1.1-ALL-PLATFORMS-CHECKSUMS.txt --ignore-missing   # macOS: shasum -a 256 -c ...
```
