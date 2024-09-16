static int dcbnl_getpfcstate(struct net_device *netdev, struct nlmsghdr *nlh,
			     u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	if (!netdev->dcbnl_ops->getpfcstate)
		return -EOPNOTSUPP;

	return nla_put_u8(skb, DCB_ATTR_PFC_STATE,
			  netdev->dcbnl_ops->getpfcstate(netdev));
}
