DSA *d2i_DSA_PUBKEY_fp(FILE *fp, DSA **dsa)
	{
	return ASN1_d2i_fp_of(DSA,DSA_new,d2i_DSA_PUBKEY,fp,dsa);
	}
