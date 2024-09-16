static void nl_fib_lookup_exit(struct net *net)
{
	netlink_kernel_release(net->ipv4.fibnl);
	net->ipv4.fibnl = NULL;
}
