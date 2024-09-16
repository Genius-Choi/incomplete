static ssize_t fuse_dev_read(struct kiocb *iocb, struct iov_iter *to)
{
	struct fuse_copy_state cs;
	struct file *file = iocb->ki_filp;
	struct fuse_dev *fud = fuse_get_dev(file);

	if (!fud)
		return -EPERM;

	if (!iter_is_iovec(to))
		return -EINVAL;

	fuse_copy_init(&cs, 1, to);

	return fuse_dev_do_read(fud, file, &cs, iov_iter_count(to));
}
