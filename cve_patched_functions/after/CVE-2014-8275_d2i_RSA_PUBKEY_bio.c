RSA *d2i_RSA_PUBKEY_bio(BIO *bp, RSA **rsa)
	{
	return ASN1_d2i_bio_of(RSA,RSA_new,d2i_RSA_PUBKEY,bp,rsa);
	}
