ossl_cipher_set_padding(VALUE self, VALUE padding)
{
    EVP_CIPHER_CTX *ctx;
    int pad = NUM2INT(padding);

    GetCipher(self, ctx);
    if (EVP_CIPHER_CTX_set_padding(ctx, pad) != 1)
	ossl_raise(eCipherError, NULL);
    return padding;
}
