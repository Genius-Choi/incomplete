static int btrfs_update_time(struct inode *inode, struct timespec *now,
			     int flags)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;

	if (btrfs_root_readonly(root))
		return -EROFS;

	if (flags & S_VERSION)
		inode_inc_iversion(inode);
	if (flags & S_CTIME)
		inode->i_ctime = *now;
	if (flags & S_MTIME)
		inode->i_mtime = *now;
	if (flags & S_ATIME)
		inode->i_atime = *now;
	return btrfs_dirty_inode(inode);
}
