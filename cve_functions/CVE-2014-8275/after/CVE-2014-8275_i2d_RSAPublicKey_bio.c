int i2d_RSAPublicKey_bio(BIO *bp, RSA *rsa)
	{
	return ASN1_item_i2d_bio(ASN1_ITEM_rptr(RSAPublicKey), bp, rsa);
	}
