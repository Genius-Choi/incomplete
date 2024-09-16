static int xenvif_open(struct net_device *dev)
{
	struct xenvif *vif = netdev_priv(dev);
	if (netif_carrier_ok(dev))
		xenvif_up(vif);
	netif_start_queue(dev);
	return 0;
}
