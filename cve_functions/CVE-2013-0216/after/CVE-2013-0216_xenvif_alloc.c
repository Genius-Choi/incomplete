struct xenvif *xenvif_alloc(struct device *parent, domid_t domid,
			    unsigned int handle)
{
	int err;
	struct net_device *dev;
	struct xenvif *vif;
	char name[IFNAMSIZ] = {};

	snprintf(name, IFNAMSIZ - 1, "vif%u.%u", domid, handle);
	dev = alloc_netdev(sizeof(struct xenvif), name, ether_setup);
	if (dev == NULL) {
		pr_warn("Could not allocate netdev\n");
		return ERR_PTR(-ENOMEM);
	}

	SET_NETDEV_DEV(dev, parent);

	vif = netdev_priv(dev);
	vif->domid  = domid;
	vif->handle = handle;
	vif->netbk  = NULL;
	vif->can_sg = 1;
	vif->csum = 1;
	atomic_set(&vif->refcnt, 1);
	init_waitqueue_head(&vif->waiting_to_free);
	vif->dev = dev;
	INIT_LIST_HEAD(&vif->schedule_list);
	INIT_LIST_HEAD(&vif->notify_list);

	vif->credit_bytes = vif->remaining_credit = ~0UL;
	vif->credit_usec  = 0UL;
	init_timer(&vif->credit_timeout);
	/* Initialize 'expires' now: it's used to track the credit window. */
	vif->credit_timeout.expires = jiffies;

	dev->netdev_ops	= &xenvif_netdev_ops;
	dev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO;
	dev->features = dev->hw_features;
	SET_ETHTOOL_OPS(dev, &xenvif_ethtool_ops);

	dev->tx_queue_len = XENVIF_QUEUE_LENGTH;

	/*
	 * Initialise a dummy MAC address. We choose the numerically
	 * largest non-broadcast address to prevent the address getting
	 * stolen by an Ethernet bridge for STP purposes.
	 * (FE:FF:FF:FF:FF:FF)
	 */
	memset(dev->dev_addr, 0xFF, ETH_ALEN);
	dev->dev_addr[0] &= ~0x01;

	netif_carrier_off(dev);

	err = register_netdev(dev);
	if (err) {
		netdev_warn(dev, "Could not register device: err=%d\n", err);
		free_netdev(dev);
		return ERR_PTR(err);
	}

	netdev_dbg(dev, "Successfully created xenvif\n");
	return vif;
}
