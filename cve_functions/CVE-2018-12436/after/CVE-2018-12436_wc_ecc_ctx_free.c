void wc_ecc_ctx_free(ecEncCtx* ctx)
{
    if (ctx) {
        ForceZero(ctx, sizeof(ecEncCtx));
        XFREE(ctx, ctx->heap, DYNAMIC_TYPE_ECC);
    }
}
