static int ip6mr_sk_init(struct mr6_table *mrt, struct sock *sk)
{
	int err = 0;
	struct net *net = sock_net(sk);

	rtnl_lock();
	write_lock_bh(&mrt_lock);
	if (likely(mrt->mroute6_sk == NULL)) {
		mrt->mroute6_sk = sk;
		net->ipv6.devconf_all->mc_forwarding++;
	} else {
		err = -EADDRINUSE;
	}
	write_unlock_bh(&mrt_lock);

	if (!err)
		inet6_netconf_notify_devconf(net, NETCONFA_MC_FORWARDING,
					     NETCONFA_IFINDEX_ALL,
					     net->ipv6.devconf_all);
	rtnl_unlock();

	return err;
}
