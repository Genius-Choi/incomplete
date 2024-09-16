static void veth_dellink(struct net_device *dev, struct list_head *head)
{
	struct veth_priv *priv;
	struct net_device *peer;

	priv = netdev_priv(dev);
	peer = priv->peer;

	unregister_netdevice_queue(dev, head);
	unregister_netdevice_queue(peer, head);
}
