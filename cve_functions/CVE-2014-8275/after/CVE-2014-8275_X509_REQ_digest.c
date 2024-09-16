int X509_REQ_digest(const X509_REQ *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	return(ASN1_item_digest(ASN1_ITEM_rptr(X509_REQ),type,(char *)data,md,len));
	}
