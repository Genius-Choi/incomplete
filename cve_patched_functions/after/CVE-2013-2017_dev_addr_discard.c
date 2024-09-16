static void dev_addr_discard(struct net_device *dev)
{
	netif_addr_lock_bh(dev);

	__dev_addr_discard(&dev->mc_list);
	netdev_mc_count(dev) = 0;

	netif_addr_unlock_bh(dev);
}
