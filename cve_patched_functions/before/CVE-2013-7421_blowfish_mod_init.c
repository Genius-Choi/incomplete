static int __init blowfish_mod_init(void)
{
	return crypto_register_alg(&alg);
}
