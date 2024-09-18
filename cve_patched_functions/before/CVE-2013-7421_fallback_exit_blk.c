static void fallback_exit_blk(struct crypto_tfm *tfm)
{
	struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	crypto_free_blkcipher(sctx->fallback.blk);
	sctx->fallback.blk = NULL;
}
