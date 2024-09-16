static __net_exit void devinet_exit_net(struct net *net)
{
#ifdef CONFIG_SYSCTL
	struct ctl_table *tbl;

	tbl = net->ipv4.forw_hdr->ctl_table_arg;
	unregister_net_sysctl_table(net->ipv4.forw_hdr);
	__devinet_sysctl_unregister(net->ipv4.devconf_dflt);
	__devinet_sysctl_unregister(net->ipv4.devconf_all);
	kfree(tbl);
#endif
	kfree(net->ipv4.devconf_dflt);
	kfree(net->ipv4.devconf_all);
}
