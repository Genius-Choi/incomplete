int ECDSA_do_verify(const unsigned char *dgst, int dgst_len, 
		const ECDSA_SIG *sig, EC_KEY *eckey)
	{
	ECDSA_DATA *ecdsa = ecdsa_check(eckey);
	if (ecdsa == NULL)
		return 0;
	return ecdsa->meth->ecdsa_do_verify(dgst, dgst_len, sig, eckey);
	}
