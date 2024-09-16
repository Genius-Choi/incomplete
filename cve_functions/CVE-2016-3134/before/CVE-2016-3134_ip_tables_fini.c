static void __exit ip_tables_fini(void)
{
	nf_unregister_sockopt(&ipt_sockopts);

	xt_unregister_matches(ipt_builtin_mt, ARRAY_SIZE(ipt_builtin_mt));
	xt_unregister_targets(ipt_builtin_tg, ARRAY_SIZE(ipt_builtin_tg));
	unregister_pernet_subsys(&ip_tables_net_ops);
}
