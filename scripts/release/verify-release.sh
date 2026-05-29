#!/usr/bin/env bash
# AMMOcoin release verifier.
#
# Verifies a detached SSH-key signature produced by sign-release.sh.
# Pinned signer identities live in `scripts/release/allowed_signers`.
#
# Usage:
#   ./verify-release.sh <signed-file>
#
# The script looks for <signed-file>.sig next to <signed-file>.
#
# Environment:
#   AMMOCOIN_ALLOWED_SIGNERS  Override path to allowed_signers (default: alongside this script)
#   AMMOCOIN_SIGN_NS          Signing namespace (default: "file" — must match signer)
#   AMMOCOIN_SIGN_IDENTITY    Expected signer identity from allowed_signers (default: release@ammocoin.org)

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
ALLOWED_SIGNERS="${AMMOCOIN_ALLOWED_SIGNERS:-$SCRIPT_DIR/allowed_signers}"
NAMESPACE="${AMMOCOIN_SIGN_NS:-file}"
IDENTITY="${AMMOCOIN_SIGN_IDENTITY:-release@ammocoin.org}"

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <signed-file>" >&2
    echo "  Expects <signed-file>.sig to exist alongside the file." >&2
    exit 2
fi

FILE="$1"
SIGFILE="${FILE}.sig"

if [[ ! -f "$FILE" ]]; then
    echo "❌ File not found: $FILE" >&2
    exit 1
fi
if [[ ! -f "$SIGFILE" ]]; then
    echo "❌ Signature not found: $SIGFILE" >&2
    echo "   Download the .sig file from the same release as the artifact." >&2
    exit 1
fi
if [[ ! -f "$ALLOWED_SIGNERS" ]]; then
    echo "❌ allowed_signers file not found: $ALLOWED_SIGNERS" >&2
    echo "   This file pins the public keys trusted to sign AMMOcoin releases." >&2
    exit 1
fi

# Check there is at least one non-comment, non-blank line.
if ! grep -Ev '^[[:space:]]*(#|$)' "$ALLOWED_SIGNERS" >/dev/null; then
    echo "❌ allowed_signers contains no trusted keys (only comments / blank lines)." >&2
    echo "   The maintainer has not yet pinned a release-signing key. Refusing to verify." >&2
    exit 1
fi

echo "🔍 Verifying $FILE"
echo "   Signature:  $SIGFILE"
echo "   Identity:   $IDENTITY"
echo "   Signers:    $ALLOWED_SIGNERS"
echo ""

# ssh-keygen -Y verify reads the file-to-verify from stdin.
if ssh-keygen -Y verify \
    -f "$ALLOWED_SIGNERS" \
    -I "$IDENTITY" \
    -n "$NAMESPACE" \
    -s "$SIGFILE" \
    <"$FILE"; then
    echo ""
    echo "✅ Signature is valid."
    echo "   The release was signed by '$IDENTITY' using a key listed in allowed_signers."
    echo "   You can now trust the SHA256 sums in this file."
    exit 0
else
    echo ""
    echo "❌ Signature verification FAILED."
    echo "   Do NOT install this release. The artifact may have been tampered with,"
    echo "   or you may be using an out-of-date allowed_signers file."
    exit 1
fi
