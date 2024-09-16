static void __net_exit ip6mr_rules_exit(struct net *net)
{
	rtnl_lock();
	ip6mr_free_table(net->ipv6.mrt6);
	net->ipv6.mrt6 = NULL;
	rtnl_unlock();
}
