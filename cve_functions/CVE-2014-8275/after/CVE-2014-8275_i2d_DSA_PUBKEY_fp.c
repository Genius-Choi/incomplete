int i2d_DSA_PUBKEY_fp(FILE *fp, DSA *dsa)
	{
	return ASN1_i2d_fp_of(DSA,i2d_DSA_PUBKEY,fp,dsa);
	}
