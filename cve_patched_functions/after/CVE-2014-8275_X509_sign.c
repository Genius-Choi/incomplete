int X509_sign(X509 *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	x->cert_info->enc.modified = 1;
	return(ASN1_item_sign(ASN1_ITEM_rptr(X509_CINF), x->cert_info->signature,
		x->sig_alg, x->signature, x->cert_info,pkey,md));
	}
