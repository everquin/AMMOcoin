# AMMO-AUTH Protocol v1

**Version:** 1.0
**Status:** Draft
**Date:** 2026-03-05
**Authors:** AMMOcoin Core Team

## Abstract

AMMO-AUTH is an on-chain authentication protocol for AMMOcoin that enables tamper-proof registration, transfer, and revocation of physical and digital items using NFC chips with secure elements. Item provenance is recorded immutably on the AMMOcoin blockchain via OP_RETURN transactions.

## Motivation

Counterfeiting of physical goods (art, collectibles, luxury items, firearms accessories) is a multi-billion dollar problem. Existing solutions rely on centralized databases that can be altered or taken offline. AMMO-AUTH leverages AMMOcoin's blockchain to provide:

- **Immutable registration** — creators register items on-chain with a single transaction
- **Cryptographic verification** — NFC chips with secure elements prove physical possession
- **Decentralized provenance** — full ownership history is publicly verifiable
- **Tamper evidence** — chip removal or cloning is detectable via challenge-response

## Design Principles

1. **Fit within OP_RETURN limits** — AMMOcoin allows 83 bytes of OP_RETURN data; all messages fit within this constraint
2. **Minimal on-chain footprint** — only hashes stored on-chain; metadata lives off-chain (IPFS, web)
3. **Implicit identity** — the transaction sender address IS the creator/owner identity (no extra field needed)
4. **Standard cryptography** — secp256k1 ECDSA throughout, matching AMMOcoin's native curve

## On-Chain Wire Format

All AMMO-AUTH messages are embedded in OP_RETURN transaction outputs with the following envelope:

```
Offset  Size  Field       Description
──────  ────  ──────────  ─────────────────────────────
0       4     magic       ASCII "AMMO" (0x41 0x4D 0x4D 0x4F)
4       1     version     Protocol version (0x01)
5       1     type        Message type identifier
6       N     payload     Type-specific data (variable length)
```

**Total size:** 6 + N bytes (must be ≤ 83 bytes)

### Message Type 0x01: REGISTER

Registers a new item on the blockchain. The sender address of this transaction is implicitly the **creator** of the item.

```
Offset  Size  Field              Description
──────  ────  ─────────────────  ─────────────────────────────────────
0       4     magic              "AMMO" (0x414D4D4F)
4       1     version            0x01
5       1     type               0x01 (REGISTER)
6       20    chip_pubkey_hash   HASH160 of the NFC chip's compressed public key
26      32    metadata_hash      SHA-256 hash of off-chain metadata (JSON)
```

**Total: 58 bytes** (within 83-byte limit)

**Semantics:**
- The transaction's sending address = creator identity
- `chip_pubkey_hash` = HASH160(compressed_secp256k1_pubkey) of the NFC chip's secure element
- `metadata_hash` = SHA-256 of a canonical JSON metadata document stored off-chain
- Only one REGISTER per `chip_pubkey_hash` is valid (first seen wins)

### Message Type 0x02: TRANSFER

Transfers ownership of a registered item. The sender must be the current owner.

```
Offset  Size  Field              Description
──────  ────  ─────────────────  ─────────────────────────────────────
0       4     magic              "AMMO" (0x414D4D4F)
4       1     version            0x01
5       1     type               0x02 (TRANSFER)
6       20    chip_pubkey_hash   HASH160 of the NFC chip's public key
26      20    new_owner_hash     HASH160 of the new owner's AMMOcoin public key
```

**Total: 46 bytes** (within 83-byte limit)

**Semantics:**
- The sender must be the current owner (creator for first transfer, or last TRANSFER recipient)
- `new_owner_hash` corresponds to the new owner's AMMOcoin address
- Ownership chain is validated by walking REGISTER → TRANSFER transactions

### Message Type 0x03: REVOKE

Revokes/deactivates an item registration. Only the current owner can revoke.

```
Offset  Size  Field              Description
──────  ────  ─────────────────  ─────────────────────────────────────
0       4     magic              "AMMO" (0x414D4D4F)
4       1     version            0x01
5       1     type               0x03 (REVOKE)
6       20    chip_pubkey_hash   HASH160 of the NFC chip's public key
26      1     reason_code        Revocation reason
```

**Total: 27 bytes** (within 83-byte limit)

**Reason codes:**

| Code | Meaning              |
|------|----------------------|
| 0x00 | Unspecified          |
| 0x01 | Item destroyed       |
| 0x02 | Chip compromised     |
| 0x03 | Duplicate/counterfeit|
| 0x04 | Owner request        |

**Semantics:**
- After revocation, no further TRANSFER messages are valid for this `chip_pubkey_hash`
- Revocation is permanent and irreversible
- Verification clients MUST check for revocation before reporting an item as authentic

