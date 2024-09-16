int i2d_PKCS8PrivateKeyInfo_bio(BIO *bp, EVP_PKEY *key)
	{
	PKCS8_PRIV_KEY_INFO *p8inf;
	int ret;
	p8inf = EVP_PKEY2PKCS8(key);
	if(!p8inf) return 0;
	ret = i2d_PKCS8_PRIV_KEY_INFO_bio(bp, p8inf);
	PKCS8_PRIV_KEY_INFO_free(p8inf);
	return ret;
	}
