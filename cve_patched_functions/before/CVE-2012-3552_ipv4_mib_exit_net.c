static __net_exit void ipv4_mib_exit_net(struct net *net)
{
	snmp_mib_free((void __percpu **)net->mib.icmpmsg_statistics);
	snmp_mib_free((void __percpu **)net->mib.icmp_statistics);
	snmp_mib_free((void __percpu **)net->mib.udplite_statistics);
	snmp_mib_free((void __percpu **)net->mib.udp_statistics);
	snmp_mib_free((void __percpu **)net->mib.net_statistics);
	snmp_mib_free((void __percpu **)net->mib.ip_statistics);
	snmp_mib_free((void __percpu **)net->mib.tcp_statistics);
}
