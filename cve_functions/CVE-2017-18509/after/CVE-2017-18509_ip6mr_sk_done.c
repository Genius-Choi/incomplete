int ip6mr_sk_done(struct sock *sk)
{
	int err = -EACCES;
	struct net *net = sock_net(sk);
	struct mr6_table *mrt;

	rtnl_lock();
	ip6mr_for_each_table(mrt, net) {
		if (sk == mrt->mroute6_sk) {
			write_lock_bh(&mrt_lock);
			mrt->mroute6_sk = NULL;
			net->ipv6.devconf_all->mc_forwarding--;
			write_unlock_bh(&mrt_lock);
			inet6_netconf_notify_devconf(net,
						     NETCONFA_MC_FORWARDING,
						     NETCONFA_IFINDEX_ALL,
						     net->ipv6.devconf_all);

			mroute_clean_tables(mrt, false);
			err = 0;
			break;
		}
	}
	rtnl_unlock();

	return err;
}
