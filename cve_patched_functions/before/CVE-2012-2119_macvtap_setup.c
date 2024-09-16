static void macvtap_setup(struct net_device *dev)
{
	macvlan_common_setup(dev);
	dev->tx_queue_len = TUN_READQ_SIZE;
}
