static int devinet_conf_ifindex(struct net *net, struct ipv4_devconf *cnf)
{
	if (cnf == net->ipv4.devconf_dflt)
		return NETCONFA_IFINDEX_DEFAULT;
	else if (cnf == net->ipv4.devconf_all)
		return NETCONFA_IFINDEX_ALL;
	else {
		struct in_device *idev
			= container_of(cnf, struct in_device, cnf);
		return idev->dev->ifindex;
	}
}
