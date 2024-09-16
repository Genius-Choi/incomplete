PKCS7 *d2i_PKCS7_bio(BIO *bp, PKCS7 **p7)
	{
	return ASN1_item_d2i_bio(ASN1_ITEM_rptr(PKCS7), bp, p7);
	}
