static int chacha20_poly1305_cleanup(EVP_CIPHER_CTX *ctx)
{
    EVP_CHACHA_AEAD_CTX *actx = aead_data(ctx);
    if (actx)
        OPENSSL_cleanse(ctx->cipher_data, sizeof(*ctx) + Poly1305_ctx_size());
    return 1;
}
