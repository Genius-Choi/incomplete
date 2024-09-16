filename_mountpoint(int dfd, struct filename *name, struct path *path,
			unsigned int flags)
{
	int error;
	if (IS_ERR(name))
		return PTR_ERR(name);
	error = path_mountpoint(dfd, name, path, flags | LOOKUP_RCU);
	if (unlikely(error == -ECHILD))
		error = path_mountpoint(dfd, name, path, flags);
	if (unlikely(error == -ESTALE))
		error = path_mountpoint(dfd, name, path, flags | LOOKUP_REVAL);
	if (likely(!error))
		audit_inode(name, path->dentry, 0);
	putname(name);
	return error;
}
