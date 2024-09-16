int i2d_X509_REQ_bio(BIO *bp, X509_REQ *req)
	{
	return ASN1_item_i2d_bio(ASN1_ITEM_rptr(X509_REQ), bp, req);
	}
