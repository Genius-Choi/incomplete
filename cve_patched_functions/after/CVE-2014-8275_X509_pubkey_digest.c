int X509_pubkey_digest(const X509 *data, const EVP_MD *type, unsigned char *md,
	     unsigned int *len)
	{
	ASN1_BIT_STRING *key;
	key = X509_get0_pubkey_bitstr(data);
	if(!key) return 0;
	return EVP_Digest(key->data, key->length, md, len, type, NULL);
	}
