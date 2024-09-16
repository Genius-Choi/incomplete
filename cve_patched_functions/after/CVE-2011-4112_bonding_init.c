static int __init bonding_init(void)
{
	int i;
	int res;

	pr_info("%s", bond_version);

	res = bond_check_params(&bonding_defaults);
	if (res)
		goto out;

	res = register_pernet_subsys(&bond_net_ops);
	if (res)
		goto out;

	res = rtnl_link_register(&bond_link_ops);
	if (res)
		goto err_link;

	bond_create_debugfs();

	for (i = 0; i < max_bonds; i++) {
		res = bond_create(&init_net, NULL);
		if (res)
			goto err;
	}

	res = bond_create_sysfs();
	if (res)
		goto err;

	register_netdevice_notifier(&bond_netdev_notifier);
	register_inetaddr_notifier(&bond_inetaddr_notifier);
out:
	return res;
err:
	rtnl_link_unregister(&bond_link_ops);
err_link:
	unregister_pernet_subsys(&bond_net_ops);
	goto out;

}
