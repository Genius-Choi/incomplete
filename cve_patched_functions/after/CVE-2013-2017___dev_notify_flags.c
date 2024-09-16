void __dev_notify_flags(struct net_device *dev, unsigned int old_flags)
{
	unsigned int changes = dev->flags ^ old_flags;

	if (changes & IFF_UP) {
		if (dev->flags & IFF_UP)
			call_netdevice_notifiers(NETDEV_UP, dev);
		else
			call_netdevice_notifiers(NETDEV_DOWN, dev);
	}

	if (dev->flags & IFF_UP &&
	    (changes & ~(IFF_UP | IFF_PROMISC | IFF_ALLMULTI | IFF_VOLATILE)))
		call_netdevice_notifiers(NETDEV_CHANGE, dev);
}
