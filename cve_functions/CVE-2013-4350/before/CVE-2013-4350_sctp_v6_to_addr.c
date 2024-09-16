static void sctp_v6_to_addr(union sctp_addr *addr, struct in6_addr *saddr,
			      __be16 port)
{
	addr->sa.sa_family = AF_INET6;
	addr->v6.sin6_port = port;
	addr->v6.sin6_addr = *saddr;
}
