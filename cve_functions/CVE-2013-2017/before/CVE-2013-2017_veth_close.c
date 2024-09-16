static int veth_close(struct net_device *dev)
{
	struct veth_priv *priv = netdev_priv(dev);

	netif_carrier_off(dev);
	netif_carrier_off(priv->peer);

	return 0;
}
