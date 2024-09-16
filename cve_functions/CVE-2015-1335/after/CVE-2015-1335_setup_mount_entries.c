static int setup_mount_entries(const struct lxc_rootfs *rootfs, struct lxc_list *mount,
	const char *lxc_name)
{
	FILE *file;
	int ret;

	file = write_mount_file(mount);
	if (!file)
		return -1;

	ret = mount_file_entries(rootfs, file, lxc_name);

	fclose(file);
	return ret;
}
