static void veth_dev_free(struct net_device *dev)
{
	struct veth_priv *priv;

	priv = netdev_priv(dev);
	free_percpu(priv->stats);
	free_netdev(dev);
}
