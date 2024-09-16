static int pcrypt_aead_init_tfm(struct crypto_aead *tfm)
{
	int cpu, cpu_index;
	struct aead_instance *inst = aead_alg_instance(tfm);
	struct pcrypt_instance_ctx *ictx = aead_instance_ctx(inst);
	struct pcrypt_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_aead *cipher;

	cpu_index = (unsigned int)atomic_inc_return(&ictx->tfm_count) %
		    cpumask_weight(cpu_online_mask);

	ctx->cb_cpu = cpumask_first(cpu_online_mask);
	for (cpu = 0; cpu < cpu_index; cpu++)
		ctx->cb_cpu = cpumask_next(ctx->cb_cpu, cpu_online_mask);

	cipher = crypto_spawn_aead(&ictx->spawn);

	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = cipher;
	crypto_aead_set_reqsize(tfm, sizeof(struct pcrypt_request) +
				     sizeof(struct aead_request) +
				     crypto_aead_reqsize(cipher));

	return 0;
}
