static int send_fd(int sock, int fd)
{
	int ret = lxc_abstract_unix_send_fd(sock, fd, NULL, 0);


	if (ret < 0) {
		SYSERROR("Error sending tty fd to parent");
		return -1;
	}

	return 0;
}
