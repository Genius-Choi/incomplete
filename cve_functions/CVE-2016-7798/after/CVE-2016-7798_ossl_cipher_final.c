ossl_cipher_final(VALUE self)
{
    EVP_CIPHER_CTX *ctx;
    int out_len;
    VALUE str;

    GetCipher(self, ctx);
    str = rb_str_new(0, EVP_CIPHER_CTX_block_size(ctx));
    if (!EVP_CipherFinal_ex(ctx, (unsigned char *)RSTRING_PTR(str), &out_len))
	ossl_raise(eCipherError, NULL);
    assert(out_len <= RSTRING_LEN(str));
    rb_str_set_len(str, out_len);

    return str;
}
