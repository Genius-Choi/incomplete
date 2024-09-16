int X509_REQ_sign(X509_REQ *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	return(ASN1_item_sign(ASN1_ITEM_rptr(X509_REQ_INFO),x->sig_alg, NULL,
		x->signature, x->req_info,pkey,md));
	}
