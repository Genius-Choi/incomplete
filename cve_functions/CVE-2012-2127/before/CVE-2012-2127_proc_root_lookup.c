static struct dentry *proc_root_lookup(struct inode * dir, struct dentry * dentry, struct nameidata *nd)
{
	if (!proc_lookup(dir, dentry, nd)) {
		return NULL;
	}
	
	return proc_pid_lookup(dir, dentry, nd);
}
