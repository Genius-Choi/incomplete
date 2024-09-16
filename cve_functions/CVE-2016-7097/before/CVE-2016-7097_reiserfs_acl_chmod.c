int reiserfs_acl_chmod(struct inode *inode)
{
	if (IS_PRIVATE(inode))
		return 0;
	if (get_inode_sd_version(inode) == STAT_DATA_V1 ||
	    !reiserfs_posixacl(inode->i_sb))
		return 0;

	return posix_acl_chmod(inode, inode->i_mode);
}
