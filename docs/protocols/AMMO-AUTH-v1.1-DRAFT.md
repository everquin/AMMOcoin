# AMMO-AUTH Protocol v1.1 (DRAFT)

**Version:** 1.1
**Status:** Draft — pending review
**Date:** 2026-05-29
**Authors:** AMMOcoin Core Team
**Supersedes:** v1.0 (see AMMO-AUTH-v1.md)

## What changed and why

The v1.0 audit identified three protocol-level flaws that prevented v1.0
from meeting its "tamper-proof" claim:

| Flaw (v1.0) | Mitigation (v1.1) |
|-------------|-------------------|
| **C1.** REGISTER has no proof the registrant ever held the chip — anyone who once scanned the chip can pre-empt the owner via first-seen. | Off-chain **chip proof-of-possession** committed via the existing `metadata_hash`. No change to on-chain message size. |
| **C2.** TRANSFER has no nonce / prev-txid binding / recipient consent — replayable, intra-block ordering non-deterministic, push-without-consent. | On-chain **`prev_txid`** binds each transfer to a specific predecessor. Off-chain **recipient countersignature** committed via a new `transfer_metadata_hash`. |
| **C3.** REVOKE is instant + single-sig + irreversible — brief wallet compromise bricks every item. | **Delayed effect**: REVOKE takes effect after 144 blocks (~6h) and can be cancelled by a subsequent REVOKE-CANCEL from the owner within that window. |

v1.1 also clarifies the spec ambiguities flagged by the audit (sender
definition for multi-input txs, intra-block ordering, endianness,
pubkey-form validation).

## On-chain compatibility

The v1.1 envelope and on-chain footprint were chosen so that **v1.0
indexers will read v1.1 messages as a different protocol version (0x02)
and ignore them**, rather than misinterpreting them. v1.1 indexers
preserve raw bytes of any AMMO-prefixed OP_RETURN with version > 0x02
for forward compatibility.

## Wire Format (unchanged envelope)

```
Offset  Size  Field       Description
──────  ────  ──────────  ─────────────────────────────
0       4     magic       ASCII "AMMO" (0x41 0x4D 0x4D 0x4F)
4       1     version     0x02  (v1.1 — was 0x01 in v1.0)
5       1     type        Message type identifier
6       N     payload     Type-specific data
```

**Total size:** 6 + N bytes (must be ≤ 80 bytes payload script-budget;
the on-chain scriptPubKey is `OP_RETURN || pushdata-prefix || payload`
and must satisfy `scriptPubKey.size() <= nMaxDatacarrierBytes` — see
`MAX_OP_RETURN_RELAY` in `source/src/script/standard.h`).

**All multi-byte integers are big-endian.** All txids and hashes are
stored on-chain in their natural display byte order (little-endian
internal, reversed for display); v1.1 follows the same convention.

## Message Types

### 0x01: REGISTER (v1.1)

Same on-chain layout as v1.0 REGISTER. The change is in what
`metadata_hash` MUST cover.

```
Offset  Size  Field              Description
──────  ────  ─────────────────  ─────────────────────────────────────
0       4     magic              "AMMO" (0x414D4D4F)
4       1     version            0x02
5       1     type               0x01 (REGISTER)
6       20    chip_pubkey_hash   HASH160 of the NFC chip's compressed public key
26      32    metadata_hash      SHA-256 of the canonical REGISTER metadata document
```

**Total: 58 bytes.**

#### REGISTER metadata document (off-chain, addressed by `metadata_hash`)

Canonical JSON per RFC 8785 (JCS). Required fields:

```jsonc
{
  "schema_version": "1.1",
  "chip_pubkey": "02ab...",                // 33-byte compressed secp256k1, hex-encoded
  "chip_anchor_block": 123456,             // Recent block height at time of signing
  "chip_anchor_block_hash": "00000…",      // Block hash at chip_anchor_block (anti-pre-sign)
  "chip_signature": "30…",                 // DER ECDSA signature, hex-encoded
  "registrant_address": "AAddr…",          // Same as the tx sender; redundancy for off-chain verify
  "name": "…",                             // Existing v1.0 fields (see v1.0 spec)
  "description": "…",
  "category": "…",
  "creator": { … },
  "attributes": { … },
  "media": [ … ]
}
```

#### Validation (v1.1, MUST all pass for the chip to be considered authentic)

A REGISTER is valid only if **all** of the following hold:

1. **On-chain:** `HASH160(SHA256(metadata_document_bytes))` equals
   `metadata_hash` on-chain. *(v1.0 already required this.)*
2. **Pubkey form:** `metadata.chip_pubkey` is exactly 33 bytes and begins
   with `0x02` or `0x03` (compressed form). Uncompressed keys MUST be
   rejected to prevent the hash-divergence attack.
