int crypto_unregister_shash(struct shash_alg *alg)
{
	return crypto_unregister_alg(&alg->base);
}
