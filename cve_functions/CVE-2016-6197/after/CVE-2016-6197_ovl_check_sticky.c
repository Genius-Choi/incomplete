static inline int ovl_check_sticky(struct dentry *dentry)
{
	struct inode *dir = ovl_dentry_real(dentry->d_parent)->d_inode;
	struct inode *inode = ovl_dentry_real(dentry)->d_inode;

	if (check_sticky(dir, inode))
		return -EPERM;

	return 0;
}
