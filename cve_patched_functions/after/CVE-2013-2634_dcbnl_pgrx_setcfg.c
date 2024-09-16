static int dcbnl_pgrx_setcfg(struct net_device *netdev, struct nlmsghdr *nlh,
			     u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	return __dcbnl_pg_setcfg(netdev, nlh, seq, tb, skb, 1);
}
