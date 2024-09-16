int addrconf_sysctl_proxy_ndp(struct ctl_table *ctl, int write,
			      void __user *buffer, size_t *lenp, loff_t *ppos)
{
	int *valp = ctl->data;
	int ret;
	int old, new;

	old = *valp;
	ret = proc_dointvec(ctl, write, buffer, lenp, ppos);
	new = *valp;

	if (write && old != new) {
		struct net *net = ctl->extra2;

		if (!rtnl_trylock())
			return restart_syscall();

		if (valp == &net->ipv6.devconf_dflt->proxy_ndp)
			inet6_netconf_notify_devconf(net, NETCONFA_PROXY_NEIGH,
						     NETCONFA_IFINDEX_DEFAULT,
						     net->ipv6.devconf_dflt);
		else if (valp == &net->ipv6.devconf_all->proxy_ndp)
			inet6_netconf_notify_devconf(net, NETCONFA_PROXY_NEIGH,
						     NETCONFA_IFINDEX_ALL,
						     net->ipv6.devconf_all);
		else {
			struct inet6_dev *idev = ctl->extra1;

			inet6_netconf_notify_devconf(net, NETCONFA_PROXY_NEIGH,
						     idev->dev->ifindex,
						     &idev->cnf);
		}
		rtnl_unlock();
	}

	return ret;
}
