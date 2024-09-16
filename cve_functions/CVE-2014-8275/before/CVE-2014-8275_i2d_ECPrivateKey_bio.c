int i2d_ECPrivateKey_bio(BIO *bp, EC_KEY *eckey)
	{
	return ASN1_i2d_bio_of(EC_KEY,i2d_ECPrivateKey,bp,eckey);
	}
