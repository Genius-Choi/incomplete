static struct crypto_instance *crypto_ccm_base_alloc(struct rtattr **tb)
{
	const char *ctr_name;
	const char *cipher_name;
	char full_name[CRYPTO_MAX_ALG_NAME];

	ctr_name = crypto_attr_alg_name(tb[1]);
	if (IS_ERR(ctr_name))
		return ERR_CAST(ctr_name);

	cipher_name = crypto_attr_alg_name(tb[2]);
	if (IS_ERR(cipher_name))
		return ERR_CAST(cipher_name);

	if (snprintf(full_name, CRYPTO_MAX_ALG_NAME, "ccm_base(%s,%s)",
		     ctr_name, cipher_name) >= CRYPTO_MAX_ALG_NAME)
		return ERR_PTR(-ENAMETOOLONG);

	return crypto_ccm_alloc_common(tb, full_name, ctr_name, cipher_name);
}
