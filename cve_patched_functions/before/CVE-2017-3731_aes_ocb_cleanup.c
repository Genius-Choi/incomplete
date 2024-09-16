static int aes_ocb_cleanup(EVP_CIPHER_CTX *c)
{
    EVP_AES_OCB_CTX *octx = EVP_C_DATA(EVP_AES_OCB_CTX,c);
    CRYPTO_ocb128_cleanup(&octx->ocb);
    return 1;
}
