static int cgroup_rmdir(char *dirname)
{
	struct dirent dirent, *direntp;
	int saved_errno = 0;
	DIR *dir;
	int ret, failed=0;
	char pathname[MAXPATHLEN];

	dir = opendir(dirname);
	if (!dir) {
		ERROR("%s: failed to open %s", __func__, dirname);
		return -1;
	}

	while (!readdir_r(dir, &dirent, &direntp)) {
		struct stat mystat;
		int rc;

		if (!direntp)
			break;

		if (!strcmp(direntp->d_name, ".") ||
		    !strcmp(direntp->d_name, ".."))
			continue;

		rc = snprintf(pathname, MAXPATHLEN, "%s/%s", dirname, direntp->d_name);
		if (rc < 0 || rc >= MAXPATHLEN) {
			ERROR("pathname too long");
			failed=1;
			if (!saved_errno)
				saved_errno = -ENOMEM;
			continue;
		}
		ret = lstat(pathname, &mystat);
		if (ret) {
			SYSERROR("%s: failed to stat %s", __func__, pathname);
			failed=1;
			if (!saved_errno)
				saved_errno = errno;
			continue;
		}
		if (S_ISDIR(mystat.st_mode)) {
			if (cgroup_rmdir(pathname) < 0) {
				if (!saved_errno)
					saved_errno = errno;
				failed=1;
			}
		}
	}

	if (rmdir(dirname) < 0) {
		SYSERROR("%s: failed to delete %s", __func__, dirname);
		if (!saved_errno)
			saved_errno = errno;
		failed=1;
	}

	ret = closedir(dir);
	if (ret) {
		SYSERROR("%s: failed to close directory %s", __func__, dirname);
		if (!saved_errno)
			saved_errno = errno;
		failed=1;
	}

	errno = saved_errno;
	return failed ? -1 : 0;
}
