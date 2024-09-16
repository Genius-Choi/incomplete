static int __init rmd160_mod_init(void)
{
	return crypto_register_shash(&alg);
}
