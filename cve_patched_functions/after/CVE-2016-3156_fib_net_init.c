static int __net_init fib_net_init(struct net *net)
{
	int error;

#ifdef CONFIG_IP_ROUTE_CLASSID
	net->ipv4.fib_num_tclassid_users = 0;
#endif
	error = ip_fib_net_init(net);
	if (error < 0)
		goto out;
	error = nl_fib_lookup_init(net);
	if (error < 0)
		goto out_nlfl;
	error = fib_proc_init(net);
	if (error < 0)
		goto out_proc;
out:
	return error;

out_proc:
	nl_fib_lookup_exit(net);
out_nlfl:
	ip_fib_net_exit(net);
	goto out;
}
