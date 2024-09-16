static void k90_cleanup_backlight(struct hid_device *dev)
{
	struct corsair_drvdata *drvdata = hid_get_drvdata(dev);

	if (drvdata->backlight) {
		drvdata->backlight->removed = true;
		led_classdev_unregister(&drvdata->backlight->cdev);
		cancel_work_sync(&drvdata->backlight->work);
		kfree(drvdata->backlight->cdev.name);
		kfree(drvdata->backlight);
	}
}
