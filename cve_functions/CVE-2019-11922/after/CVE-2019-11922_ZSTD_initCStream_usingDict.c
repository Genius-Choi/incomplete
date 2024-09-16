size_t ZSTD_initCStream_usingDict(ZSTD_CStream* zcs, const void* dict, size_t dictSize, int compressionLevel)
{
    ZSTD_CCtxParams_init(&zcs->requestedParams, compressionLevel);
    return ZSTD_initCStream_internal(zcs, dict, dictSize, NULL, zcs->requestedParams, ZSTD_CONTENTSIZE_UNKNOWN);
}
