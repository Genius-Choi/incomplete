size_t ZSTD_resetCStream(ZSTD_CStream* zcs, unsigned long long pledgedSrcSize)
{
    ZSTD_CCtx_params params = zcs->requestedParams;
    DEBUGLOG(4, "ZSTD_resetCStream: pledgedSrcSize = %u", (U32)pledgedSrcSize);
    if (pledgedSrcSize==0) pledgedSrcSize = ZSTD_CONTENTSIZE_UNKNOWN;
    params.fParams.contentSizeFlag = 1;
    return ZSTD_resetCStream_internal(zcs, NULL, 0, ZSTD_dct_auto, zcs->cdict, params, pledgedSrcSize);
}
