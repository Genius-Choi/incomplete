int ndp_callall_eventfd_handler(struct ndp *ndp)
{
	fd_set rfds;
	int fdmax;
	struct timeval tv;
	int fd = ndp_get_eventfd(ndp);
	int ret;
	int err;

	memset(&tv, 0, sizeof(tv));
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	fdmax = fd + 1;
	while (true) {
		ret = select(fdmax, &rfds, NULL, NULL, &tv);
		if (ret == -1)
			return -errno;
		if (!FD_ISSET(fd, &rfds))
			return 0;
		err = ndp_call_eventfd_handler(ndp);
		if (err)
			return err;
	}
}
