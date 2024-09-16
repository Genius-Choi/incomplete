ossl_cipher_get_auth_tag(int argc, VALUE *argv, VALUE self)
{
    VALUE vtag_len, ret;
    EVP_CIPHER_CTX *ctx;
    int tag_len = 16;

    rb_scan_args(argc, argv, "01", &vtag_len);
    if (NIL_P(vtag_len))
	vtag_len = rb_attr_get(self, id_auth_tag_len);
    if (!NIL_P(vtag_len))
	tag_len = NUM2INT(vtag_len);

    GetCipher(self, ctx);

    if (!(EVP_CIPHER_CTX_flags(ctx) & EVP_CIPH_FLAG_AEAD_CIPHER))
	ossl_raise(eCipherError, "authentication tag not supported by this cipher");

    ret = rb_str_new(NULL, tag_len);
    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_GET_TAG, tag_len, RSTRING_PTR(ret)))
	ossl_raise(eCipherError, "retrieving the authentication tag failed");

    return ret;
}
