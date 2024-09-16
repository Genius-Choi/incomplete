int i2d_DSAPrivateKey_fp(FILE *fp, DSA *dsa)
	{
	return ASN1_i2d_fp_of_const(DSA,i2d_DSAPrivateKey,fp,dsa);
	}
