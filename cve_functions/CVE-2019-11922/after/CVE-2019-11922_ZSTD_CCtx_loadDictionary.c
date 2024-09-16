ZSTDLIB_API size_t ZSTD_CCtx_loadDictionary(ZSTD_CCtx* cctx, const void* dict, size_t dictSize)
{
    return ZSTD_CCtx_loadDictionary_advanced(
            cctx, dict, dictSize, ZSTD_dlm_byCopy, ZSTD_dct_auto);
}
