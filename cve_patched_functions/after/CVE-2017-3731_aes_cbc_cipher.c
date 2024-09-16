static int aes_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                          const unsigned char *in, size_t len)
{
    EVP_AES_KEY *dat = EVP_C_DATA(EVP_AES_KEY,ctx);

    if (dat->stream.cbc)
        (*dat->stream.cbc) (in, out, len, &dat->ks,
                            EVP_CIPHER_CTX_iv_noconst(ctx),
                            EVP_CIPHER_CTX_encrypting(ctx));
    else if (EVP_CIPHER_CTX_encrypting(ctx))
        CRYPTO_cbc128_encrypt(in, out, len, &dat->ks,
                              EVP_CIPHER_CTX_iv_noconst(ctx), dat->block);
    else
        CRYPTO_cbc128_decrypt(in, out, len, &dat->ks,
                              EVP_CIPHER_CTX_iv_noconst(ctx), dat->block);

    return 1;
}
