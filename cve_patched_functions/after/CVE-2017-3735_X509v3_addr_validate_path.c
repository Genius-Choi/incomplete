int X509v3_addr_validate_path(X509_STORE_CTX *ctx)
{
    return addr_validate_path_internal(ctx, ctx->chain, NULL);
}
