static void __exit ucma_cleanup(void)
{
	unregister_net_sysctl_table(ucma_ctl_table_hdr);
	device_remove_file(ucma_misc.this_device, &dev_attr_abi_version);
	misc_deregister(&ucma_misc);
	idr_destroy(&ctx_idr);
	idr_destroy(&multicast_idr);
}
