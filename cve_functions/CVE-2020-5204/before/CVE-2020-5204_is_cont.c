static int is_cont(char *msg)
{
	char *ptr;

	ptr = strchr(msg, '\r');
	if (ptr) {
		ptr++;
		if (strchr(ptr, '\r'))
			return 1;
	}

	return 0;
}
