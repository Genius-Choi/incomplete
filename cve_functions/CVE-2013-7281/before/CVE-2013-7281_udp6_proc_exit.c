void udp6_proc_exit(struct net *net) {
	udp_proc_unregister(net, &udp6_seq_afinfo);
}
