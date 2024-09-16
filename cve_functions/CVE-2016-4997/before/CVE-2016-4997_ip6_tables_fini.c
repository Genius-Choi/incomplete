static void __exit ip6_tables_fini(void)
{
	nf_unregister_sockopt(&ip6t_sockopts);

	xt_unregister_matches(ip6t_builtin_mt, ARRAY_SIZE(ip6t_builtin_mt));
	xt_unregister_targets(ip6t_builtin_tg, ARRAY_SIZE(ip6t_builtin_tg));
	unregister_pernet_subsys(&ip6_tables_net_ops);
}
