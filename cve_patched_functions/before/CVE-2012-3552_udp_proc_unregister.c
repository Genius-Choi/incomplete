void udp_proc_unregister(struct net *net, struct udp_seq_afinfo *afinfo)
{
	proc_net_remove(net, afinfo->name);
}
