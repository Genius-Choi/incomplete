static int setup_pivot_root(const struct lxc_rootfs *rootfs)
{
	if (!rootfs->path)
		return 0;

	if (detect_ramfs_rootfs()) {
		if (prepare_ramfs_root(rootfs->mount))
			return -1;
	} else if (setup_rootfs_pivot_root(rootfs->mount, rootfs->pivot)) {
		ERROR("failed to setup pivot root");
		return -1;
	}

	return 0;
}
