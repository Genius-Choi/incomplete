ZSTDLIB_API size_t ZSTD_CCtx_setPledgedSrcSize(ZSTD_CCtx* cctx, unsigned long long pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_CCtx_setPledgedSrcSize to %u bytes", (U32)pledgedSrcSize);
    if (cctx->streamStage != zcss_init) return ERROR(stage_wrong);
    cctx->pledgedSrcSizePlusOne = pledgedSrcSize+1;
    return 0;
}
