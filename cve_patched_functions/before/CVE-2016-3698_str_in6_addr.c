static const char *str_in6_addr(struct in6_addr *addr)
{
	static char buf[INET6_ADDRSTRLEN];

	return inet_ntop(AF_INET6, addr, buf, sizeof(buf));
}
