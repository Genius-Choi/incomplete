RSA *d2i_RSAPrivateKey_fp(FILE *fp, RSA **rsa)
	{
	return ASN1_item_d2i_fp(ASN1_ITEM_rptr(RSAPrivateKey), fp, rsa);
	}
