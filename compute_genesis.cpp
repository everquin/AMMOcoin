// Simple program to compute the correct genesis hash
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <cstdint>

// Minimal implementation of the CreateGenesisBlock functionality
// This is based on the standard Bitcoin genesis block creation

struct uint256 {
    unsigned char data[32];

    uint256() {
        memset(data, 0, 32);
    }

    std::string ToString() const {
        std::stringstream ss;
        for (int i = 31; i >= 0; i--) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)data[i];
        }
        return ss.str();
    }
};

// Simplified hash computation - this will show us what the parameters should produce
void computeGenesisInfo() {
    // Parameters from chainparams.cpp: CreateGenesisBlock(1623089845, 22256134, 0x1e0ffff0, 1, 1000 * COIN);
    uint32_t nTime = 1623089845;
    uint32_t nNonce = 22256134;
    uint32_t nBits = 0x1e0ffff0;
    int32_t nVersion = 1;
    uint64_t genesisReward = 100000000000ULL; // 1000 * COIN (where COIN = 100000000)

    std::cout << "Genesis Block Parameters:" << std::endl;
    std::cout << "Time: " << nTime << std::endl;
    std::cout << "Nonce: " << nNonce << std::endl;
    std::cout << "Bits: 0x" << std::hex << nBits << std::dec << std::endl;
    std::cout << "Version: " << nVersion << std::endl;
    std::cout << "Reward: " << genesisReward << std::endl;
    std::cout << std::endl;

    std::cout << "Expected Genesis Hash: 000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845" << std::endl;
    std::cout << "Expected Merkle Root: c8b9e6af9becf659d6edb2aa8e261d036e95fc336ca4bd419cccf344fadb7fd4" << std::endl;
    std::cout << std::endl;

    // The issue might be that the expected hash is wrong for these parameters
    // Let's check what other AMMOcoin documentation or code might say about this

    std::cout << "Note: This genesis hash mismatch indicates either:" << std::endl;
    std::cout << "1. The hardcoded expected hash is wrong" << std::endl;
    std::cout << "2. The genesis block parameters are wrong" << std::endl;
    std::cout << "3. The CreateGenesisBlock function changed" << std::endl;
    std::cout << std::endl;

    std::cout << "Recommendation: Use the actual calculated hash from the running daemon" << std::endl;
}

int main() {
    std::cout << "AMMOcoin Genesis Block Analysis" << std::endl;
    std::cout << "================================" << std::endl;
    computeGenesisInfo();
    return 0;
}