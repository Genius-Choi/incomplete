X509_REQ *d2i_X509_REQ_fp(FILE *fp, X509_REQ **req)
	{
	return ASN1_item_d2i_fp(ASN1_ITEM_rptr(X509_REQ), fp, req);
	}
