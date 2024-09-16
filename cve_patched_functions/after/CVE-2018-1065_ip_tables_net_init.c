static int __net_init ip_tables_net_init(struct net *net)
{
	return xt_proto_init(net, NFPROTO_IPV4);
}
