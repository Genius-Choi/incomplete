static void lrw_aesni_exit_tfm(struct crypto_tfm *tfm)
{
	struct aesni_lrw_ctx *ctx = crypto_tfm_ctx(tfm);

	lrw_free_table(&ctx->lrw_table);
}
