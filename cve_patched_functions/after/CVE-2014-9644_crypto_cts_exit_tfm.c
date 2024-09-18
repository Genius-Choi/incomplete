static void crypto_cts_exit_tfm(struct crypto_tfm *tfm)
{
	struct crypto_cts_ctx *ctx = crypto_tfm_ctx(tfm);
	crypto_free_blkcipher(ctx->child);
}
