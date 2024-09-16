static size_t ZSTD_compress_internal (ZSTD_CCtx* cctx,
                                      void* dst, size_t dstCapacity,
                                const void* src, size_t srcSize,
                                const void* dict,size_t dictSize,
                                      ZSTD_parameters params)
{
    ZSTD_CCtx_params const cctxParams =
            ZSTD_assignParamsToCCtxParams(cctx->requestedParams, params);
    DEBUGLOG(4, "ZSTD_compress_internal");
    return ZSTD_compress_advanced_internal(cctx,
                                           dst, dstCapacity,
                                           src, srcSize,
                                           dict, dictSize,
                                           cctxParams);
}
