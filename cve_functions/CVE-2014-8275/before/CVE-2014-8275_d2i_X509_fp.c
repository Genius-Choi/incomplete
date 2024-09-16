X509 *d2i_X509_fp(FILE *fp, X509 **x509)
	{
	return ASN1_item_d2i_fp(ASN1_ITEM_rptr(X509), fp, x509);
	}
