int i2d_PUBKEY_bio(BIO *bp, EVP_PKEY *pkey)
	{
	return ASN1_i2d_bio_of(EVP_PKEY,i2d_PUBKEY,bp,pkey);
	}
