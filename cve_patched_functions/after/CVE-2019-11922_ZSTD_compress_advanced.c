size_t ZSTD_compress_advanced (ZSTD_CCtx* cctx,
                               void* dst, size_t dstCapacity,
                         const void* src, size_t srcSize,
                         const void* dict,size_t dictSize,
                               ZSTD_parameters params)
{
    DEBUGLOG(4, "ZSTD_compress_advanced");
    CHECK_F(ZSTD_checkCParams(params.cParams));
    return ZSTD_compress_internal(cctx,
                                  dst, dstCapacity,
                                  src, srcSize,
                                  dict, dictSize,
                                  params);
}
