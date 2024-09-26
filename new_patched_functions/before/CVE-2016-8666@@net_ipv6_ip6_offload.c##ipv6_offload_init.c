static int __init ipv6_offload_init(void)
{

	if (tcpv6_offload_init() < 0)
		pr_crit("%s: Cannot add TCP protocol offload\n", __func__);
	if (udp_offload_init() < 0)
		pr_crit("%s: Cannot add UDP protocol offload\n", __func__);
	if (ipv6_exthdrs_offload_init() < 0)
		pr_crit("%s: Cannot add EXTHDRS protocol offload\n", __func__);

	dev_add_offload(&ipv6_packet_offload);

	inet_add_offload(&sit_offload, IPPROTO_IPV6);

	return 0;
}
