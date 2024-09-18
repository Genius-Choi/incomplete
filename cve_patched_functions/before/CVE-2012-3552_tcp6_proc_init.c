int __net_init tcp6_proc_init(struct net *net)
{
	return tcp_proc_register(net, &tcp6_seq_afinfo);
}
