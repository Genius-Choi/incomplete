static int aes_cfb1_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                           const unsigned char *in, size_t len)
{
    EVP_AES_KEY *dat = EVP_C_DATA(EVP_AES_KEY,ctx);

    if (EVP_CIPHER_CTX_test_flags(ctx, EVP_CIPH_FLAG_LENGTH_BITS)) {
        int num = EVP_CIPHER_CTX_num(ctx);
        CRYPTO_cfb128_1_encrypt(in, out, len, &dat->ks,
                                EVP_CIPHER_CTX_iv_noconst(ctx), &num,
                                EVP_CIPHER_CTX_encrypting(ctx), dat->block);
        EVP_CIPHER_CTX_set_num(ctx, num);
        return 1;
    }

    while (len >= MAXBITCHUNK) {
        int num = EVP_CIPHER_CTX_num(ctx);
        CRYPTO_cfb128_1_encrypt(in, out, MAXBITCHUNK * 8, &dat->ks,
                                EVP_CIPHER_CTX_iv_noconst(ctx), &num,
                                EVP_CIPHER_CTX_encrypting(ctx), dat->block);
        EVP_CIPHER_CTX_set_num(ctx, num);
        len -= MAXBITCHUNK;
    }
    if (len) {
        int num = EVP_CIPHER_CTX_num(ctx);
        CRYPTO_cfb128_1_encrypt(in, out, len * 8, &dat->ks,
                                EVP_CIPHER_CTX_iv_noconst(ctx), &num,
                                EVP_CIPHER_CTX_encrypting(ctx), dat->block);
        EVP_CIPHER_CTX_set_num(ctx, num);
    }

    return 1;
}
