static void __exit exit_sd(void)
{
	int i;

	SCSI_LOG_HLQUEUE(3, printk("exit_sd: exiting sd driver\n"));

	mempool_destroy(sd_cdb_pool);
	kmem_cache_destroy(sd_cdb_cache);

	scsi_unregister_driver(&sd_template.gendrv);
	class_unregister(&sd_disk_class);

	for (i = 0; i < SD_MAJORS; i++)
		unregister_blkdev(sd_major(i), "sd");
}
