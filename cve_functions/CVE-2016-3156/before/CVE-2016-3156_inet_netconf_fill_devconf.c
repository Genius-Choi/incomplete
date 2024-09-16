static int inet_netconf_fill_devconf(struct sk_buff *skb, int ifindex,
				     struct ipv4_devconf *devconf, u32 portid,
				     u32 seq, int event, unsigned int flags,
				     int type)
{
	struct nlmsghdr  *nlh;
	struct netconfmsg *ncm;
	bool all = false;

	nlh = nlmsg_put(skb, portid, seq, event, sizeof(struct netconfmsg),
			flags);
	if (!nlh)
		return -EMSGSIZE;

	if (type == NETCONFA_ALL)
		all = true;

	ncm = nlmsg_data(nlh);
	ncm->ncm_family = AF_INET;

	if (nla_put_s32(skb, NETCONFA_IFINDEX, ifindex) < 0)
		goto nla_put_failure;

	if ((all || type == NETCONFA_FORWARDING) &&
	    nla_put_s32(skb, NETCONFA_FORWARDING,
			IPV4_DEVCONF(*devconf, FORWARDING)) < 0)
		goto nla_put_failure;
	if ((all || type == NETCONFA_RP_FILTER) &&
	    nla_put_s32(skb, NETCONFA_RP_FILTER,
			IPV4_DEVCONF(*devconf, RP_FILTER)) < 0)
		goto nla_put_failure;
	if ((all || type == NETCONFA_MC_FORWARDING) &&
	    nla_put_s32(skb, NETCONFA_MC_FORWARDING,
			IPV4_DEVCONF(*devconf, MC_FORWARDING)) < 0)
		goto nla_put_failure;
	if ((all || type == NETCONFA_PROXY_NEIGH) &&
	    nla_put_s32(skb, NETCONFA_PROXY_NEIGH,
			IPV4_DEVCONF(*devconf, PROXY_ARP)) < 0)
		goto nla_put_failure;
	if ((all || type == NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN) &&
	    nla_put_s32(skb, NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
			IPV4_DEVCONF(*devconf, IGNORE_ROUTES_WITH_LINKDOWN)) < 0)
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}
