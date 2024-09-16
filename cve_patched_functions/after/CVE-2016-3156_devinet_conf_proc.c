static int devinet_conf_proc(struct ctl_table *ctl, int write,
			     void __user *buffer,
			     size_t *lenp, loff_t *ppos)
{
	int old_value = *(int *)ctl->data;
	int ret = proc_dointvec(ctl, write, buffer, lenp, ppos);
	int new_value = *(int *)ctl->data;

	if (write) {
		struct ipv4_devconf *cnf = ctl->extra1;
		struct net *net = ctl->extra2;
		int i = (int *)ctl->data - cnf->data;
		int ifindex;

		set_bit(i, cnf->state);

		if (cnf == net->ipv4.devconf_dflt)
			devinet_copy_dflt_conf(net, i);
		if (i == IPV4_DEVCONF_ACCEPT_LOCAL - 1 ||
		    i == IPV4_DEVCONF_ROUTE_LOCALNET - 1)
			if ((new_value == 0) && (old_value != 0))
				rt_cache_flush(net);

		if (i == IPV4_DEVCONF_RP_FILTER - 1 &&
		    new_value != old_value) {
			ifindex = devinet_conf_ifindex(net, cnf);
			inet_netconf_notify_devconf(net, NETCONFA_RP_FILTER,
						    ifindex, cnf);
		}
		if (i == IPV4_DEVCONF_PROXY_ARP - 1 &&
		    new_value != old_value) {
			ifindex = devinet_conf_ifindex(net, cnf);
			inet_netconf_notify_devconf(net, NETCONFA_PROXY_NEIGH,
						    ifindex, cnf);
		}
		if (i == IPV4_DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN - 1 &&
		    new_value != old_value) {
			ifindex = devinet_conf_ifindex(net, cnf);
			inet_netconf_notify_devconf(net, NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
						    ifindex, cnf);
		}
	}

	return ret;
}
