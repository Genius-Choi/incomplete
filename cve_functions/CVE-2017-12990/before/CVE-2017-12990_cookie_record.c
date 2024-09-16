cookie_record(cookie_t *in, const u_char *bp2)
{
	int i;
	const struct ip *ip;
	const struct ip6_hdr *ip6;

	i = cookie_find(in);
	if (0 <= i) {
		ninitiator = (i + 1) % MAXINITIATORS;
		return;
	}

	ip = (const struct ip *)bp2;
	switch (IP_V(ip)) {
	case 4:
		cookiecache[ninitiator].version = 4;
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].iaddr.in4, &ip->ip_src, sizeof(struct in_addr));
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].raddr.in4, &ip->ip_dst, sizeof(struct in_addr));
		break;
	case 6:
		ip6 = (const struct ip6_hdr *)bp2;
		cookiecache[ninitiator].version = 6;
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].iaddr.in6, &ip6->ip6_src, sizeof(struct in6_addr));
		UNALIGNED_MEMCPY(&cookiecache[ninitiator].raddr.in6, &ip6->ip6_dst, sizeof(struct in6_addr));
		break;
	default:
		return;
	}
	UNALIGNED_MEMCPY(&cookiecache[ninitiator].initiator, in, sizeof(*in));
	ninitiator = (ninitiator + 1) % MAXINITIATORS;
}
