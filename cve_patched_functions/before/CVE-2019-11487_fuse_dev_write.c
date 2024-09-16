static ssize_t fuse_dev_write(struct kiocb *iocb, struct iov_iter *from)
{
	struct fuse_copy_state cs;
	struct fuse_dev *fud = fuse_get_dev(iocb->ki_filp);

	if (!fud)
		return -EPERM;

	if (!iter_is_iovec(from))
		return -EINVAL;

	fuse_copy_init(&cs, 0, from);

	return fuse_dev_do_write(fud, &cs, iov_iter_count(from));
}
