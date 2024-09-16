void inode_add_lru(struct inode *inode)
{
	if (!(inode->i_state & (I_DIRTY | I_SYNC | I_FREEING | I_WILL_FREE)) &&
	    !atomic_read(&inode->i_count) && inode->i_sb->s_flags & MS_ACTIVE)
		inode_lru_list_add(inode);
}
