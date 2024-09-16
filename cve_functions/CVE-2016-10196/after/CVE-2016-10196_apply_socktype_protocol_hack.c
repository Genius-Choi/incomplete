apply_socktype_protocol_hack(struct evutil_addrinfo *ai)
{
	struct evutil_addrinfo *ai_new;
	for (; ai; ai = ai->ai_next) {
		evutil_getaddrinfo_infer_protocols(ai);
		if (ai->ai_socktype || ai->ai_protocol)
			continue;
		ai_new = mm_malloc(sizeof(*ai_new));
		if (!ai_new)
			return -1;
		memcpy(ai_new, ai, sizeof(*ai_new));
		ai->ai_socktype = SOCK_STREAM;
		ai->ai_protocol = IPPROTO_TCP;
		ai_new->ai_socktype = SOCK_DGRAM;
		ai_new->ai_protocol = IPPROTO_UDP;

		ai_new->ai_next = ai->ai_next;
		ai->ai_next = ai_new;
	}
	return 0;
}
