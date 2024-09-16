static int nfs4_xattr_set_nfs4_label(struct dentry *dentry, const char *key,
				   const void *buf, size_t buflen,
				   int flags, int type)
{
	if (security_ismaclabel(key))
		return nfs4_set_security_label(dentry, buf, buflen);

	return -EOPNOTSUPP;
}
