static int setup_mount(const struct lxc_rootfs *rootfs, const char *fstab,
	const char *lxc_name)
{
	FILE *file;
	int ret;

	if (!fstab)
		return 0;

	file = setmntent(fstab, "r");
	if (!file) {
		SYSERROR("failed to use '%s'", fstab);
		return -1;
	}

	ret = mount_file_entries(rootfs, file, lxc_name);

	endmntent(file);
	return ret;
}
