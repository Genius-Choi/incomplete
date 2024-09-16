void __init devinet_init(void)
{
	int i;

	for (i = 0; i < IN4_ADDR_HSIZE; i++)
		INIT_HLIST_HEAD(&inet_addr_lst[i]);

	register_pernet_subsys(&devinet_ops);

	register_gifconf(PF_INET, inet_gifconf);
	register_netdevice_notifier(&ip_netdev_notifier);

	queue_delayed_work(system_power_efficient_wq, &check_lifetime_work, 0);

	rtnl_af_register(&inet_af_ops);

	rtnl_register(PF_INET, RTM_NEWADDR, inet_rtm_newaddr, NULL, NULL);
	rtnl_register(PF_INET, RTM_DELADDR, inet_rtm_deladdr, NULL, NULL);
	rtnl_register(PF_INET, RTM_GETADDR, NULL, inet_dump_ifaddr, NULL);
	rtnl_register(PF_INET, RTM_GETNETCONF, inet_netconf_get_devconf,
		      inet_netconf_dump_devconf, NULL);
}
