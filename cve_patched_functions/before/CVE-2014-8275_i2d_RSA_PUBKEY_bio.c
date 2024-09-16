int i2d_RSA_PUBKEY_bio(BIO *bp, RSA *rsa)
	{
	return ASN1_i2d_bio_of(RSA,i2d_RSA_PUBKEY,bp,rsa);
	}
