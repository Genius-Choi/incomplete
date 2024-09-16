evdns_base_parse_hosts_line(struct evdns_base *base, char *line)
{
	char *strtok_state;
	static const char *const delims = " \t";
	char *const addr = strtok_r(line, delims, &strtok_state);
	char *hostname, *hash;
	struct sockaddr_storage ss;
	int socklen = sizeof(ss);
	ASSERT_LOCKED(base);

#define NEXT_TOKEN strtok_r(NULL, delims, &strtok_state)

	if (!addr || *addr == '#')
		return 0;

	memset(&ss, 0, sizeof(ss));
	if (evutil_parse_sockaddr_port(addr, (struct sockaddr*)&ss, &socklen)<0)
		return -1;
	if (socklen > (int)sizeof(struct sockaddr_in6))
		return -1;

	if (sockaddr_getport((struct sockaddr*)&ss))
		return -1;

	while ((hostname = NEXT_TOKEN)) {
		struct hosts_entry *he;
		size_t namelen;
		if ((hash = strchr(hostname, '#'))) {
			if (hash == hostname)
				return 0;
			*hash = '\0';
		}

		namelen = strlen(hostname);

		he = mm_calloc(1, sizeof(struct hosts_entry)+namelen);
		if (!he)
			return -1;
		EVUTIL_ASSERT(socklen <= (int)sizeof(he->addr));
		memcpy(&he->addr, &ss, socklen);
		memcpy(he->hostname, hostname, namelen+1);
		he->addrlen = socklen;

		TAILQ_INSERT_TAIL(&base->hostsdb, he, next);

		if (hash)
			return 0;
	}

	return 0;
#undef NEXT_TOKEN
}
