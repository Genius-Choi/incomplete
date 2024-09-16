int crypto_register_alg(struct crypto_alg *alg)
{
	struct crypto_larval *larval;
	int err;

	err = crypto_check_alg(alg);
	if (err)
		return err;

	down_write(&crypto_alg_sem);
	larval = __crypto_register_alg(alg);
	up_write(&crypto_alg_sem);

	if (IS_ERR(larval))
		return PTR_ERR(larval);

	crypto_wait_for_test(larval);
	return 0;
}
