static int shash_compat_init(struct hash_desc *hdesc)
{
	struct shash_desc **descp = crypto_hash_ctx(hdesc->tfm);
	struct shash_desc *desc = *descp;

	desc->flags = hdesc->flags;

	return crypto_shash_init(desc);
}
