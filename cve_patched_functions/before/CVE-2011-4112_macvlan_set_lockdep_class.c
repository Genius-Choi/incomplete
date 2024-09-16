static void macvlan_set_lockdep_class(struct net_device *dev)
{
	lockdep_set_class(&dev->addr_list_lock,
			  &macvlan_netdev_addr_lock_key);
	netdev_for_each_tx_queue(dev, macvlan_set_lockdep_class_one, NULL);
}
