static void reverse(unsigned char *buf, size_t len)
{
	unsigned char tmp;
	size_t i;

	assert(buf || len == 0);
	for (i = 0; i < len / 2; ++i)
	{
		tmp = buf[i];
		buf[i] = buf[len - 1 - i];
		buf[len - 1 - i] = tmp;
	}
}
