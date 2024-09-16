ossl_cipher_block_size(VALUE self)
{
    EVP_CIPHER_CTX *ctx;

    GetCipher(self, ctx);

    return INT2NUM(EVP_CIPHER_CTX_block_size(ctx));
}
