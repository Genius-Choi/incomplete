static int perf_fasync(int fd, struct file *filp, int on)
{
	struct inode *inode = file_inode(filp);
	struct perf_event *event = filp->private_data;
	int retval;

	inode_lock(inode);
	retval = fasync_helper(fd, filp, on, &event->fasync);
	inode_unlock(inode);

	if (retval < 0)
		return retval;

	return 0;
}
