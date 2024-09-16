int ext4_write_inode(struct inode *inode, int wait)
{
	int err;

	if (current->flags & PF_MEMALLOC)
		return 0;

	if (EXT4_SB(inode->i_sb)->s_journal) {
		if (ext4_journal_current_handle()) {
			jbd_debug(1, "called recursively, non-PF_MEMALLOC!\n");
			dump_stack();
			return -EIO;
		}

		if (!wait)
			return 0;

		err = ext4_force_commit(inode->i_sb);
	} else {
		struct ext4_iloc iloc;

		err = ext4_get_inode_loc(inode, &iloc);
		if (err)
			return err;
		if (wait)
			sync_dirty_buffer(iloc.bh);
		if (buffer_req(iloc.bh) && !buffer_uptodate(iloc.bh)) {
			ext4_error(inode->i_sb, "IO error syncing inode, "
				   "inode=%lu, block=%llu", inode->i_ino,
				   (unsigned long long)iloc.bh->b_blocknr);
			err = -EIO;
		}
	}
	return err;
}
