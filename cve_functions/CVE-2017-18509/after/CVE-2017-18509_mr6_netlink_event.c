static void mr6_netlink_event(struct mr6_table *mrt, struct mfc6_cache *mfc,
			      int cmd)
{
	struct net *net = read_pnet(&mrt->net);
	struct sk_buff *skb;
	int err = -ENOBUFS;

	skb = nlmsg_new(mr6_msgsize(mfc->mf6c_parent >= MAXMIFS, mrt->maxvif),
			GFP_ATOMIC);
	if (!skb)
		goto errout;

	err = ip6mr_fill_mroute(mrt, skb, 0, 0, mfc, cmd, 0);
	if (err < 0)
		goto errout;

	rtnl_notify(skb, net, 0, RTNLGRP_IPV6_MROUTE, NULL, GFP_ATOMIC);
	return;

errout:
	kfree_skb(skb);
	if (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_MROUTE, err);
}
