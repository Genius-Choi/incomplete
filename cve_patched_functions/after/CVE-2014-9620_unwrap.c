unwrap(struct magic_set *ms, const char *fn)
{
	FILE *f;
	ssize_t len;
	char *line = NULL;
	size_t llen = 0;
	int wid = 0, cwid;
	int e = 0;

	if (strcmp("-", fn) == 0) {
		f = stdin;
		wid = 1;
	} else {
		if ((f = fopen(fn, "r")) == NULL) {
			(void)fprintf(stderr, "%s: Cannot open `%s' (%s).\n",
			    progname, fn, strerror(errno));
			return 1;
		}

		while ((len = getline(&line, &llen, f)) > 0) {
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';
			cwid = file_mbswidth(line);
			if (cwid > wid)
				wid = cwid;
		}

		rewind(f);
	}

	while ((len = getline(&line, &llen, f)) > 0) {
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		e |= process(ms, line, wid);
		if(nobuffer)
			(void)fflush(stdout);
	}

	free(line);
	(void)fclose(f);
	return e;
}
