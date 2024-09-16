static ZSTD_CCtx_params* ZSTD_createCCtxParams_advanced(
        ZSTD_customMem customMem)
{
    ZSTD_CCtx_params* params;
    if (!customMem.customAlloc ^ !customMem.customFree) return NULL;
    params = (ZSTD_CCtx_params*)ZSTD_calloc(
            sizeof(ZSTD_CCtx_params), customMem);
    if (!params) { return NULL; }
    params->customMem = customMem;
    params->compressionLevel = ZSTD_CLEVEL_DEFAULT;
    params->fParams.contentSizeFlag = 1;
    return params;
}
