GetCipherPtr(VALUE obj)
{
    if (rb_obj_is_kind_of(obj, cCipher)) {
	EVP_CIPHER_CTX *ctx;

	GetCipher(obj, ctx);

	return EVP_CIPHER_CTX_cipher(ctx);
    }
    else {
	const EVP_CIPHER *cipher;

	StringValueCStr(obj);
	cipher = EVP_get_cipherbyname(RSTRING_PTR(obj));
	if (!cipher)
	    ossl_raise(rb_eArgError,
		       "unsupported cipher algorithm: %"PRIsVALUE, obj);

	return cipher;
    }
}
