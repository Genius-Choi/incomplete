static int __init init_encrypted(void)
{
	int ret;

	hash_tfm = crypto_alloc_shash(hash_alg, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(hash_tfm)) {
		pr_err("encrypted_key: can't allocate %s transform: %ld\n",
		       hash_alg, PTR_ERR(hash_tfm));
		return PTR_ERR(hash_tfm);
	}

	ret = aes_get_sizes();
	if (ret < 0)
		goto out;
	ret = register_key_type(&key_type_encrypted);
	if (ret < 0)
		goto out;
	return 0;
out:
	crypto_free_shash(hash_tfm);
	return ret;

}
