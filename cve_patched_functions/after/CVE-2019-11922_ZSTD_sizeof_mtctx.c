static size_t ZSTD_sizeof_mtctx(const ZSTD_CCtx* cctx)
{
#ifdef ZSTD_MULTITHREAD
    return ZSTDMT_sizeof_CCtx(cctx->mtctx);
#else
    (void) cctx;
    return 0;
#endif
}
