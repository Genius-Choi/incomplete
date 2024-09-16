void tcp6_proc_exit(struct net *net)
{
	tcp_proc_unregister(net, &tcp6_seq_afinfo);
}
