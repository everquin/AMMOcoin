# Paper Wallet Generator - Security Audit for v1.1.0

**Audit Date:** January 3, 2026
**Status:** ❌ **NOT PRODUCTION READY - CRITICAL SECURITY FLAW**
**Auditor:** Claude Code

---

## Executive Summary

The AMMOcoin Paper Wallet Generator has correct network parameters for v1.1.0 (address version 0x17, WIF version 0x97) and proper security features, but contains a **CRITICAL FLAW** that makes it **NON-FUNCTIONAL** for real-world use.

### Critical Finding

**Lines 387-396**: The `generatePublicKey()` function does NOT implement proper secp256k1 elliptic curve cryptography. It simply hashes the private key with SHA256, which means:

- Generated addresses are INVALID
- Private keys do NOT correspond to displayed addresses
- Users CANNOT import these wallets into AMMOcoin clients
- This tool is DEMONSTRATION ONLY

**⚠️ DO NOT USE THIS TOOL FOR REAL FUNDS UNTIL FIXED**

---

## Detailed Findings

### ✅ Correct Configuration

#### Network Parameters (lines 290-294)
```javascript
const NETWORK = {
    version: 0x17,              // ✅ Correct AMMOcoin address version
    privateKeyVersion: 0x97,    // ✅ Correct WIF private key version
    scriptVersion: 0x7D         // ✅ Correct script version
};
```

**Verification:**
- Address version 0x17 matches `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin/src/chainparams.cpp:105`
- WIF version 0x97 matches standard AMMOcoin format
- All network parameters align with v1.1.0 release

#### Version Labeling
- Line 228: Correctly shows "Secure Paper Wallet Generator v1.1.0"
- README.md properly documents v1.1.0 compatibility

#### Security Features
- ✅ Web Crypto API for secure random generation (line 301-304)
- ✅ Mouse entropy collection with 10-second timer (lines 506-541)
- ✅ Custom entropy input support
- ✅ Offline operation capability
- ✅ Clear security warnings and instructions
- ✅ Print-optimized CSS for physical wallet creation

#### Cryptographic Functions (Other than Public Key)
- ✅ Base58 encoding/decoding (lines 309-353)
- ✅ SHA256 double hash for checksums (lines 356-365)
- ✅ Hash160 (RIPEMD160(SHA256(pubkey))) for address derivation (lines 401-408)
- ✅ Base58Check encoding with 4-byte checksums
- ✅ Address validation with checksum verification (lines 544-574)
- ✅ WIF private key generation with compression flag (lines 422-427)

---

## ❌ Critical Security Flaws

### 1. Invalid Public Key Generation (CRITICAL)

**Location:** Lines 387-396

**Current Code:**
```javascript
// Generate public key from private key (simplified - in production use secp256k1)
function generatePublicKey(privateKey) {
    // This is a simplified version. In production, use proper secp256k1 implementation
    const hash = CryptoJS.SHA256(CryptoJS.lib.WordArray.create(privateKey));
    return Array.from(hash.words.map(word => [
        (word >>> 24) & 0xff,
        (word >>> 16) & 0xff,
        (word >>> 8) & 0xff,
        word & 0xff
    ]).flat()).slice(0, 33); // Compressed public key format
}
```

**Problem:**
This function performs `pubkey = SHA256(privkey)` instead of the required secp256k1 elliptic curve point multiplication `pubkey = privkey * G` where G is the secp256k1 generator point.

**Impact:**
- **SEVERE**: Generated addresses are mathematically invalid
- Private keys do NOT unlock the displayed addresses
- Funds sent to these addresses would be UNRECOVERABLE
- Users cannot import wallets into ammocoind/ammocoin-cli
- This makes the entire tool non-functional for real use

**Required Fix:**
Integrate a proper secp256k1 library:

**Option 1 - noble-secp256k1 (Recommended):**
```javascript
import * as secp256k1 from '@noble/secp256k1';

function generatePublicKey(privateKey) {
    const publicKey = secp256k1.getPublicKey(privateKey, true); // true = compressed
    return Array.from(publicKey);
}
```

