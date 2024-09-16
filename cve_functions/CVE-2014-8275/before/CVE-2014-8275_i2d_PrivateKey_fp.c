int i2d_PrivateKey_fp(FILE *fp, EVP_PKEY *pkey)
	{
	return ASN1_i2d_fp_of(EVP_PKEY,i2d_PrivateKey,fp,pkey);
	}
