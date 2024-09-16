static int bpf_mkobj_ops(struct inode *dir, struct dentry *dentry,
			 umode_t mode, const struct inode_operations *iops)
{
	struct inode *inode;

	if (bpf_dname_reserved(dentry))
		return -EPERM;

	inode = bpf_get_inode(dir->i_sb, dir, mode | S_IFREG);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	inode->i_op = iops;
	inode->i_private = dentry->d_fsdata;

	d_instantiate(dentry, inode);
	dget(dentry);

	return 0;
}
