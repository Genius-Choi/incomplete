void platform_device_del(struct platform_device *pdev)
{
	int i;

	if (pdev) {
		device_remove_properties(&pdev->dev);
		device_del(&pdev->dev);

		if (pdev->id_auto) {
			ida_simple_remove(&platform_devid_ida, pdev->id);
			pdev->id = PLATFORM_DEVID_AUTO;
		}

		for (i = 0; i < pdev->num_resources; i++) {
			struct resource *r = &pdev->resource[i];
			if (r->parent)
				release_resource(r);
		}
	}
}
