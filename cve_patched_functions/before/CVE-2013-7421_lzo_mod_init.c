static int __init lzo_mod_init(void)
{
	return crypto_register_alg(&alg);
}
