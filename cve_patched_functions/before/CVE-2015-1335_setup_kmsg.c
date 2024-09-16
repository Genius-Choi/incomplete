static int setup_kmsg(const struct lxc_rootfs *rootfs,
		       const struct lxc_console *console)
{
	char kpath[MAXPATHLEN];
	int ret;

	if (!rootfs->path)
		return 0;
	ret = snprintf(kpath, sizeof(kpath), "%s/dev/kmsg", rootfs->mount);
	if (ret < 0 || ret >= sizeof(kpath))
		return -1;

	ret = unlink(kpath);
	if (ret && errno != ENOENT) {
		SYSERROR("error unlinking %s", kpath);
		return -1;
	}

	ret = symlink("console", kpath);
	if (ret) {
		SYSERROR("failed to create symlink for kmsg");
		return -1;
	}

	return 0;
}
