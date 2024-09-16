int generic_readlink(struct dentry *dentry, char __user *buffer, int buflen)
{
	void *cookie;
	struct inode *inode = d_inode(dentry);
	const char *link = inode->i_link;
	int res;

	if (!link) {
		link = inode->i_op->follow_link(dentry, &cookie);
		if (IS_ERR(link))
			return PTR_ERR(link);
	}
	res = readlink_copy(buffer, buflen, link);
	if (inode->i_op->put_link)
		inode->i_op->put_link(inode, cookie);
	return res;
}
