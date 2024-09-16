static void ux500_hash_shutdown(struct platform_device *pdev)
{
	struct resource *res = NULL;
	struct hash_device_data *device_data;

	device_data = platform_get_drvdata(pdev);
	if (!device_data) {
		dev_err(&pdev->dev, "%s: platform_get_drvdata() failed!\n",
			__func__);
		return;
	}

	/* Check that the device is free */
	spin_lock(&device_data->ctx_lock);
	/* current_ctx allocates a device, NULL = unallocated */
	if (!device_data->current_ctx) {
		if (down_trylock(&driver_data.device_allocation))
			dev_dbg(&pdev->dev, "%s: Cryp still in use! Shutting down anyway...\n",
				__func__);
		/**
		 * (Allocate the device)
		 * Need to set this to non-null (dummy) value,
		 * to avoid usage if context switching.
		 */
		device_data->current_ctx++;
	}
	spin_unlock(&device_data->ctx_lock);

	/* Remove the device from the list */
	if (klist_node_attached(&device_data->list_node))
		klist_remove(&device_data->list_node);

	/* If this was the last device, remove the services */
	if (list_empty(&driver_data.device_list.k_list))
		ahash_algs_unregister_all(device_data);

	iounmap(device_data->base);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res)
		release_mem_region(res->start, resource_size(res));

	if (hash_disable_power(device_data, false))
		dev_err(&pdev->dev, "%s: hash_disable_power() failed\n",
			__func__);
}
