int X509_sign_ctx(X509 *x, EVP_MD_CTX *ctx)
	{
	x->cert_info->enc.modified = 1;
	return ASN1_item_sign_ctx(ASN1_ITEM_rptr(X509_CINF),
		x->cert_info->signature,
		x->sig_alg, x->signature, x->cert_info, ctx);
	}
