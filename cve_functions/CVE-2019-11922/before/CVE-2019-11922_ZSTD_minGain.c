static size_t ZSTD_minGain(size_t srcSize, ZSTD_strategy strat)
{
    U32 const minlog = (strat==ZSTD_btultra) ? 7 : 6;
    return (srcSize >> minlog) + 2;
}
