static int __init ipv6_packet_init(void)
{
	dev_add_pack(&ipv6_packet_type);
	return 0;
}
