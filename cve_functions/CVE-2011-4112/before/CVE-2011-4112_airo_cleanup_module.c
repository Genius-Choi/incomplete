static void __exit airo_cleanup_module( void )
{
	struct airo_info *ai;
	while(!list_empty(&airo_devices)) {
		ai = list_entry(airo_devices.next, struct airo_info, dev_list);
		airo_print_info(ai->dev->name, "Unregistering...");
		stop_airo_card(ai->dev, 1);
	}
#ifdef CONFIG_PCI
	pci_unregister_driver(&airo_driver);
#endif
	remove_proc_entry("driver/aironet", NULL);
}
