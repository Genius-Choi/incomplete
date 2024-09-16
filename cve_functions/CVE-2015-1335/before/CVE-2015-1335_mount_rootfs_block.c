static int mount_rootfs_block(const char *rootfs, const char *target,
			                  const char *options)
{
	return mount_unknown_fs(rootfs, target, options);
}
