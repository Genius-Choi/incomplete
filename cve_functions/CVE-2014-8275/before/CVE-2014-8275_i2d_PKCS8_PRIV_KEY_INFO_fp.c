int i2d_PKCS8_PRIV_KEY_INFO_fp(FILE *fp, PKCS8_PRIV_KEY_INFO *p8inf)
	{
	return ASN1_i2d_fp_of(PKCS8_PRIV_KEY_INFO,i2d_PKCS8_PRIV_KEY_INFO,fp,
			      p8inf);
	}
