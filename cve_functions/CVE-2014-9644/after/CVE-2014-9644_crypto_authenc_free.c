static void crypto_authenc_free(struct crypto_instance *inst)
{
	struct authenc_instance_ctx *ctx = crypto_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->enc);
	crypto_drop_ahash(&ctx->auth);
	kfree(inst);
}