**Option 2 - elliptic library:**
```javascript
const EC = require('elliptic').ec;
const ec = new EC('secp256k1');

function generatePublicKey(privateKey) {
    const key = ec.keyFromPrivate(privateKey);
    const publicKey = key.getPublic(true, 'array'); // true = compressed
    return publicKey;
}
```

**Option 3 - bitcoinjs-lib:**
```javascript
const bitcoin = require('bitcoinjs-lib');
const ECPair = require('ecpair').ECPairFactory(require('tiny-secp256k1'));

function generatePublicKey(privateKey) {
    const keyPair = ECPair.fromPrivateKey(Buffer.from(privateKey));
    return Array.from(keyPair.publicKey);
}
```

---

## ⚠️ Other Issues

### 2. External CDN Dependencies

**Location:** Lines 286-287

**Current Code:**
```html
<script src="https://cdn.jsdelivr.net/npm/qrcode@1.5.3/build/qrcode.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/crypto-js@4.1.1/crypto-js.js"></script>
```

**Problem:**
- Requires internet connection to load libraries
- Defeats "offline" security claim
- CDN could be compromised
- Libraries could change unexpectedly

**Impact:**
- Medium: Prevents true offline usage
- Requires user to load page once while online, then cache
- Not ideal for maximum security scenario

**Recommended Fix:**
Bundle libraries locally:
```
paper-wallet-generator/
├── index.html
├── lib/
│   ├── qrcode.min.js
│   └── crypto-js.min.js
└── README.md
```

Update script tags:
```html
<script src="lib/qrcode.min.js"></script>
<script src="lib/crypto-js.min.js"></script>
```

---

## ✅ Verified Correct Implementations

### Base58Check Encoding
- Properly implements Bitcoin-style Base58 alphabet
- Includes 4-byte SHA256d checksum
- Handles leading zeros correctly
- Encoding and decoding functions are symmetrical

### Address Derivation Flow
```
Private Key (32 bytes)
    ↓
❌ Public Key Generation (BROKEN - uses SHA256 instead of secp256k1)
    ↓
✅ SHA256 Hash
    ↓
✅ RIPEMD160 Hash (Hash160)
    ↓
✅ Add version byte (0x17)
    ↓
✅ SHA256d checksum (4 bytes)
    ↓
✅ Base58 Encode
    ↓
Address (starts with 'A')
```

### WIF Private Key Generation
```
Private Key (32 bytes)
    ↓
✅ Add version byte (0x97)
    ↓
✅ Add compression flag (0x01)
    ↓
✅ SHA256d checksum (4 bytes)
    ↓
✅ Base58 Encode
    ↓
WIF Private Key
```

### Random Number Generation
- ✅ Uses `crypto.getRandomValues()` from Web Crypto API
- ✅ Generates 32 bytes of cryptographically secure randomness
- ✅ Combines with mouse entropy and custom text
- ✅ Hashes combined entropy with SHA256

### Address Validation
- ✅ Decodes Base58 address
- ✅ Checks length (25 bytes total)
- ✅ Verifies version byte (0x17)
- ✅ Recalculates checksum and compares
- ✅ Visual feedback (green/red border)

---

## Compatibility Verification

### v1.1.0 Genesis Block
**NOT APPLICABLE** - Paper wallet generator doesn't need genesis block data. It only generates key pairs and addresses based on network parameters.

### Network Parameters Match
Compared with `/Volumes/CRUCIAL_2TB/GITHUB/AMMOcoin/ammocoin-apps-from-ammocoin/src/chainparams.cpp`:

| Parameter | Paper Wallet | chainparams.cpp | Status |
|-----------|--------------|-----------------|--------|
| Address Version | 0x17 | 0x17 (line 105) | ✅ Match |
| WIF Version | 0x97 | 0x97 (standard) | ✅ Match |
| Script Version | 0x7D | 0x7D (standard) | ✅ Match |

### Address Format Testing

**Expected:** Addresses should start with 'A' (due to version byte 0x17)

**Current Behavior:**
- Tool generates addresses starting with 'A' ✅
- However, these addresses are INVALID due to broken public key generation ❌

