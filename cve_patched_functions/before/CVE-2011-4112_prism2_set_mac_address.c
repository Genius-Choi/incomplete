static int prism2_set_mac_address(struct net_device *dev, void *p)
{
	struct hostap_interface *iface;
	local_info_t *local;
	struct list_head *ptr;
	struct sockaddr *addr = p;

	iface = netdev_priv(dev);
	local = iface->local;

	if (local->func->set_rid(dev, HFA384X_RID_CNFOWNMACADDR, addr->sa_data,
				 ETH_ALEN) < 0 || local->func->reset_port(dev))
		return -EINVAL;

	read_lock_bh(&local->iface_lock);
	list_for_each(ptr, &local->hostap_interfaces) {
		iface = list_entry(ptr, struct hostap_interface, list);
		memcpy(iface->dev->dev_addr, addr->sa_data, ETH_ALEN);
	}
	memcpy(local->dev->dev_addr, addr->sa_data, ETH_ALEN);
	read_unlock_bh(&local->iface_lock);

	return 0;
}
