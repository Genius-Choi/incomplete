int crypto_register_skcipher(struct skcipher_alg *alg)
{
	struct crypto_alg *base = &alg->base;
	int err;

	err = skcipher_prepare_alg(alg);
	if (err)
		return err;

	return crypto_register_alg(base);
}
