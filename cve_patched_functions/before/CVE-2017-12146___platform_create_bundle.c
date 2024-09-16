struct platform_device * __init_or_module __platform_create_bundle(
			struct platform_driver *driver,
			int (*probe)(struct platform_device *),
			struct resource *res, unsigned int n_res,
			const void *data, size_t size, struct module *module)
{
	struct platform_device *pdev;
	int error;

	pdev = platform_device_alloc(driver->driver.name, -1);
	if (!pdev) {
		error = -ENOMEM;
		goto err_out;
	}

	error = platform_device_add_resources(pdev, res, n_res);
	if (error)
		goto err_pdev_put;

	error = platform_device_add_data(pdev, data, size);
	if (error)
		goto err_pdev_put;

	error = platform_device_add(pdev);
	if (error)
		goto err_pdev_put;

	error = __platform_driver_probe(driver, probe, module);
	if (error)
		goto err_pdev_del;

	return pdev;

err_pdev_del:
	platform_device_del(pdev);
err_pdev_put:
	platform_device_put(pdev);
err_out:
	return ERR_PTR(error);
}
