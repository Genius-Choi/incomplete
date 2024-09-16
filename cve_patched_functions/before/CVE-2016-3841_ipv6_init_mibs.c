static int __net_init ipv6_init_mibs(struct net *net)
{
	int i;

	net->mib.udp_stats_in6 = alloc_percpu(struct udp_mib);
	if (!net->mib.udp_stats_in6)
		return -ENOMEM;
	net->mib.udplite_stats_in6 = alloc_percpu(struct udp_mib);
	if (!net->mib.udplite_stats_in6)
		goto err_udplite_mib;
	net->mib.ipv6_statistics = alloc_percpu(struct ipstats_mib);
	if (!net->mib.ipv6_statistics)
		goto err_ip_mib;

	for_each_possible_cpu(i) {
		struct ipstats_mib *af_inet6_stats;
		af_inet6_stats = per_cpu_ptr(net->mib.ipv6_statistics, i);
		u64_stats_init(&af_inet6_stats->syncp);
	}


	net->mib.icmpv6_statistics = alloc_percpu(struct icmpv6_mib);
	if (!net->mib.icmpv6_statistics)
		goto err_icmp_mib;
	net->mib.icmpv6msg_statistics = kzalloc(sizeof(struct icmpv6msg_mib),
						GFP_KERNEL);
	if (!net->mib.icmpv6msg_statistics)
		goto err_icmpmsg_mib;
	return 0;

err_icmpmsg_mib:
	free_percpu(net->mib.icmpv6_statistics);
err_icmp_mib:
	free_percpu(net->mib.ipv6_statistics);
err_ip_mib:
	free_percpu(net->mib.udplite_stats_in6);
err_udplite_mib:
	free_percpu(net->mib.udp_stats_in6);
	return -ENOMEM;
}
