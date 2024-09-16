size_t ZSTD_estimateCStreamSize_usingCParams(ZSTD_compressionParameters cParams)
{
    ZSTD_CCtx_params const params = ZSTD_makeCCtxParamsFromCParams(cParams);
    return ZSTD_estimateCStreamSize_usingCCtxParams(&params);
}
