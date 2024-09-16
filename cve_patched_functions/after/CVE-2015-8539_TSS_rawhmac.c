static int TSS_rawhmac(unsigned char *digest, const unsigned char *key,
		       unsigned int keylen, ...)
{
	struct sdesc *sdesc;
	va_list argp;
	unsigned int dlen;
	unsigned char *data;
	int ret;

	sdesc = init_sdesc(hmacalg);
	if (IS_ERR(sdesc)) {
		pr_info("trusted_key: can't alloc %s\n", hmac_alg);
		return PTR_ERR(sdesc);
	}

	ret = crypto_shash_setkey(hmacalg, key, keylen);
	if (ret < 0)
		goto out;
	ret = crypto_shash_init(&sdesc->shash);
	if (ret < 0)
		goto out;

	va_start(argp, keylen);
	for (;;) {
		dlen = va_arg(argp, unsigned int);
		if (dlen == 0)
			break;
		data = va_arg(argp, unsigned char *);
		if (data == NULL) {
			ret = -EINVAL;
			break;
		}
		ret = crypto_shash_update(&sdesc->shash, data, dlen);
		if (ret < 0)
			break;
	}
	va_end(argp);
	if (!ret)
		ret = crypto_shash_final(&sdesc->shash, digest);
out:
	kfree(sdesc);
	return ret;
}
