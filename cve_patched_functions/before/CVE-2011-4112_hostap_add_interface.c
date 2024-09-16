struct net_device * hostap_add_interface(struct local_info *local,
					 int type, int rtnl_locked,
					 const char *prefix,
					 const char *name)
{
	struct net_device *dev, *mdev;
	struct hostap_interface *iface;
	int ret;

	dev = alloc_etherdev(sizeof(struct hostap_interface));
	if (dev == NULL)
		return NULL;

	iface = netdev_priv(dev);
	iface->dev = dev;
	iface->local = local;
	iface->type = type;
	list_add(&iface->list, &local->hostap_interfaces);

	mdev = local->dev;
	memcpy(dev->dev_addr, mdev->dev_addr, ETH_ALEN);
	dev->base_addr = mdev->base_addr;
	dev->irq = mdev->irq;
	dev->mem_start = mdev->mem_start;
	dev->mem_end = mdev->mem_end;

	hostap_setup_dev(dev, local, type);
	dev->destructor = free_netdev;

	sprintf(dev->name, "%s%s", prefix, name);
	if (!rtnl_locked)
		rtnl_lock();

	SET_NETDEV_DEV(dev, mdev->dev.parent);
	ret = register_netdevice(dev);

	if (!rtnl_locked)
		rtnl_unlock();

	if (ret < 0) {
		printk(KERN_WARNING "%s: failed to add new netdevice!\n",
		       dev->name);
		free_netdev(dev);
		return NULL;
	}

	printk(KERN_DEBUG "%s: registered netdevice %s\n",
	       mdev->name, dev->name);

	return dev;
}
