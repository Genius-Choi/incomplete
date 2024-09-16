static int __init init_sd(void)
{
	int majors = 0, i, err;

	SCSI_LOG_HLQUEUE(3, printk("init_sd: sd driver entry point\n"));

	for (i = 0; i < SD_MAJORS; i++)
		if (register_blkdev(sd_major(i), "sd") == 0)
			majors++;

	if (!majors)
		return -ENODEV;

	err = class_register(&sd_disk_class);
	if (err)
		goto err_out;

	err = scsi_register_driver(&sd_template.gendrv);
	if (err)
		goto err_out_class;

	sd_cdb_cache = kmem_cache_create("sd_ext_cdb", SD_EXT_CDB_SIZE,
					 0, 0, NULL);
	if (!sd_cdb_cache) {
		printk(KERN_ERR "sd: can't init extended cdb cache\n");
		goto err_out_class;
	}

	sd_cdb_pool = mempool_create_slab_pool(SD_MEMPOOL_SIZE, sd_cdb_cache);
	if (!sd_cdb_pool) {
		printk(KERN_ERR "sd: can't init extended cdb pool\n");
		goto err_out_cache;
	}

	return 0;

err_out_cache:
	kmem_cache_destroy(sd_cdb_cache);

err_out_class:
	class_unregister(&sd_disk_class);
err_out:
	for (i = 0; i < SD_MAJORS; i++)
		unregister_blkdev(sd_major(i), "sd");
	return err;
}
