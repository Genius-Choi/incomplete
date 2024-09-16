static int aesni_init_key(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                          const unsigned char *iv, int enc)
{
    int ret, mode;
    EVP_AES_KEY *dat = EVP_C_DATA(EVP_AES_KEY,ctx);

    mode = EVP_CIPHER_CTX_mode(ctx);
    if ((mode == EVP_CIPH_ECB_MODE || mode == EVP_CIPH_CBC_MODE)
        && !enc) {
        ret = aesni_set_decrypt_key(key, EVP_CIPHER_CTX_key_length(ctx) * 8,
                                    &dat->ks.ks);
        dat->block = (block128_f) aesni_decrypt;
        dat->stream.cbc = mode == EVP_CIPH_CBC_MODE ?
            (cbc128_f) aesni_cbc_encrypt : NULL;
    } else {
        ret = aesni_set_encrypt_key(key, EVP_CIPHER_CTX_key_length(ctx) * 8,
                                    &dat->ks.ks);
        dat->block = (block128_f) aesni_encrypt;
        if (mode == EVP_CIPH_CBC_MODE)
            dat->stream.cbc = (cbc128_f) aesni_cbc_encrypt;
        else if (mode == EVP_CIPH_CTR_MODE)
            dat->stream.ctr = (ctr128_f) aesni_ctr32_encrypt_blocks;
        else
            dat->stream.cbc = NULL;
    }

    if (ret < 0) {
        EVPerr(EVP_F_AESNI_INIT_KEY, EVP_R_AES_KEY_SETUP_FAILED);
        return 0;
    }

    return 1;
}
