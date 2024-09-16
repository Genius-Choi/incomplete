int X509_CRL_http_nbio(OCSP_REQ_CTX *rctx, X509_CRL **pcrl)
	{
	return OCSP_REQ_CTX_nbio_d2i(rctx,
				(ASN1_VALUE **)pcrl, ASN1_ITEM_rptr(X509_CRL));
	}
