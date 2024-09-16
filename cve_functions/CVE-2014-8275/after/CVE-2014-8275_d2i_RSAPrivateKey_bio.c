RSA *d2i_RSAPrivateKey_bio(BIO *bp, RSA **rsa)
	{
	return ASN1_item_d2i_bio(ASN1_ITEM_rptr(RSAPrivateKey), bp, rsa);
	}
