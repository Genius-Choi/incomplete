static int shash_compat_setkey(struct crypto_hash *tfm, const u8 *key,
			       unsigned int keylen)
{
	struct shash_desc **descp = crypto_hash_ctx(tfm);
	struct shash_desc *desc = *descp;

	return crypto_shash_setkey(desc->tfm, key, keylen);
}
