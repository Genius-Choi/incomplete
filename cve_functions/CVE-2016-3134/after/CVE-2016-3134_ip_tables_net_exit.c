static void __net_exit ip_tables_net_exit(struct net *net)
{
	xt_proto_fini(net, NFPROTO_IPV4);
}
