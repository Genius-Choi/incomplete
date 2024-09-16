static void __exit arp_tables_fini(void)
{
	nf_unregister_sockopt(&arpt_sockopts);
	xt_unregister_targets(arpt_builtin_tg, ARRAY_SIZE(arpt_builtin_tg));
	unregister_pernet_subsys(&arp_tables_net_ops);
}
