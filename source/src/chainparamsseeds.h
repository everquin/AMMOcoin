#ifndef BITCOIN_CHAINPARAMSSEEDS_H
#define BITCOIN_CHAINPARAMSSEEDS_H
/**
 * List of fixed seed nodes for the AMMOcoin network
 * Emergency deployment - using empty seed list
 *
 * Each line contains a BIP155 serialized (networkID, addr, port) tuple.
 */
static const uint8_t chainparams_seed_main[] = {
    // Empty for emergency deployment - will rely on DNS seeds or manual connections
};

static const uint8_t chainparams_seed_test[] = {
    // Empty for emergency deployment
};

#endif // BITCOIN_CHAINPARAMSSEEDS_H