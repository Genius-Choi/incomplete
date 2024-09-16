int X509_CRL_sign(X509_CRL *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	x->crl->enc.modified = 1;
	return(ASN1_item_sign(ASN1_ITEM_rptr(X509_CRL_INFO),x->crl->sig_alg,
		x->sig_alg, x->signature, x->crl,pkey,md));
	}
