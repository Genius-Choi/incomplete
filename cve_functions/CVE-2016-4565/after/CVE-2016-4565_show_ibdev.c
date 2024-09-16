static ssize_t show_ibdev(struct device *device, struct device_attribute *attr,
			  char *buf)
{
	int ret = -ENODEV;
	int srcu_key;
	struct ib_uverbs_device *dev = dev_get_drvdata(device);
	struct ib_device *ib_dev;

	if (!dev)
		return -ENODEV;

	srcu_key = srcu_read_lock(&dev->disassociate_srcu);
	ib_dev = srcu_dereference(dev->ib_dev, &dev->disassociate_srcu);
	if (ib_dev)
		ret = sprintf(buf, "%s\n", ib_dev->name);
	srcu_read_unlock(&dev->disassociate_srcu, srcu_key);

	return ret;
}
