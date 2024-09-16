static int veth_open(struct net_device *dev)
{
	struct veth_priv *priv;

	priv = netdev_priv(dev);
	if (priv->peer == NULL)
		return -ENOTCONN;

	if (priv->peer->flags & IFF_UP) {
		netif_carrier_on(dev);
		netif_carrier_on(priv->peer);
	}
	return 0;
}
