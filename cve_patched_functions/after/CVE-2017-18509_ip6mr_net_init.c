static int __net_init ip6mr_net_init(struct net *net)
{
	int err;

	err = ip6mr_rules_init(net);
	if (err < 0)
		goto fail;

#ifdef CONFIG_PROC_FS
	err = -ENOMEM;
	if (!proc_create("ip6_mr_vif", 0, net->proc_net, &ip6mr_vif_fops))
		goto proc_vif_fail;
	if (!proc_create("ip6_mr_cache", 0, net->proc_net, &ip6mr_mfc_fops))
		goto proc_cache_fail;
#endif

	return 0;

#ifdef CONFIG_PROC_FS
proc_cache_fail:
	remove_proc_entry("ip6_mr_vif", net->proc_net);
proc_vif_fail:
	ip6mr_rules_exit(net);
#endif
fail:
	return err;
}
