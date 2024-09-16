ZSTD_clampCParams(ZSTD_compressionParameters cParams)
{
#   define CLAMP(val,min,max) {      \
        if (val<min) val=min;        \
        else if (val>max) val=max;   \
    }
    CLAMP(cParams.windowLog, ZSTD_WINDOWLOG_MIN, ZSTD_WINDOWLOG_MAX);
    CLAMP(cParams.chainLog, ZSTD_CHAINLOG_MIN, ZSTD_CHAINLOG_MAX);
    CLAMP(cParams.hashLog, ZSTD_HASHLOG_MIN, ZSTD_HASHLOG_MAX);
    CLAMP(cParams.searchLog, ZSTD_SEARCHLOG_MIN, ZSTD_SEARCHLOG_MAX);
    CLAMP(cParams.searchLength, ZSTD_SEARCHLENGTH_MIN, ZSTD_SEARCHLENGTH_MAX);
    ZSTD_STATIC_ASSERT(ZSTD_TARGETLENGTH_MIN == 0);
    if (cParams.targetLength > ZSTD_TARGETLENGTH_MAX)
        cParams.targetLength = ZSTD_TARGETLENGTH_MAX;
    CLAMP(cParams.strategy, ZSTD_fast, ZSTD_btultra);
    return cParams;
}
