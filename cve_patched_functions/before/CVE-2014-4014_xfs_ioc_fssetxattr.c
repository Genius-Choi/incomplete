xfs_ioc_fssetxattr(
	xfs_inode_t		*ip,
	struct file		*filp,
	void			__user *arg)
{
	struct fsxattr		fa;
	unsigned int		mask;
	int error;

	if (copy_from_user(&fa, arg, sizeof(fa)))
		return -EFAULT;

	mask = FSX_XFLAGS | FSX_EXTSIZE | FSX_PROJID;
	if (filp->f_flags & (O_NDELAY|O_NONBLOCK))
		mask |= FSX_NONBLOCK;

	error = mnt_want_write_file(filp);
	if (error)
		return error;
	error = xfs_ioctl_setattr(ip, &fa, mask);
	mnt_drop_write_file(filp);
	return -error;
}
