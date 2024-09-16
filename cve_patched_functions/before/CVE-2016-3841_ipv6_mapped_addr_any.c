static bool ipv6_mapped_addr_any(const struct in6_addr *a)
{
	return ipv6_addr_v4mapped(a) && (a->s6_addr32[3] == 0);
}
