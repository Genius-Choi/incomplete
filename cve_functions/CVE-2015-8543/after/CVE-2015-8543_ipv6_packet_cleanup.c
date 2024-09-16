static void ipv6_packet_cleanup(void)
{
	dev_remove_pack(&ipv6_packet_type);
}
