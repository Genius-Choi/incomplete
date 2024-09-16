proc_map_files_get_link(struct dentry *dentry,
			struct inode *inode,
		        struct delayed_call *done)
{
	if (!capable(CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	return proc_pid_get_link(dentry, inode, done);
}
