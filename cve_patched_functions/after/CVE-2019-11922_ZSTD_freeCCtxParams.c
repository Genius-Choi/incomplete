size_t ZSTD_freeCCtxParams(ZSTD_CCtx_params* params)
{
    if (params == NULL) { return 0; }
    ZSTD_free(params, params->customMem);
    return 0;
}
