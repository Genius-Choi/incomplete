static int l2tp_eth_dev_init(struct net_device *dev)
{
	struct l2tp_eth *priv = netdev_priv(dev);

	priv->dev = dev;
	random_ether_addr(dev->dev_addr);
	memset(&dev->broadcast[0], 0xff, 6);

	return 0;
}
