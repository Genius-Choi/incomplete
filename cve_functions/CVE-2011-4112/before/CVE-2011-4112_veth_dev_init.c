static int veth_dev_init(struct net_device *dev)
{
	struct veth_net_stats __percpu *stats;
	struct veth_priv *priv;

	stats = alloc_percpu(struct veth_net_stats);
	if (stats == NULL)
		return -ENOMEM;

	priv = netdev_priv(dev);
	priv->stats = stats;
	return 0;
}
