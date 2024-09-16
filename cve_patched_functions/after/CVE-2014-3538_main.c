main(int argc, char *argv[])
{
	int ret;
	struct magic_set *ms;
	char *progname;

	if ((progname = strrchr(argv[0], '/')) != NULL)
		progname++;
	else
		progname = argv[0];

	if (argc != 2) {
		(void)fprintf(stderr, "Usage: %s file\n", progname);
		return 1;
	}

	if ((ms = magic_open(MAGIC_CHECK)) == NULL) {
		(void)fprintf(stderr, "%s: %s\n", progname, strerror(errno));
		return 1;
	}
	ret = magic_compile(ms, argv[1]) == -1 ? 1 : 0;
	if (ret == 1)
		(void)fprintf(stderr, "%s: %s\n", progname, magic_error(ms));
	magic_close(ms);
	return ret;
}
