static int dcbnl_cee_get(struct net_device *netdev, struct nlmsghdr *nlh,
			 u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	const struct dcbnl_rtnl_ops *ops = netdev->dcbnl_ops;

	if (!ops)
		return -EOPNOTSUPP;

	return dcbnl_cee_fill(skb, netdev);
}
