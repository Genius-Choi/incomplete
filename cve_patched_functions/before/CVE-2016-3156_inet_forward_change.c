static void inet_forward_change(struct net *net)
{
	struct net_device *dev;
	int on = IPV4_DEVCONF_ALL(net, FORWARDING);

	IPV4_DEVCONF_ALL(net, ACCEPT_REDIRECTS) = !on;
	IPV4_DEVCONF_DFLT(net, FORWARDING) = on;
	inet_netconf_notify_devconf(net, NETCONFA_FORWARDING,
				    NETCONFA_IFINDEX_ALL,
				    net->ipv4.devconf_all);
	inet_netconf_notify_devconf(net, NETCONFA_FORWARDING,
				    NETCONFA_IFINDEX_DEFAULT,
				    net->ipv4.devconf_dflt);

	for_each_netdev(net, dev) {
		struct in_device *in_dev;
		if (on)
			dev_disable_lro(dev);
		rcu_read_lock();
		in_dev = __in_dev_get_rcu(dev);
		if (in_dev) {
			IN_DEV_CONF_SET(in_dev, FORWARDING, on);
			inet_netconf_notify_devconf(net, NETCONFA_FORWARDING,
						    dev->ifindex, &in_dev->cnf);
		}
		rcu_read_unlock();
	}
}
