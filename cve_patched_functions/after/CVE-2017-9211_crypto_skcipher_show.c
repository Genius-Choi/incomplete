static void crypto_skcipher_show(struct seq_file *m, struct crypto_alg *alg)
{
	struct skcipher_alg *skcipher = container_of(alg, struct skcipher_alg,
						     base);

	seq_printf(m, "type         : skcipher\n");
	seq_printf(m, "async        : %s\n",
		   alg->cra_flags & CRYPTO_ALG_ASYNC ?  "yes" : "no");
	seq_printf(m, "blocksize    : %u\n", alg->cra_blocksize);
	seq_printf(m, "min keysize  : %u\n", skcipher->min_keysize);
	seq_printf(m, "max keysize  : %u\n", skcipher->max_keysize);
	seq_printf(m, "ivsize       : %u\n", skcipher->ivsize);
	seq_printf(m, "chunksize    : %u\n", skcipher->chunksize);
	seq_printf(m, "walksize     : %u\n", skcipher->walksize);
}
