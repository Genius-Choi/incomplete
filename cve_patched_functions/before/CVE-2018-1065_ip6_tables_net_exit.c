static void __net_exit ip6_tables_net_exit(struct net *net)
{
	xt_proto_fini(net, NFPROTO_IPV6);
}
