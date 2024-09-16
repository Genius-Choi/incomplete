int i2d_DSAPrivateKey_bio(BIO *bp, DSA *dsa)
	{
	return ASN1_i2d_bio_of_const(DSA,i2d_DSAPrivateKey,bp,dsa);
	}
