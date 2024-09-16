trap_name_resolved(
	int			rescode,
	int			gai_errno,
	void *			context,
	const char *		name,
	const char *		service,
	const struct addrinfo *	hints,
	const struct addrinfo *	res
	)
{
	settrap_parms *pstp;
	struct interface *localaddr;
	sockaddr_u peeraddr;

	pstp = context;
	if (rescode) {
		msyslog(LOG_ERR,
			"giving up resolving trap host %s: %s (%d)",
			name, gai_strerror(rescode), rescode);
		free(pstp);
		return;
	}
	NTP_INSIST(sizeof(peeraddr) >= res->ai_addrlen);
	memset(&peeraddr, 0, sizeof(peeraddr));
	memcpy(&peeraddr, res->ai_addr, res->ai_addrlen);
	localaddr = NULL;
	if (pstp->ifaddr_nonnull)
		localaddr = findinterface(&pstp->ifaddr);
	if (NULL == localaddr)
		localaddr = ANY_INTERFACE_CHOOSE(&peeraddr);
	if (!ctlsettrap(&peeraddr, localaddr, 0, NTP_VERSION))
		msyslog(LOG_ERR, "set trap %s -> %s failed.",
			latoa(localaddr), stoa(&peeraddr));
	free(pstp);
}
