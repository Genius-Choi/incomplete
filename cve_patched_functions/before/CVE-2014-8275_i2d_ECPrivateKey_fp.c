int i2d_ECPrivateKey_fp(FILE *fp, EC_KEY *eckey)
	{
	return ASN1_i2d_fp_of(EC_KEY,i2d_ECPrivateKey,fp,eckey);
	}
