static int padlock_sha_import_nano(struct shash_desc *desc,
				const void *in)
{
	int statesize = crypto_shash_statesize(desc->tfm);
	void *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, statesize);
	return 0;
}
