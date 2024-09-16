size_t ZSTD_CCtx_resetParameters(ZSTD_CCtx* cctx)
{
    if (cctx->streamStage != zcss_init) return ERROR(stage_wrong);
    cctx->cdict = NULL;
    return ZSTD_CCtxParams_reset(&cctx->requestedParams);
}
