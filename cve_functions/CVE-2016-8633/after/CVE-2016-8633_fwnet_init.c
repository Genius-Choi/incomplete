static int __init fwnet_init(void)
{
	int err;

	err = fw_core_add_descriptor(&rfc2374_unit_directory);
	if (err)
		return err;

#if IS_ENABLED(CONFIG_IPV6)
	err = fw_core_add_descriptor(&rfc3146_unit_directory);
	if (err)
		goto out;
#endif

	fwnet_packet_task_cache = kmem_cache_create("packet_task",
			sizeof(struct fwnet_packet_task), 0, 0, NULL);
	if (!fwnet_packet_task_cache) {
		err = -ENOMEM;
		goto out2;
	}

	err = driver_register(&fwnet_driver.driver);
	if (!err)
		return 0;

	kmem_cache_destroy(fwnet_packet_task_cache);
out2:
#if IS_ENABLED(CONFIG_IPV6)
	fw_core_remove_descriptor(&rfc3146_unit_directory);
out:
#endif
	fw_core_remove_descriptor(&rfc2374_unit_directory);

	return err;
}
