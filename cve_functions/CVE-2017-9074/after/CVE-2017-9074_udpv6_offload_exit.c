int udpv6_offload_exit(void)
{
	return inet6_del_offload(&udpv6_offload, IPPROTO_UDP);
}
