int X509_REQ_sign_ctx(X509_REQ *x, EVP_MD_CTX *ctx)
	{
	return ASN1_item_sign_ctx(ASN1_ITEM_rptr(X509_REQ_INFO),
		x->sig_alg, NULL, x->signature, x->req_info, ctx);
	}
