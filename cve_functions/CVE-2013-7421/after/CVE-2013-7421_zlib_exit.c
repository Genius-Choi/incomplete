static void zlib_exit(struct crypto_tfm *tfm)
{
	struct zlib_ctx *ctx = crypto_tfm_ctx(tfm);

	zlib_comp_exit(ctx);
	zlib_decomp_exit(ctx);
}
