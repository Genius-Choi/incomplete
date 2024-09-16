static int write_env_passwd(unsigned char *sum, size_t length)
{
	int fd;
	unsigned char c;
	int ret = 0;

	if (!sum && length < 1)
		return -EINVAL;

	fd = open(PASSWD_DIR, O_RDONLY);

	if (fd < 0)
		mkdir(PASSWD_DIR, 644);

	close(fd);

	fd = open(PASSWD_FILE, O_WRONLY | O_CREAT, 600);

	if (fd < 0)
		return fd;

	do {
		c = to_hexa(*sum >> 4 & 0xf);

		ret = write(fd, &c, sizeof(unsigned char));

		if (ret < 0)
			goto exit;

		c = to_hexa(*sum & 0xf);

		ret = write(fd, &c, sizeof(unsigned char));

		if (ret < 0)
			goto exit;

		sum++;
		length--;
	} while(length > 0);

	ret = 0;

exit:
	close(fd);

	return ret;
}
