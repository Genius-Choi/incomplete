static void wifi_setup(struct net_device *dev)
{
	dev->netdev_ops = &airo11_netdev_ops;
	dev->header_ops = &airo_header_ops;
	dev->wireless_handlers = &airo_handler_def;

	dev->type               = ARPHRD_IEEE80211;
	dev->hard_header_len    = ETH_HLEN;
	dev->mtu                = AIRO_DEF_MTU;
	dev->addr_len           = ETH_ALEN;
	dev->tx_queue_len       = 100; 

	memset(dev->broadcast,0xFF, ETH_ALEN);

	dev->flags              = IFF_BROADCAST|IFF_MULTICAST;
}
