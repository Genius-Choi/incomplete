static void crypto_rfc4543_free(struct crypto_instance *inst)
{
	struct crypto_rfc4543_instance_ctx *ctx = crypto_instance_ctx(inst);

	crypto_drop_aead(&ctx->aead);
	crypto_drop_skcipher(&ctx->null);

	kfree(inst);
}
