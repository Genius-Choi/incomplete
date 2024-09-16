int X509_NAME_digest(const X509_NAME *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(ASN1_ITEM_rptr(X509_NAME),type,(char *)data,md,len));
	}
