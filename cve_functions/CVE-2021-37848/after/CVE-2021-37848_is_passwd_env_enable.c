static int is_passwd_env_enable(void)
{
	int fd;

	fd = open(PASSWD_FILE, O_RDONLY);

	if (fd < 0)
		return 0;

	close(fd);

	return 1;
}
