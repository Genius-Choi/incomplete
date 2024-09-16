int X509_REQ_verify(X509_REQ *a, EVP_PKEY *r)
	{
	return( ASN1_item_verify(ASN1_ITEM_rptr(X509_REQ_INFO),
		a->sig_alg,a->signature,a->req_info,r));
	}
