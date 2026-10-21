#ifndef BITCOIN_CHAINPARAMSSEEDS_H
#define BITCOIN_CHAINPARAMSSEEDS_H
/**
 * List of fixed seed nodes for the AMMOcoin network
 *
 * Each line contains a BIP155 serialized (networkID, addr, port) tuple.
 * Format: network_id(1), addr_len(compactsize), addr(N), port(2 big-endian)
 */
static const uint8_t chainparams_seed_main[] = {
    0x01, 0x04, 0x4E, 0x8D, 0xC2, 0x8C, 0x90, 0x9C, // 78.141.194.140:37020  (seed1.ammocoin.org)
    0x01, 0x04, 0x68, 0xEE, 0xA5, 0x38, 0x90, 0x9C, // 104.238.165.56:37020  (seed2.ammocoin.org)
    0x01, 0x04, 0xCF, 0xF6, 0x5F, 0xD2, 0x90, 0x9C, // 207.246.95.210:37020  (seed3.ammocoin.org, New York)
    0x01, 0x04, 0x2D, 0x4C, 0x74, 0x61, 0x90, 0x9C, // 45.76.116.97:37020    (seed3.ammocoin.org, Sydney)
    0x01, 0x04, 0x90, 0xCA, 0x4F, 0x72, 0x90, 0x9C, // 144.202.79.114:37020  (seed3.ammocoin.org, Dallas)
};

static const uint8_t chainparams_seed_test[] = {
    // No testnet seed nodes currently available
};

#endif // BITCOIN_CHAINPARAMSSEEDS_H