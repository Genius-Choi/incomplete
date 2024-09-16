static void __exit dm_flakey_exit(void)
{
	dm_unregister_target(&flakey_target);
}
