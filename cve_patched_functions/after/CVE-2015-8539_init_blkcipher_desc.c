static int init_blkcipher_desc(struct blkcipher_desc *desc, const u8 *key,
			       unsigned int key_len, const u8 *iv,
			       unsigned int ivsize)
{
	int ret;

	desc->tfm = crypto_alloc_blkcipher(blkcipher_alg, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(desc->tfm)) {
		pr_err("encrypted_key: failed to load %s transform (%ld)\n",
		       blkcipher_alg, PTR_ERR(desc->tfm));
		return PTR_ERR(desc->tfm);
	}
	desc->flags = 0;

	ret = crypto_blkcipher_setkey(desc->tfm, key, key_len);
	if (ret < 0) {
		pr_err("encrypted_key: failed to setkey (%d)\n", ret);
		crypto_free_blkcipher(desc->tfm);
		return ret;
	}
	crypto_blkcipher_set_iv(desc->tfm, iv, ivsize);
	return 0;
}
