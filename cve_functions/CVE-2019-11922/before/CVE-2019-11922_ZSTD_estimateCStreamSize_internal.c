static size_t ZSTD_estimateCStreamSize_internal(int compressionLevel)
{
    ZSTD_compressionParameters const cParams = ZSTD_getCParams(compressionLevel, 0, 0);
    return ZSTD_estimateCStreamSize_usingCParams(cParams);
}
