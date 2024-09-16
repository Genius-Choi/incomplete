static __net_init int ipv4_mib_init_net(struct net *net)
{
	int i;

	net->mib.tcp_statistics = alloc_percpu(struct tcp_mib);
	if (!net->mib.tcp_statistics)
		goto err_tcp_mib;
	net->mib.ip_statistics = alloc_percpu(struct ipstats_mib);
	if (!net->mib.ip_statistics)
		goto err_ip_mib;

	for_each_possible_cpu(i) {
		struct ipstats_mib *af_inet_stats;
		af_inet_stats = per_cpu_ptr(net->mib.ip_statistics, i);
		u64_stats_init(&af_inet_stats->syncp);
	}

	net->mib.net_statistics = alloc_percpu(struct linux_mib);
	if (!net->mib.net_statistics)
		goto err_net_mib;
	net->mib.udp_statistics = alloc_percpu(struct udp_mib);
	if (!net->mib.udp_statistics)
		goto err_udp_mib;
	net->mib.udplite_statistics = alloc_percpu(struct udp_mib);
	if (!net->mib.udplite_statistics)
		goto err_udplite_mib;
	net->mib.icmp_statistics = alloc_percpu(struct icmp_mib);
	if (!net->mib.icmp_statistics)
		goto err_icmp_mib;
	net->mib.icmpmsg_statistics = kzalloc(sizeof(struct icmpmsg_mib),
					      GFP_KERNEL);
	if (!net->mib.icmpmsg_statistics)
		goto err_icmpmsg_mib;

	tcp_mib_init(net);
	return 0;

err_icmpmsg_mib:
	free_percpu(net->mib.icmp_statistics);
err_icmp_mib:
	free_percpu(net->mib.udplite_statistics);
err_udplite_mib:
	free_percpu(net->mib.udp_statistics);
err_udp_mib:
	free_percpu(net->mib.net_statistics);
err_net_mib:
	free_percpu(net->mib.ip_statistics);
err_ip_mib:
	free_percpu(net->mib.tcp_statistics);
err_tcp_mib:
	return -ENOMEM;
}
