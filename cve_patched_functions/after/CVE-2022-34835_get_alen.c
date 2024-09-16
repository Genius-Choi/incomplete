static uint get_alen(char *arg, uint default_len)
{
	uint	j;
	uint	alen;

	alen = default_len;
	for (j = 0; j < 8; j++) {
		if (arg[j] == '.') {
			alen = arg[j+1] - '0';
			break;
		} else if (arg[j] == '\0')
			break;
	}
	return alen;
}
