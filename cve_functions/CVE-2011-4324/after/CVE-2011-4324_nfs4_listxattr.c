ssize_t nfs4_listxattr(struct dentry *dentry, char *buf, size_t buflen)
{
	size_t len = strlen(XATTR_NAME_NFSV4_ACL) + 1;

	if (!nfs4_server_supports_acls(NFS_SERVER(dentry->d_inode)))
		return 0;
	if (buf && buflen < len)
		return -ERANGE;
	if (buf)
		memcpy(buf, XATTR_NAME_NFSV4_ACL, len);
	return len;
}
