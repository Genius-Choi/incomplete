int ext4_inode_is_fast_symlink(struct inode *inode)
{
        int ea_blocks = EXT4_I(inode)->i_file_acl ?
		EXT4_CLUSTER_SIZE(inode->i_sb) >> 9 : 0;

	if (ext4_has_inline_data(inode))
		return 0;

	return (S_ISLNK(inode->i_mode) && inode->i_blocks - ea_blocks == 0);
}
