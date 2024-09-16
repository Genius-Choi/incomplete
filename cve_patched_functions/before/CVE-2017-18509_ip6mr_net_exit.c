static void __net_exit ip6mr_net_exit(struct net *net)
{
#ifdef CONFIG_PROC_FS
	remove_proc_entry("ip6_mr_cache", net->proc_net);
	remove_proc_entry("ip6_mr_vif", net->proc_net);
#endif
	ip6mr_rules_exit(net);
}
