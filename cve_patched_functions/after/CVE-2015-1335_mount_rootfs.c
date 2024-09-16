static int mount_rootfs(const char *rootfs, const char *target, const char *options)
{
	char absrootfs[MAXPATHLEN];
	struct stat s;
	int i;

	typedef int (*rootfs_cb)(const char *, const char *, const char *);

	struct rootfs_type {
		int type;
		rootfs_cb cb;
	} rtfs_type[] = {
		{ S_IFDIR, mount_rootfs_dir },
		{ S_IFBLK, mount_rootfs_block },
		{ S_IFREG, mount_rootfs_file },
	};

	if (!realpath(rootfs, absrootfs)) {
		SYSERROR("failed to get real path for '%s'", rootfs);
		return -1;
	}

	if (access(absrootfs, F_OK)) {
		SYSERROR("'%s' is not accessible", absrootfs);
		return -1;
	}

	if (stat(absrootfs, &s)) {
		SYSERROR("failed to stat '%s'", absrootfs);
		return -1;
	}

	for (i = 0; i < sizeof(rtfs_type)/sizeof(rtfs_type[0]); i++) {

		if (!__S_ISTYPE(s.st_mode, rtfs_type[i].type))
			continue;

		return rtfs_type[i].cb(absrootfs, target, options);
	}

	ERROR("unsupported rootfs type for '%s'", absrootfs);
	return -1;
}
