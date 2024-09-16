int i2d_RSA_PUBKEY_fp(FILE *fp, RSA *rsa)
	{
	return ASN1_i2d_fp((I2D_OF(void))i2d_RSA_PUBKEY,fp,rsa);
	}
