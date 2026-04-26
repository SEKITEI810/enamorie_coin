// Copyright (c) 2021 The Dogecoin Core developers
// Copyright (c) 2025 The Enamorie Coin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

// Enamorie Coin Fee Design:
//   Ultra-low fees to encourage micro-tipping, social use, and community growth.
//   Target: 0.001 ENAM base fee (vs Dogecoin's 0.01 DOGE)

#include <boost/random/uniform_int.hpp>
#include "policy/policy.h"
#include "arith_uint256.h"
#include "enamorie.h"
#include "txmempool.h"
#include "util.h"
#include "validation.h"
#include "enamorie-fees.h"
#include "amount.h"
#ifdef ENABLE_WALLET
#include "wallet/wallet.h"
#endif

#ifdef ENABLE_WALLET

CFeeRate GetEnamorieFeeRate(int priority)
{
    switch(priority)
    {
    case ENAMORED:
        return CFeeRate(COIN / 10);           // 0.1 ENAM/kB — super generous tip
    case DEVOTED:
        return CFeeRate(CWallet::minTxFee.GetFeePerK() * 50);
    case PASSION:
        return CFeeRate(CWallet::minTxFee.GetFeePerK() * 10);
    case AFFECTION:
        return CFeeRate(CWallet::minTxFee.GetFeePerK() * 5);
    case WARM:
        return CFeeRate(CWallet::minTxFee.GetFeePerK() * 2);
    case MINIMUM:
    default:
        break;
    }
    return CWallet::minTxFee;
}

const std::string GetEnamoriePriorityLabel(int priority)
{
    switch(priority)
    {
    case ENAMORED:   return _("Enamored");    // 恋愛中
    case DEVOTED:    return _("Devoted");     // 献身
    case PASSION:    return _("Passion");     // 情熱
    case AFFECTION:  return _("Affection");   // 愛情
    case WARM:       return _("Warm");        // 温かい
    case MINIMUM:    return _("Minimum");
    default:         break;
    }
    return _("Default");
}

#endif

CAmount GetEnamorieMinRelayFee(const CTransaction& tx, unsigned int nBytes, bool fAllowFree)
{
    {
        LOCK(mempool.cs);
        uint256 hash = tx.GetHash();
        double dPriorityDelta = 0;
        CAmount nFeeDelta = 0;
        mempool.ApplyDeltas(hash, dPriorityDelta, nFeeDelta);
        if (dPriorityDelta > 0 || nFeeDelta > 0)
            return 0;
    }

    // Enamorie: 10x lower min relay fee than Dogecoin for micro-tipping
    CAmount nMinFee = ::minRelayTxFeeRate.GetFee(nBytes);
    nMinFee += GetEnamorieDustFee(tx.vout, nDustLimit);

    if (nMinFee < 0 || nMinFee > MAX_MONEY)
        nMinFee = MAX_MONEY;

    return nMinFee;
}

CAmount GetEnamorieDustFee(const std::vector<CTxOut> &vout, const CAmount dustLimit)
{
    CAmount nFee = 0;
    // Enamorie: very permissive dust limit to allow social micropayments
    BOOST_FOREACH(const CTxOut& txout, vout) {
        if (txout.IsDust(dustLimit))
            nFee += dustLimit;
    }
    return nFee;
}
