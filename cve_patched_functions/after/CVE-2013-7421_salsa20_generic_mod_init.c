static int __init salsa20_generic_mod_init(void)
{
	return crypto_register_alg(&alg);
}
