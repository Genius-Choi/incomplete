static char *strstr_full_case(const char *data, const char *key, int icase)
{
	const char *start, *max;
	int keylen, datalen, pos, match;

	keylen = strlen(key);
	datalen = strlen(data);

	if (keylen > datalen)
		return NULL;
	if (keylen == 0)
		return (char *) data;

	max = data+datalen-keylen;
	start = data; pos = 0;
	while (data <= max) {
		if (key[pos] == '\0') {
			if (data[pos] != '\0' && !isbound(data[pos])) {
				data++;
				pos = 0;
                                continue;
			}
			return (char *) data;
		}

		match = icase ? (i_toupper(data[pos]) == i_toupper(key[pos])) :
				 data[pos] == key[pos];

		if (match && (pos != 0 || data == start || isbound(data[-1])))
			pos++;
		else {
			data++;
                        pos = 0;
		}
	}

	return NULL;
}
