int i2d_DSA_PUBKEY_bio(BIO *bp, DSA *dsa)
	{
	return ASN1_i2d_bio_of(DSA,i2d_DSA_PUBKEY,bp,dsa);
	}
