void ext4_clear_inode(struct inode *inode)
{
	invalidate_inode_buffers(inode);
	clear_inode(inode);
	dquot_drop(inode);
	ext4_discard_preallocations(inode);
	ext4_es_remove_extent(inode, 0, EXT_MAX_BLOCKS);
	if (EXT4_I(inode)->jinode) {
		jbd2_journal_release_jbd_inode(EXT4_JOURNAL(inode),
					       EXT4_I(inode)->jinode);
		jbd2_free_inode(EXT4_I(inode)->jinode);
		EXT4_I(inode)->jinode = NULL;
	}
#ifdef CONFIG_EXT4_FS_ENCRYPTION
	if (EXT4_I(inode)->i_crypt_info)
		ext4_free_encryption_info(inode, EXT4_I(inode)->i_crypt_info);
#endif
}
