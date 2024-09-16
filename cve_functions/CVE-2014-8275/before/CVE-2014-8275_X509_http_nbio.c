int X509_http_nbio(OCSP_REQ_CTX *rctx, X509 **pcert)
	{
	return OCSP_REQ_CTX_nbio_d2i(rctx,
				(ASN1_VALUE **)pcert, ASN1_ITEM_rptr(X509));
	}
