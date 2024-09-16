static int cryptd_create(struct crypto_template *tmpl, struct rtattr **tb)
{
	struct crypto_attr_type *algt;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return PTR_ERR(algt);

	switch (algt->type & algt->mask & CRYPTO_ALG_TYPE_MASK) {
	case CRYPTO_ALG_TYPE_BLKCIPHER:
		return cryptd_create_blkcipher(tmpl, tb, &queue);
	case CRYPTO_ALG_TYPE_DIGEST:
		return cryptd_create_hash(tmpl, tb, &queue);
	case CRYPTO_ALG_TYPE_AEAD:
		return cryptd_create_aead(tmpl, tb, &queue);
	}

	return -EINVAL;
}
