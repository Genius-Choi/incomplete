http_rxchar(struct http *hp, int n, int eof)
{
	int i;
	struct pollfd pfd[1];

	while (n > 0) {
		pfd[0].fd = hp->fd;
		pfd[0].events = POLLIN;
		pfd[0].revents = 0;
		i = poll(pfd, 1, hp->timeout);
		if (i == 0)
			vtc_log(hp->vl, hp->fatal,
			    "HTTP rx timeout (fd:%d %u ms)",
			    hp->fd, hp->timeout);
		if (i < 0)
			vtc_log(hp->vl, hp->fatal,
			    "HTTP rx failed (fd:%d poll: %s)",
			    hp->fd, strerror(errno));
		assert(i > 0);
		assert(hp->prxbuf + n < hp->nrxbuf);
		i = read(hp->fd, hp->rxbuf + hp->prxbuf, n);
		if (!(pfd[0].revents & POLLIN))
			vtc_log(hp->vl, 4,
			    "HTTP rx poll (fd:%d revents: %x n=%d, i=%d)",
			    hp->fd, pfd[0].revents, n, i);
		if (i == 0 && eof)
			return (i);
		if (i == 0)
			vtc_log(hp->vl, hp->fatal,
			    "HTTP rx EOF (fd:%d read: %s)",
			    hp->fd, strerror(errno));
		if (i < 0)
			vtc_log(hp->vl, hp->fatal,
			    "HTTP rx failed (fd:%d read: %s)",
			    hp->fd, strerror(errno));
		hp->prxbuf += i;
		hp->rxbuf[hp->prxbuf] = '\0';
		n -= i;
	}
	return (1);
}
