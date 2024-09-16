static int dcbnl_pgrx_getcfg(struct net_device *netdev, struct nlmsghdr *nlh,
			     u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	return __dcbnl_pg_getcfg(netdev, nlh, tb, skb, 1);
}
