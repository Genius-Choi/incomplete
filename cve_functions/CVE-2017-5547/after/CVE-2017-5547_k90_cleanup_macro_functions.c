static void k90_cleanup_macro_functions(struct hid_device *dev)
{
	struct corsair_drvdata *drvdata = hid_get_drvdata(dev);
	struct k90_drvdata *k90 = drvdata->k90;

	if (k90) {
		sysfs_remove_group(&dev->dev.kobj, &k90_attr_group);

		k90->record_led.removed = true;
		led_classdev_unregister(&k90->record_led.cdev);
		cancel_work_sync(&k90->record_led.work);
		kfree(k90->record_led.cdev.name);

		kfree(k90);
	}
}
