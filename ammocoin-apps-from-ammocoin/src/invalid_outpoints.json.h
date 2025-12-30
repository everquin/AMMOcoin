// Copyright (c) 2018-2021 The AMMOcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
//
// Serialized list of invalid transaction outpoints for AMMOcoin
// Generated file - list of known invalid outpoints

#ifndef AMMOCOIN_INVALID_OUTPOINTS_JSON_H
#define AMMOCOIN_INVALID_OUTPOINTS_JSON_H

#include <string>

namespace invalid_out
{
    inline std::string LoadInvalidOutPoints()
    {
        // Empty array - no invalid outpoints defined yet for v1.1.0
        return "[]";
    }
}

#endif // AMMOCOIN_INVALID_OUTPOINTS_JSON_H
