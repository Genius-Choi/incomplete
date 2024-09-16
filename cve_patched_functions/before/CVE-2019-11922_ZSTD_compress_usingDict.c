size_t ZSTD_compress_usingDict(ZSTD_CCtx* cctx,
                               void* dst, size_t dstCapacity,
                         const void* src, size_t srcSize,
                         const void* dict, size_t dictSize,
                               int compressionLevel)
{
    ZSTD_parameters const params = ZSTD_getParams(compressionLevel, srcSize + (!srcSize), dict ? dictSize : 0);
    ZSTD_CCtx_params cctxParams = ZSTD_assignParamsToCCtxParams(cctx->requestedParams, params);
    assert(params.fParams.contentSizeFlag == 1);
    return ZSTD_compress_advanced_internal(cctx, dst, dstCapacity, src, srcSize, dict, dictSize, cctxParams);
}