## Off-Chain Metadata

The metadata document referenced by `metadata_hash` in REGISTER messages is a canonical JSON object stored off-chain (IPFS, HTTPS, or any addressable storage).

### Metadata Schema

```json
{
  "schema_version": "1.0",
  "name": "Item Name",
  "description": "Detailed description",
  "category": "art|collectible|firearm_accessory|luxury|other",
  "creator": {
    "name": "Creator Name",
    "url": "https://creator.example.com"
  },
  "item": {
    "serial": "Optional serial number",
    "manufacture_date": "2026-01-15",
    "edition": "1 of 100"
  },
  "media": [
    {
      "type": "image/jpeg",
      "url": "ipfs://Qm...",
      "hash": "sha256:abcdef..."
    }
  ],
  "storage_url": "ipfs://Qm... or https://..."
}
```

**Canonical JSON rules for hashing:**
1. Keys sorted alphabetically at all levels
2. No whitespace outside strings
3. UTF-8 encoding
4. No trailing commas

## NFC Challenge-Response Protocol

The challenge-response protocol proves physical possession of an NFC chip that corresponds to an on-chain registration.

### Prerequisites

- NFC chip contains a secp256k1 keypair in its secure element
- The chip's private key NEVER leaves the secure element
- The chip's compressed public key is known (written during manufacturing)
- HASH160 of the compressed public key matches an on-chain REGISTER record

### Flow

```
┌──────────┐                    ┌──────────┐                 ┌────────────┐
│  Phone   │                    │ NFC Chip │                 │ Blockchain │
│  (App)   │                    │ (Secure  │                 │            │
│          │                    │ Element) │                 │            │
└────┬─────┘                    └────┬─────┘                 └─────┬──────┘
     │                               │                             │
     │  1. Generate 32-byte nonce    │                             │
     │  ─────────────────────────>   │                             │
     │     (APDU: SIGN command)      │                             │
     │                               │                             │
     │  2. Sign nonce with           │                             │
     │     chip's private key        │                             │
     │                               │                             │
     │  3. Return signature +        │                             │
     │     compressed public key     │                             │
     │  <─────────────────────────   │                             │
     │                               │                             │
     │  4. Compute HASH160(pubkey)   │                             │
     │                               │                             │
     │  5. Query AMMO-AUTH records   │                             │
     │     for chip_pubkey_hash      │                             │
     │  ─────────────────────────────────────────────────────────> │
     │                                                             │
     │  6. Return REGISTER +         │                             │
     │     TRANSFER chain +          │                             │
     │     revocation status         │                             │
     │  <───────────────────────────────────────────────────────── │
     │                               │                             │
     │  7. Verify ECDSA signature    │                             │
     │     (nonce, pubkey, sig)      │                             │
     │                               │                             │
     │  8. Display result:           │                             │
     │     ✓ Authentic / ✗ Fake      │                             │
     │                               │                             │
```

### Verification Steps (Detail)

1. **Generate nonce:** Phone generates 32 cryptographically random bytes
2. **Send to chip:** Via NFC APDU command (ISO 7816-4), send SIGN command with nonce
3. **Chip signs:** Secure element computes ECDSA signature over SHA-256(nonce) using its private key
4. **Chip responds:** Returns DER-encoded signature (max 72 bytes) + 33-byte compressed public key
5. **Compute hash:** Phone computes `chip_pubkey_hash = RIPEMD160(SHA256(compressed_pubkey))`
6. **Blockchain lookup:** Query explorer API for all AMMO-AUTH OP_RETURN records matching `chip_pubkey_hash`
7. **Verify signature:** `ECDSA_verify(SHA256(nonce), signature, pubkey)` — confirms physical possession
8. **Validate chain:** Check REGISTER exists, walk TRANSFER chain, check for REVOKE

### Result Classification

| Condition | Result |
|-----------|--------|
| Valid signature + REGISTER found + no REVOKE | **Authentic** |
| Valid signature + REGISTER found + REVOKE exists | **Revoked** (was authentic, now deactivated) |
| Valid signature + no REGISTER found | **Unregistered** (chip is real but not registered) |
| Invalid signature | **Counterfeit** (chip is fake or tampered) |
| No NFC chip detected | **No chip** (item lacks authentication hardware) |

## Provenance Chain

The complete provenance of an item is reconstructed by scanning the blockchain for all AMMO-AUTH transactions referencing a given `chip_pubkey_hash`, ordered by block height:

```
Block 10000: REGISTER  — Creator: AAddr1, Metadata: 0xabc...
Block 10500: TRANSFER  — From: AAddr1 → To: AAddr2
Block 11200: TRANSFER  — From: AAddr2 → To: AAddr3
Block 15000: REVOKE    — By: AAddr3, Reason: Item destroyed
```

