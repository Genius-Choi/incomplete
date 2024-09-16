static long gfs2_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd) {
	case FS_IOC_GETFLAGS:
		return gfs2_get_flags(filp, (u32 __user *)arg);
	case FS_IOC_SETFLAGS:
		return gfs2_set_flags(filp, (u32 __user *)arg);
	}
	return -ENOTTY;
}
