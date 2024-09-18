static int __init sha512_generic_mod_init(void)
{
	return crypto_register_shashes(sha512_algs, ARRAY_SIZE(sha512_algs));
}
