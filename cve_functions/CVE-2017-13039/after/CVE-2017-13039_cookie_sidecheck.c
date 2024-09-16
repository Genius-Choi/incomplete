cookie_sidecheck(int i, const u_char *bp2, int initiator)
{
	const struct ip *ip;
	const struct ip6_hdr *ip6;

	ip = (const struct ip *)bp2;
	switch (IP_V(ip)) {
	case 4:
		if (cookiecache[i].version != 4)
			return 0;
		if (initiator) {
			if (UNALIGNED_MEMCMP(&ip->ip_src, &cookiecache[i].iaddr.in4, sizeof(struct in_addr)) == 0)
				return 1;
		} else {
			if (UNALIGNED_MEMCMP(&ip->ip_src, &cookiecache[i].raddr.in4, sizeof(struct in_addr)) == 0)
				return 1;
		}
		break;
	case 6:
		if (cookiecache[i].version != 6)
			return 0;
		ip6 = (const struct ip6_hdr *)bp2;
		if (initiator) {
			if (UNALIGNED_MEMCMP(&ip6->ip6_src, &cookiecache[i].iaddr.in6, sizeof(struct in6_addr)) == 0)
				return 1;
		} else {
			if (UNALIGNED_MEMCMP(&ip6->ip6_src, &cookiecache[i].raddr.in6, sizeof(struct in6_addr)) == 0)
				return 1;
		}
		break;
	default:
		break;
	}

	return 0;
}
