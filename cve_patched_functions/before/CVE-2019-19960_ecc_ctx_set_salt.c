static int ecc_ctx_set_salt(ecEncCtx* ctx, int flags, WC_RNG* rng)
{
    byte* saltBuffer = NULL;

    if (ctx == NULL || rng == NULL || flags == 0)
        return BAD_FUNC_ARG;

    saltBuffer = (flags == REQ_RESP_CLIENT) ? ctx->clientSalt : ctx->serverSalt;

    return wc_RNG_GenerateBlock(rng, saltBuffer, EXCHANGE_SALT_SZ);
}
