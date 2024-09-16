static int k90_init_backlight(struct hid_device *dev)
{
	int ret;
	struct corsair_drvdata *drvdata = hid_get_drvdata(dev);
	size_t name_sz;
	char *name;

	drvdata->backlight = kzalloc(sizeof(struct k90_led), GFP_KERNEL);
	if (!drvdata->backlight) {
		ret = -ENOMEM;
		goto fail_backlight_alloc;
	}

	name_sz =
	    strlen(dev_name(&dev->dev)) + sizeof(K90_BACKLIGHT_LED_SUFFIX);
	name = kzalloc(name_sz, GFP_KERNEL);
	if (!name) {
		ret = -ENOMEM;
		goto fail_name_alloc;
	}
	snprintf(name, name_sz, "%s" K90_BACKLIGHT_LED_SUFFIX,
		 dev_name(&dev->dev));
	drvdata->backlight->removed = false;
	drvdata->backlight->cdev.name = name;
	drvdata->backlight->cdev.max_brightness = 3;
	drvdata->backlight->cdev.brightness_set = k90_brightness_set;
	drvdata->backlight->cdev.brightness_get = k90_backlight_get;
	INIT_WORK(&drvdata->backlight->work, k90_backlight_work);
	ret = led_classdev_register(&dev->dev, &drvdata->backlight->cdev);
	if (ret != 0)
		goto fail_register_cdev;

	return 0;

fail_register_cdev:
	kfree(drvdata->backlight->cdev.name);
fail_name_alloc:
	kfree(drvdata->backlight);
	drvdata->backlight = NULL;
fail_backlight_alloc:
	return ret;
}