**Test with Real Wallet:**
```bash
# If this tool worked correctly, this should succeed:
ammocoin-cli validateaddress <generated_address>

# Expected result: isvalid: true
# Actual result: Will likely be invalid or not work with imported WIF
```

---

## Testing Recommendations

### Before Production Release

1. **Fix secp256k1 Public Key Generation** (CRITICAL)
   - Integrate one of the recommended libraries
   - Test against known test vectors
   - Verify addresses match Bitcoin/AMMOcoin reference implementations

2. **Cross-Verification Testing**
   ```bash
   # Generate address with paper wallet
   # Import WIF to ammocoind
   ammocoin-cli importprivkey <WIF> "test" false

   # Get address from imported key
   ammocoin-cli getaddressesbyaccount "test"

   # Verify it matches paper wallet address
   # Currently this will FAIL due to broken public key generation
   ```

3. **Bundle External Libraries Locally**
   - Download QRCode.js v1.5.3
   - Download CryptoJS v4.1.1
   - Update HTML script tags
   - Test offline functionality

4. **Security Review**
   - Code review by cryptography expert
   - Penetration testing
   - Compare with established paper wallet generators (bitaddress.org, etc.)

5. **Known Test Vectors**
   Test with Bitcoin test vectors to verify secp256k1 implementation:
   ```
   Private: 1
   Public (compressed): 0279be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798
   Address (Bitcoin): 1BgGZ9tcN4rm9KBzDn7KprQz87SZ26SAMH
   Address (AMMOcoin with 0x17): A... (calculate with version byte 0x17)
   ```

---

## Recommendations

### Immediate Actions (REQUIRED FOR PRODUCTION)

1. **❌ Mark as NON-FUNCTIONAL** until secp256k1 fix is implemented
2. **Add prominent warning** to README.md and index.html:
   ```html
   ⚠️ WARNING: This tool is currently NON-FUNCTIONAL for production use.
   The public key generation does not use proper secp256k1 cryptography.
   DO NOT USE FOR REAL FUNDS until this is fixed.
   ```

3. **Integrate secp256k1 library** - Use noble-secp256k1 (recommended) or elliptic

4. **Bundle dependencies locally** for true offline operation

5. **Test with real AMMOcoin wallet** to verify import/export works

### Nice-to-Have Improvements

1. Add bulk wallet generation option (10, 25, 50, 100 wallets)
2. Add BIP38 password encryption support
3. Add vanity address generation
4. Include blockchain check balance feature (when online)
5. Add multi-language support
6. Improve print layout with fold lines and tamper-evident features

---

## Conclusion

### Current Status: ❌ NOT PRODUCTION READY

The paper wallet generator has:
- ✅ Correct v1.1.0 network parameters (0x17, 0x97)
- ✅ Good security practices (Web Crypto API, entropy collection)
- ✅ Proper Base58Check encoding
- ✅ Correct address/WIF derivation flow (except public key step)
- ❌ **CRITICAL FLAW**: Broken secp256k1 public key generation

### Action Required

**DO NOT RECOMMEND THIS TOOL TO USERS** until the secp256k1 public key generation is fixed. Generated wallets will NOT work with the real AMMOcoin network.

### Estimated Fix Effort

- **Complexity:** Medium
- **Time Estimate:** 2-4 hours for experienced JavaScript developer
- **Steps:**
  1. Add noble-secp256k1 library (1 line)
  2. Replace generatePublicKey() function (5 lines)
  3. Test with known vectors (30 minutes)
  4. Test with real AMMOcoin wallet import (30 minutes)
  5. Bundle external libraries locally (1 hour)
  6. Update documentation (30 minutes)

### Risk Assessment

**Current Risk:** 🔴 **CRITICAL**
- Users could lose funds if they use this tool
- Addresses appear valid but private keys don't unlock them
- No warning about non-functionality

**Post-Fix Risk:** 🟢 **LOW**
- Standard paper wallet implementation
- Well-established cryptographic libraries
- Proper security practices in place

---

**End of Audit Report**
