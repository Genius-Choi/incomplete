DSA *d2i_DSA_PUBKEY_bio(BIO *bp, DSA **dsa)
	{
	return ASN1_d2i_bio_of(DSA,DSA_new,d2i_DSA_PUBKEY,bp,dsa);
	}
