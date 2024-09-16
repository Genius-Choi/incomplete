static struct fwnet_device *fwnet_dev_find(struct fw_card *card)
{
	struct fwnet_device *dev;

	list_for_each_entry(dev, &fwnet_device_list, dev_link)
		if (dev->card == card)
			return dev;

	return NULL;
}
