static int macvlan_stop(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;

	if (vlan->port->passthru) {
		dev_set_promiscuity(lowerdev, -1);
		goto hash_del;
	}

	dev_mc_unsync(lowerdev, dev);
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(lowerdev, -1);

	dev_uc_del(lowerdev, dev->dev_addr);

hash_del:
	macvlan_hash_del(vlan, !dev->dismantle);
	return 0;
}
