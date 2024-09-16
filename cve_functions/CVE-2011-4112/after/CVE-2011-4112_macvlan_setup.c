static void macvlan_setup(struct net_device *dev)
{
	macvlan_common_setup(dev);
	dev->tx_queue_len	= 0;
}
