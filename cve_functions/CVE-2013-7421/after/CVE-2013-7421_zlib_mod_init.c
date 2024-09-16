static int __init zlib_mod_init(void)
{
	return crypto_register_pcomp(&zlib_alg);
}
