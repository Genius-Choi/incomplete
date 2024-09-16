static int multicast_join(int sd, struct sockaddr *sa)
{
	struct ip_mreqn mreq;
	struct sockaddr_in *sin = (struct sockaddr_in *)sa;

	memset(&mreq, 0, sizeof(mreq));
	mreq.imr_address = sin->sin_addr;
	mreq.imr_multiaddr.s_addr = inet_addr(MC_SSDP_GROUP);
        if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))) {
		if (EADDRINUSE == errno)
			return 0;

		logit(LOG_ERR, "Failed joining group %s: %s", MC_SSDP_GROUP, strerror(errno));
		return -1;
	}

	return 0;
}
