int is_link(const char *fname) {
	assert(fname);
	if (*fname == '\0')
		return 0;

	struct stat s;
	if (lstat(fname, &s) == 0) {
		if (S_ISLNK(s.st_mode))
			return 1;
	}

	return 0;
}
