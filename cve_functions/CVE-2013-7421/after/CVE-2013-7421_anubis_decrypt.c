static void anubis_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct anubis_ctx *ctx = crypto_tfm_ctx(tfm);
	anubis_crypt(ctx->D, dst, src, ctx->R);
}
