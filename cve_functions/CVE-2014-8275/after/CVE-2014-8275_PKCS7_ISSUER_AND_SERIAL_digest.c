int PKCS7_ISSUER_AND_SERIAL_digest(PKCS7_ISSUER_AND_SERIAL *data, const EVP_MD *type,
	     unsigned char *md, unsigned int *len)
	{
	return(ASN1_item_digest(ASN1_ITEM_rptr(PKCS7_ISSUER_AND_SERIAL),type,
		(char *)data,md,len));
	}
