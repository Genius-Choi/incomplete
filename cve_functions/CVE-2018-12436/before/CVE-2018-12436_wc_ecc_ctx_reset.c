int wc_ecc_ctx_reset(ecEncCtx* ctx, WC_RNG* rng)
{
    if (ctx == NULL || rng == NULL)
        return BAD_FUNC_ARG;

    ecc_ctx_init(ctx, ctx->protocol);
    return ecc_ctx_set_salt(ctx, ctx->protocol, rng);
}
