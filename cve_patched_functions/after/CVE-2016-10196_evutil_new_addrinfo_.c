evutil_new_addrinfo_(struct sockaddr *sa, ev_socklen_t socklen,
    const struct evutil_addrinfo *hints)
{
	struct evutil_addrinfo *res;
	EVUTIL_ASSERT(hints);

	if (hints->ai_socktype == 0 && hints->ai_protocol == 0) {
		/* Indecisive user! Give them a UDP and a TCP. */
		struct evutil_addrinfo *r1, *r2;
		struct evutil_addrinfo tmp;
		memcpy(&tmp, hints, sizeof(tmp));
		tmp.ai_socktype = SOCK_STREAM; tmp.ai_protocol = IPPROTO_TCP;
		r1 = evutil_new_addrinfo_(sa, socklen, &tmp);
		if (!r1)
			return NULL;
		tmp.ai_socktype = SOCK_DGRAM; tmp.ai_protocol = IPPROTO_UDP;
		r2 = evutil_new_addrinfo_(sa, socklen, &tmp);
		if (!r2) {
			evutil_freeaddrinfo(r1);
			return NULL;
		}
		r1->ai_next = r2;
		return r1;
	}

	/* We're going to allocate extra space to hold the sockaddr. */
	res = mm_calloc(1,sizeof(struct evutil_addrinfo)+socklen);
	if (!res)
		return NULL;
	res->ai_addr = (struct sockaddr*)
	    (((char*)res) + sizeof(struct evutil_addrinfo));
	memcpy(res->ai_addr, sa, socklen);
	res->ai_addrlen = socklen;
	res->ai_family = sa->sa_family; /* Same or not? XXX */
	res->ai_flags = EVUTIL_AI_LIBEVENT_ALLOCATED;
	res->ai_socktype = hints->ai_socktype;
	res->ai_protocol = hints->ai_protocol;

	return res;
}
