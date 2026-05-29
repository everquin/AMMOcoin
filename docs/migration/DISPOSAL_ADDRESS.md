# Canonical Disposal Wallet Address

**Status:** Not yet published — placeholder sentinel `PENDING-AMMO-CORE-PUBLICATION` in code.

The v1.0 → v1.1 migration requires holders of v1.0 AMMO to send their
balance to a one-way "disposal" wallet on the v1.0 chain, which the
AMMOcoin Core team uses as proof for distributing v1.1 AMMO on the new
chain (see commit `74c6ff1e`).

## Where the canonical address lives

The single source of truth is the constant `DISPOSAL_ADDRESS_CANONICAL`
in `scripts/migration/verify-disposal-address.py` at a **signed git
tag**. Any other "official" channel (email, chat, social media,
unsigned README) is **not** the source of truth and may be a phishing
attempt.

## How users verify they have the right address

```
# Clone the repo at the published tag
git clone https://github.com/everquin/AMMOcoin.git
cd AMMOcoin
git checkout v1.1.0-disposal-published   # or whatever tag the announcement names

# Verify the tag's signature (see docs/release/SIGNING.md)
./scripts/release/verify-release.sh CHANGELOG.md      # any signed file in the tag

# Run the verifier against the address you've been told about
python3 scripts/migration/verify-disposal-address.py <CANDIDATE_ADDRESS>
```

Expected output: `✅ Address matches canonical disposal address.` (or
a `❌` mismatch, in which case do not send).

## How the maintainer publishes the address

When the disposal wallet is finalized:

1. **Generate the disposal address** on an air-gapped machine. Keep no
   private key for it — this is a one-way burn. (If you need the v1.0
   AMMO sent there to be moveable for accounting, generate the key on a
   hardware wallet with a passphrase you commit to destroy after the
   migration window closes.)
2. **Commit the on-chain commitment**: broadcast a single v1.0
   transaction with an `OP_RETURN` containing the disposal address
   (base58, plain ASCII), signed by a well-known AMMOcoin Core wallet
   address. Record the resulting txid.
3. **Edit `scripts/migration/verify-disposal-address.py`**:
   ```python
   DISPOSAL_ADDRESS_CANONICAL = "<the address>"
   DISPOSAL_ADDRESS_ONCHAIN_COMMITMENT_TXID = "<the txid from step 2>"
   ```
4. **Sign the commit** with the release SSH key:
   `git commit -S` (with `git config gpg.format ssh` already set).
5. **Tag and publish**: e.g. `git tag -s v1.1.0-disposal-published` then
   `git push origin v1.1.0-disposal-published`.
6. **Announce** on every channel, always including the tag name and a
   `git log <tag> -p scripts/migration/verify-disposal-address.py`
   command so users can audit the diff themselves.

The combination of (a) commit signing, (b) on-chain commitment, and
(c) a signed git tag means an attacker has to compromise at least two
of {release SSH key, an AMMOcoin Core wallet, the GitHub repo} to
substitute a malicious address — none of which is plausible without
public detection.

## Why a sentinel placeholder instead of a "TBD" address

Pre-publishing a placeholder address risks users sending funds to it
either by accident (cut-and-paste) or by misreading docs as
authoritative. The `PENDING-` prefix makes the value an invalid
AMMOcoin address — wallets reject it at send time — and the verifier
hard-fails any comparison. This is intentional friction; it cannot be
removed until the real address is signed and tagged.