### Validation Rules

1. The first transaction MUST be a REGISTER (no orphan TRANSFERs)
2. Each TRANSFER sender must match the current owner (creator for first, last TRANSFER recipient after)
3. No transactions after a REVOKE are valid
4. Transactions from unauthorized senders are ignored (invalid TRANSFERs)

## APDU Command Specification

### SIGN Command (Phone → Chip)

| Field | Value | Description |
|-------|-------|-------------|
| CLA   | 0x80  | Custom class |
| INS   | 0x01  | SIGN instruction |
| P1    | 0x00  | Reserved |
| P2    | 0x00  | Reserved |
| Lc    | 0x20  | Data length (32 bytes) |
| Data  | nonce | 32-byte random nonce |
| Le    | 0x00  | Expect variable-length response |

### SIGN Response (Chip → Phone)

| Field      | Size     | Description |
|------------|----------|-------------|
| signature  | 64-72    | DER-encoded ECDSA signature |
| pubkey     | 33       | Compressed secp256k1 public key |
| SW1-SW2    | 2        | Status word (0x9000 = success) |

### GET_PUBKEY Command (Phone → Chip)

| Field | Value | Description |
|-------|-------|-------------|
| CLA   | 0x80  | Custom class |
| INS   | 0x02  | GET_PUBKEY instruction |
| P1    | 0x00  | Reserved |
| P2    | 0x00  | Reserved |
| Le    | 0x21  | Expected length (33 bytes) |

## RPC Support

### `sendopreturn` RPC Command

High-level RPC command for creating AMMO-AUTH transactions:

```
sendopreturn "fromaddress" "hexdata"

Arguments:
1. "fromaddress"  (string, required) The sender address
2. "hexdata"      (string, required) Hex-encoded OP_RETURN payload

Result:
"txid"            (string) The transaction ID

Example:
ammocoin-cli sendopreturn "AAddr1" "414d4d4f010100112233...aabbccdd"
```

### `createrawtransaction` Extension

The `createrawtransaction` RPC now supports a `"data"` key in the outputs object:

```json
{
  "data": "414d4d4f0101..."
}
```

This creates an OP_RETURN output with the given hex data.

## Explorer API

### `GET /api/auth/lookup?hash=<chip_pubkey_hash_hex>`

Returns all AMMO-AUTH records for a given chip public key hash.

```json
{
  "chip_pubkey_hash": "00112233445566778899aabbccddeeff00112233",
  "records": [
    {
      "type": "REGISTER",
      "txid": "abc123...",
      "block_height": 10000,
      "block_time": 1709654400,
      "creator_address": "AAddr1",
      "metadata_hash": "def456..."
    },
    {
      "type": "TRANSFER",
      "txid": "ghi789...",
      "block_height": 10500,
      "block_time": 1709784000,
      "from_address": "AAddr1",
      "new_owner_hash": "aabbccdd..."
    }
  ],
  "current_owner": "AAddr2",
  "is_revoked": false,
  "status": "authentic"
}
```

## Security Considerations

1. **Chip cloning:** Secure elements are designed to prevent private key extraction. Physical tampering destroys the chip.
2. **Replay attacks:** The 32-byte random nonce ensures each challenge-response is unique.
3. **Man-in-the-middle:** NFC range is ~4cm, limiting interception. The challenge is generated locally.
4. **Blockchain reorganizations:** Use sufficient confirmation depth (6+ blocks) before trusting REGISTER records.
5. **Metadata integrity:** Off-chain metadata is verified by comparing its SHA-256 hash against the on-chain `metadata_hash`.
6. **First-seen rule:** Only the first REGISTER for a `chip_pubkey_hash` is valid, preventing registration squatting after the fact.

## Future Extensions (v2)

- **Batch registration:** Multiple items in one transaction using serialized records
- **Metadata update:** New message type to update the metadata hash without transferring ownership
- **Multi-signature ownership:** Require M-of-N signatures for high-value items
- **Time-locked transfers:** Transfers that become valid after a specified block height
- **Price feed integration:** Embed item valuation in AMMO at time of registration

## Reference Implementation

- **C++ core:** `source/src/script/standard.cpp` — `GetScriptForOpReturn(vector<unsigned char>)` overload
- **RPC:** `source/src/rpc/rawtransaction.cpp` — `sendopreturn` command and `createrawtransaction` data support
- **Explorer API:** `blockchain-explorer/src/app/api/auth/lookup/route.ts`
- **Flutter app:** `AMMOcoin_App/lib/services/auth_protocol_service.dart`
