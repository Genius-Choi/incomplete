RSA *d2i_RSAPublicKey_bio(BIO *bp, RSA **rsa)
	{
	return ASN1_item_d2i_bio(ASN1_ITEM_rptr(RSAPublicKey), bp, rsa);
	}
