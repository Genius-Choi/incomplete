void ZSTD_CCtx_reset(ZSTD_CCtx* cctx)
{
    cctx->streamStage = zcss_init;
    cctx->pledgedSrcSizePlusOne = 0;
}
