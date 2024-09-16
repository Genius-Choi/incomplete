static void __net_exit fib_net_exit(struct net *net)
{
	fib_proc_exit(net);
	nl_fib_lookup_exit(net);
	ip_fib_net_exit(net);
}
