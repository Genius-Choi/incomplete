void macvlan_dellink(struct net_device *dev, struct list_head *head)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	list_del(&vlan->list);
	unregister_netdevice_queue(dev, head);
}
