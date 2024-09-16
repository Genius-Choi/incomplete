static __net_exit void sysctl_route_net_exit(struct net *net)
{
	struct ctl_table *tbl;

	tbl = net->ipv4.route_hdr->ctl_table_arg;
	unregister_net_sysctl_table(net->ipv4.route_hdr);
	BUG_ON(tbl == ipv4_route_flush_table);
	kfree(tbl);
}
