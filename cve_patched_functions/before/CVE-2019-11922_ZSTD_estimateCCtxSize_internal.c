static size_t ZSTD_estimateCCtxSize_internal(int compressionLevel)
{
    ZSTD_compressionParameters const cParams = ZSTD_getCParams(compressionLevel, 0, 0);
    return ZSTD_estimateCCtxSize_usingCParams(cParams);
}
