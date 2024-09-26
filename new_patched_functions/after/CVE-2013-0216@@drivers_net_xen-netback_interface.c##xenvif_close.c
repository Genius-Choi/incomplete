static int xenvif_close(struct net_device *dev)
{
	struct xenvif *vif = netdev_priv(dev);
	if (netif_carrier_ok(dev))
		xenvif_down(vif);
	netif_stop_queue(dev);
	return 0;
}
