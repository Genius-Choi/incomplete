static void __exit fwnet_cleanup(void)
{
	driver_unregister(&fwnet_driver.driver);
	kmem_cache_destroy(fwnet_packet_task_cache);
#if IS_ENABLED(CONFIG_IPV6)
	fw_core_remove_descriptor(&rfc3146_unit_directory);
#endif
	fw_core_remove_descriptor(&rfc2374_unit_directory);
}
