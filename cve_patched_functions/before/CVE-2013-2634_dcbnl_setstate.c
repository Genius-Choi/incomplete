static int dcbnl_setstate(struct net_device *netdev, struct nlmsghdr *nlh,
			  u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	u8 value;

	if (!tb[DCB_ATTR_STATE])
		return -EINVAL;

	if (!netdev->dcbnl_ops->setstate)
		return -EOPNOTSUPP;

	value = nla_get_u8(tb[DCB_ATTR_STATE]);

	return nla_put_u8(skb, DCB_ATTR_STATE,
			  netdev->dcbnl_ops->setstate(netdev, value));
}
