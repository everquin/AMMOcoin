// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1623089845, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    0        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1623089845,
    0,
    0};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1623089845,
    0,
    0};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x76;
        pchMessageStart[1] = 0x63;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0xf3;
        vAlertPubKey = ParseHex("0438abfcd93b479132fcf6ba1e14d644e458f0db10d1a254d35956b45cf205a1daa6bdfe83b4a7b5464e344930633cde9df41f95c16588ec37707a3ffd9e86b74f");
        nDefaultPort = 37020;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // AMMOcoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 0;
        nRejectBlockOutdatedMajority = 0;
        nToCheckBlockUpgradeMajority = 0;
        nMinerThreads = 0;
        nTargetTimespan = 9 * 60;
        nTargetSpacing = 3 * 60;
        nMaturity = 20;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 9999999999 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 10000;
        nModifierUpdateBlock = 0;
        nZerocoinStartHeight = 0;
        nZerocoinStartTime = 1623089845;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 999999999; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 999999999;
        nBlockDoubleAccumulated = 999999999;
        nEnforceNewSporkKey = 1623089845;
        nRejectOldSporkKey = 1527811200; 

        // Public coin spend enforcement
        nPublicZCSpends = 1;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = 0;
        nSupplyBeforeFakeSerial = 0;   // zerocoin supply at block nFakeSerialBlockheightEnd

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04fff000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        // AMMOcoin v1.1.0 Genesis Block - Hybrid Migration
        // Snapshot: v1.0 block 434881 (c23bdb63ff149251...)
        // Generated: 2025-12-21 22:10:44 UTC
        // Top 61 holders: 218,707,052.20 AMMO (94.1%)
        // Migration fund: 13,690,696.25 AMMO (5.9%) for 10,019 addresses
        
        const char* pszTimestamp = "AMMOcoin v1.1.0 Genesis - June 2021 - Privacy Enhanced";
        CMutableTransaction txNew;
        txNew.nTime = 1623089845;
        txNew.vin.resize(1);
        txNew.vout.resize(62);  // 61 top holders + 1 migration fund
        
        // Genesis input
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)
            << vector<unsigned char>((const unsigned char*)pszTimestamp,
                                      (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        
        // === TOP 61 HOLDERS (218,707,052.20 AMMO - 94.1%) ===
        
        // Rank 1: ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL = 36,952,699.99980000 AMMO
        txNew.vout[0].nValue = 3695269999980000LL;  // 36952699.99980000 AMMO
        txNew.vout[0].scriptPubKey = GetScriptForDestination(DecodeDestination("ANj3fDwDYTjf1Mb7XvgjHLrs6aSKeKXakL"));
        
        // Rank 2: AYdWeryG24AR6VzWAGEEQD4KmubxDuMoVA = 14,915,500.00000000 AMMO
        txNew.vout[1].nValue = 1491550000000000LL;  // 14915500.00000000 AMMO
        txNew.vout[1].scriptPubKey = GetScriptForDestination(DecodeDestination("AYdWeryG24AR6VzWAGEEQD4KmubxDuMoVA"));
        
        // Rank 3: AZuE2SixrvwwEn7dVmJPYa8xhztXwB7g24 = 13,008,000.00000000 AMMO
        txNew.vout[2].nValue = 1300800000000000LL;  // 13008000.00000000 AMMO
        txNew.vout[2].scriptPubKey = GetScriptForDestination(DecodeDestination("AZuE2SixrvwwEn7dVmJPYa8xhztXwB7g24"));
        
        // Rank 4: AWhtZPWBCMs4fUt7nhqP6MTyzgssHHbQze = 10,682,700.00000000 AMMO
        txNew.vout[3].nValue = 1068270000000000LL;  // 10682700.00000000 AMMO
        txNew.vout[3].scriptPubKey = GetScriptForDestination(DecodeDestination("AWhtZPWBCMs4fUt7nhqP6MTyzgssHHbQze"));
        
        // Rank 5: AdzyWnDzqCSHPxPB6KN3cYtUEPt1uwH4SR = 10,217,100.00000000 AMMO
        txNew.vout[4].nValue = 1021710000000000LL;  // 10217100.00000000 AMMO
        txNew.vout[4].scriptPubKey = GetScriptForDestination(DecodeDestination("AdzyWnDzqCSHPxPB6KN3cYtUEPt1uwH4SR"));
        
        // Rank 6: AcbDmc15qunTh6VSJ3DikmMq11MQ321iPq = 9,758,400.00000000 AMMO
        txNew.vout[5].nValue = 975840000000000LL;  // 9758400.00000000 AMMO
        txNew.vout[5].scriptPubKey = GetScriptForDestination(DecodeDestination("AcbDmc15qunTh6VSJ3DikmMq11MQ321iPq"));
        
        // Rank 7: ATcs6iwoZQk6mgmQ9mBF2xpGsaAeNw6tQ4 = 9,668,985.53000000 AMMO
        txNew.vout[6].nValue = 966898553000000LL;  // 9668985.53000000 AMMO
        txNew.vout[6].scriptPubKey = GetScriptForDestination(DecodeDestination("ATcs6iwoZQk6mgmQ9mBF2xpGsaAeNw6tQ4"));
        
        // Rank 8: ANEgk4D9g39BHNcNKwuqPRu6BEwoune7wT = 9,646,000.00000000 AMMO
        txNew.vout[7].nValue = 964600000000000LL;  // 9646000.00000000 AMMO
        txNew.vout[7].scriptPubKey = GetScriptForDestination(DecodeDestination("ANEgk4D9g39BHNcNKwuqPRu6BEwoune7wT"));
        
        // Rank 9: APRRL8UV3QPUzBEhBUB5NXLZ8ovBqxQ9wn = 9,458,800.00000000 AMMO
        txNew.vout[8].nValue = 945880000000000LL;  // 9458800.00000000 AMMO
        txNew.vout[8].scriptPubKey = GetScriptForDestination(DecodeDestination("APRRL8UV3QPUzBEhBUB5NXLZ8ovBqxQ9wn"));
        
        // Rank 10: AavFTu96nBj1F47gRw3emCX6yP3XVhuqRa = 9,207,700.00000000 AMMO
        txNew.vout[9].nValue = 920770000000000LL;  // 9207700.00000000 AMMO
        txNew.vout[9].scriptPubKey = GetScriptForDestination(DecodeDestination("AavFTu96nBj1F47gRw3emCX6yP3XVhuqRa"));
        
        // Rank 11: AZSGN4Jo3XqhuTD8WkNTS5oSTdtjXbxQpt = 9,154,700.00000000 AMMO
        txNew.vout[10].nValue = 915470000000000LL;  // 9154700.00000000 AMMO
        txNew.vout[10].scriptPubKey = GetScriptForDestination(DecodeDestination("AZSGN4Jo3XqhuTD8WkNTS5oSTdtjXbxQpt"));
        
        // Rank 12: AJbd6WboYPecXXwBDkKMTeXQHMrkmhMyWK = 7,357,000.00000000 AMMO
        txNew.vout[11].nValue = 735700000000000LL;  // 7357000.00000000 AMMO
        txNew.vout[11].scriptPubKey = GetScriptForDestination(DecodeDestination("AJbd6WboYPecXXwBDkKMTeXQHMrkmhMyWK"));
        
        // Rank 13: ASLNgBYwjySk3z6xNZgpajA8MLMP5eBcLD = 6,544,600.00000000 AMMO
        txNew.vout[12].nValue = 654460000000000LL;  // 6544600.00000000 AMMO
        txNew.vout[12].scriptPubKey = GetScriptForDestination(DecodeDestination("ASLNgBYwjySk3z6xNZgpajA8MLMP5eBcLD"));
        
        // Rank 14: AaBdD5uhRcfLVk8QbDhnVrxACaic2uXaoK = 5,157,662.42000000 AMMO
        txNew.vout[13].nValue = 515766242000000LL;  // 5157662.42000000 AMMO
        txNew.vout[13].scriptPubKey = GetScriptForDestination(DecodeDestination("AaBdD5uhRcfLVk8QbDhnVrxACaic2uXaoK"));
        
        // Rank 15: AXfEFpVi3RyypyLwAhEaNmXeC6iu6DQDbu = 4,735,900.00000000 AMMO
        txNew.vout[14].nValue = 473590000000000LL;  // 4735900.00000000 AMMO
        txNew.vout[14].scriptPubKey = GetScriptForDestination(DecodeDestination("AXfEFpVi3RyypyLwAhEaNmXeC6iu6DQDbu"));
        
        // Rank 16: AUCRKZm4TwKNuoGtsYfrT6CnUdjUiaG4jx = 4,536,500.00000000 AMMO
        txNew.vout[15].nValue = 453650000000000LL;  // 4536500.00000000 AMMO
        txNew.vout[15].scriptPubKey = GetScriptForDestination(DecodeDestination("AUCRKZm4TwKNuoGtsYfrT6CnUdjUiaG4jx"));
        
        // Rank 17: AKcjahJP6e9jz1QUud3ddnBspFiD4fuJuz = 4,525,300.00000000 AMMO
        txNew.vout[16].nValue = 452530000000000LL;  // 4525300.00000000 AMMO
        txNew.vout[16].scriptPubKey = GetScriptForDestination(DecodeDestination("AKcjahJP6e9jz1QUud3ddnBspFiD4fuJuz"));
        
        // Rank 18: Aa8ceG29F6fK8kk54111YkXWxBNmfUtaZf = 3,946,111.74000000 AMMO
        txNew.vout[17].nValue = 394611174000000LL;  // 3946111.74000000 AMMO
        txNew.vout[17].scriptPubKey = GetScriptForDestination(DecodeDestination("Aa8ceG29F6fK8kk54111YkXWxBNmfUtaZf"));
        
        // Rank 19: AawgwnXoXguHfDaU7zZaRCGDkeLjy9MrUh = 3,880,301.00000000 AMMO
        txNew.vout[18].nValue = 388030100000000LL;  // 3880301.00000000 AMMO
        txNew.vout[18].scriptPubKey = GetScriptForDestination(DecodeDestination("AawgwnXoXguHfDaU7zZaRCGDkeLjy9MrUh"));
        
        // Rank 20: ATGArBPh3sxJbYH3MK6q5Sk6df9MTepk7K = 3,787,600.00000000 AMMO
        txNew.vout[19].nValue = 378760000000000LL;  // 3787600.00000000 AMMO
        txNew.vout[19].scriptPubKey = GetScriptForDestination(DecodeDestination("ATGArBPh3sxJbYH3MK6q5Sk6df9MTepk7K"));
        
        // Rank 21: AKSKBjniA32Nk4dvhL6VtTYLnrdgeVwYCQ = 3,576,100.00000000 AMMO
        txNew.vout[20].nValue = 357610000000000LL;  // 3576100.00000000 AMMO
        txNew.vout[20].scriptPubKey = GetScriptForDestination(DecodeDestination("AKSKBjniA32Nk4dvhL6VtTYLnrdgeVwYCQ"));
        
        // Rank 22: AUW3zZFgkNyJCQEDegkpPjvJgS5bTz8Huh = 3,574,500.00000000 AMMO
        txNew.vout[21].nValue = 357450000000000LL;  // 3574500.00000000 AMMO
        txNew.vout[21].scriptPubKey = GetScriptForDestination(DecodeDestination("AUW3zZFgkNyJCQEDegkpPjvJgS5bTz8Huh"));
        
        // Rank 23: AT7rBQKPYz4sihx5p6tVPeKMnyaW3BkXww = 3,126,800.00000000 AMMO
        txNew.vout[22].nValue = 312680000000000LL;  // 3126800.00000000 AMMO
        txNew.vout[22].scriptPubKey = GetScriptForDestination(DecodeDestination("AT7rBQKPYz4sihx5p6tVPeKMnyaW3BkXww"));
        
        // Rank 24: AP81HYXuDiKnpoZrEv59NyPjo5oxRzZadw = 2,832,400.00000000 AMMO
        txNew.vout[23].nValue = 283240000000000LL;  // 2832400.00000000 AMMO
        txNew.vout[23].scriptPubKey = GetScriptForDestination(DecodeDestination("AP81HYXuDiKnpoZrEv59NyPjo5oxRzZadw"));
        
        // Rank 25: AQye2euhbzNm76xJTDgPT7w9A4Lkss7nQf = 2,254,816.49000000 AMMO
        txNew.vout[24].nValue = 225481649000000LL;  // 2254816.49000000 AMMO
        txNew.vout[24].scriptPubKey = GetScriptForDestination(DecodeDestination("AQye2euhbzNm76xJTDgPT7w9A4Lkss7nQf"));
        
        // Rank 26: AZhRSguEFJoXHkNeJ61aKBmBE1sjvjTBT9 = 1,880,500.00000000 AMMO
        txNew.vout[25].nValue = 188050000000000LL;  // 1880500.00000000 AMMO
        txNew.vout[25].scriptPubKey = GetScriptForDestination(DecodeDestination("AZhRSguEFJoXHkNeJ61aKBmBE1sjvjTBT9"));
        
        // Rank 27: ANTTNpSKV7y2m6b4CTpZ64sPzBzsnzcvaF = 1,404,648.05000000 AMMO
        txNew.vout[26].nValue = 140464805000000LL;  // 1404648.05000000 AMMO
        txNew.vout[26].scriptPubKey = GetScriptForDestination(DecodeDestination("ANTTNpSKV7y2m6b4CTpZ64sPzBzsnzcvaF"));
        
        // Rank 28: AQUcL11hU9qVtYHmJMSp1teMen7HMxm11H = 1,373,357.82000000 AMMO
        txNew.vout[27].nValue = 137335782000000LL;  // 1373357.82000000 AMMO
        txNew.vout[27].scriptPubKey = GetScriptForDestination(DecodeDestination("AQUcL11hU9qVtYHmJMSp1teMen7HMxm11H"));
        
        // Rank 29: ASbz14cWCKJefgdcyE4X9qhDVwzEvPhBpJ = 1,246,500.88000000 AMMO
        txNew.vout[28].nValue = 124650088000000LL;  // 1246500.88000000 AMMO
        txNew.vout[28].scriptPubKey = GetScriptForDestination(DecodeDestination("ASbz14cWCKJefgdcyE4X9qhDVwzEvPhBpJ"));
        
        // Rank 30: AUaeBdhcDyy1PLmNH5SJrBawv2neFejJ5q = 1,103,100.00000000 AMMO
        txNew.vout[29].nValue = 110310000000000LL;  // 1103100.00000000 AMMO
        txNew.vout[29].scriptPubKey = GetScriptForDestination(DecodeDestination("AUaeBdhcDyy1PLmNH5SJrBawv2neFejJ5q"));
        
        // Rank 31: ANTBaSzxmJvEZTuYCRqn4r5jMYVxQxpvyy = 1,086,985.59000000 AMMO
        txNew.vout[30].nValue = 108698559000000LL;  // 1086985.59000000 AMMO
        txNew.vout[30].scriptPubKey = GetScriptForDestination(DecodeDestination("ANTBaSzxmJvEZTuYCRqn4r5jMYVxQxpvyy"));
        
        // Rank 32: AFvH9Jk8iWdmwGysGykjsU7vEtS99fuZhp = 1,083,646.50000000 AMMO
        txNew.vout[31].nValue = 108364650000000LL;  // 1083646.50000000 AMMO
        txNew.vout[31].scriptPubKey = GetScriptForDestination(DecodeDestination("AFvH9Jk8iWdmwGysGykjsU7vEtS99fuZhp"));
        
        // Rank 33: AbU5XWG2NMJNc2JJ3o2BfrDsRy4b7ALUfJ = 958,739.84000000 AMMO
        txNew.vout[32].nValue = 95873984000000LL;  // 958739.84000000 AMMO
        txNew.vout[32].scriptPubKey = GetScriptForDestination(DecodeDestination("AbU5XWG2NMJNc2JJ3o2BfrDsRy4b7ALUfJ"));
        
        // Rank 34: Aewm1ufcJYoCWfd4BUqAPdBSDQjKxqpsnp = 929,929.88000000 AMMO
        txNew.vout[33].nValue = 92992988000000LL;  // 929929.88000000 AMMO
        txNew.vout[33].scriptPubKey = GetScriptForDestination(DecodeDestination("Aewm1ufcJYoCWfd4BUqAPdBSDQjKxqpsnp"));
        
        // Rank 35: Aev2o5JLRiKXG7Ef9DaAPGmWFeFVRn5KEV = 917,900.00000000 AMMO
        txNew.vout[34].nValue = 91790000000000LL;  // 917900.00000000 AMMO
        txNew.vout[34].scriptPubKey = GetScriptForDestination(DecodeDestination("Aev2o5JLRiKXG7Ef9DaAPGmWFeFVRn5KEV"));
        
        // Rank 36: AJKmy5owCXwmyjwiWZCK8zrp3RgfAe8mVa = 488,957.69000000 AMMO
        txNew.vout[35].nValue = 48895769000000LL;  // 488957.69000000 AMMO
        txNew.vout[35].scriptPubKey = GetScriptForDestination(DecodeDestination("AJKmy5owCXwmyjwiWZCK8zrp3RgfAe8mVa"));
        
        // Rank 37: AZdQ7mJHH61YfSTANWaSbNRicUasGvZZS4 = 478,651.80000000 AMMO
        txNew.vout[36].nValue = 47865180000000LL;  // 478651.80000000 AMMO
        txNew.vout[36].scriptPubKey = GetScriptForDestination(DecodeDestination("AZdQ7mJHH61YfSTANWaSbNRicUasGvZZS4"));
        
        // Rank 38: AN5c8UabTdohMtzCuyVPS69ptqGfaqf7rL = 477,701.96000000 AMMO
        txNew.vout[37].nValue = 47770196000000LL;  // 477701.96000000 AMMO
        txNew.vout[37].scriptPubKey = GetScriptForDestination(DecodeDestination("AN5c8UabTdohMtzCuyVPS69ptqGfaqf7rL"));
        
        // Rank 39: AdedL2HjKkztjh5mSgeWFXVGVpGfsFjbGp = 472,735.96000000 AMMO
        txNew.vout[38].nValue = 47273596000000LL;  // 472735.96000000 AMMO
        txNew.vout[38].scriptPubKey = GetScriptForDestination(DecodeDestination("AdedL2HjKkztjh5mSgeWFXVGVpGfsFjbGp"));
        
        // Rank 40: ALmYjpU1MYpZYkZ5v88QbkJPUSzwv6owc7 = 287,110.00000000 AMMO
        txNew.vout[39].nValue = 28711000000000LL;  // 287110.00000000 AMMO
        txNew.vout[39].scriptPubKey = GetScriptForDestination(DecodeDestination("ALmYjpU1MYpZYkZ5v88QbkJPUSzwv6owc7"));
        
        // Rank 41: AMzSGFTVZJDQGZsQeWckdFRyK5sxx1XG5u = 280,539.07000000 AMMO
        txNew.vout[40].nValue = 28053907000000LL;  // 280539.07000000 AMMO
        txNew.vout[40].scriptPubKey = GetScriptForDestination(DecodeDestination("AMzSGFTVZJDQGZsQeWckdFRyK5sxx1XG5u"));
        
        // Rank 42: AW9eQirViddzuo6iMXhY5pRyAgHkHzpccw = 235,264.09000000 AMMO
        txNew.vout[41].nValue = 23526409000000LL;  // 235264.09000000 AMMO
        txNew.vout[41].scriptPubKey = GetScriptForDestination(DecodeDestination("AW9eQirViddzuo6iMXhY5pRyAgHkHzpccw"));
        
        // Rank 43: AHdhhTDD7EThT2ggyiaD6YceAszs8xyMy1 = 200,400.00000000 AMMO
        txNew.vout[42].nValue = 20040000000000LL;  // 200400.00000000 AMMO
        txNew.vout[42].scriptPubKey = GetScriptForDestination(DecodeDestination("AHdhhTDD7EThT2ggyiaD6YceAszs8xyMy1"));
        
        // Rank 44: AK4m2H87QccsX6SW7ziiQe14RLSWncNmjM = 197,587.50000000 AMMO
        txNew.vout[43].nValue = 19758750000000LL;  // 197587.50000000 AMMO
        txNew.vout[43].scriptPubKey = GetScriptForDestination(DecodeDestination("AK4m2H87QccsX6SW7ziiQe14RLSWncNmjM"));
        
        // Rank 45: ASERgHexthMPcSfc3vz6PhXd7cCPyNZoLe = 140,100.00000000 AMMO
        txNew.vout[44].nValue = 14010000000000LL;  // 140100.00000000 AMMO
        txNew.vout[44].scriptPubKey = GetScriptForDestination(DecodeDestination("ASERgHexthMPcSfc3vz6PhXd7cCPyNZoLe"));
        
        // Rank 46: AeKqBnYTBMDFnt4dxiqRyZSVUtr6wZ9Xrg = 138,599.00000000 AMMO
        txNew.vout[45].nValue = 13859900000000LL;  // 138599.00000000 AMMO
        txNew.vout[45].scriptPubKey = GetScriptForDestination(DecodeDestination("AeKqBnYTBMDFnt4dxiqRyZSVUtr6wZ9Xrg"));
        
        // Rank 47: AG3Lra2nudQXHR5SukVkJsDuKh9nWnMyqJ = 128,550.00000000 AMMO
        txNew.vout[46].nValue = 12855000000000LL;  // 128550.00000000 AMMO
        txNew.vout[46].scriptPubKey = GetScriptForDestination(DecodeDestination("AG3Lra2nudQXHR5SukVkJsDuKh9nWnMyqJ"));
        
        // Rank 48: AVpipvv4NMtV7H4W3PpQrwvX8m5XdyaLTU = 100,200.00000000 AMMO
        txNew.vout[47].nValue = 10020000000000LL;  // 100200.00000000 AMMO
        txNew.vout[47].scriptPubKey = GetScriptForDestination(DecodeDestination("AVpipvv4NMtV7H4W3PpQrwvX8m5XdyaLTU"));
        
        // Rank 49: AT5pfGw5Te5CnnTrcVT6q9Cqp52LpKrd9i = 100,000.00000000 AMMO
        txNew.vout[48].nValue = 10000000000000LL;  // 100000.00000000 AMMO
        txNew.vout[48].scriptPubKey = GetScriptForDestination(DecodeDestination("AT5pfGw5Te5CnnTrcVT6q9Cqp52LpKrd9i"));
        
        // Rank 50: AUVMWn8xhPr5R5gAZQQQJpkni9w8LQ7dhV = 87,550.00000000 AMMO
        txNew.vout[49].nValue = 8755000000000LL;  // 87550.00000000 AMMO
        txNew.vout[49].scriptPubKey = GetScriptForDestination(DecodeDestination("AUVMWn8xhPr5R5gAZQQQJpkni9w8LQ7dhV"));
        
        // Rank 51: Aad8M2fiKfHoTrRafbUpYwtF4Uua3mztnX = 85,118.75000000 AMMO
        txNew.vout[50].nValue = 8511875000000LL;  // 85118.75000000 AMMO
        txNew.vout[50].scriptPubKey = GetScriptForDestination(DecodeDestination("Aad8M2fiKfHoTrRafbUpYwtF4Uua3mztnX"));
        
        // Rank 52: AZ9kYUfhyJ67ihmLSKGnmgj1tmqjNsCXuo = 68,262.50000000 AMMO
        txNew.vout[51].nValue = 6826250000000LL;  // 68262.50000000 AMMO
        txNew.vout[51].scriptPubKey = GetScriptForDestination(DecodeDestination("AZ9kYUfhyJ67ihmLSKGnmgj1tmqjNsCXuo"));
        
        // Rank 53: ATSJASCPZCFS3PcEEy5fXXjRRs5Fx1xQCk = 62,400.00000000 AMMO
        txNew.vout[52].nValue = 6240000000000LL;  // 62400.00000000 AMMO
        txNew.vout[52].scriptPubKey = GetScriptForDestination(DecodeDestination("ATSJASCPZCFS3PcEEy5fXXjRRs5Fx1xQCk"));
        
        // Rank 54: ATChPPTzAWKVDPN4mVDEmiezUjNhB3bQcc = 55,137.50000000 AMMO
        txNew.vout[53].nValue = 5513750000000LL;  // 55137.50000000 AMMO
        txNew.vout[53].scriptPubKey = GetScriptForDestination(DecodeDestination("ATChPPTzAWKVDPN4mVDEmiezUjNhB3bQcc"));
        
        // Rank 55: AS1pX4fAzseXDWHhCZoNifEiYkebwXQBkE = 25,010.00000000 AMMO
        txNew.vout[54].nValue = 2501000000000LL;  // 25010.00000000 AMMO
        txNew.vout[54].scriptPubKey = GetScriptForDestination(DecodeDestination("AS1pX4fAzseXDWHhCZoNifEiYkebwXQBkE"));
        
        // Rank 56: AYpXXqc6izdNgncz3pT6znif6kXCNLrcSN = 25,000.00000000 AMMO
        txNew.vout[55].nValue = 2500000000000LL;  // 25000.00000000 AMMO
        txNew.vout[55].scriptPubKey = GetScriptForDestination(DecodeDestination("AYpXXqc6izdNgncz3pT6znif6kXCNLrcSN"));
        
        // Rank 57: AXsRG2b8t7ZAVPtyWviTqeaiAzdDENrBqU = 20,300.00000000 AMMO
        txNew.vout[56].nValue = 2030000000000LL;  // 20300.00000000 AMMO
        txNew.vout[56].scriptPubKey = GetScriptForDestination(DecodeDestination("AXsRG2b8t7ZAVPtyWviTqeaiAzdDENrBqU"));
        
        // Rank 58: AJWk49WqqpC9ftbE1QFU2CNGNxMQdaAPmH = 16,762.50000000 AMMO
        txNew.vout[57].nValue = 1676250000000LL;  // 16762.50000000 AMMO
        txNew.vout[57].scriptPubKey = GetScriptForDestination(DecodeDestination("AJWk49WqqpC9ftbE1QFU2CNGNxMQdaAPmH"));
        
        // Rank 59: AJUDSn6d69TPzP5TpsuqCWcadzRdKZXP93 = 16,625.00000000 AMMO
        txNew.vout[58].nValue = 1662500000000LL;  // 16625.00000000 AMMO
        txNew.vout[58].scriptPubKey = GetScriptForDestination(DecodeDestination("AJUDSn6d69TPzP5TpsuqCWcadzRdKZXP93"));
        
        // Rank 60: AXeN1nj5EGeYCQrXj3stRKxTRkxX9CiRaS = 15,800.00000000 AMMO
        txNew.vout[59].nValue = 1580000000000LL;  // 15800.00000000 AMMO
        txNew.vout[59].scriptPubKey = GetScriptForDestination(DecodeDestination("AXeN1nj5EGeYCQrXj3stRKxTRkxX9CiRaS"));
        
        // Rank 61: AVjeRE62a5eajBSg8b3dknfpAVGbwQBrBd = 11,203.13995480 AMMO
        txNew.vout[60].nValue = 1120313995480LL;  // 11203.13995480 AMMO
        txNew.vout[60].scriptPubKey = GetScriptForDestination(DecodeDestination("AVjeRE62a5eajBSg8b3dknfpAVGbwQBrBd"));
        
        // === MIGRATION FUND (13,690,696.25 AMMO - 5.9%) ===
        // Covers 10,019 remaining addresses
        // Address range: 0.01245611 to 7,601.00000000 AMMO
        txNew.vout[61].nValue = 1369069625046043LL;  // 13690696.25046043 AMMO
        txNew.vout[61].scriptPubKey = GetScriptForDestination(DecodeDestination("Ae3MNUbjbwngiW5CvAN7i2eReEGmjd1EKs"));
        
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1623089845;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 0;  // TO BE MINED

        // Mine genesis block
        printf("Mining genesis block...\n");
        while (UintToArith256(genesis.GetHash()) > UintToArith256(consensus.powLimit)) {
            genesis.nNonce++;
            if (genesis.nNonce % 100000 == 0)
                printf("nNonce: %u\n", genesis.nNonce);
        }
        printf("\n=== GENESIS MINED ===\n");
        printf("nNonce: %u\n", genesis.nNonce);
        printf("Hash: %s\n", genesis.GetHash().ToString().c_str());
        printf("Merkle: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("=====================\n\n");

        hashGenesisBlock = genesis.GetHash();
        // assert(hashGenesisBlock == uint256("0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"));  // Uncomment after mining
        // assert(genesis.hashMerkleRoot == uint256("0xc8b9e6af9becf659d6edb2aa8e261d036e95fc336ca4bd419cccf344fadb7fd4"));  // Uncomment after mining

        vSeeds.push_back(CDNSSeedData("ammo.capital", "node1.ammo.capital"));
        vSeeds.push_back(CDNSSeedData("n2.ammo.capital", "node2.ammo.capital"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 24);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 151);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 14400;
        strSporkKey = "0480112f99ac7d13e872e1f9cda3a6a9af21a924a3c264ce5d98977c9ede10df10bcf97c77bb4019e73c49fad25761fe18638565eca6079e892dc49ba4ea9db658";
        strSporkKeyOld = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
        strObfuscationPoolDummyAddress = "AVLB4nXQgqxcbGAkbdgbYpvWS5BLYqmHj2";
        nStartMasternodePayments = 1623089845;

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 637; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zammo to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0x6d;
        pchMessageStart[2] = 0x04;
        pchMessageStart[3] = 0x3e;
        vAlertPubKey = ParseHex("04de73d2365a0eb67422f135486e5905aa2dba95de663457a018581fcdbf2180a8711d45eda5eab5465ce0f8decc07b16c32cd2d6d12d56cc40088eb6036254426");
        nDefaultPort = 47020;
        nEnforceBlockUpgradeMajority = 0;
        nRejectBlockOutdatedMajority = 0;
        nToCheckBlockUpgradeMajority = 0;
        nMinerThreads = 0;
        nTargetTimespan = 9 * 60;
        nTargetSpacing = 3 * 60;
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0;
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 0;
        nZerocoinStartTime = 1623089845;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 999999999; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 999999999; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1623089845;
        nRejectOldSporkKey = 1522454400; 

        // Public coin spend enforcement
        nPublicZCSpends = 1;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1623089845;
        genesis.nNonce = 0;  // TO BE MINED

        hashGenesisBlock = genesis.GetHash();
        // assert(hashGenesisBlock == uint256("0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"));  // Uncomment after mining

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); 
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 66);  
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);     
        
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet ammocoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
        strSporkKey = "04a06125133f0df9c6f51875db0e8501e3657812d48ed0ed7e8f5949d48321c0aeec3664a36a974663624068fe5914ab2ef05252ece79837123b13ac8a72a7a0f8";
        strSporkKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "TN8dHSiqpwxiF7jqdj5M538AM2SRb2kQvV";
        nStartMasternodePayments = 1623089845;
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x3f;
        pchMessageStart[1] = 0xc9;
        pchMessageStart[2] = 0x36;
        pchMessageStart[3] = 0xd2;
        nDefaultPort = 51476;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 0;
        nRejectBlockOutdatedMajority = 0;
        nToCheckBlockUpgradeMajority = 0;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // AMMOcoin: 1 day
        nTargetSpacing = 1 * 60;        // AMMOcoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 20;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 300;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1623089845;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999; //Last valid accumulator checkpoint

        // Public coin spend enforcement
        nPublicZCSpends = 350;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;

        //! Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1623089845;
        genesis.nNonce = 0;  // TO BE MINED

        hashGenesisBlock = genesis.GetHash();
        // assert(hashGenesisBlock == uint256("0x000001c42e69d7894876ecd725cd1b92d629c154dde2044a6e561f9d77fa2845"));  // Uncomment after mining
        //assert(hashGenesisBlock == uint256("0x6015fc3102f574b9dc068a05a1a563bb55d526743f4d69e8005dd5976b75f4cd"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
