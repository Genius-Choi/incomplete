int i2d_PUBKEY_fp(FILE *fp, EVP_PKEY *pkey)
	{
	return ASN1_i2d_fp_of(EVP_PKEY,i2d_PUBKEY,fp,pkey);
	}
