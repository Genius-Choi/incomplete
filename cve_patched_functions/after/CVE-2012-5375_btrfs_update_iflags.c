void btrfs_update_iflags(struct inode *inode)
{
	struct btrfs_inode *ip = BTRFS_I(inode);

	inode->i_flags &= ~(S_SYNC|S_APPEND|S_IMMUTABLE|S_NOATIME|S_DIRSYNC);

	if (ip->flags & BTRFS_INODE_SYNC)
		inode->i_flags |= S_SYNC;
	if (ip->flags & BTRFS_INODE_IMMUTABLE)
		inode->i_flags |= S_IMMUTABLE;
	if (ip->flags & BTRFS_INODE_APPEND)
		inode->i_flags |= S_APPEND;
	if (ip->flags & BTRFS_INODE_NOATIME)
		inode->i_flags |= S_NOATIME;
	if (ip->flags & BTRFS_INODE_DIRSYNC)
		inode->i_flags |= S_DIRSYNC;
}
