// Copyright (c) 2015-2022 The Dogecoin Core developers
// Copyright (c) 2025 The Enamorie Coin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "policy/policy.h"
#include "arith_uint256.h"
#include "enamorie.h"
#include "txmempool.h"
#include "util.h"
#include "validation.h"
#include "enamorie-fees.h"

int static generateMTRandom(unsigned int s, int range)
{
    boost::mt19937 gen(s);
    boost::uniform_int<> dist(1, range);
    return dist(gen);
}

// Enamorie: Digishield minimum difficulty handling
bool AllowDigishieldMinDifficultyForBlock(const CBlockIndex* pindexLast, const CBlockHeader *pblock, const Consensus::Params& params)
{
    if (!params.fPowAllowMinDifficultyBlocks)
        return false;

    if (pindexLast->nHeight < 157500)
        return false;

    return (pblock->GetBlockTime() > pindexLast->GetBlockTime() + params.nPowTargetSpacing*2);
}

unsigned int CalculateEnamorieNextWorkRequired(const CBlockIndex* pindexLast, int64_t nFirstBlockTime, const Consensus::Params& params)
{
    int nHeight = pindexLast->nHeight + 1;
    const int64_t retargetTimespan = params.nPowTargetTimespan;
    const int64_t nActualTimespan = pindexLast->GetBlockTime() - nFirstBlockTime;
    int64_t nModulatedTimespan = nActualTimespan;
    int64_t nMaxTimespan;
    int64_t nMinTimespan;

    if (params.fDigishieldDifficultyCalculation)
    {
        nModulatedTimespan = retargetTimespan + (nModulatedTimespan - retargetTimespan) / 8;
        nMinTimespan = retargetTimespan - (retargetTimespan / 4);
        nMaxTimespan = retargetTimespan + (retargetTimespan / 2);
    } else if (nHeight > 10000) {
        nMinTimespan = retargetTimespan / 4;
        nMaxTimespan = retargetTimespan * 4;
    } else if (nHeight > 5000) {
        nMinTimespan = retargetTimespan / 8;
        nMaxTimespan = retargetTimespan * 4;
    } else {
        nMinTimespan = retargetTimespan / 16;
        nMaxTimespan = retargetTimespan * 4;
    }

    if (nModulatedTimespan < nMinTimespan)
        nModulatedTimespan = nMinTimespan;
    else if (nModulatedTimespan > nMaxTimespan)
        nModulatedTimespan = nMaxTimespan;

    const arith_uint256 bnPowLimit = UintToArith256(params.powLimit);
    arith_uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);
    bnNew *= nModulatedTimespan;
    bnNew /= retargetTimespan;

    if (bnNew > bnPowLimit)
        bnNew = bnPowLimit;

    return bnNew.GetCompact();
}

bool CheckAuxPowProofOfWork(const CBlockHeader& block, const Consensus::Params& params)
{
    if (!block.IsLegacy() && params.fStrictChainId && block.GetChainId() != params.nAuxpowChainId)
        return error("%s : block does not have our chain ID"
                     " (got %d, expected %d, full nVersion %d)",
                     __func__, block.GetChainId(),
                     params.nAuxpowChainId, block.nVersion);

    if (!block.auxpow) {
        if (block.IsAuxpow())
            return error("%s : no auxpow on block with auxpow version", __func__);
        if (!CheckProofOfWork(block.GetPoWHash(), block.nBits, params))
            return error("%s : non-AUX proof of work failed", __func__);
        return true;
    }

    if (!block.IsAuxpow())
        return error("%s : auxpow on block with non-auxpow version", __func__);
    if (!CheckProofOfWork(block.auxpow->getParentBlockPoWHash(), block.nBits, params))
        return error("%s : AUX proof of work failed", __func__);
    if (!block.auxpow->check(block.GetHash(), block.GetChainId(), params))
        return error("%s : AUX POW is not valid", __func__);

    return true;
}

// =============================================================
// Enamorie Coin Block Subsidy
// =============================================================
// Design goals for user growth:
//   - Fast 30s blocks → quick confirmations → better UX
//   - Generous initial supply → low barrier, everyone gets coins
//   - Slow halving (525,600 blocks ≈ 6 months) → steady miner incentive
//   - Permanent tail emission (500 ENAM) → no mining cliff
//   - Low fees → micro-tipping & community tipping culture
// =============================================================
CAmount GetEnamorieBlockSubsidy(int nHeight, const Consensus::Params& consensusParams, uint256 prevHash)
{
    int halvings = nHeight / consensusParams.nSubsidyHalvingInterval;

    if (!consensusParams.fSimplifiedRewards)
    {
        // Phase 1 (blocks 0–144,999): Random rewards — excitement & discovery phase
        // Range: 1–50,000 ENAM per block, halved each interval
        const std::string cseed_str = prevHash.ToString().substr(7, 7);
        const char* cseed = cseed_str.c_str();
        char* endp = NULL;
        long seed = strtol(cseed, &endp, 16);
        CAmount maxReward = (50000 >> halvings) - 1;
        int rand = generateMTRandom(seed, maxReward);
        return (1 + rand) * COIN;
    }
    else if (halvings < 8)
    {
        // Phase 2 (blocks 145,000+): Simplified constant rewards per era
        // Era 0: 10,000 ENAM → Era 1: 5,000 → ... → Era 7: ~78 ENAM
        return (10000 * COIN) >> halvings;
    }
    else
    {
        // Phase 3: Permanent tail emission — keeps miners incentivized forever
        // 500 ENAM per block, always. This is ~0.001% annual inflation at maturity.
        return 500 * COIN;
    }
}
