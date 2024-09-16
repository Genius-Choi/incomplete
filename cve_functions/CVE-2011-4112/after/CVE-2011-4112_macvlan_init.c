static int macvlan_init(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	const struct net_device *lowerdev = vlan->lowerdev;

	dev->state		= (dev->state & ~MACVLAN_STATE_MASK) |
				  (lowerdev->state & MACVLAN_STATE_MASK);
	dev->features 		= lowerdev->features & MACVLAN_FEATURES;
	dev->features		|= NETIF_F_LLTX;
	dev->gso_max_size	= lowerdev->gso_max_size;
	dev->iflink		= lowerdev->ifindex;
	dev->hard_header_len	= lowerdev->hard_header_len;

	macvlan_set_lockdep_class(dev);

	vlan->pcpu_stats = alloc_percpu(struct macvlan_pcpu_stats);
	if (!vlan->pcpu_stats)
		return -ENOMEM;

	return 0;
}
