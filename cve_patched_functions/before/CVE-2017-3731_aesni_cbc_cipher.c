static int aesni_cbc_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                            const unsigned char *in, size_t len)
{
    aesni_cbc_encrypt(in, out, len, &EVP_C_DATA(EVP_AES_KEY,ctx)->ks.ks,
                      EVP_CIPHER_CTX_iv_noconst(ctx),
                      EVP_CIPHER_CTX_encrypting(ctx));

    return 1;
}
