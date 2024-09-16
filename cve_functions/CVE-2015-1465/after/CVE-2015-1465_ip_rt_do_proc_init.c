static int __net_init ip_rt_do_proc_init(struct net *net)
{
	struct proc_dir_entry *pde;

	pde = proc_create("rt_cache", S_IRUGO, net->proc_net,
			  &rt_cache_seq_fops);
	if (!pde)
		goto err1;

	pde = proc_create("rt_cache", S_IRUGO,
			  net->proc_net_stat, &rt_cpu_seq_fops);
	if (!pde)
		goto err2;

#ifdef CONFIG_IP_ROUTE_CLASSID
	pde = proc_create("rt_acct", 0, net->proc_net, &rt_acct_proc_fops);
	if (!pde)
		goto err3;
#endif
	return 0;

#ifdef CONFIG_IP_ROUTE_CLASSID
err3:
	remove_proc_entry("rt_cache", net->proc_net_stat);
#endif
err2:
	remove_proc_entry("rt_cache", net->proc_net);
err1:
	return -ENOMEM;
}
