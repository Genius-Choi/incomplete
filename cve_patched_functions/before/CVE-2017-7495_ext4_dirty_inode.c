void ext4_dirty_inode(struct inode *inode, int flags)
{
	handle_t *handle;

	if (flags == I_DIRTY_TIME)
		return;
	handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
	if (IS_ERR(handle))
		goto out;

	ext4_mark_inode_dirty(handle, inode);

	ext4_journal_stop(handle);
out:
	return;
}
