static int read_default_passwd(unsigned char *sum, size_t length)
{
	int i = 0;
	int len = strlen(default_passwd);
	unsigned char *buf = (unsigned char *)default_passwd;
	unsigned char c;

	if (ARRAY_SIZE(default_passwd) == 1)
		return -ENOSYS;

	if (!sum || length < 1)
		return -EINVAL;

	for (i = 0; i < len && length > 0; i++) {
		c = buf[i];
		i++;

		*sum = to_digit(c) << 4;

		c = buf[i];

		*sum |= to_digit(c);
		sum++;
		length--;
	}

	return 0;
}
