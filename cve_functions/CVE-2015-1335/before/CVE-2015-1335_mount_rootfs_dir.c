static int mount_rootfs_dir(const char *rootfs, const char *target,
			                const char *options)
{
	unsigned long mntflags;
	char *mntdata;
	int ret;

	if (parse_mntopts(options, &mntflags, &mntdata) < 0) {
		free(mntdata);
		return -1;
	}

	ret = mount(rootfs, target, "none", MS_BIND | MS_REC | mntflags, mntdata);
	free(mntdata);

	return ret;
}
