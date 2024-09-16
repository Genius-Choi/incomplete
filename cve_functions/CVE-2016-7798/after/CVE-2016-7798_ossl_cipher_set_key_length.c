ossl_cipher_set_key_length(VALUE self, VALUE key_length)
{
    int len = NUM2INT(key_length);
    EVP_CIPHER_CTX *ctx;

    GetCipher(self, ctx);
    if (EVP_CIPHER_CTX_set_key_length(ctx, len) != 1)
        ossl_raise(eCipherError, NULL);

    return key_length;
}
