int i2d_X509_fp(FILE *fp, X509 *x509)
	{
	return ASN1_item_i2d_fp(ASN1_ITEM_rptr(X509), fp, x509);
	}
