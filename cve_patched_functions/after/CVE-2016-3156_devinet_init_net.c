static __net_init int devinet_init_net(struct net *net)
{
	int err;
	struct ipv4_devconf *all, *dflt;
#ifdef CONFIG_SYSCTL
	struct ctl_table *tbl = ctl_forward_entry;
	struct ctl_table_header *forw_hdr;
#endif

	err = -ENOMEM;
	all = &ipv4_devconf;
	dflt = &ipv4_devconf_dflt;

	if (!net_eq(net, &init_net)) {
		all = kmemdup(all, sizeof(ipv4_devconf), GFP_KERNEL);
		if (!all)
			goto err_alloc_all;

		dflt = kmemdup(dflt, sizeof(ipv4_devconf_dflt), GFP_KERNEL);
		if (!dflt)
			goto err_alloc_dflt;

#ifdef CONFIG_SYSCTL
		tbl = kmemdup(tbl, sizeof(ctl_forward_entry), GFP_KERNEL);
		if (!tbl)
			goto err_alloc_ctl;

		tbl[0].data = &all->data[IPV4_DEVCONF_FORWARDING - 1];
		tbl[0].extra1 = all;
		tbl[0].extra2 = net;
#endif
	}

#ifdef CONFIG_SYSCTL
	err = __devinet_sysctl_register(net, "all", all);
	if (err < 0)
		goto err_reg_all;

	err = __devinet_sysctl_register(net, "default", dflt);
	if (err < 0)
		goto err_reg_dflt;

	err = -ENOMEM;
	forw_hdr = register_net_sysctl(net, "net/ipv4", tbl);
	if (!forw_hdr)
		goto err_reg_ctl;
	net->ipv4.forw_hdr = forw_hdr;
#endif

	net->ipv4.devconf_all = all;
	net->ipv4.devconf_dflt = dflt;
	return 0;

#ifdef CONFIG_SYSCTL
err_reg_ctl:
	__devinet_sysctl_unregister(dflt);
err_reg_dflt:
	__devinet_sysctl_unregister(all);
err_reg_all:
	if (tbl != ctl_forward_entry)
		kfree(tbl);
err_alloc_ctl:
#endif
	if (dflt != &ipv4_devconf_dflt)
		kfree(dflt);
err_alloc_dflt:
	if (all != &ipv4_devconf)
		kfree(all);
err_alloc_all:
	return err;
}
