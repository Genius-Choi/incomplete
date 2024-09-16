static void ipv6_cleanup_mibs(struct net *net)
{
	free_percpu(net->mib.udp_stats_in6);
	free_percpu(net->mib.udplite_stats_in6);
	free_percpu(net->mib.ipv6_statistics);
	free_percpu(net->mib.icmpv6_statistics);
	kfree(net->mib.icmpv6msg_statistics);
}
