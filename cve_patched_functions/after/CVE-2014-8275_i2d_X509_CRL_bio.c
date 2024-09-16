int i2d_X509_CRL_bio(BIO *bp, X509_CRL *crl)
	{
	return ASN1_item_i2d_bio(ASN1_ITEM_rptr(X509_CRL), bp, crl);
	}
