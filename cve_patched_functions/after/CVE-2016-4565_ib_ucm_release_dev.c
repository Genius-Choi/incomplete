static void ib_ucm_release_dev(struct device *dev)
{
	struct ib_ucm_device *ucm_dev;

	ucm_dev = container_of(dev, struct ib_ucm_device, dev);
	cdev_del(&ucm_dev->cdev);
	if (ucm_dev->devnum < IB_UCM_MAX_DEVICES)
		clear_bit(ucm_dev->devnum, dev_map);
	else
		clear_bit(ucm_dev->devnum - IB_UCM_MAX_DEVICES, overflow_map);
	kfree(ucm_dev);
}
