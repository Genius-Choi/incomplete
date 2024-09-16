static int sctp_v6_available(union sctp_addr *addr, struct sctp_sock *sp)
{
	int type;
	const struct in6_addr *in6 = (const struct in6_addr *)&addr->v6.sin6_addr;

	type = ipv6_addr_type(in6);
	if (IPV6_ADDR_ANY == type)
		return 1;
	if (type == IPV6_ADDR_MAPPED) {
		if (sp && !sp->v4mapped)
			return 0;
		if (sp && ipv6_only_sock(sctp_opt2sk(sp)))
			return 0;
		sctp_v6_map_v4(addr);
		return sctp_get_af_specific(AF_INET)->available(addr, sp);
	}
	if (!(type & IPV6_ADDR_UNICAST))
		return 0;

	return ipv6_chk_addr(sock_net(&sp->inet.sk), in6, NULL, 0);
}
