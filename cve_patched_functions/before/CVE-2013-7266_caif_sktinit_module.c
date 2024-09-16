static int __init caif_sktinit_module(void)
{
	int err = sock_register(&caif_family_ops);
	if (!err)
		return err;
	return 0;
}