3. **Hash binding:** `HASH160(metadata.chip_pubkey)` equals the on-chain
   `chip_pubkey_hash`.
4. **Proof of possession:** `metadata.chip_signature` is a valid ECDSA
   signature over the SHA-256 of the concatenation
   `"AMMO-AUTH-v1.1 REGISTER" || registrant_address ||
   chip_anchor_block_hash`, verified against `metadata.chip_pubkey`.
5. **Freshness:** `chip_anchor_block_hash` matches a real AMMOcoin block
   at `chip_anchor_block`, AND `chip_anchor_block` is no more than 1008
   blocks (~42h) before the on-chain REGISTER's confirmation height.
   This prevents a long-ago-scanned chip key from being weaponized
   months later.
6. **First-seen wins** *(only after passing 1-5)*: among multiple
   REGISTERs for the same `chip_pubkey_hash`, the earliest-confirmed
   valid one wins. Pre-emption by a scan-only attacker is no longer
   possible — they cannot produce a valid chip_signature.

### 0x02: TRANSFER (v1.1, new on-chain field)

```
Offset  Size  Field                    Description
──────  ────  ───────────────────────  ────────────────────────────────────────
0       4     magic                    "AMMO"
4       1     version                  0x02
5       1     type                     0x02 (TRANSFER)
6       20    chip_pubkey_hash         HASH160 of the chip key
26      20    new_owner_hash           HASH160 of the new owner's pubkey
46      32    prev_txid                txid of REGISTER or prior TRANSFER being chained
```

**Total: 78 bytes** (script size: 80 bytes).

#### Validation

1. **Sender authorization:** every input to the TRANSFER transaction
   that signs with SIGHASH_ALL must be controlled by the *current*
   owner. *Current owner* = the address whose `HASH160` equals
   `new_owner_hash` of the message identified by the previous valid
   TRANSFER, or the `registrant_address` from the REGISTER metadata if
   no transfer has occurred yet. **Inputs from non-owner addresses
   invalidate the TRANSFER.** (Fixes the "first input wins" ambiguity in
   v1.0.)
2. **Predecessor binding:** `prev_txid` MUST equal the txid of the
   immediately previous valid AMMO-AUTH message for this
   `chip_pubkey_hash` (REGISTER or TRANSFER). A v1.1 indexer rejects
   any TRANSFER whose `prev_txid` does not match the canonical chain
   head — even from the current owner. This eliminates the replay and
   parallel-fork attacks of v1.0.
3. **Intra-block ordering:** if two valid TRANSFERs both reference the
   same `prev_txid` and confirm in the same block, the one whose
   transaction index in the block is lower wins. (Spec-mandated
   tiebreak: previously indeterminate.)
4. **Recipient consent (optional but recommended):** the new owner
   confirms acceptance by broadcasting a single TRANSFER-ACK
   (type 0x12) at any time after the TRANSFER confirms. Until ACK,
   the new owner is shown as "pending" in compliant clients;
   third-party reputation systems SHOULD NOT treat the chip as
   reassigned for liability/regulatory purposes until ACK is seen.
   This prevents weaponized forced-transfers without making opt-in a
   hard requirement.

### 0x12: TRANSFER-ACK (v1.1, new)

```
Offset  Size  Field              Description
──────  ────  ─────────────────  ─────────────────────────────────────
0       4     magic              "AMMO"
4       1     version            0x02
5       1     type               0x12 (TRANSFER-ACK)
6       20    chip_pubkey_hash   HASH160 of the chip key
26      32    transfer_txid      txid of the TRANSFER being acknowledged
```

**Total: 58 bytes.**

**Validation:** the sender must equal the `new_owner_hash` of the
referenced TRANSFER. Cosmetic only — does not alter ownership; only
flips the "pending" flag in clients.

### 0x03: REVOKE (v1.1, delayed-effect)

```
Offset  Size  Field              Description
──────  ────  ─────────────────  ─────────────────────────────────────
0       4     magic              "AMMO"
4       1     version            0x02
5       1     type               0x03 (REVOKE)
6       20    chip_pubkey_hash   HASH160 of the chip key
26      1     reason_code        Revocation reason (codes unchanged from v1.0)
```

**Total: 27 bytes.**

#### Validation

1. **Sender authorization:** as for TRANSFER — every signing input must
   be from the current owner.
2. **Delayed effect:** a REVOKE takes effect at confirmation height
   `H + REVOKE_DELAY_BLOCKS` (default: 144, ≈ 6 hours), NOT at
   confirmation height. Transfers and ACKs that confirm in the delay
   window remain valid until the effective height. After the effective
   height, no further AMMO-AUTH messages for that chip are valid.
