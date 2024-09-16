static long do_vmsplice(struct file *f, struct iov_iter *iter, unsigned int flags)
{
	if (unlikely(flags & ~SPLICE_F_ALL))
		return -EINVAL;

	if (!iov_iter_count(iter))
		return 0;

	if (iov_iter_rw(iter) == WRITE)
		return vmsplice_to_pipe(f, iter, flags);
	else
		return vmsplice_to_user(f, iter, flags);
}
