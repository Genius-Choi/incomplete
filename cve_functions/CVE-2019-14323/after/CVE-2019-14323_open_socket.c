static int open_socket(char *ifname, struct sockaddr *addr, int port)
{
	int sd, val, rc;
	char loop;
	struct ip_mreqn mreq;
	struct sockaddr_in sin, *address = (struct sockaddr_in *)addr;

	sd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
	if (sd < 0)
		return -1;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr = address->sin_addr;
	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		close(sd);
		logit(LOG_ERR, "Failed binding to %s:%d: %s", inet_ntoa(address->sin_addr), port, strerror(errno));
		return -1;
	}
#if 0
        ENABLE_SOCKOPT(sd, SOL_SOCKET, SO_REUSEADDR);
#ifdef SO_REUSEPORT
        ENABLE_SOCKOPT(sd, SOL_SOCKET, SO_REUSEPORT);
#endif
#endif
	memset(&mreq, 0, sizeof(mreq));
	mreq.imr_address = address->sin_addr;
	mreq.imr_multiaddr.s_addr = inet_addr(MC_SSDP_GROUP);
        if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))) {
		close(sd);
		logit(LOG_ERR, "Failed joining group %s: %s", MC_SSDP_GROUP, strerror(errno));
		return -1;
	}

	val = 2;		/* Default 2, but should be configurable */
	rc = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_TTL, &val, sizeof(val));
	if (rc < 0) {
		close(sd);
		logit(LOG_ERR, "Failed setting multicast TTL: %s", strerror(errno));
		return -1;
	}

	loop = 0;
	rc = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
	if (rc < 0) {
		close(sd);
		logit(LOG_ERR, "Failed disabing multicast loop: %s", strerror(errno));
		return -1;
	}

	rc = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &address->sin_addr, sizeof(address->sin_addr));
	if (rc < 0) {
		close(sd);
		logit(LOG_ERR, "Failed setting multicast interface: %s", strerror(errno));
		return -1;
	}

	logit(LOG_DEBUG, "Adding new interface %s with address %s", ifname, inet_ntoa(address->sin_addr));

	return sd;
}
