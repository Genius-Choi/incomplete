static void set_carrier_state(struct fwnet_device *dev)
{
	if (dev->peer_count > 1)
		netif_carrier_on(dev->netdev);
	else
		netif_carrier_off(dev->netdev);
}
