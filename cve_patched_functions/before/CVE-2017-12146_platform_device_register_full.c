struct platform_device *platform_device_register_full(
		const struct platform_device_info *pdevinfo)
{
	int ret = -ENOMEM;
	struct platform_device *pdev;

	pdev = platform_device_alloc(pdevinfo->name, pdevinfo->id);
	if (!pdev)
		goto err_alloc;

	pdev->dev.parent = pdevinfo->parent;
	pdev->dev.fwnode = pdevinfo->fwnode;

	if (pdevinfo->dma_mask) {
		/*
		 * This memory isn't freed when the device is put,
		 * I don't have a nice idea for that though.  Conceptually
		 * dma_mask in struct device should not be a pointer.
		 * See http://thread.gmane.org/gmane.linux.kernel.pci/9081
		 */
		pdev->dev.dma_mask =
			kmalloc(sizeof(*pdev->dev.dma_mask), GFP_KERNEL);
		if (!pdev->dev.dma_mask)
			goto err;

		*pdev->dev.dma_mask = pdevinfo->dma_mask;
		pdev->dev.coherent_dma_mask = pdevinfo->dma_mask;
	}

	ret = platform_device_add_resources(pdev,
			pdevinfo->res, pdevinfo->num_res);
	if (ret)
		goto err;

	ret = platform_device_add_data(pdev,
			pdevinfo->data, pdevinfo->size_data);
	if (ret)
		goto err;

	if (pdevinfo->properties) {
		ret = platform_device_add_properties(pdev,
						     pdevinfo->properties);
		if (ret)
			goto err;
	}

	ret = platform_device_add(pdev);
	if (ret) {
err:
		ACPI_COMPANION_SET(&pdev->dev, NULL);
		kfree(pdev->dev.dma_mask);

err_alloc:
		platform_device_put(pdev);
		return ERR_PTR(ret);
	}

	return pdev;
}
