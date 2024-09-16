cmd_http_expect_close(CMD_ARGS)
{
	struct http *hp;
	struct pollfd fds[1];
	char c;
	int i;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AZ(av[1]);
	assert(hp->sfd != NULL);

	vtc_log(vl, 4, "Expecting close (fd = %d)", hp->fd);
	while (1) {
		fds[0].fd = hp->fd;
		fds[0].events = POLLIN | POLLERR;
		fds[0].revents = 0;
		i = poll(fds, 1, 1000);
		if (i == 0)
			vtc_log(vl, hp->fatal, "Expected close: timeout");
		if (i != 1 || !(fds[0].revents & POLLIN))
			vtc_log(vl, hp->fatal,
			    "Expected close: poll = %d, revents = 0x%x",
			    i, fds[0].revents);
		i = read(hp->fd, &c, 1);
		if (i == 0)
			break;
		if (i == 1 && vct_islws(c))
			continue;
		vtc_log(vl, hp->fatal,
		    "Expecting close: read = %d, c = 0x%02x", i, c);
	}
	vtc_log(vl, 4, "fd=%d EOF, as expected", hp->fd);
}
