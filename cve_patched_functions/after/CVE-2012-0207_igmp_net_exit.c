static void __net_exit igmp_net_exit(struct net *net)
{
	proc_net_remove(net, "mcfilter");
	proc_net_remove(net, "igmp");
}
