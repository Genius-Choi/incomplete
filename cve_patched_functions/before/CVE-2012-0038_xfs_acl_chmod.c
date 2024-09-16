xfs_acl_chmod(struct inode *inode)
{
	struct posix_acl *acl;
	int error;

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;

	acl = xfs_get_acl(inode, ACL_TYPE_ACCESS);
	if (IS_ERR(acl) || !acl)
		return PTR_ERR(acl);

	error = posix_acl_chmod(&acl, GFP_KERNEL, inode->i_mode);
	if (error)
		return error;

	error = xfs_set_acl(inode, ACL_TYPE_ACCESS, acl);
	posix_acl_release(acl);
	return error;
}
