int i2d_PKCS8_PRIV_KEY_INFO_bio(BIO *bp, PKCS8_PRIV_KEY_INFO *p8inf)
	{
	return ASN1_i2d_bio_of(PKCS8_PRIV_KEY_INFO,i2d_PKCS8_PRIV_KEY_INFO,bp,
			       p8inf);
	}
