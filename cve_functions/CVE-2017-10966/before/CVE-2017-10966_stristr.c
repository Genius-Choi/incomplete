char *stristr(const char *data, const char *key)
{
	const char *max;
	int keylen, datalen, pos;

	keylen = strlen(key);
	datalen = strlen(data);

	if (keylen > datalen)
		return NULL;
	if (keylen == 0)
		return (char *) data;

	max = data+datalen-keylen;
	pos = 0;
	while (data <= max) {
		if (key[pos] == '\0')
                        return (char *) data;

		if (i_toupper(data[pos]) == i_toupper(key[pos]))
			pos++;
		else {
			data++;
                        pos = 0;
		}
	}

	return NULL;
}
