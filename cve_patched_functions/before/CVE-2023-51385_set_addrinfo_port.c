set_addrinfo_port(struct addrinfo *addrs, int port)
{
	struct addrinfo *addr;

	for (addr = addrs; addr != NULL; addr = addr->ai_next) {
		switch (addr->ai_family) {
		case AF_INET:
			((struct sockaddr_in *)addr->ai_addr)->
			    sin_port = htons(port);
			break;
		case AF_INET6:
			((struct sockaddr_in6 *)addr->ai_addr)->
			    sin6_port = htons(port);
			break;
		}
	}
}
