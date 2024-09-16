static void __exit dm_multipath_exit(void)
{
	destroy_workqueue(kmpath_handlerd);
	destroy_workqueue(kmultipathd);

	dm_unregister_target(&multipath_target);
	kmem_cache_destroy(_mpio_cache);
}
