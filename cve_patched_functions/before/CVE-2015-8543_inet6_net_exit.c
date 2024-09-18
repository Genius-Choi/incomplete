static void __net_exit inet6_net_exit(struct net *net)
{
#ifdef CONFIG_PROC_FS
	udp6_proc_exit(net);
	tcp6_proc_exit(net);
	ac6_proc_exit(net);
#endif
	ipv6_cleanup_mibs(net);
}
