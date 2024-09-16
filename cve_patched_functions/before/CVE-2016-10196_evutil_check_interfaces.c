evutil_check_interfaces(int force_recheck)
{
	evutil_socket_t fd = -1;
	struct sockaddr_in sin, sin_out;
	struct sockaddr_in6 sin6, sin6_out;
	ev_socklen_t sin_out_len = sizeof(sin_out);
	ev_socklen_t sin6_out_len = sizeof(sin6_out);
	int r;
	if (have_checked_interfaces && !force_recheck)
		return 0;

	if (evutil_check_ifaddrs() == 0) {
		/* Use a nice sane interface, if this system has one. */
		return 0;
	}

	/* Ugh. There was no nice sane interface.  So to check whether we have
	 * an interface open for a given protocol, will try to make a UDP
	 * 'connection' to a remote host on the internet.  We don't actually
	 * use it, so the address doesn't matter, but we want to pick one that
	 * keep us from using a host- or link-local interface. */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(53);
	r = evutil_inet_pton(AF_INET, "18.244.0.188", &sin.sin_addr);
	EVUTIL_ASSERT(r);

	memset(&sin6, 0, sizeof(sin6));
	sin6.sin6_family = AF_INET6;
	sin6.sin6_port = htons(53);
	r = evutil_inet_pton(AF_INET6, "2001:4860:b002::68", &sin6.sin6_addr);
	EVUTIL_ASSERT(r);

	memset(&sin_out, 0, sizeof(sin_out));
	memset(&sin6_out, 0, sizeof(sin6_out));

	/* XXX some errnos mean 'no address'; some mean 'not enough sockets'. */
	if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) >= 0 &&
	    connect(fd, (struct sockaddr*)&sin, sizeof(sin)) == 0 &&
	    getsockname(fd, (struct sockaddr*)&sin_out, &sin_out_len) == 0) {
		/* We might have an IPv4 interface. */
		evutil_found_ifaddr((struct sockaddr*) &sin_out);
	}
	if (fd >= 0)
		evutil_closesocket(fd);

	if ((fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) >= 0 &&
	    connect(fd, (struct sockaddr*)&sin6, sizeof(sin6)) == 0 &&
	    getsockname(fd, (struct sockaddr*)&sin6_out, &sin6_out_len) == 0) {
		/* We might have an IPv6 interface. */
		evutil_found_ifaddr((struct sockaddr*) &sin6_out);
	}

	if (fd >= 0)
		evutil_closesocket(fd);

	return 0;
}
