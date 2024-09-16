static int macvlan_hard_header(struct sk_buff *skb, struct net_device *dev,
			       unsigned short type, const void *daddr,
			       const void *saddr, unsigned len)
{
	const struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;

	return dev_hard_header(skb, lowerdev, type, daddr,
			       saddr ? : dev->dev_addr, len);
}
