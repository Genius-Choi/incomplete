xfs_xattr_acl_set(struct dentry *dentry, const char *name,
		const void *value, size_t size, int flags, int type)
{
	struct inode *inode = dentry->d_inode;
	struct posix_acl *acl = NULL;
	int error = 0;

	if (flags & XATTR_CREATE)
		return -EINVAL;
	if (type == ACL_TYPE_DEFAULT && !S_ISDIR(inode->i_mode))
		return value ? -EACCES : 0;
	if ((current_fsuid() != inode->i_uid) && !capable(CAP_FOWNER))
		return -EPERM;

	if (!value)
		goto set_acl;

	acl = posix_acl_from_xattr(value, size);
	if (!acl) {
		/*
		 * acl_set_file(3) may request that we set default ACLs with
		 * zero length -- defend (gracefully) against that here.
		 */
		goto out;
	}
	if (IS_ERR(acl)) {
		error = PTR_ERR(acl);
		goto out;
	}

	error = posix_acl_valid(acl);
	if (error)
		goto out_release;

	error = -EINVAL;
	if (acl->a_count > XFS_ACL_MAX_ENTRIES)
		goto out_release;

	if (type == ACL_TYPE_ACCESS) {
		umode_t mode = inode->i_mode;
		error = posix_acl_equiv_mode(acl, &mode);

		if (error <= 0) {
			posix_acl_release(acl);
			acl = NULL;

			if (error < 0)
				return error;
		}

		error = xfs_set_mode(inode, mode);
		if (error)
			goto out_release;
	}

 set_acl:
	error = xfs_set_acl(inode, type, acl);
 out_release:
	posix_acl_release(acl);
 out:
	return error;
}
