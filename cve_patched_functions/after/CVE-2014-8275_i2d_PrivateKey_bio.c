int i2d_PrivateKey_bio(BIO *bp, EVP_PKEY *pkey)
	{
	return ASN1_i2d_bio_of(EVP_PKEY,i2d_PrivateKey,bp,pkey);
	}
