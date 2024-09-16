static __net_exit void ipv4_mib_exit_net(struct net *net)
{
	kfree(net->mib.icmpmsg_statistics);
	free_percpu(net->mib.icmp_statistics);
	free_percpu(net->mib.udplite_statistics);
	free_percpu(net->mib.udp_statistics);
	free_percpu(net->mib.net_statistics);
	free_percpu(net->mib.ip_statistics);
	free_percpu(net->mib.tcp_statistics);
}
