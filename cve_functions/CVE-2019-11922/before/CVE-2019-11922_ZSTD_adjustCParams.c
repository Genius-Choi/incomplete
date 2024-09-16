ZSTD_adjustCParams(ZSTD_compressionParameters cPar,
                   unsigned long long srcSize,
                   size_t dictSize)
{
    cPar = ZSTD_clampCParams(cPar);
    return ZSTD_adjustCParams_internal(cPar, srcSize, dictSize);
}
