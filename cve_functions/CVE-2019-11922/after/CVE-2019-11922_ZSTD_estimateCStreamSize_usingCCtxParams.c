size_t ZSTD_estimateCStreamSize_usingCCtxParams(const ZSTD_CCtx_params* params)
{
    if (params->nbWorkers > 0) { return ERROR(GENERIC); }
    {   size_t const CCtxSize = ZSTD_estimateCCtxSize_usingCCtxParams(params);
        size_t const blockSize = MIN(ZSTD_BLOCKSIZE_MAX, (size_t)1 << params->cParams.windowLog);
        size_t const inBuffSize = ((size_t)1 << params->cParams.windowLog) + blockSize;
        size_t const outBuffSize = ZSTD_compressBound(blockSize) + 1;
        size_t const streamingSize = inBuffSize + outBuffSize;

        return CCtxSize + streamingSize;
    }
}
