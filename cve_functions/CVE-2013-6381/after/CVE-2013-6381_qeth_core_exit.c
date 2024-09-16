static void __exit qeth_core_exit(void)
{
	qeth_clear_dbf_list();
	destroy_workqueue(qeth_wq);
	ccwgroup_driver_unregister(&qeth_core_ccwgroup_driver);
	ccw_driver_unregister(&qeth_ccw_driver);
	kmem_cache_destroy(qeth_qdio_outbuf_cache);
	kmem_cache_destroy(qeth_core_header_cache);
	root_device_unregister(qeth_core_root_dev);
	qeth_unregister_dbf_views();
	pr_info("core functions removed\n");
}
