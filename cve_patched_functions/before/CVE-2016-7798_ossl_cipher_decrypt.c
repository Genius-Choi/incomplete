ossl_cipher_decrypt(int argc, VALUE *argv, VALUE self)
{
    return ossl_cipher_init(argc, argv, self, 0);
}
