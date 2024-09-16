static int dcbnl_setdcbx(struct net_device *netdev, struct nlmsghdr *nlh,
			 u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	u8 value;

	if (!netdev->dcbnl_ops->setdcbx)
		return -EOPNOTSUPP;

	if (!tb[DCB_ATTR_DCBX])
		return -EINVAL;

	value = nla_get_u8(tb[DCB_ATTR_DCBX]);

	return nla_put_u8(skb, DCB_ATTR_DCBX,
			  netdev->dcbnl_ops->setdcbx(netdev, value));
}
