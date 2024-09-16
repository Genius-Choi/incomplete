ZSTD_CCtx_params* ZSTD_createCCtxParams(void)
{
    return ZSTD_createCCtxParams_advanced(ZSTD_defaultCMem);
}
