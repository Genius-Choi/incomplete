static int btrfs_fiemap(struct inode *inode, struct fiemap_extent_info *fieinfo,
		__u64 start, __u64 len)
{
	int	ret;

	ret = fiemap_check_flags(fieinfo, BTRFS_FIEMAP_FLAGS);
	if (ret)
		return ret;

	return extent_fiemap(inode, fieinfo, start, len, btrfs_get_extent_fiemap);
}
