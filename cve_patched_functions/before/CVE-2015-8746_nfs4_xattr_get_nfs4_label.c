static int nfs4_xattr_get_nfs4_label(struct dentry *dentry, const char *key,
				   void *buf, size_t buflen, int type)
{
	if (security_ismaclabel(key))
		return nfs4_get_security_label(d_inode(dentry), buf, buflen);
	return -EOPNOTSUPP;
}
