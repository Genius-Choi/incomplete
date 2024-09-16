int match_wildcards(const char *cmask, const char *data)
{
	char *mask, *newmask, *p1, *p2;
	int ret;

	newmask = mask = g_strdup(cmask);
	for (; *mask != '\0' && *data != '\0'; mask++) {
		if (*mask != '*') {
			if (*mask != '?' && i_toupper(*mask) != i_toupper(*data))
				break;

			data++;
			continue;
		}

		while (*mask == '?' || *mask == '*') mask++;
		if (*mask == '\0') {
			data += strlen(data);
			break;
		}

		p1 = strchr(mask, '*');
		p2 = strchr(mask, '?');
		if (p1 == NULL || (p2 < p1 && p2 != NULL)) p1 = p2;

		if (p1 != NULL) *p1 = '\0';

		data = stristr(data, mask);
		if (data == NULL) break;

		data += strlen(mask);
		mask += strlen(mask)-1;

		if (p1 != NULL) *p1 = p1 == p2 ? '?' : '*';
	}

	while (*mask == '*') mask++;

	ret = data != NULL && *data == '\0' && *mask == '\0';
	g_free(newmask);

	return ret;
}
