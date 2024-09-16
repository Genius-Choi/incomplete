static int bpf_link(struct dentry *old_dentry, struct inode *dir,
		    struct dentry *new_dentry)
{
	if (bpf_dname_reserved(new_dentry))
		return -EPERM;

	return simple_link(old_dentry, dir, new_dentry);
}
