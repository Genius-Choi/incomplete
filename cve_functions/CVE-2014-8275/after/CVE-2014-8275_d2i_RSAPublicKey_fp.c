RSA *d2i_RSAPublicKey_fp(FILE *fp, RSA **rsa)
	{
	return ASN1_item_d2i_fp(ASN1_ITEM_rptr(RSAPublicKey), fp, rsa);
	}
