# Verifying AMMOcoin Release Signatures

AMMOcoin releases are signed with an SSH key (OpenSSH `ssh-keygen -Y sign`,
the same primitive git uses for SSH-key commit signing). SHA256 checksums
alone protect against accidental corruption; the signature protects against
deliberate substitution on GitHub Releases or a mirror.

Two artifacts are published per release:

- `AMMOcoin-vX.Y.Z-ALL-PLATFORMS-CHECKSUMS.txt` — SHA256 of every binary
- `AMMOcoin-vX.Y.Z-ALL-PLATFORMS-CHECKSUMS.txt.sig` — detached SSH-key signature

## For users: verifying a release

**Prerequisite:** OpenSSH 8.0 or newer (`ssh-keygen` with `-Y` subcommand).
Check with `ssh-keygen -Y verify 2>&1 | head -1` — if you see a usage message,
you're good.

1. Download from the same release:
   - the binary you want to install (e.g. `AMMOcoin-v1.1.0-Linux-x86_64.tar.gz`)
   - the `…CHECKSUMS.txt` file
   - the `…CHECKSUMS.txt.sig` file (must be from the *same* release tag)
2. Clone this repository (or download `scripts/release/`) — you need
   `verify-release.sh` and `allowed_signers`. **Do not** download
   `allowed_signers` from anywhere except this repository at a tagged commit;
   that file is the trust root.
3. Verify the signature:
   ```
   ./scripts/release/verify-release.sh AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt
   ```
   Expected output ends with `✅ Signature is valid.`
4. Verify the binary's checksum matches the (now-trusted) CHECKSUMS file:
   ```
   sha256sum -c AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt 2>&1 \
     | grep AMMOcoin-v1.1.0-Linux-x86_64.tar.gz
   ```
   Expected: `…tar.gz: OK`.

If either step fails, **do not run the binary.** Open an issue against the
GitHub repo. A failed verification is more likely a corrupt download or an
outdated `allowed_signers` than a real attack — but treat it as the latter
until you confirm.

## For the release maintainer: signing a release

**One-time key setup** (do this once, on an offline or hardware-protected
machine; never on a CI runner):

```bash
ssh-keygen -t ed25519 \
  -f ~/.ssh/ammocoin_release_ed25519 \
  -C "release@ammocoin.org"
```

Use a strong passphrase. Back up `ammocoin_release_ed25519` (the private key)
to encrypted offline storage — losing it forces a key-rotation announcement.

**Pin the public key in the repo:**

1. Open `scripts/release/allowed_signers`.
2. Append a line of the form
   `release@ammocoin.org ssh-ed25519 AAAA…<base64>… release@ammocoin.org`
   (copy from `~/.ssh/ammocoin_release_ed25519.pub` and prepend the identity).
3. Commit and tag. Once tagged, users at that tag (or later) can verify.

**Signing a release:**

```bash
AMMOCOIN_SIGN_KEY=~/.ssh/ammocoin_release_ed25519 \
  ./scripts/release/sign-release.sh \
    releases/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt
```

This produces `…CHECKSUMS.txt.sig`. Upload **both** files to the GitHub
Release. Per-platform `…-CHECKSUM.txt` files in `releases/` are
convenience artifacts; only the aggregate file needs a signature.

## Key rotation

If the release key is compromised or rotated:

1. Push a commit that **removes** the old key line from `allowed_signers`
   and **adds** the new one. Sign that commit with the *new* key.
2. Cut a new release signed with the new key.
3. Publish a notice (GitHub Releases description, project channels) saying
   the old key is revoked as of commit `<sha>` and any signature it produces
   from now on should be rejected.

Users who track the repo by pulling tags pick up the new `allowed_signers`
automatically; users running an older checkout will fail verification until
they update — which is the desired behaviour.

## Why SSH-key signing (not GPG)?

- Re-uses an existing OpenSSH key — no separate keyring, no `gpg-agent`.
- Verifier is `ssh-keygen`, already installed everywhere a developer would
  build from source.
- `allowed_signers` is plain text and version-controlled; the trust root is
  the git history, not a keyserver.
- Same model git itself uses (`gpg.format = ssh`), so signers reuse muscle
  memory.

The trade-off: SSH signing has no equivalent of GPG's web of trust. AMMOcoin
mitigates this by pinning keys directly in this repo — the trust assumption
is "the maintainer who controls write access to `allowed_signers` is the
same one whose signature appears in `…CHECKSUMS.txt.sig`."
