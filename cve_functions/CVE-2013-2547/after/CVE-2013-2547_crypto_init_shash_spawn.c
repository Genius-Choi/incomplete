int crypto_init_shash_spawn(struct crypto_shash_spawn *spawn,
			    struct shash_alg *alg,
			    struct crypto_instance *inst)
{
	return crypto_init_spawn2(&spawn->base, &alg->base, inst,
				  &crypto_shash_type);
}
