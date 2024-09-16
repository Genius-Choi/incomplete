void uio_unregister_device(struct uio_info *info)
{
	struct uio_device *idev;

	if (!info || !info->uio_dev)
		return;

	idev = info->uio_dev;

	uio_free_minor(idev);

	if (info->irq && (info->irq != UIO_IRQ_CUSTOM))
		free_irq(info->irq, idev);

	uio_dev_del_attributes(idev);

	device_destroy(&uio_class, MKDEV(uio_major, idev->minor));
	kfree(idev);

	return;
}
