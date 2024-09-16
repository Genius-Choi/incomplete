int X509_CRL_digest(const X509_CRL *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(ASN1_ITEM_rptr(X509_CRL),type,(char *)data,md,len));
	}
