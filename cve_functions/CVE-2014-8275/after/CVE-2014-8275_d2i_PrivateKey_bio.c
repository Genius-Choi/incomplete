EVP_PKEY *d2i_PrivateKey_bio(BIO *bp, EVP_PKEY **a)
	{
	return ASN1_d2i_bio_of(EVP_PKEY,EVP_PKEY_new,d2i_AutoPrivateKey,bp,a);
	}
