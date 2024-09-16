EVP_PKEY *d2i_PrivateKey_fp(FILE *fp, EVP_PKEY **a)
{
	return ASN1_d2i_fp_of(EVP_PKEY,EVP_PKEY_new,d2i_AutoPrivateKey,fp,a);
}
