static void sctp_v6_inaddr_any(union sctp_addr *addr, __be16 port)
{
	memset(addr, 0x00, sizeof(union sctp_addr));
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_port = port;
}
