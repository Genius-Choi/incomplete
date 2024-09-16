static void __bond_resend_igmp_join_requests(struct net_device *dev)
{
	struct in_device *in_dev;

	rcu_read_lock();
	in_dev = __in_dev_get_rcu(dev);
	if (in_dev)
		ip_mc_rejoin_groups(in_dev);
	rcu_read_unlock();
}
