int null_stdfds(void)
{
	int fd, ret = -1;

	fd = open("/dev/null", O_RDWR);
	if (fd < 0)
		return -1;

	if (dup2(fd, 0) < 0)
		goto err;
	if (dup2(fd, 1) < 0)
		goto err;
	if (dup2(fd, 2) < 0)
		goto err;

	ret = 0;
err:
	close(fd);
	return ret;
}
