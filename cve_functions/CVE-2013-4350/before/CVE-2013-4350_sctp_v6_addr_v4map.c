static void sctp_v6_addr_v4map(struct sctp_sock *sp, union sctp_addr *addr)
{
	if (sp->v4mapped && AF_INET == addr->sa.sa_family)
		sctp_v4_map_v6(addr);
}
