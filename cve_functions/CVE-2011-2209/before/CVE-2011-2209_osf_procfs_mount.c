osf_procfs_mount(char *dirname, struct procfs_args __user *args, int flags)
{
	struct procfs_args tmp;

	if (copy_from_user(&tmp, args, sizeof(tmp)))
		return -EFAULT;

	return do_mount("", dirname, "proc", flags, NULL);
}
