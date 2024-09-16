void __init ip_fib_init(void)
{
	rtnl_register(PF_INET, RTM_NEWROUTE, inet_rtm_newroute, NULL, NULL);
	rtnl_register(PF_INET, RTM_DELROUTE, inet_rtm_delroute, NULL, NULL);
	rtnl_register(PF_INET, RTM_GETROUTE, NULL, inet_dump_fib, NULL);

	register_pernet_subsys(&fib_net_ops);
	register_netdevice_notifier(&fib_netdev_notifier);
	register_inetaddr_notifier(&fib_inetaddr_notifier);

	fib_trie_init();
}
