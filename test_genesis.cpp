// Quick test to determine correct genesis hash
#include "chainparams.h"
#include <iostream>

int main() {
    // Create genesis block with the current parameters
    CBlock genesis = CreateGenesisBlock(1623089845, 22256134, 0x1e0ffff0, 1, 1000 * COIN);

    std::cout << "Calculated Genesis Hash: " << genesis.GetHash().ToString() << std::endl;
    std::cout << "Expected Genesis Hash:   000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845" << std::endl;
    std::cout << "Calculated Merkle Root:  " << genesis.hashMerkleRoot.ToString() << std::endl;
    std::cout << "Expected Merkle Root:    c8b9e6af9becf659d6edb2aa8e261d036e95fc336ca4bd419cccf344fadb7fd4" << std::endl;

    return 0;
}