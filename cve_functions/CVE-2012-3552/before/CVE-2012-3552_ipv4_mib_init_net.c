static __net_init int ipv4_mib_init_net(struct net *net)
{
	if (snmp_mib_init((void __percpu **)net->mib.tcp_statistics,
			  sizeof(struct tcp_mib),
			  __alignof__(struct tcp_mib)) < 0)
		goto err_tcp_mib;
	if (snmp_mib_init((void __percpu **)net->mib.ip_statistics,
			  sizeof(struct ipstats_mib),
			  __alignof__(struct ipstats_mib)) < 0)
		goto err_ip_mib;
	if (snmp_mib_init((void __percpu **)net->mib.net_statistics,
			  sizeof(struct linux_mib),
			  __alignof__(struct linux_mib)) < 0)
		goto err_net_mib;
	if (snmp_mib_init((void __percpu **)net->mib.udp_statistics,
			  sizeof(struct udp_mib),
			  __alignof__(struct udp_mib)) < 0)
		goto err_udp_mib;
	if (snmp_mib_init((void __percpu **)net->mib.udplite_statistics,
			  sizeof(struct udp_mib),
			  __alignof__(struct udp_mib)) < 0)
		goto err_udplite_mib;
	if (snmp_mib_init((void __percpu **)net->mib.icmp_statistics,
			  sizeof(struct icmp_mib),
			  __alignof__(struct icmp_mib)) < 0)
		goto err_icmp_mib;
	if (snmp_mib_init((void __percpu **)net->mib.icmpmsg_statistics,
			  sizeof(struct icmpmsg_mib),
			  __alignof__(struct icmpmsg_mib)) < 0)
		goto err_icmpmsg_mib;

	tcp_mib_init(net);
	return 0;

err_icmpmsg_mib:
	snmp_mib_free((void __percpu **)net->mib.icmp_statistics);
err_icmp_mib:
	snmp_mib_free((void __percpu **)net->mib.udplite_statistics);
err_udplite_mib:
	snmp_mib_free((void __percpu **)net->mib.udp_statistics);
err_udp_mib:
	snmp_mib_free((void __percpu **)net->mib.net_statistics);
err_net_mib:
	snmp_mib_free((void __percpu **)net->mib.ip_statistics);
err_ip_mib:
	snmp_mib_free((void __percpu **)net->mib.tcp_statistics);
err_tcp_mib:
	return -ENOMEM;
}
