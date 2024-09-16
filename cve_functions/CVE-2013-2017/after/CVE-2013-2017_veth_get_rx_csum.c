static u32 veth_get_rx_csum(struct net_device *dev)
{
	struct veth_priv *priv;

	priv = netdev_priv(dev);
	return priv->ip_summed == CHECKSUM_UNNECESSARY;
}
