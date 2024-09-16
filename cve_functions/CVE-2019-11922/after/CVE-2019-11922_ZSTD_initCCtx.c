static void ZSTD_initCCtx(ZSTD_CCtx* cctx, ZSTD_customMem memManager)
{
    assert(cctx != NULL);
    memset(cctx, 0, sizeof(*cctx));
    cctx->customMem = memManager;
    cctx->bmi2 = ZSTD_cpuid_bmi2(ZSTD_cpuid());
    {   size_t const err = ZSTD_CCtx_resetParameters(cctx);
        assert(!ZSTD_isError(err));
        (void)err;
    }
}
