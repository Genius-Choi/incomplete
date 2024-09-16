int X509_digest(const X509 *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(ASN1_ITEM_rptr(X509),type,(char *)data,md,len));
	}
