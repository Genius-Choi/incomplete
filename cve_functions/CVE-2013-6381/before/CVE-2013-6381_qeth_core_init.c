static int __init qeth_core_init(void)
{
	int rc;

	pr_info("loading core functions\n");
	INIT_LIST_HEAD(&qeth_core_card_list.list);
	INIT_LIST_HEAD(&qeth_dbf_list);
	rwlock_init(&qeth_core_card_list.rwlock);
	mutex_init(&qeth_mod_mutex);

	qeth_wq = create_singlethread_workqueue("qeth_wq");

	rc = qeth_register_dbf_views();
	if (rc)
		goto out_err;
	qeth_core_root_dev = root_device_register("qeth");
	rc = PTR_RET(qeth_core_root_dev);
	if (rc)
		goto register_err;
	qeth_core_header_cache = kmem_cache_create("qeth_hdr",
			sizeof(struct qeth_hdr) + ETH_HLEN, 64, 0, NULL);
	if (!qeth_core_header_cache) {
		rc = -ENOMEM;
		goto slab_err;
	}
	qeth_qdio_outbuf_cache = kmem_cache_create("qeth_buf",
			sizeof(struct qeth_qdio_out_buffer), 0, 0, NULL);
	if (!qeth_qdio_outbuf_cache) {
		rc = -ENOMEM;
		goto cqslab_err;
	}
	rc = ccw_driver_register(&qeth_ccw_driver);
	if (rc)
		goto ccw_err;
	qeth_core_ccwgroup_driver.driver.groups = qeth_drv_attr_groups;
	rc = ccwgroup_driver_register(&qeth_core_ccwgroup_driver);
	if (rc)
		goto ccwgroup_err;

	return 0;

ccwgroup_err:
	ccw_driver_unregister(&qeth_ccw_driver);
ccw_err:
	kmem_cache_destroy(qeth_qdio_outbuf_cache);
cqslab_err:
	kmem_cache_destroy(qeth_core_header_cache);
slab_err:
	root_device_unregister(qeth_core_root_dev);
register_err:
	qeth_unregister_dbf_views();
out_err:
	pr_err("Initializing the qeth device driver failed\n");
	return rc;
}
