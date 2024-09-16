static ssize_t abi_version_show(struct device *device,
				struct device_attribute *attr, char *buf)
{
	struct ib_uverbs_device *dev =
			container_of(device, struct ib_uverbs_device, dev);
	int ret = -ENODEV;
	int srcu_key;
	struct ib_device *ib_dev;

	srcu_key = srcu_read_lock(&dev->disassociate_srcu);
	ib_dev = srcu_dereference(dev->ib_dev, &dev->disassociate_srcu);
	if (ib_dev)
		ret = sprintf(buf, "%d\n", ib_dev->uverbs_abi_ver);
	srcu_read_unlock(&dev->disassociate_srcu, srcu_key);

	return ret;
}
