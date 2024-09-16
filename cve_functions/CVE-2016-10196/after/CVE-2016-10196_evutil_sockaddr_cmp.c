evutil_sockaddr_cmp(const struct sockaddr *sa1, const struct sockaddr *sa2,
    int include_port)
{
	int r;
	if (0 != (r = (sa1->sa_family - sa2->sa_family)))
		return r;

	if (sa1->sa_family == AF_INET) {
		const struct sockaddr_in *sin1, *sin2;
		sin1 = (const struct sockaddr_in *)sa1;
		sin2 = (const struct sockaddr_in *)sa2;
		if (sin1->sin_addr.s_addr < sin2->sin_addr.s_addr)
			return -1;
		else if (sin1->sin_addr.s_addr > sin2->sin_addr.s_addr)
			return 1;
		else if (include_port &&
		    (r = ((int)sin1->sin_port - (int)sin2->sin_port)))
			return r;
		else
			return 0;
	}
#ifdef AF_INET6
	else if (sa1->sa_family == AF_INET6) {
		const struct sockaddr_in6 *sin1, *sin2;
		sin1 = (const struct sockaddr_in6 *)sa1;
		sin2 = (const struct sockaddr_in6 *)sa2;
		if ((r = memcmp(sin1->sin6_addr.s6_addr, sin2->sin6_addr.s6_addr, 16)))
			return r;
		else if (include_port &&
		    (r = ((int)sin1->sin6_port - (int)sin2->sin6_port)))
			return r;
		else
			return 0;
	}
#endif
	return 1;
}
