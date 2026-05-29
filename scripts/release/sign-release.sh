#!/usr/bin/env bash
# AMMOcoin release signer.
#
# Produces a detached SSH-key signature next to the input file (e.g.
# CHECKSUMS.txt -> CHECKSUMS.txt.sig). Uses OpenSSH's `ssh-keygen -Y sign`,
# which is the same primitive git uses for SSH-key commit signing.
#
# Usage:
#   ./sign-release.sh <file-to-sign> [<file-to-sign> ...]
#
# Environment:
#   AMMOCOIN_SIGN_KEY   Path to the SSH private key (default: ~/.ssh/id_ed25519)
#   AMMOCOIN_SIGN_NS    Signing namespace (default: "file" — matches verifier)
#
# Example:
#   AMMOCOIN_SIGN_KEY=~/.ssh/ammocoin_release_ed25519 \
#     ./scripts/release/sign-release.sh releases/AMMOcoin-v1.1.0-ALL-PLATFORMS-CHECKSUMS.txt

set -euo pipefail

SIGN_KEY="${AMMOCOIN_SIGN_KEY:-$HOME/.ssh/id_ed25519}"
NAMESPACE="${AMMOCOIN_SIGN_NS:-file}"

if [[ $# -lt 1 ]]; then
    echo "Usage: $0 <file-to-sign> [<file-to-sign> ...]" >&2
    exit 2
fi

if [[ ! -f "$SIGN_KEY" ]]; then
    echo "❌ Signing key not found: $SIGN_KEY" >&2
    echo "   Set AMMOCOIN_SIGN_KEY to your release key, or use the default ~/.ssh/id_ed25519." >&2
    exit 1
fi

# Reject RSA keys < 3072 bits. SSH-key signing accepts any key the agent
# accepts, but a weak RSA key would be a silent downgrade.
KEYTYPE=$(ssh-keygen -l -f "$SIGN_KEY" 2>/dev/null | awk '{print $4}' | tr -d '()')
KEYBITS=$(ssh-keygen -l -f "$SIGN_KEY" 2>/dev/null | awk '{print $1}')
case "$KEYTYPE" in
    ED25519|ED25519-SK|ECDSA|ECDSA-SK) ;;
    RSA)
        if [[ "$KEYBITS" -lt 3072 ]]; then
            echo "❌ RSA key is only $KEYBITS bits. Use >=3072-bit RSA or (preferred) Ed25519." >&2
            exit 1
        fi
        ;;
    *)
        echo "⚠️  Unknown key type '$KEYTYPE'. Proceeding, but verify the verifier accepts it." >&2
        ;;
esac

echo "🔐 Signing with: $SIGN_KEY ($KEYTYPE $KEYBITS-bit)"
echo "   Namespace: $NAMESPACE"
echo ""

for f in "$@"; do
    if [[ ! -f "$f" ]]; then
        echo "❌ Not a regular file: $f" >&2
        exit 1
    fi
    # ssh-keygen -Y sign writes "$f.sig" next to the input.
    ssh-keygen -Y sign -f "$SIGN_KEY" -n "$NAMESPACE" "$f"
    echo "✓ Signed: $f -> $f.sig"
done

echo ""
echo "📦 Publish both <file> and <file>.sig together."
echo "   Users verify with: scripts/release/verify-release.sh <file>"
