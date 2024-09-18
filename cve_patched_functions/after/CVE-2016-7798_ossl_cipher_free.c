ossl_cipher_free(void *ptr)
{
    EVP_CIPHER_CTX_free(ptr);
}
