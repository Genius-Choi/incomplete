void __destroy_inode(struct inode *inode)
{
	BUG_ON(inode_has_buffers(inode));
	security_inode_free(inode);
	fsnotify_inode_delete(inode);
	if (!inode->i_nlink) {
		WARN_ON(atomic_long_read(&inode->i_sb->s_remove_count) == 0);
		atomic_long_dec(&inode->i_sb->s_remove_count);
	}

#ifdef CONFIG_FS_POSIX_ACL
	if (inode->i_acl && inode->i_acl != ACL_NOT_CACHED)
		posix_acl_release(inode->i_acl);
	if (inode->i_default_acl && inode->i_default_acl != ACL_NOT_CACHED)
		posix_acl_release(inode->i_default_acl);
#endif
	this_cpu_dec(nr_inodes);
}
