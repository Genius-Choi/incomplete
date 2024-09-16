static char **list_to_types(const char *list, int *flag)
{
	int i;
	const char *p = list;
	char **res = NULL;

	if (p && strncmp(p, "no", 2) == 0) {
		*flag = BLKID_FLTR_NOTIN;
		p += 2;
	}
	if (!p || !*p) {
		fprintf(stderr, "error: -u <list> argument is empty\n");
		goto err;
	}
	for (i = 1; p && (p = strchr(p, ',')); i++, p++);

	res = xcalloc(i + 1, sizeof(char *));
	p = *flag & BLKID_FLTR_NOTIN ? list + 2 : list;
	i = 0;

	while(p) {
		const char *word = p;
		p = strchr(p, ',');
		res[i++] = p ? xstrndup(word, p - word) : xstrdup(word);
		if (p)
			p++;
	}
	res[i] = NULL;
	return res;
err:
	*flag = 0;
	free(res);
	exit(BLKID_EXIT_OTHER);
}
