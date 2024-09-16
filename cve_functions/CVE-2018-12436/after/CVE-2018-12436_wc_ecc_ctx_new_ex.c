ecEncCtx* wc_ecc_ctx_new_ex(int flags, WC_RNG* rng, void* heap)
{
    int       ret = 0;
    ecEncCtx* ctx = (ecEncCtx*)XMALLOC(sizeof(ecEncCtx), heap,
                                                              DYNAMIC_TYPE_ECC);

    if (ctx) {
        ctx->protocol = (byte)flags;
        ctx->heap     = heap;
    }

    ret = wc_ecc_ctx_reset(ctx, rng);
    if (ret != 0) {
        wc_ecc_ctx_free(ctx);
        ctx = NULL;
    }

    return ctx;
}
