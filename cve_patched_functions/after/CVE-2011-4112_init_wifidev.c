static struct net_device *init_wifidev(struct airo_info *ai,
					struct net_device *ethdev)
{
	int err;
	struct net_device *dev = alloc_netdev(0, "wifi%d", wifi_setup);
	if (!dev)
		return NULL;
	dev->ml_priv = ethdev->ml_priv;
	dev->irq = ethdev->irq;
	dev->base_addr = ethdev->base_addr;
	dev->wireless_data = ethdev->wireless_data;
	SET_NETDEV_DEV(dev, ethdev->dev.parent);
	memcpy(dev->dev_addr, ethdev->dev_addr, dev->addr_len);
	err = register_netdev(dev);
	if (err<0) {
		free_netdev(dev);
		return NULL;
	}
	return dev;
}
