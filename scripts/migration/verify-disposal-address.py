#!/usr/bin/env python3
"""
Verify that a candidate disposal-wallet address matches the canonical one
pinned in this repository.

USERS SHOULD RUN THIS before sending any v1.0 AMMO to a "disposal" address
that they've been told about via email, chat, social media, or any other
out-of-band channel. Phishing for the v1.0→v1.1 migration is the highest-
value attack against AMMOcoin holders today: a single wrong address email
to the migration cohort can drain millions of AMMO.

Usage:
    python3 verify-disposal-address.py <candidate-address>

Exit codes:
    0  — candidate matches the pinned canonical address (safe to send)
    1  — mismatch OR canonical address has not yet been published (DO NOT SEND)
    2  — usage error
"""

import sys
from pathlib import Path

# The canonical AMMOcoin v1.0→v1.1 migration disposal address.
#
# Sentinel "PENDING-<reason>" until the AMMOcoin Core team publishes the
# real address via a signed release commit. The verifier below hard-fails
# while the sentinel is in place, so users cannot be misled into sending
# funds before this is finalized.
#
# When publishing the real address:
#   1. Replace the sentinel with the actual base58 address.
#   2. Sign the commit using the SSH release key in scripts/release/.
#   3. Tag the release and announce; the tag is what users verify against.
DISPOSAL_ADDRESS_CANONICAL = "PENDING-AMMO-CORE-PUBLICATION"

# Optional: the txid of an on-chain commitment (on the v1.0 chain) that
# anchors this address. Verifiers can additionally check this via a v1.0
# block explorer once published.
DISPOSAL_ADDRESS_ONCHAIN_COMMITMENT_TXID = "PENDING"


def is_sentinel(value: str) -> bool:
    return value.startswith("PENDING")


def main() -> int:
    if len(sys.argv) != 2:
        print("Usage: python3 verify-disposal-address.py <candidate-address>", file=sys.stderr)
        return 2

    candidate = sys.argv[1].strip()

    if is_sentinel(DISPOSAL_ADDRESS_CANONICAL):
        print("❌ The canonical disposal address has NOT been published yet.")
        print(f"   Pinned value: {DISPOSAL_ADDRESS_CANONICAL!r}")
        print()
        print("   DO NOT SEND any v1.0 AMMO to a disposal address until the")
        print("   AMMOcoin Core team publishes the address in a signed commit")
        print("   to this repository (file: scripts/migration/verify-disposal-address.py).")
        print()
        print("   You can subscribe to the project's release feed at")
        print("   https://github.com/everquin/AMMOcoin/releases to be notified.")
        return 1

    if candidate == DISPOSAL_ADDRESS_CANONICAL:
        print(f"✅ Address matches canonical disposal address.")
        print(f"   Address:           {DISPOSAL_ADDRESS_CANONICAL}")
        print(f"   v1.0 commitment:   {DISPOSAL_ADDRESS_ONCHAIN_COMMITMENT_TXID}")
        print()
        print("   You can additionally cross-check the commitment txid above")
        print("   on a trusted v1.0 block explorer to confirm the address was")
        print("   announced on-chain by the AMMOcoin Core team.")
        return 0

    print(f"❌ MISMATCH — the candidate address does NOT match the canonical disposal address.")
    print(f"   Candidate (DO NOT USE): {candidate}")
    print(f"   Canonical:              {DISPOSAL_ADDRESS_CANONICAL}")
    print()
    print("   This is almost certainly a phishing attempt. Do not send funds.")
    print("   Report the source of the wrong address to the AMMOcoin Core team.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
