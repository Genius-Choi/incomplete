size_t ZSTD_getBlockSize(const ZSTD_CCtx* cctx)
{
    ZSTD_compressionParameters const cParams = cctx->appliedParams.cParams;
    assert(!ZSTD_checkCParams(cParams));
    return MIN (ZSTD_BLOCKSIZE_MAX, (U32)1 << cParams.windowLog);
}