3. **Cancellation:** the current owner may broadcast a REVOKE-CANCEL
   (type 0x13) at any height `< H + REVOKE_DELAY_BLOCKS` to nullify a
   pending REVOKE. This is the recovery path for a compromised wallet
   that issues a malicious REVOKE before the legitimate owner can
   stop it — provided the owner notices within the window.
4. **Irreversibility after effective height:** once the delay window
   passes without cancellation, the REVOKE is permanent.

### 0x13: REVOKE-CANCEL (v1.1, new)

```
Offset  Size  Field              Description
──────  ────  ─────────────────  ─────────────────────────────────────
0       4     magic              "AMMO"
4       1     version            0x02
5       1     type               0x13 (REVOKE-CANCEL)
6       20    chip_pubkey_hash   HASH160 of the chip key
26      32    revoke_txid        txid of the REVOKE being cancelled
```

**Total: 58 bytes.**

**Validation:** sender must equal current owner; `revoke_txid` must
identify a REVOKE that has not yet taken effect; cancellation itself
takes effect immediately.

## Spec Clarifications (resolutions to v1.0 ambiguities)

- **Sender of a multi-input tx:** every input that signs with
  SIGHASH_ALL must be from the current owner. (v1.0 said "the sender";
  implementations diverged on which input.)
- **Intra-block ordering:** transaction index ascending; for the rare
  case of identical prev_txid bindings (an indexer bug or chain
  reorganisation), txid lex order is the final tiebreak.
- **Endianness:** all multi-byte integers in v1.1 messages are
  big-endian. Hashes and txids are stored in their natural display
  byte order. *(v1.0 was silent.)*
- **APDU SIGN response format:** SIGN MUST return raw 64-byte (r ||
  s) Schnorr-style signatures, NOT DER. This eliminates the
  variable-length parsing ambiguity flagged by the audit. (Chip
  firmware change required.)
- **Metadata canonical JSON:** RFC 8785 (JCS) is now normative.

## Indexer Requirements (v1.1)

A v1.1-compliant indexer MUST:

1. Verify all on-chain validation rules above before adding a record to
   the index — invalid REGISTERs/TRANSFERs/REVOKEs are dropped, not
   merely flagged.
2. Fetch the metadata document for every REGISTER and verify
   proof-of-possession before treating the chip as "authentic." Chips
   whose metadata is unreachable are flagged as "unverified" — never
   "authentic."
3. Preserve raw bytes of any unrecognised AMMO-prefixed OP_RETURN
   (version > 0x02) so that future indexer versions can re-process the
   chain.
4. Use deterministic per-block tiebreaking (tx index ascending) so two
   honest indexers produce identical state.

## Migration from v1.0

v1.0 chips already on-chain remain visible to v1.1 indexers but are
displayed as "v1.0 — proof of possession not verified". Owners who
want to upgrade can issue a v1.1 REGISTER-UPGRADE (type 0x21,
specification deferred to a future revision) referencing the
original v1.0 REGISTER's txid; ownership history transfers across.
v1.1 chips MUST NOT be downgraded to v1.0 — no protocol path is
provided.

## Implementation impact (estimate)

| Component | Change |
|-----------|--------|
| Daemon `source/src/script/standard.h` | No change (envelope fits within current `MAX_OP_RETURN_RELAY`). |
| Daemon `source/src/rpc/rawtransaction.cpp` | `sendopreturn` is sufficient; no new RPCs needed. |
| Explorer `blockchain-explorer/src/app/api/auth/lookup/route.ts` | Significant: validate proof-of-possession, prev-txid chaining, delayed REVOKE, recipient ACK, transfer authorization via address. ~300 LOC. |
| Flutter app `AMMOcoin_App/lib/services/auth_protocol_service.dart` | Produce v1.1 messages, perform chip sign/verify, fetch+verify metadata. ~500 LOC. |
| Chip firmware | SIGN must return raw 64-byte sig (not DER). Embedded change, requires re-flash. |
| Spec docs | This file becomes `AMMO-AUTH-v1.1.md` (drop -DRAFT) once approved. |

## Open questions for review

1. **`chip_anchor_block` freshness window** — 1008 blocks (~42h) chosen
   to allow chips to be pre-signed during manufacturing/distribution
   but invalidate stale captures. Is this the right window for the
   physical-goods use case?
2. **TRANSFER-ACK opt-in vs mandatory** — v1.1 makes ACK optional to
   avoid breaking the "send chip to a fresh address" use case. Should
   it be mandatory for high-value categories (firearm_accessory, art)?
3. **REVOKE delay length** — 144 blocks (~6h) balances recovery
   window vs. legitimate revocation latency. Acceptable?
4. **REGISTER-UPGRADE path** — deferred. Should v1.1 ship without an
   upgrade path for existing v1.0 chips, or block on defining one?

---

**This draft is for review only. Do not implement until approved and
the -DRAFT suffix is removed.**
