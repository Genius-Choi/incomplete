static int update_time(struct inode *inode, struct timespec *time, int flags)
{
	if (inode->i_op->update_time)
		return inode->i_op->update_time(inode, time, flags);

	if (flags & S_ATIME)
		inode->i_atime = *time;
	if (flags & S_VERSION)
		inode_inc_iversion(inode);
	if (flags & S_CTIME)
		inode->i_ctime = *time;
	if (flags & S_MTIME)
		inode->i_mtime = *time;
	mark_inode_dirty_sync(inode);
	return 0;
}
