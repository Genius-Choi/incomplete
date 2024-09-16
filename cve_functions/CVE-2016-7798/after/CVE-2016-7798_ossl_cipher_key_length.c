ossl_cipher_key_length(VALUE self)
{
    EVP_CIPHER_CTX *ctx;

    GetCipher(self, ctx);

    return INT2NUM(EVP_CIPHER_CTX_key_length(ctx));
}
