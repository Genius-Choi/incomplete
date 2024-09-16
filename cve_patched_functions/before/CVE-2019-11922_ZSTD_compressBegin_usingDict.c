size_t ZSTD_compressBegin_usingDict(ZSTD_CCtx* cctx, const void* dict, size_t dictSize, int compressionLevel)
{
    ZSTD_parameters const params = ZSTD_getParams(compressionLevel, ZSTD_CONTENTSIZE_UNKNOWN, dictSize);
    ZSTD_CCtx_params const cctxParams =
            ZSTD_assignParamsToCCtxParams(cctx->requestedParams, params);
    DEBUGLOG(4, "ZSTD_compressBegin_usingDict (dictSize=%u)", (U32)dictSize);
    return ZSTD_compressBegin_internal(cctx, dict, dictSize, ZSTD_dct_auto, ZSTD_dtlm_fast, NULL,
                                       cctxParams, ZSTD_CONTENTSIZE_UNKNOWN, ZSTDb_not_buffered);
}
