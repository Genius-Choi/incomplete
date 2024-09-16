static int inet_netconf_msgsize_devconf(int type)
{
	int size = NLMSG_ALIGN(sizeof(struct netconfmsg))
		   + nla_total_size(4);	/* NETCONFA_IFINDEX */
	bool all = false;

	if (type == NETCONFA_ALL)
		all = true;

	if (all || type == NETCONFA_FORWARDING)
		size += nla_total_size(4);
	if (all || type == NETCONFA_RP_FILTER)
		size += nla_total_size(4);
	if (all || type == NETCONFA_MC_FORWARDING)
		size += nla_total_size(4);
	if (all || type == NETCONFA_PROXY_NEIGH)
		size += nla_total_size(4);
	if (all || type == NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN)
		size += nla_total_size(4);

	return size;
}
