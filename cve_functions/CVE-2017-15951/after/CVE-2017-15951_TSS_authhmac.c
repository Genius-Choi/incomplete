static int TSS_authhmac(unsigned char *digest, const unsigned char *key,
			unsigned int keylen, unsigned char *h1,
			unsigned char *h2, unsigned char h3, ...)
{
	unsigned char paramdigest[SHA1_DIGEST_SIZE];
	struct sdesc *sdesc;
	unsigned int dlen;
	unsigned char *data;
	unsigned char c;
	int ret;
	va_list argp;

	sdesc = init_sdesc(hashalg);
	if (IS_ERR(sdesc)) {
		pr_info("trusted_key: can't alloc %s\n", hash_alg);
		return PTR_ERR(sdesc);
	}

	c = h3;
	ret = crypto_shash_init(&sdesc->shash);
	if (ret < 0)
		goto out;
	va_start(argp, h3);
	for (;;) {
		dlen = va_arg(argp, unsigned int);
		if (dlen == 0)
			break;
		data = va_arg(argp, unsigned char *);
		if (!data) {
			ret = -EINVAL;
			break;
		}
		ret = crypto_shash_update(&sdesc->shash, data, dlen);
		if (ret < 0)
			break;
	}
	va_end(argp);
	if (!ret)
		ret = crypto_shash_final(&sdesc->shash, paramdigest);
	if (!ret)
		ret = TSS_rawhmac(digest, key, keylen, SHA1_DIGEST_SIZE,
				  paramdigest, TPM_NONCE_SIZE, h1,
				  TPM_NONCE_SIZE, h2, 1, &c, 0, 0);
out:
	kzfree(sdesc);
	return ret;
}
