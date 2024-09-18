static struct crypto_instance *chainiv_alloc(struct rtattr **tb)
{
	struct crypto_attr_type *algt;
	struct crypto_instance *inst;
	int err;

	algt = crypto_get_attr_type(tb);
	if (IS_ERR(algt))
		return ERR_CAST(algt);

	err = crypto_get_default_rng();
	if (err)
		return ERR_PTR(err);

	inst = skcipher_geniv_alloc(&chainiv_tmpl, tb, 0, 0);
	if (IS_ERR(inst))
		goto put_rng;

	inst->alg.cra_ablkcipher.givencrypt = chainiv_givencrypt_first;

	inst->alg.cra_init = chainiv_init;
	inst->alg.cra_exit = skcipher_geniv_exit;

	inst->alg.cra_ctxsize = sizeof(struct chainiv_ctx);

	if (!crypto_requires_sync(algt->type, algt->mask)) {
		inst->alg.cra_flags |= CRYPTO_ALG_ASYNC;

		inst->alg.cra_ablkcipher.givencrypt =
			async_chainiv_givencrypt_first;

		inst->alg.cra_init = async_chainiv_init;
		inst->alg.cra_exit = async_chainiv_exit;

		inst->alg.cra_ctxsize = sizeof(struct async_chainiv_ctx);
	}

	inst->alg.cra_ctxsize += inst->alg.cra_ablkcipher.ivsize;

out:
	return inst;

put_rng:
	crypto_put_default_rng();
	goto out;
}
