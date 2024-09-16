static u8 rds_tcp_get_tos_map(u8 tos)
{
	/* all user tos mapped to default 0 for TCP transport */
	return 0;
}
