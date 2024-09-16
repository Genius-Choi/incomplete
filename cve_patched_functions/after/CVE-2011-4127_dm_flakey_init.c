static int __init dm_flakey_init(void)
{
	int r = dm_register_target(&flakey_target);

	if (r < 0)
		DMERR("register failed %d", r);

	return r;
}
