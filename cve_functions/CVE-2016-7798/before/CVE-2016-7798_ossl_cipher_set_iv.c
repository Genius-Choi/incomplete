ossl_cipher_set_iv(VALUE self, VALUE iv)
{
    EVP_CIPHER_CTX *ctx;
    int iv_len = 0;

    StringValue(iv);
    GetCipher(self, ctx);

#if defined(HAVE_AUTHENTICATED_ENCRYPTION)
    if (EVP_CIPHER_CTX_flags(ctx) & EVP_CIPH_FLAG_AEAD_CIPHER)
	iv_len = (int)(VALUE)EVP_CIPHER_CTX_get_app_data(ctx);
#endif
    if (!iv_len)
	iv_len = EVP_CIPHER_CTX_iv_length(ctx);
    if (RSTRING_LEN(iv) != iv_len)
	ossl_raise(rb_eArgError, "iv must be %d bytes", iv_len);

    if (EVP_CipherInit_ex(ctx, NULL, NULL, NULL, (unsigned char *)RSTRING_PTR(iv), -1) != 1)
	ossl_raise(eCipherError, NULL);

    return iv;
}
