applyparam(magic_t magic)
{
	size_t i;

	for (i = 0; i < __arraycount(pm); i++) {
		if (pm[i].value == 0)
			continue;
		if (magic_setparam(magic, pm[i].tag, &pm[i].value) == -1) {
			(void)fprintf(stderr, "%s: Can't set %s %s\n", progname,
				pm[i].name, strerror(errno));
			exit(1);
		}
	}
}
