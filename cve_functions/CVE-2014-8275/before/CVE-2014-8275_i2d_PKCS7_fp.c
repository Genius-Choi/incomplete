int i2d_PKCS7_fp(FILE *fp, PKCS7 *p7)
	{
	return ASN1_item_i2d_fp(ASN1_ITEM_rptr(PKCS7), fp, p7);
	}
