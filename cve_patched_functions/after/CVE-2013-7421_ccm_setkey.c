static int ccm_setkey(struct crypto_aead *tfm, const u8 *in_key,
		      unsigned int key_len)
{
	struct crypto_aes_ctx *ctx = crypto_aead_ctx(tfm);
	int ret;

	ret = crypto_aes_expand_key(ctx, in_key, key_len);
	if (!ret)
		return 0;

	tfm->base.crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
	return -EINVAL;
}
