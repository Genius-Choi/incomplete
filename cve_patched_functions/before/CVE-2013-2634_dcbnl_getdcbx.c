static int dcbnl_getdcbx(struct net_device *netdev, struct nlmsghdr *nlh,
			 u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	if (!netdev->dcbnl_ops->getdcbx)
		return -EOPNOTSUPP;

	return nla_put_u8(skb, DCB_ATTR_DCBX,
			  netdev->dcbnl_ops->getdcbx(netdev));
}
