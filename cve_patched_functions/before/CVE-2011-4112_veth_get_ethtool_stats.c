static void veth_get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *data)
{
	struct veth_priv *priv;

	priv = netdev_priv(dev);
	data[0] = priv->peer->ifindex;
}
