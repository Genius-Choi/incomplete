static void crypto_ccm_free(struct crypto_instance *inst)
{
	struct ccm_instance_ctx *ctx = crypto_instance_ctx(inst);

	crypto_drop_spawn(&ctx->cipher);
	crypto_drop_skcipher(&ctx->ctr);
	kfree(inst);
}
