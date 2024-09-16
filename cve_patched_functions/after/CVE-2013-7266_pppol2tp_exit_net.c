static __net_exit void pppol2tp_exit_net(struct net *net)
{
	remove_proc_entry("pppol2tp", net->proc_net);
}
