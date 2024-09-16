int NETSCAPE_SPKI_verify(NETSCAPE_SPKI *a, EVP_PKEY *r)
	{
	return(ASN1_item_verify(ASN1_ITEM_rptr(NETSCAPE_SPKAC),
		a->sig_algor,a->signature,a->spkac,r));
	}
