ossl_cipher_iv_length(VALUE self)
{
    EVP_CIPHER_CTX *ctx;
    int len = 0;

    GetCipher(self, ctx);
#if defined(HAVE_AUTHENTICATED_ENCRYPTION)
    if (EVP_CIPHER_CTX_flags(ctx) & EVP_CIPH_FLAG_AEAD_CIPHER)
	len = (int)(VALUE)EVP_CIPHER_CTX_get_app_data(ctx);
#endif
    if (!len)
	len = EVP_CIPHER_CTX_iv_length(ctx);

    return INT2NUM(len);
}
