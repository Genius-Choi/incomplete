static int __init early_platform_left(struct early_platform_driver *epdrv,
				       int id)
{
	struct platform_device *pd;

	list_for_each_entry(pd, &early_platform_device_list, dev.devres_head)
		if (platform_match(&pd->dev, &epdrv->pdrv->driver))
			if (pd->id >= id)
				return 1;

	return 0;
}
