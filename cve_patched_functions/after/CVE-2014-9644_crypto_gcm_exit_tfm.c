static void crypto_gcm_exit_tfm(struct crypto_tfm *tfm)
{
	struct crypto_gcm_ctx *ctx = crypto_tfm_ctx(tfm);

	crypto_free_ahash(ctx->ghash);
	crypto_free_ablkcipher(ctx->ctr);
}
