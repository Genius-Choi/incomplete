static int __init tgr192_mod_init(void)
{
	return crypto_register_shashes(tgr_algs, ARRAY_SIZE(tgr_algs));
}
