static int macvlan_open(struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;
	int err;

	if (vlan->port->passthru) {
		dev_set_promiscuity(lowerdev, 1);
		goto hash_add;
	}

	err = -EBUSY;
	if (macvlan_addr_busy(vlan->port, dev->dev_addr))
		goto out;

	err = dev_uc_add(lowerdev, dev->dev_addr);
	if (err < 0)
		goto out;
	if (dev->flags & IFF_ALLMULTI) {
		err = dev_set_allmulti(lowerdev, 1);
		if (err < 0)
			goto del_unicast;
	}

hash_add:
	macvlan_hash_add(vlan);
	return 0;

del_unicast:
	dev_uc_del(lowerdev, dev->dev_addr);
out:
	return err;
}
