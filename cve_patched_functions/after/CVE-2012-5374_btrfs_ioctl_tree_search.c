static noinline int btrfs_ioctl_tree_search(struct file *file,
					   void __user *argp)
{
	 struct btrfs_ioctl_search_args *args;
	 struct inode *inode;
	 int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	args = memdup_user(argp, sizeof(*args));
	if (IS_ERR(args))
		return PTR_ERR(args);

	inode = fdentry(file)->d_inode;
	ret = search_ioctl(inode, args);
	if (ret == 0 && copy_to_user(argp, args, sizeof(*args)))
		ret = -EFAULT;
	kfree(args);
	return ret;
}
