static int __init cipso_v4_init(void)
{
	int ret_val;

	ret_val = cipso_v4_cache_init();
	if (ret_val != 0)
		panic("Failed to initialize the CIPSO/IPv4 cache (%d)\n",
		      ret_val);

	return 0;
}
