RSA *d2i_RSA_PUBKEY_fp(FILE *fp, RSA **rsa)
	{
	return ASN1_d2i_fp((void *(*)(void))
			   RSA_new,(D2I_OF(void))d2i_RSA_PUBKEY, fp,
			   (void **)rsa);
	}
