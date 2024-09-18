setparam(const char *p)
{
	size_t i;
	char *s;

	if ((s = strchr(p, '=')) == NULL)
		goto badparm;

	for (i = 0; i < __arraycount(pm); i++) {
		if (strncmp(p, pm[i].name, s - p) != 0)
			continue;
		pm[i].value = atoi(s + 1);
		return;
	}
badparm:
	(void)fprintf(stderr, "%s: Unknown param %s\n", progname, p);
	exit(1);
}
