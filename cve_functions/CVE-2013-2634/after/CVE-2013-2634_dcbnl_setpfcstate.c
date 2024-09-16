static int dcbnl_setpfcstate(struct net_device *netdev, struct nlmsghdr *nlh,
			     u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	u8 value;

	if (!tb[DCB_ATTR_PFC_STATE])
		return -EINVAL;

	if (!netdev->dcbnl_ops->setpfcstate)
		return -EOPNOTSUPP;

	value = nla_get_u8(tb[DCB_ATTR_PFC_STATE]);

	netdev->dcbnl_ops->setpfcstate(netdev, value);

	return nla_put_u8(skb, DCB_ATTR_PFC_STATE, 0);
}
