load(const char *magicfile, int flags)
{
	struct magic_set *magic = magic_open(flags);
	if (magic == NULL) {
		(void)fprintf(stderr, "%s: %s\n", progname, strerror(errno));
		return NULL;
	}
	if (magic_load(magic, magicfile) == -1) {
		(void)fprintf(stderr, "%s: %s\n",
		    progname, magic_error(magic));
		magic_close(magic);
		return NULL;
	}
	return magic;
}
