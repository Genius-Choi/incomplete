int wc_ecc_ctx_set_info(ecEncCtx* ctx, const byte* info, int sz)
{
    if (ctx == NULL || info == 0 || sz < 0)
        return BAD_FUNC_ARG;

    ctx->kdfInfo   = info;
    ctx->kdfInfoSz = sz;

    return 0;
}
