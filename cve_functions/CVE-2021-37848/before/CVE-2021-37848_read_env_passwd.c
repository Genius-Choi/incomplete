static int read_env_passwd(unsigned char *sum, size_t length)
{
	int fd;
	int ret = 0;
	unsigned char c;

	if (!sum && length < 1)
		return -EINVAL;

	fd = open(PASSWD_FILE, O_RDONLY);

	if (fd < 0)
		return fd;

	do {
		ret = read(fd, &c, sizeof(char));

		if (ret < 0)
			goto exit;

		*sum = to_digit(c) << 4;

		ret = read(fd, &c, sizeof(char));

		if (ret < 0)
			goto exit;

		*sum |= to_digit(c);
		sum++;
		length--;
	} while(length > 0);

exit:

	ret = 0;

	close(fd);

	return ret;
}
