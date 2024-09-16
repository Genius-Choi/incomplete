int NETSCAPE_SPKI_sign(NETSCAPE_SPKI *x, EVP_PKEY *pkey, const EVP_MD *md)
	{
	return(ASN1_item_sign(ASN1_ITEM_rptr(NETSCAPE_SPKAC), x->sig_algor,NULL,
		x->signature, x->spkac,pkey,md));
	}
