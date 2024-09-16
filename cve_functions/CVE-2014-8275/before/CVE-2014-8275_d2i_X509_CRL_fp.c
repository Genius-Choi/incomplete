X509_CRL *d2i_X509_CRL_fp(FILE *fp, X509_CRL **crl)
	{
	return ASN1_item_d2i_fp(ASN1_ITEM_rptr(X509_CRL), fp, crl);
	}
