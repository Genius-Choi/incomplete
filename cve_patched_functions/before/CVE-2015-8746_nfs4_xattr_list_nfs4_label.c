static size_t nfs4_xattr_list_nfs4_label(struct dentry *dentry, char *list,
				       size_t list_len, const char *name,
				       size_t name_len, int type)
{
	size_t len = 0;

	if (nfs_server_capable(d_inode(dentry), NFS_CAP_SECURITY_LABEL)) {
		len = security_inode_listsecurity(d_inode(dentry), NULL, 0);
		if (list && len <= list_len)
			security_inode_listsecurity(d_inode(dentry), list, len);
	}
	return len;
}
