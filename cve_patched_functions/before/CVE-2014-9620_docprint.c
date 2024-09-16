docprint(const char *opts)
{
	size_t i;
	int comma;
	char *sp, *p;

	p = strstr(opts, "%o");
	if (p == NULL) {
		fprintf(stdout, "%s", opts);
		return;
	}

	for (sp = p - 1; sp > opts && *sp == ' '; sp--)
		continue;

	fprintf(stdout, "%.*s", (int)(p - opts), opts);

	comma = 0;
	for (i = 0; i < __arraycount(nv); i++) {
		fprintf(stdout, "%s%s", comma++ ? ", " : "", nv[i].name);
		if (i && i % 5 == 0) {
			fprintf(stdout, ",\n%*s", (int)(p - sp - 1), "");
			comma = 0;
		}
	}

	fprintf(stdout, "%s", opts + (p - opts) + 2);
}
