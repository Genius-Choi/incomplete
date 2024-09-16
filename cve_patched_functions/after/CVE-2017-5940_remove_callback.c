static int remove_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
	(void) sb;
	(void) typeflag;
	(void) ftwbuf;
	
	int rv = remove(fpath);
	if (rv)
		perror(fpath);

	return rv;
}
