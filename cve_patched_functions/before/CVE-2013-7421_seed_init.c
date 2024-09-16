static int __init seed_init(void)
{
	return crypto_register_alg(&seed_alg);
}
