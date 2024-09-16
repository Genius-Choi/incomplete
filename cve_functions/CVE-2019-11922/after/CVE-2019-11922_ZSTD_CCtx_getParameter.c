size_t ZSTD_CCtx_getParameter(ZSTD_CCtx* cctx, ZSTD_cParameter param, unsigned* value)
{
    return ZSTD_CCtxParam_getParameter(&cctx->requestedParams, param, value);
}
