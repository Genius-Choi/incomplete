static int __net_init ip6mr_rules_init(struct net *net)
{
	net->ipv6.mrt6 = ip6mr_new_table(net, RT6_TABLE_DFLT);
	return net->ipv6.mrt6 ? 0 : -ENOMEM;
}
