static int __net_init udp4_proc_init_net(struct net *net)
{
	return udp_proc_register(net, &udp4_seq_afinfo);
}
