ssize_t nfs4_getxattr(struct dentry *dentry, const char *key, void *buf,
		size_t buflen)
{
	struct inode *inode = dentry->d_inode;

	if (strcmp(key, XATTR_NAME_NFSV4_ACL) != 0)
		return -EOPNOTSUPP;

	return nfs4_proc_get_acl(inode, buf, buflen);
}
