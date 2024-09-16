static void ib_ucm_remove_one(struct ib_device *device, void *client_data)
{
	struct ib_ucm_device *ucm_dev = client_data;

	if (!ucm_dev)
		return;

	device_unregister(&ucm_dev->dev);
}
