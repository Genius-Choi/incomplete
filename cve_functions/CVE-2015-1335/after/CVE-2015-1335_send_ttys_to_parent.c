static int send_ttys_to_parent(struct lxc_handler *handler)
{
	struct lxc_conf *conf = handler->conf;
	const struct lxc_tty_info *tty_info = &conf->tty_info;
	int i;
	int sock = handler->ttysock[0];

	for (i = 0; i < tty_info->nbtty; i++) {
		struct lxc_pty_info *pty_info = &tty_info->pty_info[i];
		if (send_fd(sock, pty_info->slave) < 0)
			goto bad;
		close(pty_info->slave);
		pty_info->slave = -1;
		if (send_fd(sock, pty_info->master) < 0)
			goto bad;
		close(pty_info->master);
		pty_info->master = -1;
	}

	close(handler->ttysock[0]);
	close(handler->ttysock[1]);

	return 0;

bad:
	ERROR("Error writing tty fd to parent");
	return -1;
}
