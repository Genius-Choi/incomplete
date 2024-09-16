ossl_cipher_encrypt(int argc, VALUE *argv, VALUE self)
{
    return ossl_cipher_init(argc, argv, self, 1);
}
