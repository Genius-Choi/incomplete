static void __net_exit udp4_proc_exit_net(struct net *net)
{
	udp_proc_unregister(net, &udp4_seq_afinfo);
}
