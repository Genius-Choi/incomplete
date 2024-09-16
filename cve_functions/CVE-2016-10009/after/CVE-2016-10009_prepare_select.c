prepare_select(fd_set **fdrp, fd_set **fdwp, int *fdl, u_int *nallocp,
    struct timeval **tvpp)
{
	u_int i, sz;
	int n = 0;
	static struct timeval tv;
	time_t deadline;

	for (i = 0; i < sockets_alloc; i++) {
		switch (sockets[i].type) {
		case AUTH_SOCKET:
		case AUTH_CONNECTION:
			n = MAXIMUM(n, sockets[i].fd);
			break;
		case AUTH_UNUSED:
			break;
		default:
			fatal("Unknown socket type %d", sockets[i].type);
			break;
		}
	}

	sz = howmany(n+1, NFDBITS) * sizeof(fd_mask);
	if (*fdrp == NULL || sz > *nallocp) {
		free(*fdrp);
		free(*fdwp);
		*fdrp = xmalloc(sz);
		*fdwp = xmalloc(sz);
		*nallocp = sz;
	}
	if (n < *fdl)
		debug("XXX shrink: %d < %d", n, *fdl);
	*fdl = n;
	memset(*fdrp, 0, sz);
	memset(*fdwp, 0, sz);

	for (i = 0; i < sockets_alloc; i++) {
		switch (sockets[i].type) {
		case AUTH_SOCKET:
		case AUTH_CONNECTION:
			FD_SET(sockets[i].fd, *fdrp);
			if (sshbuf_len(sockets[i].output) > 0)
				FD_SET(sockets[i].fd, *fdwp);
			break;
		default:
			break;
		}
	}
	deadline = reaper();
	if (parent_alive_interval != 0)
		deadline = (deadline == 0) ? parent_alive_interval :
		    MINIMUM(deadline, parent_alive_interval);
	if (deadline == 0) {
		*tvpp = NULL;
	} else {
		tv.tv_sec = deadline;
		tv.tv_usec = 0;
		*tvpp = &tv;
	}
	return (1);
}
