ossl_cipher_new(const EVP_CIPHER *cipher)
{
    VALUE ret;
    EVP_CIPHER_CTX *ctx;

    ret = ossl_cipher_alloc(cCipher);
    AllocCipher(ret, ctx);
    if (EVP_CipherInit_ex(ctx, cipher, NULL, NULL, NULL, -1) != 1)
	ossl_raise(eCipherError, NULL);

    return ret;
}
