static __net_exit void pppoe_exit_net(struct net *net)
{
	remove_proc_entry("pppoe", net->proc_net);
}
