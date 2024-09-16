static int timerfd_fget(int fd, struct fd *p)
{
	struct fd f = fdget(fd);
	if (!f.file)
		return -EBADF;
	if (f.file->f_op != &timerfd_fops) {
		fdput(f);
		return -EINVAL;
	}
	*p = f;
	return 0;
}
