// Copyright (c) 2021 The Dogecoin Core developers
// Copyright (c) 2025 The Enamorie Coin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ENAMORIE_FEES_H
#define BITCOIN_ENAMORIE_FEES_H

#include "amount.h"
#include "chain.h"
#include "chainparams.h"

#ifdef ENABLE_WALLET

// Fee tiers for Enamorie Coin — love-themed labels
enum FeeRatePreset
{
    MINIMUM,        // 最低限 (0.001 ENAM)
    WARM,           // 温かい
    AFFECTION,      // 愛情
    PASSION,        // 情熱
    DEVOTED,        // 献身
    ENAMORED        // 恋愛中 (最高)
};

CFeeRate GetEnamorieFeeRate(int priority);
const std::string GetEnamoriePriorityLabel(int priority);
#endif // ENABLE_WALLET

CAmount GetEnamorieMinRelayFee(const CTransaction& tx, unsigned int nBytes, bool fAllowFree);
CAmount GetEnamorieDustFee(const std::vector<CTxOut> &vout, const CAmount dustLimit);

#endif // BITCOIN_ENAMORIE_FEES_H
