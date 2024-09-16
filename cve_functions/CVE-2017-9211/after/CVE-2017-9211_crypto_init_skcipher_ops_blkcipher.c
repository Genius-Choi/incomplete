static int crypto_init_skcipher_ops_blkcipher(struct crypto_tfm *tfm)
{
	struct crypto_alg *calg = tfm->__crt_alg;
	struct crypto_skcipher *skcipher = __crypto_skcipher_cast(tfm);
	struct crypto_blkcipher **ctx = crypto_tfm_ctx(tfm);
	struct crypto_blkcipher *blkcipher;
	struct crypto_tfm *btfm;

	if (!crypto_mod_get(calg))
		return -EAGAIN;

	btfm = __crypto_alloc_tfm(calg, CRYPTO_ALG_TYPE_BLKCIPHER,
					CRYPTO_ALG_TYPE_MASK);
	if (IS_ERR(btfm)) {
		crypto_mod_put(calg);
		return PTR_ERR(btfm);
	}

	blkcipher = __crypto_blkcipher_cast(btfm);
	*ctx = blkcipher;
	tfm->exit = crypto_exit_skcipher_ops_blkcipher;

	skcipher->setkey = skcipher_setkey_blkcipher;
	skcipher->encrypt = skcipher_encrypt_blkcipher;
	skcipher->decrypt = skcipher_decrypt_blkcipher;

	skcipher->ivsize = crypto_blkcipher_ivsize(blkcipher);
	skcipher->keysize = calg->cra_blkcipher.max_keysize;

	return 0;
}
